#!/usr/bin/env python

from generator.actions import Actions
import string
import random

def random_string(a, b):
    chars = string.letters + string.digits
    result = ''.join(random.choice(chars) for _ in range(random.randint(a, b))) + random.choice(string.letters)
    return result

class PipelineGenerator(Actions):
    def setup_contains(self, service_id):
        """ Setup the 'contains' function """
        self.state['services'][service_id]['config'] = random_string(2, random.randint(4, 10))
        self.write('%s\n' % self.state['services'][service_id]['config'])

    def doit_contains(self, i, service_id, data):
        lines = data.split('\n')[:-1]
        results = []
        for line in lines:
            # print "CHECKING", repr(line)
            if len(line) and line in self.state['services'][service_id]['config']:
                results.append(line + "\n")

        # print "RESULTS", repr(results)
        return ''.join(results)
#            return data
#        else:
#            return ''

    def doit_does_not_contain(self, i, service_id, data):
        lines = data.split('\n')[:-1]
        results = []
        for line in lines:
            if line not in self.state['services'][service_id]['config']:
                results.append(line + "\n")
        
        return ''.join(results)

    def doit_wc(self, i, service_id, data):
        in_word = 0
        char_count = self.state['char_count']
        line_count = self.state['line_count'] 
        word_count = self.state['word_count']
        current_line_count = 0

        result = ''

        data = list(data)
        # print "GOT DATA", repr(data)
        while len(data):
            i = data.pop(0)
            # print "GOT", repr(i)
            char_count += 1
            
            if i.isalpha():
                if in_word == 0:
                    in_word = 1
            else:
                if in_word == 1:
                    in_word = 0
                    word_count += 1

            if i == '\n':
                line_count += 1
                result += ': %d %d %d' % (char_count, word_count, line_count)

            result += i
        
        self.state['char_count'] = char_count
        self.state['line_count'] = line_count
        self.state['word_count'] = word_count 

        # print "RESULT", repr(result)
        return result

    def doit_compress(self, i, service_id, data):
        def write_char(char, count):
            out = ''
            if count > 1:
                out = "%d" % count
            elif char >= '0' and char <= '9':
                out = "1"
            return out + char

        count = 1
        current = None
        last = None
        seen = 0
        result = ''

        for i in data:
            last = current
            current = i
            if current == '\n':
                if seen > 0:
                    result += write_char(last, count)
                    count = 1  
                result += write_char('\n', 1)
                seen = 0
            else:
                if last == current:
                    count += 1
                else:
                    if seen:
                        result += write_char(last, count)
                        count = 1
                seen += 1

        return result

    def doit_decompress(self, i, service_id, data):
        # we don't process anything if decompress is the first CB
        if i == 0:
            return None

        data = list(data)
    
        out = ''
        while len(data):
            c = data.pop(0)
            if c.isdigit():
                if len(data):
                    out += data.pop(0) * int(c)
                else:
                    out += '\n' * (int(c) - 1)
            else:
                out += c

        return out

    def setup_does_not_contain(self, service_id):
        self.state['services'][service_id]['config'] = random_string(2, random.randint(4, 10))
        self.write('%s\n' % self.state['services'][service_id]['config'])

    def get_service(self, service_id):
        for service in self.state['services']:
            if service['id'] == service_id:
                return service

    def start(self):
        self.state['services'] =  (
                {'name': 'contains', 'config': None, 'setup': self.setup_contains, 'method': self.doit_contains},
                {'name': 'word-count', 'config': None, 'method': self.doit_wc},
                {'name': 'does-not-contain', 'config': None, 'setup': self.setup_does_not_contain, 'method': self.doit_does_not_contain},
                {'name': 'compress', 'config': None, 'method': self.doit_compress},
                {'name': 'decompress', 'config': None, 'method': self.doit_decompress}
                )
        
        self.state['char_count'] = 0
        self.state['line_count'] = 0
        self.state['word_count'] = 0

        i = 0
        for service in self.state['services']:
            service['id'] = i
            service['fd'] = (i * 2) + 3
            i += 1

        self.state['configured'] = []

        self.read(delim='\n', expect='Function pipelines made easy!\n')
        self.read(delim='\n', expect='available functions include:\n')
        for service in self.state['services']:
            self.read(delim='\n', expect='%d: %s\n' % (service['id'], service['name']))

    def get_service_list(self):
        service_list = []
        for service in self.state['services']:
            if service['id'] not in self.state['configured']:
                service_list.append(service['id'])

        return service_list

    def do_service_list(self):
        service_list = self.get_service_list()
        if len(service_list) > 0:
            service_list_str = ''.join(map(str, service_list))
            self.read(delim='\n', expect='Which function do you wish to include?  Available: [%s] (Enter an empty line to stop configuration)' % service_list_str)
        return service_list

    def setup(self):
        while True:
            services = self.do_service_list()
            if len(self.get_service_list()) == 0:
                break

            if self.chance(.25):
                self.write('\n')
                break

            service = random.choice(services)
            if 'method' in self.get_service(service):
                self.write('%d\n' %  service)
                self.state['configured'].append(service)
            else:
                self.write('\n')
                break

        if len(self.state['configured']) == 0:
            self.read(delim='\n', expect='no functions configured.\n')
            return -1

        for service in self.state['services']:
            if service['id'] not in self.state['configured']:
                self.read(delim='\n', expect='Setting %s to read from 65535 and write to 65535 (via %d)' % (service['name'], service['fd']))

        if len(self.state['configured']) > 0:
            service_names = []
            for service_id in self.state['configured']:
                service_names.append(self.state['services'][service_id]['name'])
            self.read(delim='\n', expect='function pipeline: %s\n' % (' '.join(service_names)))

        for service_id in self.state['configured']:
            if 'setup' not in self.state['services'][service_id]:
                continue
            self.read(delim='\n', expect="How do you want to configure '%s'?\n" % self.state['services'][service_id]['name'])
            self.state['services'][service_id]['setup'](service_id)


        ports = [0]
        
        if len(self.state['configured']) > 1:
            port = 0
            for i in self.state['configured']:
                if port > 0:
                    ports.append(self.get_service(i)['fd'])
                    ports.append(self.get_service(i)['fd'] + 1)
                port += 1
        ports.append(1)

        for service_id in self.state['configured']:
            service = self.get_service(service_id)
            self.read(delim='\n', expect='Setting %s to read from %d and write to %d (via %d)' % (service['name'], ports.pop(0), ports.pop(0), service['fd']))
   
    def do_it(self):
        data = random_string(3, random.randint(4, 10)) + "\n"
        self.write(data)
        i = 0
        for service_id in self.state['configured']:
            if 'method' in self.state['services'][service_id]:
                data = self.state['services'][service_id]['method'](i, service_id, data)
            if data == None:
                return -1
            i += 1
        if len(data) > 0:
            self.read(length=len(data), expect=data)

    def finish(self):
        self.write('\x00\n')
