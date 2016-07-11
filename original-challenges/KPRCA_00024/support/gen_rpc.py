#!/usr/bin/env python
#
# Copyright (c) 2014 Kaprica Security, Inc.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
#
# Parses a protocol description and outputs C code for the client and server
#
import os.path
from pyparsing import (
    Combine, Forward, Group, Keyword, LineEnd, LineStart, Literal, NotAny, OneOrMore, Optional,
    StringEnd, Word, ZeroOrMore, alphas, dblQuotedString, nums, printables,
    removeQuotes, restOfLine, alphanums
)

class DuplicateException(Exception):
    pass

class Spec(object):
    def __init__(self):
        self.state = {}

    def parse_enum(self, s, l, t):
        values = []
        for x in xrange(0, len(t), 2):
            name, value = t[x:x+2]
            if name in self.state:
                raise Exception('Duplicate constant `%s\' in enum' % name)
            self.state[name] = Constant(name, value)
            values += [self.state[name]]

        return [Enum(values)]

    def parse_struct(self, s, l, t):
        if len(set(map(lambda x: x.identifier, t))) != len(t):
            raise Exception('Duplicate identifier in struct')

        return [Struct(t)]

    def parse_union(self, s, l, t):
        discriminant = t[0]
        declarations = t[1]
        result = Union(discriminant)
        for value, declaration in declarations:
            if value == "default":
                result.add_case(None, declaration)
            else:
                result.add_case(value, declaration)
        return [result]

    def parse_const(self, s, l, t):
        name, value = t
        if name in self.state:
            raise Exception('Duplicate constant `%s\' in const' % name)
        self.state[name] = Constant(name, value)
        return []

    def parse_builtin(self, s, l, t):
        unsigned = False
        if t[0] == "float":
            return Float()
        elif t[0] == "double":
            return Float(8)
        elif t[0] == "bool":
            return Bool()
        elif t[0] == "unsigned":
            unsigned = True

        if t[1] == "int":
            return Integer(unsigned=unsigned)
        elif t[1] == "hyper":
            return Integer(unsigned=unsigned, size=8)

        raise Exception("Unhandled builtin %s" % t[0])


    def parse_decl(self, s, l, t):
        type_spec = t[0]
        if type_spec == "void":
            return [Void()]

        identifier = t[1]
        if identifier == "*":
            optional = True
            size = 1
            identifier = t[2]
        elif len(t) > 3:
            optional = t[2] == '<'
            size = t[3]
        else:
            size = None
            optional = None

        return [Decl(identifier, type_spec, optional, size)]

    def parse_type_def(self, s, l, t):
        keyword = t[0]
        if keyword in ("typedef"):
            return [t[1]]
        elif keyword in ("enum", "struct", "union"):
            return [Decl(t[1], t[2])]
        elif keyword in ("program"):
            return [Program(t[1], t[3], t[2])]

    def parse_version_def(self, s, l, t):
        identifier = t[0]
        number = t[-1]
        return [Version(identifier, number, t[1:-1])]

    def parse_procedure_def(self, s, l, t):
        return_type = t[0]
        identifier = t[1]
        number = t[-1] 
        return [Procedure(identifier, number, return_type, t[2:-1])]
        
    def get_parser(self):
        declaration = Forward()
        keyword = (
            Keyword("enum") |
            Keyword("case") |
            Keyword("struct") |
            Keyword("default") |
            Keyword("switch") |
            Keyword("union") |
            Keyword("const") |
            Keyword("unsigned") |
            Keyword("int") |
            Keyword("hyper") |
            Keyword("float") |
            Keyword("double") |
            Keyword("bool") |
            Keyword("typedef") |
            Keyword("opaque") |
            Keyword("string") |
            Keyword("void") |
            Keyword("program") | 
            Keyword("version")
        )
        identifier = NotAny(keyword) + Word(alphas + alphas.upper(), alphanums + alphanums.upper() + "_", asKeyword=True)

        constant = Combine(Optional("-") + Word(nums))
        constant.setParseAction(lambda s,l,t: [int(t[0])])

        value = constant | identifier

        enum_body = Literal("{").suppress() + identifier + Literal("=").suppress() + value + ZeroOrMore(Literal(",").suppress() + identifier + Literal("=").suppress() + value) + Literal("}").suppress()
        enum_type_spec = Literal("enum").suppress() + enum_body
        enum_body.setParseAction(self.parse_enum)

        struct_body = Literal("{").suppress() + OneOrMore(declaration + Literal(";").suppress()) + Literal("}").suppress()
        struct_type_spec = Literal("struct").suppress() + struct_body
        struct_body.setParseAction(self.parse_struct)
        
        case_stmt = Literal("case").suppress() + value + Literal(":").suppress() + declaration + Literal(";").suppress()
        default_stmt = Literal("default") + Literal(":").suppress() + declaration + Literal(";").suppress()
        union_body = Literal("switch").suppress() + Literal("(").suppress() + declaration + Literal(")").suppress() + Literal("{").suppress() + Group(OneOrMore(Group(case_stmt)) + Optional(Group(default_stmt))) + Literal("}").suppress()
        union_type_spec = Literal("union").suppress() + union_body
        union_body.setParseAction(self.parse_union)
        
        constant_def = Literal("const").suppress() + identifier + Literal("=").suppress() + constant + Literal(";").suppress()
        constant_def.setParseAction(self.parse_const)
        
        type_spec = (
            (Optional(Literal("unsigned")) + Literal("int")).setParseAction(self.parse_builtin) |
            (Optional(Literal("unsigned")) + Literal("hyper")).setParseAction(self.parse_builtin) |
            Literal("float").setParseAction(self.parse_builtin) |
            Literal("double").setParseAction(self.parse_builtin) |
            Literal("bool").setParseAction(self.parse_builtin) |
            enum_type_spec |
            struct_type_spec |
            union_type_spec |
            identifier
        )
        proc_return = Literal("void") | type_spec
        procedure_def = proc_return + identifier + Literal("(").suppress() + (Literal("void") | type_spec) + ZeroOrMore(Literal(",").suppress() + type_spec) + Literal(")").suppress() + Literal("=").suppress() + constant + Literal(";").suppress()
        procedure_def.setParseAction(self.parse_procedure_def)
        version_def = Literal("version").suppress() + identifier + Literal("{").suppress() + OneOrMore(procedure_def) + Literal("}").suppress() + Literal("=").suppress() + constant + Literal(";").suppress()
        version_def.setParseAction(self.parse_version_def)
        program_body = Literal("{").suppress() + Group(OneOrMore(version_def)) + Literal("}").suppress()
        
        type_def = (
            (Literal("typedef") + declaration + Literal(";")) |
            (Literal("enum") + identifier + enum_body + Literal(";")) |
            (Literal("struct") + identifier + struct_body + Literal(";")) |
            (Literal("union") + identifier + union_body + Literal(";")) |
            (Literal("program") + identifier + program_body + Literal("=").suppress() + constant + Literal(";"))
        )
        type_def.setParseAction(self.parse_type_def)

        declaration << (
            (type_spec + identifier + Literal("[") + value + Literal("]")) |
            (type_spec + identifier + Literal("<") + value + Literal(">")) |
            (type_spec + identifier) |
            (Literal("opaque") + identifier + Literal("[") + value + Literal("]")) |
            (Literal("opaque") + identifier + Literal("<") + value + Literal(">")) |
            (Literal("string") + identifier + Literal("<") + value + Literal(">")) |
            (type_spec + Literal("*") + identifier) |
            Literal("void")
        )
        declaration.setParseAction(self.parse_decl)

        definition = type_def | constant_def
        specification = ZeroOrMore(definition)
        comment = (Literal("#") + restOfLine).suppress()
        specification.ignore(comment)

        return specification

    def parseString(self, s):
        parser = self.get_parser()
        self.declarations = parser.parseString(s, parseAll=True)

    def check(self):
        for d in self.declarations:
            d.check(self.state)

    def dump_xdr_h(self, name):
        f = open('%s_xdr.h' % name, 'w')
        f.write('/* AUTOMATICALLY GENERATED - DO NOT EDIT! */\n\n')
        f.write('#include <stdlib.h>\n')
        f.write('/* Standard definitions */\n')
        f.write('typedef unsigned char opaque;\n')
        f.write('typedef char string;\n')
        f.write('/* Begin constants */\n')
        for name, value in self.state.items():
            value.generate_def(self.state, f)
        f.write('/* End constants */\n\n')
        for d in self.declarations:
            if isinstance(d, Program): continue
            f.write('typedef ')
            d.generate_decl(self.state, f)
            f.write(';\n\n')
        for d in self.declarations:
            if isinstance(d, Program): continue
            d.type_spec.generate_def(self.state, f, d.identifier)
            f.write(';\n\n')
        for d in self.declarations:
            if isinstance(d, Program): continue
            f.write('int marshal_%s(%s *data, unsigned char **_out, size_t *_size);\n' % (d.identifier, d.identifier))
            f.write('int unmarshal_%s(%s *data, unsigned char **_in, size_t *_size);\n' % (d.identifier, d.identifier))

    def dump_xdr_c(self, name):
        f = open('%s_xdr.c' % name, 'w')
        f.write('/* AUTOMATICALLY GENERATED - DO NOT EDIT! */\n')
        f.write('#include "libxdr.h"\n')
        f.write('#include "%s_xdr.h"\n' % name)
        state = dict(self.state)
        for d in self.declarations:
            if isinstance(d, Program): continue
            state[d.identifier] = d.type_spec
        for d in self.declarations:
            if isinstance(d, Program): continue
            f.write('int marshal_%s(%s *data, unsigned char **_out, size_t *_size) {\n' % (d.identifier, d.identifier))
            f.write('int _result;\n')
            d.type_spec.generate_marshal(state, f, '(*data)')
            f.write('return 0;\n')
            f.write('}\n\n')
            f.write('int unmarshal_%s(%s *data, unsigned char **_in, size_t *_size) {\n' % (d.identifier, d.identifier))
            f.write('int _result;\n')
            d.type_spec.generate_unmarshal(state, f, '(*data)')
            f.write('return 0;\n')
            f.write('}\n\n')

    def dump_rpc_client_h(self, name):
        prog = None
        for d in self.declarations:
            if isinstance(d, Program):
                if prog is not None:
                    raise Exception('More than one program defined')
                prog = d
        if prog is None:
            raise Exception('No program is defined')
        f = open('%s_client.h' % name, 'w')
        f.write('/* AUTOMATICALLY GENERATED - DO NOT EDIT! */\n')
        f.write('#include "%s_xdr.h"\n\n' % name)
        
        # define program functions
        prog.generate_client_h(self.state, f)

    def dump_rpc_client_c(self, name):
        prog = None
        for d in self.declarations:
            if isinstance(d, Program):
                if prog is not None:
                    raise Exception('More than one program defined')
                prog = d
        if prog is None:
            raise Exception('No program is defined')
        f = open('%s_client.c' % name, 'w')
        f.write('/* AUTOMATICALLY GENERATED - DO NOT EDIT! */\n')
        f.write('#include "librpc.h"\n')
        f.write('#include "%s_client.h"\n\n' % name)
        
        f.write('static unsigned char __buf[RPC_BUF_SIZE];\n')
        f.write('static rpc_common __rpc;\n\n')
        # define program functions
        prog.generate_client_c(self.state, f)

    def dump_rpc_server_h(self, name):
        prog = None
        for d in self.declarations:
            if isinstance(d, Program):
                if prog is not None:
                    raise Exception('More than one program defined')
                prog = d
        if prog is None:
            raise Exception('No program is defined')
        f = open('%s_server.h' % name, 'w')
        f.write('/* AUTOMATICALLY GENERATED - DO NOT EDIT! */\n')
        f.write('#include "%s_xdr.h"\n\n' % name)

        # define program functions
        prog.generate_server_h(self.state, f)

    def dump_rpc_server_c(self, name):
        prog = None
        for d in self.declarations:
            if isinstance(d, Program):
                if prog is not None:
                    raise Exception('More than one program defined')
                prog = d
        if prog is None:
            raise Exception('No program is defined')
        f = open('%s_server.c' % name, 'w')
        f.write('/* AUTOMATICALLY GENERATED - DO NOT EDIT! */\n')
        f.write('#include "librpc.h"\n')
        f.write('#include "%s_server.h"\n\n' % name)

        f.write('static unsigned char __buf[RPC_BUF_SIZE];\n')
        f.write('static rpc_common __rpc;\n')
        
        # define program functions
        prog.generate_server_c(self.state, f)

class Integer(object):
    def __init__(self, unsigned=False, size=4):
        self.unsigned = unsigned
        self.size = size

    def generate_def(self, state, f, name=''):
        f.write('%s%s' % ('unsigned ' if self.unsigned else '', 'long long' if self.size == 8 else 'long'))

    def generate_marshal(self, state, f, prefix):
        name = 'hyper' if self.size == 8 else 'int'
        name = 'unsigned_'+name if self.unsigned else name
        f.write('_result = marshal_%s(&%s, _out, _size);\n' % (name, prefix))
        f.write('CHECK_RESULT();\n')

    def generate_unmarshal(self, state, f, prefix):
        name = 'hyper' if self.size == 8 else 'int'
        name = 'unsigned_'+name if self.unsigned else name
        f.write('_result = unmarshal_%s(&%s, _in, _size);\n' % (name, prefix))
        f.write('CHECK_RESULT();\n')

class Float(object):
    def __init__(self, size=4):
        self.size = size

    def __str__(self):
        if self.size == 4:
            return 'float'
        else:
            return 'double'

    def generate_def(self, state, f, name=''):
        f.write(str(self))

    def generate_marshal(self, state, f, prefix):
        name = 'double' if self.size == 8 else 'float'
        f.write('_result = marshal_%s(&%s, _out, _size);\n' % (name, prefix))
        f.write('CHECK_RESULT();\n')

    def generate_unmarshal(self, state, f, prefix):
        name = 'double' if self.size == 8 else 'float'
        f.write('_result = unmarshal_%s(&%s, _in, _size);\n' % (name, prefix))
        f.write('CHECK_RESULT();\n')

class Bool(object):
    def __init__(self):
        pass

    def generate_def(self, state, f, name=''):
        raise NotImplementedError()

    def generate_marshal(self, state, f, prefix):
        raise NotImplementedError()

    def generate_unmarshal(self, state, f, prefix):
        raise NotImplementedError()

class Constant(object):
    def __init__(self, name, value):
        self.name = name
        self.value = value

    def generate_def(self, scope, f):
        if isinstance(self.value, str):
            self.value = scope[self.value]
            if isinstance(self.value, Constant):
                self.value = self.value.value
            else:
                raise Exception('Constants can only be assigned with constants\n')
        f.write('#define %s %d\n' % (self.name, self.value))

    def generate_marshal(self, state, f, prefix):
        raise NotImplementedError()

    def generate_unmarshal(self, state, f, prefix):
        raise NotImplementedError()

class Decl(object):
    def __init__(self, identifier, type_spec, optional=None, array=None):
        self.identifier = identifier
        self.type_spec = type_spec
        self.optional = optional
        self.array = array

    def generate_decl(self, state, f):
        if self.identifier in state:
            raise DuplicateException()

        #if isinstance(self.type_spec, str):
        #    self.type_spec = state[self.type_spec]

        state = dict(state)
        state[self.identifier] = self.type_spec
        self.type_spec.generate_decl(state, f, self.identifier)
        f.write(' %s%s' % ('*' if self.array is not None else '', self.identifier))

    def generate_def(self, state, f):
        if self.identifier in state:
            raise DuplicateException()

        def print_type():
            if isinstance(self.type_spec, str):
                f.write(self.type_spec)
            else:
                self.type_spec.generate_def(state, f)

        state = dict(state)
        state[self.identifier] = self.type_spec
        if self.optional:
            f.write('struct {\n')
            f.write('unsigned long count;\n')
            print_type()
            f.write(' *data;\n')
            f.write('} %s' % self.identifier)
        elif self.array is not None:
            print_type()
            f.write(' %s[%d]' % (self.identifier, self.array))
        else:
            print_type()
            f.write(' %s' % self.identifier)

    def generate_marshal(self, state, f, prefix):
        name = '%s.%s' % (prefix, self.identifier)
        def generate_marshal(state, f, name, type_spec):
            if isinstance(self.type_spec, str):
                f.write('_result = marshal_%s(&%s, _out, _size);\n' % (self.type_spec, name))
                f.write('CHECK_RESULT();\n')
            else:
                self.type_spec.generate_marshal(state, f, name)
        if self.optional:
            f.write('_result = marshal_unsigned_int(&%s.count, _out, _size);\n' % (name))
            f.write('CHECK_RESULT();\n')
            if self.array:
                f.write('if (%s.count > %d) return -1;\n' % (name, self.array))
            f.write('{\nsize_t i;\nfor (i = 0; i < %s.count; i++) {\n' % name)
            generate_marshal(state, f, '%s.data[i]' % name, self.type_spec)
            f.write('}\n}\n')
        elif self.array is not None:
            f.write('{\nsize_t i;\nfor (i = 0; i < %s; i++) {\n' % str(self.array))
            generate_marshal(state, f, '%s[i]' % name, self.type_spec)
            f.write('}\n}\n')
        else:
            generate_marshal(state, f, name, self.type_spec)

    def generate_unmarshal(self, state, f, prefix):
        name = '%s.%s' % (prefix, self.identifier)
        def generate_unmarshal(state, f, name, type_spec):
            if isinstance(self.type_spec, str):
                f.write('_result = unmarshal_%s(&%s, _in, _size);\n' % (self.type_spec, name))
                f.write('CHECK_RESULT();\n')
            else:
                self.type_spec.generate_unmarshal(state, f, name)
        if self.optional:
            f.write('_result = unmarshal_unsigned_int(&%s.count, _in, _size);\n' % (name))
            f.write('CHECK_RESULT();\n')
            if self.array:
                f.write('if (%s.count > %d) return -1;\n' % (name, self.array))
            f.write('_result = _checked_calloc((void **)&%s.data, %s.count, sizeof(%s.data[0]));\n' % (name, name, name))
            f.write('{\nsize_t i;\nfor (i = 0; i < %s.count; i++) {\n' % name)
            generate_unmarshal(state, f, '%s.data[i]' % name, self.type_spec)
            f.write('}\n}\n')
        elif self.array is not None:
            f.write('{\nsize_t i;\nfor (i = 0; i < %s; i++) {\n' % str(self.array))
            generate_unmarshal(state, f, '%s[i]' % name, self.type_spec)
            f.write('}\n}\n')
        else:
            generate_unmarshal(state, f, name, self.type_spec)

class Enum(object):
    def __init__(self, values):
        self.values = values

    def generate_def(self, state, f, name=''):
        pass

    def generate_decl(self, state, f, name):
        f.write('long')

    def generate_marshal(self, state, f, prefix):
        # XXX check value is valid for enum
        f.write('_result = marshal_int(&%s, _out, _size);\n' % prefix)
        f.write('CHECK_RESULT();\n')

    def generate_unmarshal(self, state, f, prefix):
        # XXX check value is valid for enum
        f.write('_result = unmarshal_int(&%s, _in, _size);\n' % prefix)
        f.write('CHECK_RESULT();\n')

class Struct(object):
    def __init__(self, declarations):
        self.declarations = declarations

    def generate_def(self, state, f, name=''):
        f.write('struct %s {\n' % name)
        for d in self.declarations:
            d.generate_def(state, f)
            f.write(';\n')
        f.write('}')

    def generate_decl(self, state, f, name):
        f.write('struct %s' % name)

    def generate_marshal(self, state, f, prefix):
        for d in self.declarations:
            d.generate_marshal(state, f, prefix)

    def generate_unmarshal(self, state, f, prefix):
        for d in self.declarations:
            d.generate_unmarshal(state, f, prefix)

class Union(object):
    def __init__(self, discriminant):
        self.discriminant = discriminant
        self.cases = {}

    def add_case(self, value, declaration):
        if value in self.cases:
            raise Exception('Duplicate case statement')
        self.cases[value] = declaration

    def generate_def(self, state, f, name=''):
        f.write('struct %s {\n' % name)
        self.discriminant.generate_def(state, f)
        f.write(';\n')
        f.write('union {\n')
        for v, d in self.cases.items():
            if isinstance(d, Void): continue
            d.generate_def(state, f)
            f.write(';\n')
        f.write('} value;\n')
        f.write('}')

    def generate_decl(self, state, f, name):
        f.write('struct %s' % name)

    def generate_marshal(self, state, f, prefix):
        self.discriminant.generate_marshal(state, f, prefix)
        f.write('switch (%s.%s) {\n' % (prefix, self.discriminant.identifier))
        for v, d in self.cases.items():
            if v is None:
                f.write('default:\n')
            else:
                f.write('case %s:\n' % str(v))
            d.generate_marshal(state, f, prefix + '.value')
            f.write('break;\n')
        if None not in self.cases:
            f.write('default:\nreturn -1;\n')
        f.write('}\n')

    def generate_unmarshal(self, state, f, prefix):
        self.discriminant.generate_unmarshal(state, f, prefix)
        f.write('switch (%s.%s) {\n' % (prefix, self.discriminant.identifier))
        for v, d in self.cases.items():
            if v is None:
                f.write('default:\n')
            else:
                f.write('case %s:\n' % str(v))
            d.generate_unmarshal(state, f, prefix + '.value')
            f.write('break;\n')
        if None not in self.cases:
            f.write('default:\nreturn -1;\n')
        f.write('}\n')

class Program(object):
    def __init__(self, identifier, number, contents):
        self.identifier = identifier
        self.number = number
        self.contents = contents

    def check(self, state):
        if self.identifier in state:
            raise DuplicateException()    
        
        if isinstance(self.number, str):
            self.number = self.state[self.number]
        if isinstance(self.number, int) or isinstance(self.number, long):
            if self.number < 0:
                raise Exception("Program number cannot be negative")
        else:
            raise Exception("Bad number for program")

        state = dict(state)
        state[self.identifier] = self

        for c in self.contents:
            c.check(state)

    def generate_client_h(self, state, f):
        f.write('int %s_init(int fd);\n' % self.identifier)
        for v in self.contents:
            if not isinstance(v, Version):
                raise Exception("Program should only contain version nodes")
            v.generate_client_h(state, f)

    def generate_client_c(self, state, f):
        f.write('int %s_init(int fd) {\n' % self.identifier)
        f.write('__rpc.fd = fd;\n')
        f.write('__rpc.prog = %s;\n' % self.number)
        for v in self.contents:
            f.write('#ifdef %s\n' % v.identifier)
            f.write('__rpc.vers = %s;\n' % v.number)
            f.write('#endif\n')
        f.write('}\n\n')

        for v in self.contents:
            if not isinstance(v, Version):
                raise Exception("Program should only contain version nodes")
            v.generate_client_c(state, f)

    def generate_server_h(self, state, f):
        f.write('int %s_run(int fd);\n' % self.identifier)
        for v in self.contents:
            v.generate_server_h(state, f)

    def generate_server_c(self, state, f):
        for v in self.contents:
            v.generate_server_c(state, f)
        f.write('int %s_run(int fd) {\n' % self.identifier)
        f.write('size_t avail;\n')
        f.write('ssize_t _result;\n')
        f.write('unsigned char *buf;\n')
        f.write('__rpc.fd = fd;\n')
        f.write('while (1) {\n')
        f.write('rpc_msg msg;\n')
        f.write('if ((_result = _rpc_recv(&__rpc, __buf, sizeof(__buf))) < 0) break;\n')
        f.write('buf = __buf;\navail = _result;\n')
        f.write('result = unmarshal_rpc_msg(&msg, &buf, &avail);\n')
        f.write('if (_result < 0) continue;\n')
        f.write('if (msg.body.mtype != CALL) continue;\n')
        f.write('if (msg.body.value.cbody.rpcvers != 2) continue;\n')
        f.write('if (msg.body.value.cbody.prog != %s) continue;\n' % str(self.number))
        f.write('switch (msg.body.value.cbody.vers) {\n')
        for v in self.contents:
            f.write('case %s:\n' % str(v.number))
            f.write('__handle_%s(&msg, buf, avail);\n' % v.identifier)
            f.write('break;\n')
        f.write('}\n')
        f.write('}\n')
        f.write('return 0;\n')
        f.write('}\n')

class Version(object):
    def __init__(self, identifier, number, procedures):
        self.identifier = identifier
        self.number = number
        self.procedures = procedures

    def generate_client_h(self, state, f):
        f.write('#ifdef %s\n' % self.identifier)
        for p in self.procedures:
            p.generate_client_h(state, f)
        f.write('#endif /* defined(%s) */\n' % self.identifier)

    def generate_client_c(self, state, f):
        f.write('#ifdef %s\n' % self.identifier)
        for p in self.procedures:
            p.generate_client_c(state, f)
        f.write('#endif /* defined(%s) */\n' % self.identifier)

    def generate_server_h(self, state, f):
        for p in self.procedures:
            p.generate_server_h(state, f, self.identifier)

    def generate_server_c(self, state, f):
        for p in self.procedures:
            p.generate_server_c(state, f, self.identifier)
        f.write('static void __handle_%s(rpc_msg *msg, unsigned char *buf, size_t avail) {\n' % self.identifier)
        f.write('switch (msg->body.value.cbody.proc) {\n')
        for p in self.procedures:
            f.write('case %s:\n' % str(p.number))
            f.write('__%s_%s(msg, buf, avail);\n' % (self.identifier, p.identifier))
            f.write('break;\n')
        f.write('}\n')
        f.write('}\n')

class Procedure(object):
    def __init__(self, identifier, number, return_type, args):
        self.identifier = identifier
        self.number = number
        self.return_type = return_type
        self.args = args

    def generate_server_h(self, state, f, version):
        f.write('%s %s_%s(' % (self.return_type, version, self.identifier))
        for i in xrange(0, len(self.args)):
            if i != 0:
                f.write(', ')
            f.write(str(self.args[i]))
        f.write(');\n')

    def generate_server_c(self, state, f, version):
        f.write('static void __%s_%s(rpc_msg *msg, unsigned char *buf, size_t avail) {\n' % (version, self.identifier))
        f.write('int _result;\n')
        f.write('rpc_msg reply;\n')
        for i in xrange(0, len(self.args)):
            f.write('%s a%d;\n' % (self.args[i], i))
        f.write('%s retval;\n' % (self.return_type))
        for i in xrange(0, len(self.args)):
            f.write('_result = unmarshal_%s(&a%d, &buf, &avail);\n' % (self.args[i], i))
            # XXX verify result
        f.write('retval = %s_%s(' % (version, self.identifier))
        for i in xrange(0, len(self.args)):
            if i != 0:
                f.write(', ')
            f.write('a%d' % i)
        f.write(');\n')
        f.write('buf = __buf;\navail = sizeof(__buf);\n')
        f.write('reply.xid = msg->xid;\nreply.body.mtype = REPLY;\n')
        f.write('reply.body.value.rbody.stat = MSG_ACCEPTED;\n')
        f.write('reply.body.value.rbody.value.areply.verf.flavor = AUTH_NONE;\n')
        f.write('reply.body.value.rbody.value.areply.verf.body.count = 0;\n')
        f.write('reply.body.value.rbody.value.areply.reply_data.stat = SUCCESS;\n')
        f.write('_result = marshal_rpc_msg(&reply, &buf, &avail);\n')
        # XXX check result
        f.write('_result = marshal_%s(&retval, &buf, &avail);\n' % self.return_type)
        # XXX check result
        f.write('_result = _rpc_send(&__rpc, __buf, sizeof(__buf) - avail);\n')
        # XXX check result
        f.write('}\n')

    def generate_client_h(self, state, f):
        f.write('%s %s (' % (self.return_type, self.identifier))
        for i in xrange(0, len(self.args)):
            if i != 0:
                f.write(', ')
            f.write(str(self.args[i]))
        f.write(');\n')

    def generate_client_c(self, state, f):
        f.write('%s %s (' % (self.return_type, self.identifier))
        for i in xrange(0, len(self.args)):
            if i != 0:
                f.write(', ')
            f.write('%s a%d' % (self.args[i], i))
        f.write(') {\n')
        f.write('int _result;\n')
        f.write('size_t avail = sizeof(__buf);\n')
        f.write('unsigned char *buf = __buf;\n')
        f.write('rpc_msg msg, reply;\n')
        f.write('%s retval;\n' % str(self.return_type))
        f.write('msg.xid = __rpc.xid++;\n')
        f.write('msg.body.mtype = CALL;\n')
        f.write('msg.body.value.cbody.rpcvers = 2;\n')
        f.write('msg.body.value.cbody.prog = __rpc.prog;\n')
        f.write('msg.body.value.cbody.vers = __rpc.vers;\n')
        f.write('msg.body.value.cbody.proc = %s;\n' % str(self.number))
        f.write('msg.body.value.cbody.cred.flavor = AUTH_NONE;\n')
        f.write('msg.body.value.cbody.cred.body.count = 0;\n')
        f.write('msg.body.value.cbody.verf.flavor = AUTH_NONE;\n')
        f.write('msg.body.value.cbody.verf.body.count = 0;\n')
        f.write('_result = marshal_rpc_msg(&msg, &buf, &avail);\n')
        f.write('ASSERT_RESULT();\n')
        for i in xrange(0, len(self.args)):
            f.write('_result = marshal_%s(&a%d, &buf, &avail);\n' % (self.args[i], i))
            f.write('ASSERT_RESULT();\n')
        f.write('_result = _rpc_send(&__rpc, __buf, sizeof(__buf) - avail);\n')
        f.write('ASSERT_RESULT();\n')
        f.write('_result = _rpc_recv(&__rpc, __buf, sizeof(__buf));\n')
        f.write('ASSERT_RESULT();\n')
        f.write('buf = __buf;\navail = _result;\n')
        f.write('_result = unmarshal_rpc_msg(&reply, &buf, &avail);\n')
        f.write('ASSERT_RESULT();\n')
        f.write('if (reply.xid != msg.xid) exit(1);\n')
        f.write('_result = unmarshal_%s(&retval, &buf, &avail);\n' % str(self.return_type))
        f.write('ASSERT_RESULT();\n')
        f.write('return retval;\n')
        f.write('}\n\n')

class Void(object):
    def check():
        pass

    def generate_marshal(self, state, f, prefix):
        pass

    def generate_unmarshal(self, state, f, prefix):
        pass

if __name__ == '__main__':
    import sys
    f = open(sys.argv[1], "r")
    spec = Spec()
    spec.parseString(f.read())
    name = os.path.splitext(os.path.basename(sys.argv[1]))[0]
    spec.dump_xdr_h(name)
    spec.dump_xdr_c(name)
    spec.dump_rpc_client_h(name)
    spec.dump_rpc_client_c(name)
    spec.dump_rpc_server_h(name)
    spec.dump_rpc_server_c(name)
