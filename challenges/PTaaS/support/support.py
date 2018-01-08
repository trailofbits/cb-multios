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
#

import ctypes

from os.path import dirname, abspath, join

class Image(ctypes.Structure):
    _pack_ = 1
    _fields_ = [('width', ctypes.c_uint),
                ('height', ctypes.c_uint),
                ('data', ctypes.c_ubyte * (3 * 40 * 40))]

class Chunk(ctypes.Structure):
    pass

class Pool(ctypes.Structure):
    _fields_ = [('size', ctypes.c_size_t),
                ('head', ctypes.POINTER(Chunk))]

class Vector(ctypes.Structure):
    _fields_ = [('x', ctypes.c_double),
                ('y', ctypes.c_double),
                ('z', ctypes.c_double)]

class Ray(ctypes.Structure):
    _fields_ = [('origin', Vector),
                ('direction', Vector)]

class Shape(ctypes.Structure):
    pass

Shape._fields_ = [('next', ctypes.POINTER(Shape)),
                  ('type', ctypes.c_int),
                  ('material', ctypes.c_int),
                  ('position', Vector),
                  ('color', Vector),
                  ('emission', Vector)]

class Sphere(ctypes.Structure):
    _fields_ = [('shape', Shape),
                ('data', ctypes.c_size_t),
                ('radius', ctypes.c_float),
                ('intersect', ctypes.c_size_t),
                ('id', ctypes.c_uint)]

class Plane(ctypes.Structure):
    _fields_ = [('shape', Shape),
                ('normal', Vector),
                ('data', ctypes.c_size_t),
                ('intersect', ctypes.c_size_t),
                ('id', ctypes.c_uint)]

class PTCtx(ctypes.Structure):
    _fields_ = [('pool', Pool),
                ('camera', Ray),
                ('fov', ctypes.c_double),
                ('head', ctypes.POINTER(Shape))]

class Support(object):
    def __init__(self, magic_page):
        path = join(dirname(dirname(abspath(__file__))), 'build', 'patched', 'so', 'NRFIN_00054.so')
        self.lib = ctypes.cdll.LoadLibrary(path)

        self.lib.strtod.restype = ctypes.c_double
        self.lib.vector_mag_sqr.restype = ctypes.c_double 
        self.lib.make_vector.restype = Vector
        self.lib.vector_norm.restype = Vector
        self.lib.make_ray.restype = Ray

        self.ctx = PTCtx()
        self.lib.pt_init(ctypes.pointer(self.ctx))

        self.img = Image()
        self.lib.image_init(ctypes.pointer(self.img), 40, 40)

        self.shapes = []

        self.magic_page = magic_page

    def destroy(self):
        self.lib.pt_destroy(ctypes.pointer(self.ctx))
        self.lib.image_destroy(ctypes.pointer(self.img))

    def setup_camera(self, ray, fov):
        self.lib.pt_setup_camera(ctypes.pointer(self.ctx), ray, fov)

    def add_sphere(self, material, position, color, emission, radius):
        if self.lib.vector_mag_sqr(emission) > 1e-6:
            emission = self.lib.vector_norm(emission)

        color = self.lib.vector_norm(color)

        # Need to do this manually so as not to call allocate
        sphere = Sphere()
        self.lib.shape_init(ctypes.pointer(sphere), ctypes.c_int(0), ctypes.c_int(material),
                position, color, emission)
        self.lib.sphere_init(ctypes.pointer(sphere), radius)

        sphere.shape.next = self.ctx.head
        self.ctx.head = ctypes.pointer(sphere.shape)

        # Keep reference to avoid gc
        self.shapes.append(sphere)

    def add_plane(self, material, position, color, emission, normal):
        if self.lib.vector_mag_sqr(emission) > 1e-6:
            emission = self.lib.vector_norm(emission)

        normal = self.lib.vector_norm(normal)
        color = self.lib.vector_norm(color)

        # Need to do this manually so as not to call allocate
        plane = Plane()
        self.lib.shape_init(ctypes.pointer(plane), ctypes.c_int(1), ctypes.c_int(material),
                position, color, emission)
        self.lib.plane_init(ctypes.pointer(plane), normal)

        plane.shape.next = self.ctx.head
        self.ctx.head = ctypes.pointer(plane.shape)

        # Keep reference to avoid gc
        self.shapes.append(plane)

    def clear_ctx(self):
        self.lib.pt_clear_ctx(ctypes.pointer(self.ctx))
        del self.shapes[:]

    def render(self):
        self.lib.pt_render(ctypes.pointer(self.ctx), ctypes.pointer(self.img))

        ret = '40 40\n'
        for i in self.img.data:
            ret += '%s ' % i
        ret += '\n'

        return ret

    def calculate_csum(self):
        ret = 0
        for i in xrange(1024):
            ret = ret ^ ord(self.magic_page[i * 4])

        for i in self.img.data:
            ret = ret ^ i

        return ret

    def strtod(self, s):
        d = ctypes.c_double()
        self.lib.strtod(s, ctypes.pointer(d))
        return d

    def make_vector(self, v):
        return self.lib.make_vector(v[0], v[1], v[2])

    def make_ray(self, o, d):
        return self.lib.make_ray(o, d)

