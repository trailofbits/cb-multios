#!/usr/bin/env python

from generator.actions import Actions
import random
import string
from struct import pack


class StringSearch(Actions):


    def start(self):

        self.root=bst()
        self.string_entries=[]
        self.string_entries_count=0

    def top(self):

        pass

    def exit(self):

        self.write('x\n')

    def add_string(self):

        string_to_add = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(random.randint(10, 1028)))

        self.write('a/' + string_to_add + '\n')

        # trunc string to max size in the service
        string_to_add=string_to_add[:1023]

        key=self.root.calc_token(string_to_add)

        self.root.insert(key, string_to_add)

        # save in a list for easier access when selecting one at random
        self.string_entries.append(string_to_add)
        self.string_entries_count+=1


    def find_strings(self):

        if self.string_entries_count == 0:
            return

        #pick a random string 
        choice_number = random.randint(0, self.string_entries_count-1)
        string_choice = self.string_entries[choice_number]

        # send the command to do a find
        self.write('f/'+ string_choice + '\n')

        expect_string = '{}\n'.format(self.string_entries[choice_number])
        self.read(delim='\n', expect=expect_string) 

    def delete_strings (self):

        # if there are no strings available to delete, just return
        if self.string_entries_count == 0:
            return

        # randomly select a string to delete
        choice_number = random.randint(0, self.string_entries_count-1)
        string_choice = self.string_entries[choice_number]

        # send the delete command to the service
        self.write('d/'+ string_choice + '\n')

        # delete it from the poller's version of the BST
        key=self.root.calc_token(string_choice)
        self.root.delete(key, string_choice)


        # now remove it from the list used to randomly select a string
        self.string_entries_count-=1
        self.string_entries.remove(string_choice)


    def walk_tree(self):

        # get a list of the results from the tree walk from the internal BST
        my_results = []
        my_results = self.root.walk_tree(my_results)

        #send the command to the service
        self.write('w\n')
    
        # results should match the internal BST
        for item in my_results:
            self.read(delim='\n', expect=item)

    def get_stats(self):

        total_nodes = 0
        left_nodes = 0
        right_nodes = 0

        total_nodes, left_nodes, right_nodes = self.root.get_stats()

        if total_nodes > 1:
            left_percent = left_nodes * 100 / (left_nodes + right_nodes)
            right_percent = right_nodes * 100 / (left_nodes + right_nodes)
        else:
            left_percent = 0
            right_percent = 0

        self.write('s\n')

        expect_string = '# of Nodes: ' + '{}'.format(total_nodes)
        self.read(delim='\n', expect = expect_string)

        expect_string = '% left nodes: ' + '{}'.format(left_percent)
        self.read(delim='\n', expect=expect_string)

        expect_string = '% right nodes: ' + '{}'.format(right_percent)
        self.read(delim='\n', expect = expect_string)



class bst:

    def __init__(self, key=None, value=None):

        self.left=None
        self.right=None
        self.value = []
        self.count=0

        
        if value is not None:
            self.value.append(value)
            self.count=1
            self.key=key

    def calc_token(self, value):


        if value is None:
            return -1

        tmp_token=5381

        for char in value:

            # do all the masking to 32 bits so it will match the C implementation
            tmp_token = ((((tmp_token << 5) & 0xffffffff) + tmp_token) + (ord(char) & 0xff)) & 0xffffffff

        return tmp_token


    def insert(self, key, value):


        if self.value:
            if key < self.key:

                if self.left is None:

                    self.left=bst( key, value)
                    self.left.count=1
                else:

                    self.left.insert(key, value)
            elif key > self.key:

                if self.right is None:
                    self.right = bst(key, value)
                else:
                    self.right.insert(key, value)
            else:

                self.count+=1
                self.value.append(value)

        else:

            self.value.append(value)
            self.count+=1
            self.key=key


    def find(self, key, parent=None):

        if key <self.key:
            if self.left is None:
                return None, None
            return self.left.find(key, self)
        elif key > self.key:
            if self.right is None:
                return None, None
            return self.right.find(key, self)
        else:
            return self, parent


    def walk_tree(self, results_list):


        if self.left:
            self.left.walk_tree(results_list)

        for item in self.value:
            results_list.append(item)

        if self.right:
            self.right.walk_tree(results_list)

        return results_list


    def get_stats(self):

        left_results = 0
        right_results = 0

        if self.left:
           left_results=self.left.count_nodes(left_results)

        if self.right:
            right_results=self.right.count_nodes(right_results)


        total_results = left_results + right_results

        if self.value:
            total_results += 1

        return total_results, left_results, right_results



    def count_nodes(self, results):

        if self.left:
            results=self.left.count_nodes(results)

        if self.value:
            results+= 1

        if self.right:
            results=self.right.count_nodes(results)

        return results


    def delete(self, key, str):


        node, parent = self.find(key)

        # did not find the node with the value, just return
        if node is None:
            return

        # if there are more than one value stored in this node, just remove the one value, but the node stays
        if node.count > 1:
            node.value.remove(str)
            node.count-=1
            return

        # this must be the root node
        if parent is None:
            if node.left is None and node.right is None:
                node.value=[]
                node.count=0
                return

        # this is a leaf node, just delete it and fixup the reference to it
        if node.left is None and node.right is None:

            if parent:
                if parent.left is node:
                    parent.left = None
                else:
                    parent.right = None

                del node
            else:
                self.value = []

        # the node has two children so find its in-order predecessor and promote it up
        elif node.left is not None and node.right is not None:

            parent=node

            #first go to the left
            successor = node.left

            # then all the way to the right until there are no more nodes to the right
            while successor.right:
                parent = successor
                successor = successor.right

            # now copy this node's data to the node that is being deleted
            node.key = successor.key
            node.value = successor.value
            node.count = successor.count

            # now link around the successor's old node, and delete it
            if parent.left == successor:
                parent.left = successor.left
            else:
                parent.right = successor.left

            del successor

        # the node only has one child  Just link around the one being deleted
        else:

            if node.left:
                n = node.left
            else:
                n = node.right

            if parent:
                if parent.left is node:
                    parent.left = n
                else:
                    parent.right = n

                del node

            else:

                self.left = n.left
                self.right = n.right
                self.value = n.value
                self.key = n.key

    
