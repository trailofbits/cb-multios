# CML

### DARPA performer group
Kaprica Security (KPRCA)

## Description

A flexible markup language parser with support for a featureful query language.

### Feature List

A customizable parser allows the user to specify the reserved characters of the markup language. The user can adapt the language to reduce the need for esape characters, etc.

Nodes have a tag, namespace, and attributes. The name and value of the attributes can contain any character, if the user inserts an escape character. The language has a special tag, *cml*, that changes the namespace of child nodes, as well as providng other metadata.

Once data has been loaded into the service, the user can retrieve tag, namespace, and attributes, as well as change attributes and query for nodes in the data. The query language supports targetting ancestors, descendants, the parent, children, and siblings, and testing the tag, namespace, attribute, and index of nodes.

## Vulnerability
### Vuln 1
In Parser::parse (parser.cc:116) there is a type confusion vulnerability with *cml* nodes. During parsing, a node with a *cml* tag and a default namespace is special and gives the parser some extra information. However, Parser::parse fails to check the namespace in addition to the tag resulting in type confusion. An attacker can exploit this vulnerability as with a type 2 POV. A patch is either verify the namespace as well as the tag, or use the *cls* member.

#### Generic class of vulnerability

Type Confusion

#### CWE classification

CWE-843: Access of Resource Using Incompatible Type ('Type Confusion')

#### Challenges

 - Reliable tracking of types statically is difficult. The nature of the service leads to state explosion that makes symbolic execution also difficult.
 - Dynamic analysis is useful if the CRS is able to generate a test case using fuzzing or other methods.
 - Proving may require inference of the heap layout.

#### Difficulty

 - **Discovery**: hard
 - **Proving**: hard
 - **Patching**: medium
