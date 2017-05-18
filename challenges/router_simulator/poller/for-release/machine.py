from generator.actions import Actions
import random
import string

def random_alphanum(max_size, min_size=2):
    alphanum = string.letters + string.digits
    max_size = max_size if max_size >= min_size else min_size
    return ''.join(random.choice(alphanum) for c in range(max_size))

def ip_to_string(ip):
    return '%d.%d.%d.%d' % ((ip >> 24) & 0xff,(ip >> 16) & 0xff,(ip >> 8) & 0xff,(ip >> 0) & 0xff)

def random_ip(length):
    ip = random.randint(0, 0xFFFFFFFF)
    mask = (0xFFFFFFFF << (32 - length)) & 0xFFFFFFFF
    ip = ip & mask
    return ip_to_string(ip), ip_to_string(mask)

class Router(Actions):
    def start(self):
        self.state['routers'] = {}
        self.state['routes'] = {}

    def menu(self):
        self.read(length=2, expect='> ')

    def add(self):
        length = random.randint(0, 32)
        ip, mask = random_ip(length)
        valid_asn = len(self.state['routers']) > 0 and self.chance(0.95)
        if valid_asn:
            asn = random.choice(self.state['routers'].keys())
            self.write('add %s %s %d\n' % (ip, mask, asn))
            self.state['routes'][(ip, mask)] = asn
        else:
            asn = random.randint(-1000000, 1000000)
            while asn in self.state['routers']:
                asn = random.randint(-1000000, 1000000)
            self.write('add %s %s %d\n' % (ip, mask, asn))
            self.read(delim='\n', expect='BAD ARGUMENTS\n')

    def delete(self):
        valid_route = len(self.state['routes']) > 0 and self.chance(0.8)
        if valid_route:
            route = random.choice(self.state['routes'].keys())
            del self.state['routes'][route]
            self.write('delete %s %s\n' % (route[0], route[1]))
        else:
            length = random.randint(1, 32)
            ip, mask = random_ip(length)
            while (ip, mask) in self.state['routes']:
                length = random.randint(1, 32)
                ip, mask = random_ip(length)
            self.write('delete %s %s\n' % (ip, mask))
            self.read(delim='\n', expect='ROUTE NOT FOUND\n')

    def query(self):
        ip = random.randint(0, 0xFFFFFFFF)
        self.write('query %s\n' % ip_to_string(ip))

        for length in range(32, -1, -1):
            mask = (0xFFFFFFFF << (32 - length)) & 0xFFFFFFFF
            route = self.state['routes'].get((ip_to_string(ip & mask), ip_to_string(mask)))
            if route:
                router_name, router_ip = self.state['routers'][route]
                self.read(delim='\n', expect='Next hop for %s is %s, AS %d (%s)\n' % (
                    ip_to_string(ip),
                    router_ip,
                    route,
                    router_name))
                break
        else:
            self.read(delim='\n', expect='Next hop for %s is BLACKHOLE.\n' % ip_to_string(ip))

    def enable(self):
        self.write('enable racoiaws\n')

    def enable_error(self):
        self.write('enable %s\n' % random_alphanum(80))
        self.read(delim='\n', expect='BAD PASSWORD\n')

    def enable_menu(self):
        self.read(length=2, expect='$ ')

    def enable_quit(self):
        self.write('quit\n')

    def enable_add(self):
        asn = random.randint(1, 0xFFFF)
        name = random_alphanum(100)
        ip, mask = random_ip(32) # mask is unused
        self.write('add %d\n' % asn)
        if asn in self.state['routers']:
            self.read(delim='\n', expect='BAD ARGUMENTS\n')
        else:
            self.read(delim='\n', expect='AS %d\n' % asn)
            self.read(delim='\n', expect=' Name: \n')
            self.read(delim='\n', expect=' IP: 0.0.0.0\n')
            self.read(length=13, expect='Modify name? ')
            self.write('y\n')
            self.read(length=10,expect='New name? ')
            self.write(name + '\n')
            self.read(length=11, expect='Modify IP? ')
            self.write('y\n')
            self.read(length=8,expect='New IP? ')
            self.write(ip + '\n')
            self.state['routers'][asn] = (name, ip)

    def enable_delete(self):
        valid_asn = len(self.state['routers']) > 0 and self.chance(0.8)
        if valid_asn:
            asn = random.choice(self.state['routers'].keys())
            self.write('delete %d\n' % asn)
            del self.state['routers'][asn]

            to_delete = []
            for k, v in self.state['routes'].iteritems():
                if v == asn:
                    to_delete.append(k)
            for k in to_delete:
                del self.state['routes'][k]
        else:
            asn = random.randint(-1000000, 1000000)
            while asn in self.state['routers']:
                asn = random.randint(-1000000, 1000000)
            self.write('delete %d\n' % asn)
            self.read(delim='\n', expect='BAD ARGUMENTS\n')

    def enable_edit(self):
        valid_asn = len(self.state['routers']) > 0 and self.chance(0.8)
        if valid_asn:
            asn = random.choice(self.state['routers'].keys())
            name, ip = self.state['routers'][asn]
            self.write('edit %d\n' % asn)
            self.read(delim='\n', expect='AS %d\n' % asn)
            self.read(delim='\n', expect=' Name: %s\n' % name)
            self.read(delim='\n', expect=' IP: %s\n' % ip)
            self.read(length=13, expect='Modify name? ')
            if self.chance(0.5):
                name = random_alphanum(100)
                self.write('y\n')
                self.read(length=10,expect='New name? ')
                self.write(name + '\n')
            else:
                self.write('n\n')
            self.read(length=11, expect='Modify IP? ')
            if self.chance(0.5):
                ip, mask = random_ip(32)
                self.write('y\n')
                self.read(length=8,expect='New IP? ')
                self.write(ip + '\n')
            else:
                self.write('n\n')
            self.state['routers'][asn] = (name, ip)
        else:
            asn = random.randint(1, 1000000)
            while asn in self.state['routers']:
                asn = random.randint(1, 1000000)
            self.write('edit %d\n' % asn)
            self.read(delim='\n', expect='BAD ARGUMENTS\n')

    def enable_list(self):
        self.write('list\n')
        for asn in sorted(self.state['routers'].keys()):
            (name, ip) = self.state['routers'][asn]
            self.read(delim='\n', expect='AS %d\n' % asn)
            self.read(delim='\n', expect=' Name: %s\n' % name)
            self.read(delim='\n', expect=' IP: %s\n' % ip)

    def quit(self):
        self.write('quit\n')
        self.read('GOOD-BYE\n')
