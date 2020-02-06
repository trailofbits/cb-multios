from generator.actions import Actions
import random
import string
import struct
import numpy as np
import math

TOL = .00099
NTOL = -.00099

class Matrix(Actions):
    def _select_matrix(self):
        self._read("Select Matrix 1 or Matrix 2\n")
        self._read(">> ")
        self.state['cur_mtx'] = int(random.choice("12"))
        self.write("%d\n" % (self.state['cur_mtx']) )


    def _select_row_col_size(self):
        if random.randint(0,2):
            row_size = 9
            col_size = 9
        else:
            row_size = random.randint(1,15)
            col_size = random.randint(1,15)

        self._read("New Row Size (0 to stay the same): ")
        self.write("%d\n" % (row_size) )
        self._read("New Column Size (0 to stay the same): ")
        self.write("%d\n" % (col_size) )
        return (row_size, col_size)

    def _fill_cur_matrix(self, row, col):
        mtx = ""
        for x in xrange(row * col):
            mtx += "%d " % (random.randint(-1000, 1000))
        self.state['matrix'][self.state['cur_mtx']] = np.matrix(mtx)
        self.state['matrix'][self.state['cur_mtx']] = self.state['matrix'][self.state['cur_mtx']].reshape(row, col)
        mtx = mtx[:-1]
        return mtx

    def _read(self, data):
        self.read(length=len(data), expect=data)

    def _read_matrix(self, m, is_float=False):
        mtx = m.tolist()
        if not is_float:
            for row in mtx:
                self._read("|")
                for cell in row:
                    self._read(" %d |" % (cell))
                self._read("\n")
        else:
            for row in mtx:
                self._read("|")
                for cell in row:
                    f_pos = cell if cell >= 0 else cell * -1
                    i = int(f_pos)
                    if int((f_pos - i) * 10000) == 9999:
                        i += 1;

                    if abs(cell) < 0.01:
                        self.comment(str(cell))
                        self.read(delim='.', expect='.*', expect_format='pcre')
                    elif(cell >= NTOL):
                        self._read(" %d" % i)
                    else:
                        self._read(" -%d" % i)
                    self.read(delim='|', expect='.*', expect_format='pcre')
                self._read("\n")

    def _swap_nonzero_cell(self, mtx, i, j):
        init_row = i
        num_rows, num_cols = mtx.shape
        while i < num_rows:
            if mtx[i,j] > TOL or mtx[i,j] < NTOL:
                t1 = np.matrix.copy(mtx[init_row])
                t2 = np.matrix.copy(mtx[i])
                mtx[init_row] = t2
                mtx[i] = t1
                return
            i += 1

    def _subtract_row(self, mtx, row_idx1, row_idx2, col_offset, scalar):
        j = col_offset
        num_rows, num_cols = mtx.shape
        while j < num_cols:
            temp1 = mtx[row_idx1, j] * scalar
            temp2 = mtx[row_idx2, j]
            mtx[row_idx2, j] = temp2 - temp1
            j += 1

    def start(self):
        #self.delay(100)
        self.state['matrix'] = []
        self.state['matrix'].append(np.matrix(0))
        self.state['matrix'].append(np.matrix(0))
        self.state['matrix'].append(np.matrix(0))
        self.state['cur_mtx'] = 1
        self.state['matrix_type'] = "INT"
        self.state['matrix'][0].astype(int)
        self.state['randdata'] = []
        self.state['randidx'] = 0
        for x in xrange(1024):
            self.state['randdata'].append(struct.unpack('<b', self.magic_page[x*3:x*3+1])[0])


        self._read("Matrix math is fun!\n")
        self.read("-------------------\n")

    def main_menu(self):
        self._read("Make a selection: \n")
        self._read("1. Input Matrix\n")
        self._read("2. Print Matrix\n")
        self._read("3. Add Matrices\n")
        self._read("4. Subtract Matrices\n")
        self._read("5. Multiply Matrices\n")
        self._read("6. Swap Matrix Row\n")
        self._read("7. Swap Matrix Col\n")
        self._read("8. Transpose Matrix\n")
        self._read("9. Perform Reduced Row Echelon Form on Matrix\n")
        self._read("10. Randomize Matrix\n")
        self._read("11. Exit\n")
        self._read(">> ")

    def input_matrix(self):
        self.write("1\n")
        self._read("Inputting Matrix Values:\n")
        self._select_matrix()
        row, col = self._select_row_col_size()
        mtx = self._fill_cur_matrix(row, col)
        self.write(mtx + "\n")

    def print_matrix(self):
        self.write("2\n")
        self._read("Print Matrices:\n")
        self._read("-Matrix 1-\n")
        self._read_matrix(self.state['matrix'][1])
        self._read("\n")
        self._read("-Matrix 2-\n")
        self._read_matrix(self.state['matrix'][2])
        self._read("\n")
        self._read("-Resultant Matrix-\n")
        self._read_matrix(self.state['matrix'][0], self.state['matrix_type'] == "FLOAT")

    def add_matrices(self):
        self.write("3\n")
        self._read("Adding Matrices:\n")
        if self.state['matrix'][1].shape != self.state['matrix'][2].shape:
            self._read("Could not add matrices together. Check sizes\n")
        else:
            self.state['matrix_type'] = "INT"
            self.state['matrix'][0].astype(int)
            self.state['matrix'][0] = self.state['matrix'][1] + self.state['matrix'][2]
            self._read("Result:\n")
            self._read_matrix(self.state['matrix'][0], self.state['matrix_type'] == "FLOAT")

    def subtract_matrices(self):
        self.write("4\n")
        self._read("Subtracting Matrices:\n")
        if self.state['matrix'][1].shape != self.state['matrix'][2].shape:
            self._read("Could not subtract matrices. Check sizes\n")
        else:
            self.state['matrix_type'] = "INT"
            self.state['matrix'][0].astype(int)
            self.state['matrix'][0] = self.state['matrix'][1] - self.state['matrix'][2]
            self._read("Result:\n")
            self._read_matrix(self.state['matrix'][0], self.state['matrix_type'] == "FLOAT")

    def multiply_matrices(self):
        self.write("5\n")
        self._read("Multiplying Matrices:\n")
        if self.state['matrix'][1].shape[1] != self.state['matrix'][2].shape[0]:
            self._read("Could not multiply matrices together. Check sizes\n")
        else:
            self.state['matrix_type'] = "INT"
            self.state['matrix'][0].astype(int)
            self.state['matrix'][0] = self.state['matrix'][1] * self.state['matrix'][2]
            self._read("Result:\n")
            self._read_matrix(self.state['matrix'][0], self.state['matrix_type'] == "FLOAT")

    def swap_rows(self):
        self.write("6\n")
        self._read("Swap Rows in a  Matrix:\n")
        self._select_matrix()
        idx1 = random.randint(0, self.state['matrix'][self.state['cur_mtx']].shape[0] - 1)
        idx2 = random.randint(0, self.state['matrix'][self.state['cur_mtx']].shape[0] - 1)
        self._read("Enter Row Index 1: ")
        self.write("%d\n" % (idx1))
        self._read("Enter Row Index 2: ")
        self.write("%d\n" % (idx2))

        self._read("Original Matrix\n")
        self._read_matrix(self.state['matrix'][self.state['cur_mtx']])

        t1 = np.matrix.copy(self.state['matrix'][self.state['cur_mtx']][idx1])
        t2 = np.matrix.copy(self.state['matrix'][self.state['cur_mtx']][idx2])
        self.state['matrix'][self.state['cur_mtx']][idx1] = t2
        self.state['matrix'][self.state['cur_mtx']][idx2] = t1

        self._read("Swapped Rows\n")
        self._read_matrix(self.state['matrix'][self.state['cur_mtx']])

    def swap_cols(self):
        self.write("7\n")
        self._read("Swap Columns in a  Matrix:\n")
        self._select_matrix()
        idx1 = random.randint(0, self.state['matrix'][self.state['cur_mtx']].shape[1] - 1)
        idx2 = random.randint(0, self.state['matrix'][self.state['cur_mtx']].shape[1] - 1)
        self._read("Enter Column Index 1: ")
        self.write("%d\n" % (idx1))
        self._read("Enter Column Index 2: ")
        self.write("%d\n" % (idx2))

        self._read("Original Matrix\n")
        self._read_matrix(self.state['matrix'][self.state['cur_mtx']])

        self.state['matrix'][self.state['cur_mtx']] = self.state['matrix'][self.state['cur_mtx']].transpose()
        t1 = np.matrix.copy(self.state['matrix'][self.state['cur_mtx']][idx1])
        t2 = np.matrix.copy(self.state['matrix'][self.state['cur_mtx']][idx2])
        self.state['matrix'][self.state['cur_mtx']][idx1] = t2
        self.state['matrix'][self.state['cur_mtx']][idx2] = t1
        self.state['matrix'][self.state['cur_mtx']] = self.state['matrix'][self.state['cur_mtx']].transpose()

        self._read("Swapped Columns\n")
        self._read_matrix(self.state['matrix'][self.state['cur_mtx']])

    def transpose(self):
        self.write("8\n")
        self._read("Transpose a Matrix:\n")
        self._select_matrix()

        self._read("Original Matrix\n")
        self._read_matrix(self.state['matrix'][self.state['cur_mtx']])
        self.state['matrix'][self.state['cur_mtx']] = self.state['matrix'][self.state['cur_mtx']].transpose()
        self._read("Transposed Matrix\n")
        self._read_matrix(self.state['matrix'][self.state['cur_mtx']])

    def rref(self):
        self.write("9\n")
        self._read("Perform Reduced Row Echelon Form on Matrix\n")
        self._select_matrix()
        self.state['matrix'][0] = np.matrix.copy(self.state['matrix'][self.state['cur_mtx']])
        self.state['matrix_type'] = "FLOAT"
        self.state['matrix'][0] = self.state['matrix'][0].astype(np.float32)

        num_rows, num_cols = self.state['matrix'][0].shape
        divisor = 1.0
        i = 0
        j = 0
        while i < num_rows and j < num_cols:
            if divisor <= TOL and divisor >= NTOL:
                i -= 1
            self._swap_nonzero_cell(self.state['matrix'][0], i, j)
            divisor = self.state['matrix'][0][i,j]

            k = j
            while k  < num_cols:
                if divisor <= TOL and divisor >= NTOL:
                    break
                if divisor - 1 <= TOL and divisor -1 >= NTOL:
                    break
                temp = self.state['matrix'][0][i,k]
                self.state['matrix'][0][i, k] = temp / divisor
                k += 1

            k = 0
            while k  < num_rows:
                if divisor <= TOL and divisor >= NTOL:
                    break
                if k == i:
                    k += 1
                    continue
                scalar = self.state['matrix'][0][k,j]
                if scalar > TOL or scalar < NTOL:
                    self._subtract_row(self.state['matrix'][0], i, k, j, scalar)
                k += 1

            i += 1
            j += 1

        self._read("RREF Result:\n")
        self._read_matrix(self.state['matrix'][0], self.state['matrix_type'] == "FLOAT")

    def get_rand(self):
        if self.state['randidx'] == 1024:
            self.state['randidx'] = 0
        result = self.state['randdata'][self.state['randidx']]
        self.state['randidx'] += 1
        return result

    def do_randomize(self):
        self.write("10\n")
        self._read("Create a Random Matrix:\n")
        self._select_matrix()
        row, col = self._select_row_col_size()
        self.state['matrix'][self.state['cur_mtx']] = np.matrix([0] * row * col)
        self.state['matrix'][self.state['cur_mtx']] = self.state['matrix'][self.state['cur_mtx']].reshape(row, col)
        for i in xrange(row):
            for j in xrange(col):
                self.state['matrix'][self.state['cur_mtx']][(i,j)] = self.get_rand()
        self.main_menu()
        self.print_matrix()

    def exit(self):
        self.write("11\n")
        self._read("Exiting...\n")

