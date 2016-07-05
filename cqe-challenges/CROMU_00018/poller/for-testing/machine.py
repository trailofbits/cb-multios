#!/usr/bin/env python

from generator.actions import Actions
from random import randint
import random
import math
import numpy
import struct

VGF_MAGIC = 0x78330909
VGF_VERSION = 0x0001

VGF_OBJECT_RECT = 0
VGF_OBJECT_TRIANGLE = 1
VGF_OBJECT_LINE = 2
VGF_OBJECT_CIRCLE = 3
VGF_OBJECT_END = 100

VGF_OBJECT_SETTINGS_NOFILL = 0
VGF_OBJECT_SETTINGS_FILL = 1

VGF_MAX_X = 512
VGF_MAX_Y = 512

VGF_MAX_LAYER = 6

VGF_MAX_COLOR = 200

VGF_DEFAULT_COLOR_INDEX = 0xFFFF

# Do integer division and round (truncate) like C does
def c_divide_int( v1, v2 ):
    result = v1 / v2

    if ( result < 0 ):
        result2 = abs(v1) / abs(v2)
        return (-result2)
    else:
        return result

def rand_or_equal( start, end ):
    start = abs(start)
    end = abs(end)

    if ( start == end ):
        return start
    elif ( start > end ):
        return random.randint( end, start )
    else:
        return random.randint( start, end )

def get_xy( x_pos, y_pos, width ):
    return (x_pos + (y_pos * width))

class VGFLayerRender:
    def __init__( self, width, height, layer_count ):
        self.render_layers = [ [VGF_DEFAULT_COLOR_INDEX for i in range( width * height )] for j in range( layer_count )]

        self.width = width
        self.height = height
        self.layer_count = layer_count

        self.current_layer = 0

    def set_current_layer( self, current_layer ):
        self.current_layer = current_layer

    def draw_pixel( self, x, y, color_index ):
        self.render_layers[self.current_layer][ get_xy( x, y, self.width ) ] = color_index

    def get_width( self ):
        return self.width

    def get_height( self ):
        return self.height

    def render_to_single_layer( self ):
        single_layer = [VGF_DEFAULT_COLOR_INDEX for i in range( self.width * self.height )]

        for cur_layer in self.render_layers:
            for i in range(self.width * self.height):
                if ( cur_layer[i] is not VGF_DEFAULT_COLOR_INDEX ):
                    single_layer[i] = cur_layer[i]

        return single_layer

def vline_helper( x0, y0, line_len, render_obj, color_index ):
    if ( x0 >= render_obj.get_width() ):
        return

    if ( y0 >= render_obj.get_height() ):
        return

    cur = 0
    while ( cur < line_len ):
        if ( y0 + cur >= render_obj.get_height() ):
            break

        render_obj.draw_pixel( x0, (y0+cur), color_index )
        #layer_data[ get_xy( x0, (y0+cur), width ) ] = color_index
        cur += 1

def hline_helper( x0, y0, line_len, render_obj, color_index ):
    if ( x0 >= render_obj.get_width() ):
        return

    if ( y0 >= render_obj.get_height() ):
        return

    cur = 0
    while ( cur < line_len ):
        if ( x0 + cur >= render_obj.get_width() ):
            break

        render_obj.draw_pixel( (x0+cur), y0, color_index )
        cur += 1

def line_helper( x0, y0, x1, y1, render_obj, color_index ):
    dx = abs( x1 - x0 )
    dy = abs( y1 - y0 )

    if ( dx > dy ):
        dist = dx
    else:
        dist = dy

    if ( x0 < x1 ):
        sx = 1
    else:
        sx = -1

    if ( y0 < y1 ):
        sy = 1
    else:
        sy = -1

    x_pos = x0
    y_pos = y0

    errx = 0
    erry = 0

    count = 0
    while ( count <= dist+1 ):
        render_obj.draw_pixel( x_pos, y_pos, color_index )

        errx += dx
        erry += dy

        if ( errx > dist ):
            errx -= dist
            x_pos += sx

        if ( erry > dist ):
            erry -= dist
            y_pos += sy

        count += 1

class VGFObjLine():
    x_start = 0
    y_start = 0
    x_end = 0
    y_end = 0

    def __init__(self):
        self.x_start = 0
        self.y_start = 0
        self.x_end = 0
        self.y_end = 0

    def generate_random(self, max_x, max_y, bad_data = True):

        if ( random.randint( 0, 50 ) == 0 and bad_data == True ):
            self.x_start = random.randint( 0, 65000 )
        else:
            self.x_start = rand_or_equal( 0, max_x - 1 )

        if ( random.randint( 0, 50 ) == 0 and bad_data == True ):
            self.y_start = random.randint( 0, 65000 )
        else:
            self.y_start = rand_or_equal( 0, max_y - 1 )

        if ( random.randint( 0, 50 ) == 0 and bad_data == True ):
            self.x_end = random.randint( 0, 65000 )
        else:
            self.x_end = rand_or_equal( 0, max_x - 1 )

        if ( random.randint( 0, 50 ) == 0 and bad_data == True ):
            self.y_end = random.randint( 0, 65000 )
        else:
            self.y_end = rand_or_equal( 0, max_y - 1 )

    def generate_file_data(self):
        # Output data structure
        file_data = struct.pack( 'H', self.x_start )
        file_data += struct.pack( 'H', self.y_start )
        file_data += struct.pack( 'H', self.x_end )
        file_data += struct.pack( 'H', self.y_end )

        return file_data

    def render(self, render_obj, color_index, do_fill ):
        if ( self.x_start >= render_obj.get_width() or
             self.y_start >= render_obj.get_height() or
             self.x_end >= render_obj.get_width() or
             self.y_end >= render_obj.get_height() ):
            return

        if ( self.x_start > self.x_end ):
            return

        if ( self.y_start > self.y_end ):
            return

        line_helper( self.x_start, self.y_start, self.x_end, self.y_end, render_obj, color_index )


class VGFObjRect():
    x_start = 0
    y_start = 0
    x_len = 0
    y_len = 0

    def __init__(self):
        self.x_start = 0
        self.y_start = 0
        self.x_len = 0
        self.y_len = 0

    def generate_random(self, max_x, max_y, bad_data = True):

        if ( random.randint( 0, 50 ) == 0 and bad_data == True ):
            self.x_start = random.randint( 0, 65000 )
            max_x_len = max_x
        else:
            self.x_start = random.randint( 0, max_x - 1 )
            max_x_len = (max_x - self.x_start)

        if ( random.randint( 0, 50 ) == 0 and bad_data == True ):
            self.y_start = random.randint( 0, 65000 )
            max_y_len = max_y
        else:
            self.y_start = random.randint( 0, max_y - 1 )
            max_y_len = (max_y - self.y_start)


        if ( random.randint( 0, 50 ) == 0 and bad_data == True ):
            self.x_len = random.randint( 0, 65000 )
        else:
            self.x_len = rand_or_equal( 0, max_x_len )

        if ( random.randint( 0, 50 ) == 0 and bad_data == True ):
            self.y_len = random.randint( 0, 65000 )
        else:
            self.y_len = rand_or_equal( 0, max_y_len )

    def generate_file_data(self):
        # Output data structure
        file_data = struct.pack( 'H', self.x_start )
        file_data += struct.pack( 'H', self.y_start )
        file_data += struct.pack( 'H', self.x_len )
        file_data += struct.pack( 'H', self.y_len )

        return file_data

    def render(self, render_obj, color_index, do_fill ):
        # Render rectangle
        x_pos = self.x_start
        y_pos = self.y_start
        x_start = self.x_start
        y_start = self.y_start
        x_end = self.x_start + self.x_len
        y_end = self.y_start + self.y_len

        if ( x_end >= render_obj.get_width()  or y_end >= render_obj.get_height() ):
            return

        if ( x_start >= render_obj.get_width() or y_start >= render_obj.get_height() ):
            return

        while ( x_pos < x_end ):
            render_obj.draw_pixel( x_pos, y_pos, color_index )
            x_pos += 1

        while ( y_pos < y_end ):
            render_obj.draw_pixel( x_pos, y_pos, color_index )
            y_pos += 1

        while ( x_pos > x_start ):
            render_obj.draw_pixel( x_pos, y_pos, color_index )
            x_pos -= 1

        while ( y_pos > y_start ):
            render_obj.draw_pixel( x_pos, y_pos, color_index )
            y_pos -= 1

        if ( do_fill == True ):
            x_pos = self.x_start+1

            while ( x_pos < x_end ):
                y_pos = y_start + 1

                while ( y_pos < y_end ):
                    render_obj.draw_pixel( x_pos, y_pos, color_index )

                    y_pos += 1

                x_pos += 1

class VGFObjCircle():
    x_start = 0
    y_start = 0
    radius = 0

    def __init__(self):
        self.x_start = 0
        self.y_start = 0
        self.radius = 0

    def generate_random(self, max_x, max_y, bad_data = True):

        min_x_y = max_x
        if ( max_y < min_x_y ):
            min_x_y = max_y

        self.radius = rand_or_equal( 1, min_x_y/2 )

        if ( random.randint( 0, 50 ) == 0 and bad_data == True ):
            self.x_start = random.randint( 0, 65000 )
        else:
            self.x_start = rand_or_equal( self.radius, max_x - self.radius )

        if ( random.randint( 0, 50 ) == 0 and bad_data == True ):
            self.y_start = random.randint( 0, 65000 )
        else:
            self.y_start = rand_or_equal( self.radius, max_y - self.radius )

    def generate_file_data(self):
        # Output data structure
        file_data = struct.pack( 'H', self.x_start )
        file_data += struct.pack( 'H', self.y_start )
        file_data += struct.pack( 'H', self.radius )

        return file_data

    def render(self, render_obj, color_index, do_fill ):
        # Render circle (use line helper)
        x_pos = self.x_start
        y_pos = self.y_start

        if ( x_pos >= render_obj.get_width() or
             y_pos >= render_obj.get_height() or
             (x_pos+self.radius) >= render_obj.get_width() or
             (y_pos+self.radius) >= render_obj.get_height() ):
            return

        if ( do_fill ):
            x_pos = self.x_start
            y_pos = self.y_start

            x = 0
            y = self.radius
            radius_error = 1 - self.radius
            ddF_x = 1
            ddF_y = -2 * self.radius

            vline_helper( x_pos, y_pos-y, 2*y, render_obj, color_index )

            while ( x < y ):
                if ( radius_error >= 0 ):
                    y -= 1
                    ddF_y += 2
                    radius_error += ddF_y

                x += 1
                ddF_x += 2
                radius_error += ddF_x

                vline_helper( x_pos+x, y_pos-y, 2*y, render_obj, color_index )
                vline_helper( x_pos+y, y_pos-x, 2*x, render_obj, color_index )
                vline_helper( x_pos-x, y_pos-y, 2*y, render_obj, color_index )
                vline_helper( x_pos-y, y_pos-x, 2*x, render_obj, color_index )

        else:
            x_pos = self.x_start
            y_pos = self.y_start
            x = 0
            y = self.radius
            radius = self.radius
            radius_error = 1 - self.radius
            ddF_x = 1
            ddF_y = -2 * self.radius

            render_obj.draw_pixel( x_pos, y_pos+radius, color_index )
            render_obj.draw_pixel( x_pos, y_pos-radius, color_index )
            render_obj.draw_pixel( x_pos+radius, y_pos, color_index )
            render_obj.draw_pixel( x_pos-radius, y_pos, color_index )

            while ( x < y ):
                if ( radius_error >= 0 ):
                    y -= 1
                    ddF_y += 2
                    radius_error += ddF_y

                x += 1
                ddF_x += 2
                radius_error += ddF_x

                render_obj.draw_pixel( x_pos + x, y_pos + y, color_index )
                render_obj.draw_pixel( x_pos - x, y_pos + y, color_index )
                render_obj.draw_pixel( x_pos + x, y_pos - y, color_index )
                render_obj.draw_pixel( x_pos - x, y_pos - y, color_index )

                render_obj.draw_pixel( x_pos + y, y_pos + x, color_index )
                render_obj.draw_pixel( x_pos - y, y_pos + x, color_index )
                render_obj.draw_pixel( x_pos + y, y_pos - x, color_index )
                render_obj.draw_pixel( x_pos - y, y_pos - x, color_index )

class VGFObjTriangle():
    x0 = 0
    y0 = 0
    x1 = 0
    y1 = 0
    x2 = 0
    y2 = 0

    def __init__(self):
        self.x0 = 0
        self.y0 = 0
        self.x1 = 0
        self.y1 = 0
        self.x2 = 0
        self.y2 = 0

    def generate_random(self, max_x, max_y, bad_data = True):

        if ( random.randint( 0, 50 ) == 0 and bad_data == True ):
            self.x0 = random.randint( 0, 65000 )
        else:
            self.x0 = rand_or_equal( 0, max_x - 1 )

        if ( random.randint( 0, 50 ) == 0 and bad_data == True ):
            self.y0 = random.randint( 0, 65000 )
        else:
            self.y0 = rand_or_equal( 0, max_y - 1 )

        if ( random.randint( 0, 50 ) == 0 and bad_data == True ):
            self.x1 = random.randint( 0, 65000 )
        else:
            self.x1 = rand_or_equal( 0, max_x - 1 )

        if ( random.randint( 0, 50 ) == 0 and bad_data == True ):
            self.y1 = random.randint( 0, 65000 )
        else:
            self.y1 = rand_or_equal( 0, max_y - 1 )

        if ( random.randint( 0, 50 ) == 0 and bad_data == True ):
            self.x2 = random.randint( 0, 65000 )
        else:
            self.x2 = rand_or_equal( 0, max_x - 1 )

        if ( random.randint( 0, 50 ) == 0 and bad_data == True ):
            self.y2 = random.randint( 0, 65000 )
        else:
            self.y2 = rand_or_equal( 0, max_y - 1 )

    def generate_file_data(self):
        # Output data structure
        file_data = struct.pack( 'H', self.x0 )
        file_data += struct.pack( 'H', self.y0 )
        file_data += struct.pack( 'H', self.x1 )
        file_data += struct.pack( 'H', self.y1 )
        file_data += struct.pack( 'H', self.x2 )
        file_data += struct.pack( 'H', self.y2 )

        return file_data

    def render(self, render_obj, color_index, do_fill ):
        # Render triangle
        if ( self.x0 >= render_obj.get_width() or
             self.y0 >= render_obj.get_height() or
             self.x1 >= render_obj.get_width() or
             self.y1 >= render_obj.get_height() or
             self.x2 >= render_obj.get_width() or
             self.y2 >= render_obj.get_height() ):
            return

        x_pos1 = self.x0
        y_pos1 = self.y0
        x_pos2 = self.x1
        y_pos2 = self.y1
        x_pos3 = self.x2
        y_pos3 = self.y2

        if ( do_fill ):
            # SORT coordinates in the proper order

            if ( y_pos1 > y_pos2 ):
                y_pos2,y_pos1 = y_pos1,y_pos2
                x_pos2,x_pos1 = x_pos1,x_pos2

            if ( y_pos2 > y_pos3 ):
                y_pos3,y_pos2 = y_pos2,y_pos3
                x_pos3,x_pos2 = x_pos2,x_pos3

            if ( y_pos1 > y_pos2 ):
                y_pos2,y_pos1 = y_pos1,y_pos2
                x_pos2,x_pos1 = x_pos1,x_pos2

            if ( y_pos1 == y_pos3 ):
                xh = x_pos1
                xl = x_pos1

                if ( x_pos2 < xl ):
                    xl = x_pos2
                elif ( x_pos2 > xh ):
                    xh = x_pos2

                if ( x_pos3 < xl ):
                    xl = x_pos3
                elif ( x_pos3 > xh ):
                    xh = x_pos3

                hline_helper( xl, y_pos1, (xh-xl), render_obj, color_index )

            else:
                dx31 = (x_pos3 - x_pos1)
                dy31 = (y_pos3 - y_pos1)
                dx32 = (x_pos3 - x_pos2)
                dy32 = (y_pos3 - y_pos2)
                dy21 = (y_pos2 - y_pos1)
                dx21 = (x_pos2 - x_pos1)

                sl = 0
                sh = 0

                if ( y_pos2 == y_pos3 ):
                    last_y = y_pos2
                else:
                    last_y = y_pos2 - 1

                if ( y_pos1 == y_pos2 ):
                    xl = x_pos1
                    xh = x_pos2

                    if ( xl > xh ):
                        xl,xh = xh,xl

                    hline_helper( xl, y_pos1, (xh-xl), render_obj, color_index )

                    y = y_pos2
                else:
                    y = y_pos1
                    while ( y <= last_y ):
                        xh = x_pos1 + c_divide_int(sh, dy31)
                        xl = x_pos1 + c_divide_int(sl, dy21)

                        sh += dx31
                        sl += dx21

                        if ( xl > xh ):
                            xh,xl = xl,xh

                        hline_helper( xl, y, (xh-xl), render_obj, color_index )

                        y += 1

                sh = dx31 * (y - y_pos1)
                sl = dx32 * (y - y_pos2)

                while ( y <= y_pos3 ):
                    xh = x_pos1 + c_divide_int(sh, dy31)
                    xl = x_pos2 + c_divide_int(sl, dy32)

                    sh += dx31
                    sl += dx32

                    if ( xl > xh ):
                        xh,xl = xl,xh

                    hline_helper( xl, y, (xh-xl), render_obj, color_index )

                    y += 1

        else:
            # Do not fill triangle
            line_helper( self.x0, self.y0, self.x1, self.y1, render_obj, color_index )
            line_helper( self.x1, self.y1, self.x2, self.y2, render_obj, color_index )
            line_helper( self.x2, self.y2, self.x0, self.y0, render_obj, color_index )

class VGFObject():

    def __init__( self, layer, color_index, settings ):
        self.object_layer = layer
        self.object_color_index = color_index
        self.object_settings = settings

    def generate_random(self, max_x, max_y, bad_data = False):
        self.object_type = random.randint( 0, 3 )

        if ( self.object_type == VGF_OBJECT_LINE ):
            self.object_data = VGFObjLine()
        elif ( self.object_type == VGF_OBJECT_RECT ):
            self.object_data = VGFObjRect()
        elif ( self.object_type == VGF_OBJECT_CIRCLE ):
            self.object_data = VGFObjCircle()
        elif ( self.object_type == VGF_OBJECT_TRIANGLE ):
            self.object_data = VGFObjTriangle()

        self.object_data.generate_random( max_x, max_y, bad_data )

    def generate_file_data(self):
        # Output data structure
        file_data = struct.pack( 'B', self.object_type )
        file_data += struct.pack( 'B', self.object_layer )
        file_data += struct.pack( 'B', self.object_color_index )
        file_data += struct.pack( 'B', self.object_settings )

        file_data += self.object_data.generate_file_data()

        return file_data

    def render(self, render_obj):
        render_obj.set_current_layer( self.object_layer )
        if ( self.object_settings == VGF_OBJECT_SETTINGS_FILL ):
            self.object_data.render( render_obj, self.object_color_index, True )
        else:
            self.object_data.render( render_obj, self.object_color_index, False )

class VGFColor():

    def __init__(self, red, green, blue):
        self.red = red
        self.green = green
        self.blue = blue

    def generate_file_data(self):
        file_data = struct.pack( 'B', self.red )
        file_data += struct.pack( 'B', self.green )
        file_data += struct.pack( 'B', self.blue )

        return file_data

class VGFFile():
    object_list = []
    color_list = []

    def __init__(self):
        self.object_list = []
        self.color_list = []
        self.layer_count = 0

    def set_layer_count(self, layer_count):
        self.layer_count = layer_count

    def add_object(self, new_obj):
        self.object_list.insert( len(self.object_list), new_obj )

    def add_color(self, new_color):
        self.color_list.insert( len(self.color_list), new_color )

class VGFSimulator(Actions):

    vgf_file = None

    def start(self):
        vgf_file = None
        return

    def send_vgf(self):
        # Generate VGF data
        new_file = VGFFile()

        file_data = ''

        obj_count = random.randint( 0, 15 )
        color_count = random.randint( 1, 20 )

        # Generate data -- rare chance of invalid data
        if ( random.randint( 0, 50 ) == 0 ):
            vgf_max_x = random.randint( 2, 65000 )
        else:
            vgf_max_x = random.randint( 2, VGF_MAX_X-1 )

        if ( random.randint( 0, 50 ) == 0 ):
            vgf_max_y = random.randint( 2, 65000 )
        else:
            vgf_max_y = random.randint( 2, VGF_MAX_Y-1 )

        if ( random.randint( 0, 50 ) == 0 ):
            vgf_max_layer = random.randint( 1, 255 )
        else:
            vgf_max_layer = random.randint( 1, VGF_MAX_LAYER-1 )

        new_file.width = vgf_max_x
        new_file.height = vgf_max_y

        # Send VGF header
        vgf_header_data = struct.pack( 'I', VGF_MAGIC )
        vgf_header_data += struct.pack( 'H', VGF_VERSION )
        vgf_header_data += struct.pack( 'H', vgf_max_y )
        vgf_header_data += struct.pack( 'H', vgf_max_x )
        vgf_header_data += struct.pack( 'B', vgf_max_layer )

        file_data += vgf_header_data

        # Iterate objects
        i = 0
        while i < obj_count:
            value = random.randint( 0, 3 )

            if ( vgf_max_layer == 0 or vgf_max_layer == 1 ):
                object_layer = 0
            else:
                object_layer = random.randint( 0, vgf_max_layer-1 )

            if ( color_count == 0 or color_count == 1 ):
                object_color = 0
            else:
                object_color = random.randint( 0, color_count-1 )

            object_fill = random.randint( 0, 1 )

            new_object = VGFObject( object_layer, object_color, object_fill )

            new_object.generate_random( vgf_max_x, vgf_max_y, True )

            file_data += new_object.generate_file_data()

            new_file.add_object( new_object )

            i += 1

        # Write end
        end_object_data = struct.pack( 'B', VGF_OBJECT_END )
        end_object_data += struct.pack( 'B', 0 )
        end_object_data += struct.pack( 'B', 0 )
        end_object_data += struct.pack( 'B', 0 )

        file_data += end_object_data

        # Write colors
        file_data += struct.pack( 'B', color_count )

        # Loop through colors
        i = 0
        while ( i < color_count ):
            red = random.randint( 0, 255 )
            green = random.randint( 0, 255 )
            blue = random.randint( 0, 255 )

            new_color = VGFColor( red, green, blue )

            color_data = new_color.generate_file_data()

            # Write out color data
            file_data += color_data

            # Add color
            new_file.add_color( new_color )

            # Next color
            i += 1

        new_file.set_layer_count( vgf_max_layer )
        self.vgf_file = new_file

        self.write( struct.pack( "H", len(file_data) ) )
        self.write( file_data )

    def receive_pmp(self):
        # Render data

        # Check width, height, and layer count!
        if ( self.vgf_file.width > VGF_MAX_X ):
            return

        if ( self.vgf_file.height > VGF_MAX_Y ):
            return

        if ( self.vgf_file.layer_count > VGF_MAX_LAYER ):
            return

        if ( self.vgf_file.width == 0 ):
            return

        if ( self.vgf_file.height == 0 ):
            return

        render_layers = VGFLayerRender( self.vgf_file.width, self.vgf_file.height, self.vgf_file.layer_count )

        for cur_obj in self.vgf_file.object_list:

            layer_index = cur_obj.object_layer
            color_index = cur_obj.object_color_index
            settings = cur_obj.object_settings

            if ( color_index >= len( self.vgf_file.color_list ) ):
                return

            if ( layer_index >= self.vgf_file.layer_count ):
                return

            cur_obj.render( render_layers )

        # Render all layers
        render_single_layer = render_layers.render_to_single_layer()

        # pmImageSize calculation
        col_size = (self.vgf_file.width * 3)

        if ( col_size % 4 != 0 ):
            col_size = (col_size & ~0x3) + 4

        pmImageSize = (col_size * self.vgf_file.height)

        pmFileSize = pmImageSize + 54
        if ( pmFileSize % 4 != 0 ):
            pmFileSize = (pmFileSize & ~0x3) + 4

        # Expect data
        pmp_header = struct.pack( 'H', 0x4d50 )
        pmp_header += struct.pack( 'I', pmFileSize )
        pmp_header += struct.pack( 'H', 0 )
        pmp_header += struct.pack( 'H', 0 )
        pmp_header += struct.pack( 'I', 54 )

        pmp_info = struct.pack( 'I', 40 )
        pmp_info += struct.pack( 'I', self.vgf_file.width )
        pmp_info += struct.pack( 'I', self.vgf_file.height )
        pmp_info += struct.pack( 'H', 1 )
        pmp_info += struct.pack( 'H', 24 )
        pmp_info += struct.pack( 'I', 0 )
        pmp_info += struct.pack( 'I', pmImageSize )
        pmp_info += struct.pack( 'I', 2835 )
        pmp_info += struct.pack( 'I', 2835 )
        pmp_info += struct.pack( 'I', 0 )
        pmp_info += struct.pack( 'I', 0 )

        self.read( length=len(pmp_header), expect=pmp_header )
        self.read( length=len(pmp_info), expect=pmp_info )

        # Render
        width = self.vgf_file.width
        row = self.vgf_file.height
        while ( row > 0 ):
            col = 0
            bytecount = 0

            row_data = ''
            while ( col < width ):
                if ( render_single_layer[ get_xy( col, (row-1), width ) ] == VGF_DEFAULT_COLOR_INDEX ):
                    row_data += struct.pack( 'B', 0x0 )
                    row_data += struct.pack( 'B', 0x0 )
                    row_data += struct.pack( 'B', 0x0 )
                else:
                    color_obj = self.vgf_file.color_list[ render_single_layer[ get_xy( col, (row-1), width )] ]

                    row_data += struct.pack( 'B', color_obj.blue )
                    row_data += struct.pack( 'B', color_obj.green )
                    row_data += struct.pack( 'B', color_obj.red )

                bytecount += 3
                col += 1

            while ( bytecount % 4 != 0 ):
                row_data += struct.pack('B', 0x0)
                bytecount += 1

            self.read( length=len(row_data), expect=row_data )

            row -= 1

    def exit(self):
        return

    def do_test(self):
        print "Testing"

if __name__ == "__main__":
    sim = VGFSimulator()
    sim.do_test()
