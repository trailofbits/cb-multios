# Copyright (C) 2014 Narf Industries <info@narfindustries.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

from generator.actions import Actions
from os.path import dirname, abspath, join
import random
import string
import sys

sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), 'support'))
from support import Support

class PTaaS(Actions):
    def start(self):
        #self.delay(100)
        self.state['model'] = Support(self.magic_page)

    def command(self):
        self.read(delim='\n', expect='Enter \'s\' for sphere, \'p\' for plane, \'c\' for camera, \'r\' for render, \'q\' for quit\n')

    def invalid(self):
        valid_commands = set('csprq')
        invalid_commands = set(string.letters) - valid_commands

        self.write(random.choice(list(invalid_commands)) + '\n')
        self.read(delim='\n', expect='No such command!\n')

    def camera(self):
        self.write('c\n')

        origin = tuple(['%s' % random.randint(-100, 100) for i in xrange(3)])
        direction = tuple(['%s' % random.randint(1, 100) for i in xrange(3)])
        fov = '%.1f' % (random.randint(1, 9) / 10.0)

        origin = self.state['model'].make_vector([self.state['model'].strtod(c) for c in origin])
        direction = self.state['model'].make_vector([self.state['model'].strtod(c) for c in direction])
        fov = self.state['model'].strtod(fov)

        self.read(delim='\n', expect='Enter camera position as "x, y, z":')
        self.write('%s, %s, %s\n' % (origin.x, origin.y, origin.z))

        self.read(delim='\n', expect='Enter camera direction as "x, y, z":')
        self.write('%s, %s, %s\n' % (direction.x, direction.y, direction.z))

        self.read(delim='\n', expect='Enter camera fov:')
        self.write('%s\n' % fov)

        self.state['model'].setup_camera(self.state['model'].make_ray(origin, direction), fov)

    def sphere(self):
        self.write('s\n')

        material = random.getrandbits(1)
        position = tuple(['%s' % random.randint(-100, 100) for i in xrange(3)])
        color = tuple(['%s' % random.randint(1, 100) for i in xrange(3)])
        radius = '%s' % random.randint(50, 100)

        if self.chance(0.2):
            emission = tuple(['%s' % random.randint(1, 100) for i in xrange(3)])
        else:
            emission = ('0', '0', '0')

        position = self.state['model'].make_vector([self.state['model'].strtod(c) for c in position])
        color = self.state['model'].make_vector([self.state['model'].strtod(c) for c in color])
        radius = self.state['model'].strtod(radius)
        emission = self.state['model'].make_vector([self.state['model'].strtod(c) for c in emission])

        self.read(delim='\n', expect='Enter \'d\' for diffuse, \'s\' for specular:')
        self.write('s\n' if material else 'd\n')

        self.read(delim='\n', expect='Enter radius:')
        self.write('%s\n' % radius.value)

        self.read(delim='\n', expect='Enter position as "x, y, z":')
        self.write('%s, %s, %s\n' % (position.x, position.y, position.z))

        self.read(delim='\n', expect='Enter color as "r, g, b":')
        self.write('%s, %s, %s\n' % (color.x, color.y, color.z))

        self.read(delim='\n', expect='Enter emission as "r, g, b":')
        self.write('%s, %s, %s\n' % (emission.x, emission.y, emission.z))

        self.state['model'].add_sphere(material, position, color, emission, radius)

    def plane(self):
        self.write('p\n')

        material = random.getrandbits(1)
        position = tuple(['%s' % random.randint(-100, 100) for i in xrange(3)])
        color = tuple(['%s' % random.randint(1, 100) for i in xrange(3)])
        normal = tuple(['%s' % random.randint(1, 100) for i in xrange(3)])

        if self.chance(0.2):
            emission = tuple(['%s' % random.randint(1, 100) for i in xrange(3)])
        else:
            emission = ('0', '0', '0')

        position = self.state['model'].make_vector([self.state['model'].strtod(c) for c in position])
        color = self.state['model'].make_vector([self.state['model'].strtod(c) for c in color])
        normal = self.state['model'].make_vector([self.state['model'].strtod(c) for c in normal])
        emission = self.state['model'].make_vector([self.state['model'].strtod(c) for c in emission])

        self.read(delim='\n', expect='Enter \'d\' for diffuse, \'s\' for specular:')
        self.write('s\n' if material else 'd\n')

        self.read(delim='\n', expect='Enter normal as "x, y, z":')
        self.write('%s, %s, %s\n' % (normal.x, normal.y, normal.z))

        self.read(delim='\n', expect='Enter position as "x, y, z":')
        self.write('%s, %s, %s\n' % (position.x, position.y, position.z))

        self.read(delim='\n', expect='Enter color as "r, g, b":')
        self.write('%s, %s, %s\n' % (color.x, color.y, color.z))

        self.read(delim='\n', expect='Enter emission as "r, g, b":')
        self.write('%s, %s, %s\n' % (emission.x, emission.y, emission.z))

        self.state['model'].add_plane(material, position, color, emission, normal)

    def render(self):
        self.write('r\n')
        render = self.state['model'].render()
        self.state['model'].clear_ctx()

        for line in render.splitlines():
            self.read(delim='\n', expect=line)

        csum_str = '%x' % self.state['model'].calculate_csum()
        csum_str = '0' * (8 - len(csum_str)) + csum_str + '\n'
        self.read(length=len(csum_str), expect=csum_str)

    def quit(self):
        self.write('q\n')
        self.state['model'].destroy()

