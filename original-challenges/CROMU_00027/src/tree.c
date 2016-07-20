/*

Author: Debbie Nuttall <debbie@cromulence.co>

Copyright (c) 2015 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#include <libcgc.h>
#include "stdlib.h"
#include "malloc.h"
#include "error.h"
#include "tree.h"

TreeNode *root;

#define NUM_INITIAL_PAGES 20
struct InitialPageInfo InitialInfo[NUM_INITIAL_PAGES] = {
  { "Hello", "Hello, World!~n" },
  { "Hello.Name", "Hello, #name#!~n"
                  "This page outputs the value of a variable called name.~n"
                  "If the variable is not passed to the page (via the INTERACT method), it has no value and prints nothing.~n" },
  { "Server", "The ACS Server responds to the following messages:~n"
              "~tACS-0.1~[COMMAND~] (indicates no commands follow)~n"
              "~tACS+0.1~[COMMAND~] (indicates another command follows)~n"},
  { "Server.Commands", "Commands all share the form:~n"
                "~tCOMMAND:page_name:length:data~n"
                "The Commands are REQUEST, QUERY, SEND, REMOVE, VISUALIZE, and INTERACT.~n"},
  { "Server.Commands.REQUEST", "The REQUEST command fetches a page.~n"
                        "~t~[REQUEST:somepage::~]~n"},
  { "Server.Commands.QUERY", "The QUERY command retrieves a listing of the pages on the server.~n"
                      "To retrieve the entire list of all pages:~n"
                      "~t~[QUERY:::~]~n"
                      "To retrieve a subset of the page tree:~n"
                      "~t~[QUERY:somepage::~]~n"},
  { "Server.Commands.SEND", "Upload a page to the server~n"
                      "~t~[SEND:newpage:length:pagedata~]~n"},
  { "Server.Commands.REMOVE", "Remove a page from the server~n"
                        "~t~[REMOVE:pagename::~]~n"},
  { "Server.Commands.VISUALIZE", "Process and display page data without uploading it to the server~n"
                          "~t~[VISUALIZE::length:pagedata~]~n"},
  { "Server.Commands.INTERACT", "Fetch a page from the server using variable substitution.~n"
                          "~t~[INTERACT:pagename:length:variabledata~]~n"
                          "~tvariabledata is in the form: ~[var:name:value~]~[var:name:value~]...~n"},
  { "AML", "ASCII Markup Language"},
  { "AML.Commands", "ASCII Markup Language uses the ~~ character as a command code~n"
                    "~t~~n converts to newline~n"
                    "~t~~t converts to tab~n"},
  { "AML.Literals", "AML uses certain characters as control codes~n"
                    "Those characters can be inserted as literals using the escape character ~~~n"
                    "~t~~~[ inserts left bracket~n"
                    "~t~~~] inserts right bracket~n"
                    "~t~~~~ inserts tilde~n"
                    "~t~~~# inserts hash~n"},
  { "AML.Variables", "AML supports string variables.~n"
                      "Variables are created within a script (see AML.Scripts)~n"
                      "and referenced with this syntax:~n"
                      "~t~#variable~#~n"},  
  { "AML.Scripts",  "AML supports additional commands within script tags ~[~]~n"
                    "~t~[var:name:value~] - sets a variable~n"
                    "~t~[line:character:length~] - insert a line of characters~n"
                    "~t~[box:pagedata~] - put the page data inside a box outlined with *'s~n" },
  { "AML.Examples", "AML examples~n"},
  { "AML.Examples.Line", "Draw some lines~n[line:X:80]~n"
                        "[line:A:42]~n"
                        "[line:B:1][line:C:2][line:*:100]~n"
                        "[line:~:5][line:*:1][line:[:5]~n" },
  { "AML.Examples.Variableset", "Set a variable [var:name:Sterling]~n"
                                "Then get the variable: #name#~n" },
  { "AML.Examples.ManyVariables", "[var:var0:value0][var:var1:value1][var:var2:value2][var:var3:value3][var:var4:value4][var:var5:value5][var:var6:value6][var:var7:value7][var:var8:value8][var:var9:value9]~n"
                                  "#var0##var1##var2##var3##var4##var5##var6##var7##var8##var9#~n" },
  { "AML.Examples.Box", "Test putting some stuff in a box~n"
                        "[box:Help, I'm trapped in a box!]~n"
                        "[box:~nLine in a box[line:X:15]~n]"}
};

// Initializes the server by loading pages into memory
int InitializeTree() {
  TreeNode *ptr;
  for (int i = 0; i < NUM_INITIAL_PAGES; ++i) {
    TreeNode *node = calloc(sizeof(TreeNode), 1);
    VerifyPointerOrTerminate(node, "TreeNode during initialization");
    strncpy(node->name, InitialInfo[i].name, sizeof(node->name));
    node->page_size = strlen(InitialInfo[i].data) + 1;
    node->page = calloc(node->page_size, 1);
    VerifyPointerOrTerminate(node->page, "node->page during initialization");
    memcpy(node->page, InitialInfo[i].data, node->page_size);
    if (InsertNodeInTree(node) != 0) {
      free(node->page);
      free(node);
      return -1;
    } 
  }
  return 0;
}

void WalkTree(TreeNode *nodein) {
#ifdef PATCHED
  TreeNode *node_stack[128];
#else
  TreeNode *node_stack[64];
#endif
  int indent = 0;
  int index = 0;
  int what = 0xfe;
  TreeNode *node = nodein;

  printf("@s\n", node);

  if (node->child) {
    node_stack[index++] = node->child;
    node_stack[index++] = (TreeNode *)(indent + 1);
  }

  while (index > 0) {
    // Pop node
    indent = (int)node_stack[--index];
    node = node_stack[--index];
    
    for (int i=0; i<indent; i++) {
      printf("    ");
    }
    printf("@s\n", node);

    if (node->peer) {
      node_stack[index++] = node->peer;
      node_stack[index++] = (TreeNode *)indent;
    }
    
    if (node->child) {
      node_stack[index++] = node->child;
      node_stack[index++] = (TreeNode *)(indent + 1);
    }
  }
}

int PrintTree(char *name) {
  TreeNode *start;
  if (name == NULL || name[0]=='\0') {
    start = root;
  } else {
    start = LookupNode(name);
  }
  if (start == NULL) {
    printf("ERROR: Tree not found: @s\n", name);
    return -1;
  }
  WalkTree(start);

  return 0;
}

void FreeTree(TreeNode *node) {
  if (node->child != NULL) {
    FreeTree(node->child);
  }
  if (node->peer != NULL) {
    FreeTree(node->peer);
  }
  if (node->page != NULL) {
    free(node->page);
  }
  free(node);
}

int DeleteNode(char *name) {
  TreeNode *node, *parent;
  // Lookup node
  node = LookupNode(name);
  if (node == NULL) {
    printf("ERROR: Could not locate node for deletion\n");
    return -1;
  }
  // Lookup parent node
  char local_name[64];
  memcpy(local_name, name, sizeof(local_name));
  char *last_part = strrchr(local_name, '.');
  if (last_part == NULL) {
    parent = root;
  } else {
    last_part[0] = '\0';
    parent = LookupNode(local_name);
  }
  if (node == NULL || parent == NULL) {
    return -1;
  }
  // Take node out of tree
  if (parent->child == NULL) {
    return -1;
  } else if (parent->child == node) {
    parent->child = node->peer;
    node->peer = NULL;
  } else {
    TreeNode *prev = parent->child;
    while (prev->peer != node && prev != NULL) {
      prev = prev->peer;
    }
    if (prev == NULL) {
      printf("ERROR: Could not locate node for deletion\n");
      return -1;
    }
    prev->peer = node->peer;
    node->peer = NULL;
  }
  FreeTree(node);
  return 0;
}

// Finds a node in the tree by name. 
// Returns pointer to the node or NULL
TreeNode *LookupNode(char *name) {  
  TreeNode *node = root->child;
  // Make a local copy of the name and walk its subparts
  char local_name[64];
  memcpy(local_name, name, sizeof(local_name));
  char *part = local_name;
  char *next_part = strchr(local_name, '.');
  if (next_part != NULL) {
    next_part[0] = '\0';
  }
  while (node != NULL) {
    if (strcmp(node->name, part) == 0)
    {
      if (next_part == NULL) {
        return node;
      } else {
        part = next_part + 1;
        next_part = strchr(part, '.');
        if (next_part != NULL) {
          next_part[0] = '\0';
        }
        node = node->child;
      }
    } else {
      node = node->peer;
    }
  }
  return node;
}

int InsertNodeInTree(TreeNode *node) {
  if (root == NULL) {
    TreeNode *node = calloc(sizeof(TreeNode), 1);
    VerifyPointerOrTerminate(node, "root TreeNode during insert");
    node->name[0] = '.';
    root = node;
  }
  // Make sure node doesn't exist
  if (LookupNode(node->name) != NULL) {
    printf("ERROR: node already exists\n");
    return -1;
  }
  // Make sure name isn't blank
  if (node->name[0] == '\0') {
    printf("ERROR: Name cannot be blank\n");
    return -1;
  }
   // Lookup parent node
  char local_name[64];
  memcpy(local_name, node->name, sizeof(local_name));
  char *last_part = strrchr(local_name, '.');
  TreeNode *insert_location = root;
  // If no subparts in name, insert as child to root
  if (last_part == NULL) {
    if (insert_location->child == NULL) {
      insert_location->child = node;
    } else {
      insert_location = insert_location->child;
      while (insert_location->peer != NULL) {
        insert_location = insert_location->peer;
      }
      insert_location->peer = node;
    }
    return 0;
  } 
  // Strip leading portion of name
  strncpy(node->name, last_part + 1, sizeof(node->name));  
  last_part[0] = '\0';
  insert_location = LookupNode(local_name);
  if (insert_location == NULL) {
    printf("ERROR: Parent node doesn't exist: @s\n", local_name);
    return -1;
  }
  if (insert_location->child == NULL) {
    insert_location->child = node;
    return 0;
  } else {
    insert_location = insert_location->child;
    while (insert_location->peer != NULL) {
      insert_location = insert_location->peer;
    }
    insert_location->peer = node;
    return 0;
  }
}