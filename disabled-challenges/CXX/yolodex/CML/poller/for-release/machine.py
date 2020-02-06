#!/usr/bin/env python
from generator.actions import Actions
import random
import struct

class Node(object):
    def __init__(self, tag, parent):
        self.tag = tag
        self.ns = None
        self.attr = {}
        self.children = []
        self.cml = False
        self.parent = parent

    def to_string(self, parser):
        children = ''.join([x.to_string(parser) for x in self.children])
        return parser.open_tag(self) + children + parser.close_tag(self)

class Parser(object):
    def __init__(self, chars, version_string):
        self.left = chars[0]
        self.right = chars[1]
        self.sep = chars[2]
        self.assign = chars[3]
        self.close = chars[4]
        self.escape_char = chars[5]
        self.reserved = set(chars)
        self.tag_chars = list(set([chr(x) for x in xrange(1,255)]) - self.reserved)
        self.version_string = version_string

    def escape(self, s):
        return ''.join([self.escape_char + x if x in self.reserved else x for x in s])

    def random_string(self, length):
        return ''.join([chr(random.randint(1,255)) for x in xrange(length)])

    def random_tag(self, length):
        return ''.join([random.choice(self.tag_chars) for x in xrange(length)])

    def open_tag(self, node):
        attr = ''.join([self.sep + self.escape(a[0]) + self.assign + self.escape(a[1]) for a in node.attr.items()])
        return self.left + node.tag + attr + self.right

    def close_tag(self, node):
        return self.left + self.close + node.tag + self.right

    def generate_node(self, ns=None, parent=None):
        if random.randint(0, 30) == 0 and not ('c' in self.reserved or 'm' in self.reserved or 'l' in self.reserved) and ns is None:
            # random cml node
            node = Node('cml', parent)
            node.cml = True
            node.attr['namespace'] = self.random_string(random.randint(1, 10))
            node.attr['version'] = self.version_string
        else:
            node = Node(self.random_tag(random.randint(3, 7)), parent)
        node.ns = ns
        if random.randint(0, 2) == 0:
            # add some attributes
            for x in xrange(random.randint(1, 5)):
                name = self.random_string(random.randint(3, 8))
                value = self.random_string(random.randint(3, 8))
                node.attr[name] = value
        if random.randint(0, 3) == 0:
            # add some children
            for x in xrange(random.randint(1, 4)):
                child = self.generate_node(node.attr['namespace'] if node.cml else node.ns, node)
                node.children.append(child)
        return node

    def _ancestors(self, node, remaining):
        ancestors = []
        p = node.parent
        while p is not None:
            ancestors.append(p)
            p = p.parent
        p = random.choice(ancestors)
        return self.generate_query(p, remaining)

    def _descendants(self, node, remaining):
        def recurse(n, nodes):
            nodes.extend(n.children)
            for x in n.children:
                recurse(x, nodes)
        children = []
        recurse(node, children)
        p = random.choice(children)
        return self.generate_query(p, remaining)

    def _parent(self, node, remaining):
        return self.generate_query(node.parent, remaining)

    def _children(self, node, remaining):
        x = random.choice(range(len(node.children)))
        return chr(0x84) + struct.pack('>H', x) + self.generate_query(node.children[x], remaining - 1)

    def _siblings(self, node, remaining):
        node = node.parent
        x = random.choice(range(len(node.children)))
        return chr(0x84) + struct.pack('>H', x) + self.generate_query(node.children[x], remaining - 1)

    def _tag(self, node, remaining):
        return node.tag + chr(0) + self.generate_query(node, remaining)

    def _namespace(self, node, remaining):
        return node.ns + chr(0) + self.generate_query(node, remaining)

    def _attribute(self, node, remaining):
        name, value = random.choice(node.attr.items())
        return name + chr(0) + value + chr(0) + self.generate_query(node, remaining)

    def generate_query(self, node, remaining):
        if remaining <= 0:
            return ''
        instructions = [
            #(lambda n: node.parent is not None, self._ancestors, 0x01),
            (lambda n: len(node.children) > 0, self._descendants, 0x02),
            #(lambda n: node.parent is not None, self._parent, 0x03),
            #(lambda n: len(node.children) > 0, self._children, 0x04),
            #(lambda n: node.parent is not None, self._siblings, 0x05),
            (lambda n: True, self._tag, 0x81),
            (lambda n: node.ns is not None, self._namespace, 0x82),
            (lambda n: len(node.attr) > 0, self._attribute, 0x83)
        ]
        possible = list(filter(lambda x: x[0](node), instructions))
        insn = random.choice(possible)
        return chr(insn[2]) + insn[1](node, remaining-1)

    def apply_query(self, node, instructions, idx=0):
        if node is None or len(instructions) == 0:
            return node
        insn = ord(instructions[0])
        instructions = instructions[1:]
        if insn == 0x01:
            result = self.apply_query(node.parent, instructions)
            if result is None:
                result = self.apply_query(node.parent, chr(insn) + instructions)
            return result
        elif insn == 0x02:
            for c in node.children:
                result = self.apply_query(c, instructions)
                if result is not None:
                    return result
            for c in node.children:
                result = self.apply_query(c, chr(insn) + instructions)
                if result is not None:
                    return result
        elif insn == 0x03:
            return self.apply_query(node.parent, instructions)
        elif insn == 0x04:
            for i in range(len(node.children)):
                result = self.apply_query(node.children[i], instructions, i)
                if result is not None:
                    return result
            return None
        elif insn == 0x05:
            node = node.parent
            if node is None:
                return None
            for i in range(len(node.children)):
                result = self.apply_query(node.children[i], instructions, i)
                if result is not None:
                    return result
            return None
        elif insn == 0x81:
            size = instructions.index(chr(0))
            tag = instructions[:size]
            instructions = instructions[size+1:]
            if node.tag != tag:
                return None
            return self.apply_query(node, instructions, idx)
        elif insn == 0x82:
            size = instructions.index(chr(0))
            ns = instructions[:size]
            instructions = instructions[size+1:]
            if node.ns != ns:
                return None
            return self.apply_query(node, instructions, idx)
        elif insn == 0x83:
            size = instructions.index(chr(0))
            name = instructions[:size]
            instructions = instructions[size+1:]
            size = instructions.index(chr(0))
            value = instructions[:size]
            instructions = instructions[size+1:]
            if name not in node.attr or node.attr[name] != value:
                return None
            return self.apply_query(node, instructions, idx)
        elif insn == 0x84:
            idx2 = struct.unpack('>H', instructions[0:2])[0]
            if idx != idx2:
                return None
            return self.apply_query(node, instructions[2:], idx)
        else:
            raise Exception('unexpected insn: %02X' % ord(insn))

class TemplateGenerator(Actions):
    INIT = chr(0)
    LOAD_DATA = chr(1)
    GET_ATTR = chr(2)
    SET_ATTR = chr(3)
    LIST_ATTR = chr(4)
    GET_TAG = chr(5)
    GET_NS = chr(6)
    QUERY = chr(7)
    VERSION_CHECK = chr(8)
    SUCCESS = chr(0)
    INVALID_OP = chr(1)
    INVALID_DESC = chr(2)
    NOT_READY = chr(3)
    INVALID_DATA = chr(4)
    NOT_FOUND = chr(5)

    def start(self):
        #self.delay(100)
        self.state['next_id'] = 0
        self.state['nodes'] = {}
        self.state['parser'] = None

        self.init_parser()
        self.load_data()

    def wrap_string(self, s):
        return struct.pack('>H', len(s)) + s

    def next_descriptor(self, node):
        self.state['next_id'] += 1
        desc = struct.pack('<I', self.state['next_id'])
        self.state['nodes'][desc] = node
        return desc

    def menu(self):
        pass

    def init_parser(self):
        chars = [chr(x) for x in random.sample(range(1, 255), 6)]
        self.state['parser'] = Parser(chars, '%u.%u' % struct.unpack('<II', self.magic_page[5:9] + self.magic_page[1:5]))

        self.write(self.INIT + ''.join(chars))
        self.read(length=1, expect=self.SUCCESS)

    def load_data(self):
        node = self.state['parser'].generate_node()
        s = node.to_string(self.state['parser'])

        self.write(self.LOAD_DATA + self.wrap_string(s))
        self.read(length=1, expect=self.SUCCESS)
        self.read(length=4, expect=self.next_descriptor(node))

    def get_attr(self):
        if len(self.state['nodes']) == 0:
            return
        desc, node = random.choice(self.state['nodes'].items())
        if len(node.attr) == 0:
            self.write(self.GET_ATTR + desc + self.wrap_string(self.state['parser'].random_string(8)))
            self.read(length=1, expect=self.NOT_FOUND)
        else:
            name, value = random.choice(node.attr.items())
            self.write(self.GET_ATTR + desc + self.wrap_string(name))
            self.read(length=1, expect=self.SUCCESS)
            s = self.wrap_string(value)
            self.read(length=len(s), expect=s)

    def set_attr(self):
        if len(self.state['nodes']) == 0:
            return
        desc, node = random.choice(self.state['nodes'].items())
        name = self.state['parser'].random_string(random.randint(3, 8))
        value = self.state['parser'].random_string(random.randint(3, 8))
        node.attr[name] = value
        self.write(self.SET_ATTR + desc + self.wrap_string(name) + self.wrap_string(value))
        self.read(length=1, expect=self.SUCCESS)

    def list_attr(self):
        if len(self.state['nodes']) == 0:
            return
        desc, node = random.choice(self.state['nodes'].items())
        self.write(self.LIST_ATTR + desc)
        self.read(length=1, expect=self.SUCCESS)
        self.read(length=2, expect=struct.pack('>H', len(node.attr)))
        if len(node.attr) > 0:
            self.read(length=2*len(node.attr)+len(''.join(node.attr.keys())))

    def get_tag(self):
        if len(self.state['nodes']) == 0:
            return
        desc, node = random.choice(self.state['nodes'].items())
        self.write(self.GET_TAG + desc)
        self.read(length=1, expect=self.SUCCESS)
        s = self.wrap_string(node.tag)
        self.read(length=len(s), expect=s)

    def get_ns(self):
        if len(self.state['nodes']) == 0:
            return
        desc, node = random.choice(self.state['nodes'].items())
        self.write(self.GET_NS + desc)
        if node.ns is None:
            self.read(length=1, expect=self.NOT_FOUND)
        else:
            self.read(length=1, expect=self.SUCCESS)
            s = self.wrap_string(node.ns)
            self.read(length=len(s), expect=s)

    def query(self):
        if len(self.state['nodes']) == 0:
            return
        desc, node = random.choice(self.state['nodes'].items())
        qs = self.state['parser'].generate_query(node, random.randint(10, 20))
        result = self.state['parser'].apply_query(node, qs)
        assert result is not None

        self.write(self.QUERY + desc + self.wrap_string(qs))
        self.read(length=1, expect=self.SUCCESS)
        self.read(length=4, expect=self.next_descriptor(result))

    def quit(self):
        pass

    def version_check(self):
        def find_cml(node):
            if node.cml: return node
            for c in node.children:
                result = find_cml(c)
                if result: return result
            return None
        for desc in self.state['nodes'].keys():
            node = find_cml(self.state['nodes'][desc])
            if node:
                break
        if node is None:
            return
        if not self.state['nodes'][desc].cml:
            qs = chr(0x02) + chr(0x81) + 'cml\0'
            result = self.state['parser'].apply_query(self.state['nodes'][desc], qs)
            self.write(self.QUERY + desc + self.wrap_string(qs))
            self.read(length=1, expect=self.SUCCESS)
            desc = self.next_descriptor(result)
            self.read(length=4, expect=desc)
        self.write(self.VERSION_CHECK + desc)
        self.read(length=1, expect=self.SUCCESS)
