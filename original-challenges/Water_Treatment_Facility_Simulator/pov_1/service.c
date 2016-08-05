/*

Author: Joe Rogers <joe@cromulence.com>

Copyright (c) 2015 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#include <libcgc.h>

#define EBP (5)

unsigned int ReadBytes(int fd, char *buf, unsigned int len) {
	unsigned int total_bytes = 0;
	size_t rx_bytes;
	char c;

	while (total_bytes < len) {
		if (receive(fd, &c, 1, &rx_bytes) != 0) {
			return(0);
		}
		if (rx_bytes == 0) {
			return(0);
		}
		buf[total_bytes++] = c;
	}

	return(total_bytes);
}

unsigned int ReadUntil(int fd, char delim, char *buf, unsigned int maxlen) {
	unsigned int total_bytes = 0;
	size_t rx_bytes;
	char c;

	while (total_bytes < maxlen-1) {
		if (receive(fd, &c, 1, &rx_bytes) != 0) {
			return(0);
		}
		if (rx_bytes == 0) {
			return(0);
		}
		if (c == delim) {
			break;
		}
		buf[total_bytes++] = c;
	}
	buf[total_bytes] = '\0';

	return(total_bytes);
}

unsigned int SendBytes(int fd, char *buf, unsigned int len) {
	size_t tx_bytes;
	unsigned int total_bytes = 0;

	while (total_bytes < len) {
		if (transmit(fd, buf+total_bytes, 1, &tx_bytes) != 0) {
			return(0);
		}
		if (tx_bytes != 1) {
			return(0);
		}
		total_bytes++;
	}

	return(total_bytes);
}

unsigned int pov_strlen(char *buf) {
	unsigned int len = 0;
	while (*(buf+len) != '\0') {
		len++;
	}
	return(len);
}

unsigned int SendString(int fd, char *buf) {
	unsigned int len = 0;

	return(SendBytes(fd, buf, pov_strlen(buf)));
}

void NegotiateType1Pov(unsigned int ipmask, unsigned int regmask, unsigned int regnum, unsigned int *type1_ip, unsigned int *type1_reg) {
	unsigned int PovType = 1;

	// Request Type 1 negotitation
	if (SendBytes(3, (char *)&PovType, 4) != 4) {
		_terminate(-1);
	}

	// Send the ipmask
	if (SendBytes(3, (char *)&ipmask, 4) != 4) {
		_terminate(-1);
	}

	// Send the regmask
	if (SendBytes(3, (char *)&regmask, 4) != 4) {
		_terminate(-1);
	}

	// Send the register number we'll be controlling
	if (SendBytes(3, (char *)&regnum, 4) != 4) {
		_terminate(-1);
	}

	// get the 4-byte value for eip
	if (ReadBytes(3, (char *)type1_ip, 4) != 4) {
		_terminate(-1);
	} 
	// get the 4-byte value for the register
	if (ReadBytes(3, (char *)type1_reg, 4) != 4) {
		_terminate(-1);
	}

	return;

}

char *Split(char *buf, char delim) {
	char *curr = buf;

	while (*curr != '\0') {
		if (*curr == delim) {
			*curr = '\0';
			return(buf);
		}
		curr++;
	}
	return(NULL);
}

int pov_strncmp(char *s1, char *s2, unsigned int len) {
	unsigned int curr = 0;

	while (*s1 != '\0' && *s2 != '\0' && curr < len) {
		if (*s1 < *s2)
			return(-1);
		if (*s1 > *s2)
			return(1);
		s1++;
		s2++;
		curr++;
	}

	if (curr == len)
		return(0);
	if (*s1 == *s2)
		return(0);
	if (*s1) 
		return(1);
	if (*s2) 
		return(-1);

	return(0);
}

void itoa(unsigned int i, char *buf) {
	unsigned int t;
	unsigned int digit = 0;

	// doesn't handle numbers larger than 999 because we don't need to
	if (i > 999)
		return;

	// hundreds digit
	t = i / 100;
	if (t > 0) {
		*buf++ = t+'0';
		digit = 1;
	}
	
	// tens digit
	i -= t*100;
	t = i / 10;
	if (digit || t > 0) {
		*buf++ = t+'0';
		digit = 1;
	}

	// ones digit
	i -= t*10;
	*buf++ = i+'0';

	*buf = '\0';

	return;
}

// handles very basic x.yz which is sufficient for PoV
void ftoa(double f, char *buf) {
        unsigned int len;

        itoa((unsigned int)f, buf);
        len = pov_strlen(buf);
        *(buf+len) = '.';
        f -= (unsigned int)f;
        f *= 10.0;
        *(buf+len+1) = (unsigned int)f + '0';
        f -= (unsigned int)f;
        f *= 10.0;
        *(buf+len+2) = (unsigned int)f + '0';
        *(buf+len+3) = '\0';

}

double atof(char *buf) {
	double whole = 0.0;
	double fraction = 0.0;
	double divisor = 10.0;

	// parse the integer portion
	while (*buf != '\0') {
		if (*buf == '.') {
			// found the decimal point
			buf++;
			break;
		}
		if (*buf < '0' || *buf > '9') {
			buf++;
			continue;
		}
		whole = (whole * 10.0) + (*buf - '0');
		buf++;
	}

	// parse the fractional portion
	while (*buf != '\0') {
		if (*buf < '0' || *buf > '9') {
			break;
		}
		fraction += (*buf - '0')/divisor;
		divisor /= 10.0;
		buf++;
	}

	return(whole+fraction);
}

void str_range(char *buf, char *out, unsigned int start, unsigned int end) {
	unsigned int i;
	unsigned int curr = 0;
	for (i = start; i <= end; i++) {
		out[curr++] = buf[i];
	}
	out[curr] = '\0';
}
	
void ParsePlantStatus(char *buf, double *Flow, double *Cbod, double *Tss, double *Tn, double *Tp) {
	char *line;
	unsigned int count = 0;
	char value[20];

	// split each line on the newline
	while ((line = Split(buf, '\n'))) {
		// see if the current line is the Influent (the only one we care about)
		if (!pov_strncmp("Influent", line, 8)) {
			if (count == 0) {
				// don't want the section header which is the 
				// first line matching this text
				count = 1;
				buf = line + pov_strlen(line)+1;
				continue;
			}
			// parse the values from the Influent line
			str_range(line, value, 16, 25);
			*Flow = atof(value);

			str_range(line, value, 26, 36);
			*Cbod = atof(value);

			str_range(line, value, 37, 47);
			*Tss = atof(value);

			str_range(line, value, 48, 58);
			*Tn = atof(value);

			str_range(line, value, 59, 69);
			*Tp = atof(value);
		}

		buf = line + pov_strlen(line)+1;
	}

}

double FilterReduction(double Loading) {
	if (Loading > 12.0) {
		return(1.0);
	} else if (Loading >= 10.0) {
		return(0.4);
	} else if (Loading >= 9.0) {
		return(0.25);
	} else if (Loading >= 8.0) {
		return(0.2);
	} else if (Loading >= 7.0) {
		return(0.15);
	} else if (Loading >= 6.0) {
		return(0.1);
	} else if (Loading >= 3.0) {
		return(0.05);
	} else if (Loading >= 1.0) {
		return(0.01);
	} else {
		return(0.0);
	}
}

void SetParameters(double PctAeration, double GlycerinRate, double AlumRate, double ChlorineRate) {
	char buf[8192];
	char float_buf[64];

	SendString(STDOUT, "3\n");  // ASP menu
	ReadUntil(STDIN, ':', buf, 8192);

	ftoa(PctAeration, float_buf);
	SendString(STDOUT, "1\n");  // aeration rate menu
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "0\n");  // ASP 0
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, float_buf);  
	SendString(STDOUT, "\n");  
	ReadUntil(STDIN, ':', buf, 8192);

	SendString(STDOUT, "1\n");  // aeration rate menu
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "1\n");  // ASP 1
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, float_buf);  
	SendString(STDOUT, "\n");  
	ReadUntil(STDIN, ':', buf, 8192);

	SendString(STDOUT, "1\n");  // aeration rate menu
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "2\n");  // ASP 2
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, float_buf);  
	SendString(STDOUT, "\n");  
	ReadUntil(STDIN, ':', buf, 8192);

	ftoa(GlycerinRate, float_buf);
	SendString(STDOUT, "2\n");  // glycerin rate menu
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "0\n");  // ASP 0
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, float_buf);  
	SendString(STDOUT, "\n");  
	ReadUntil(STDIN, ':', buf, 8192);

	SendString(STDOUT, "2\n");  // glycerin rate menu
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "1\n");  // ASP 1
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, float_buf);  
	SendString(STDOUT, "\n");  
	ReadUntil(STDIN, ':', buf, 8192);

	SendString(STDOUT, "2\n");  // glycerin rate menu
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "2\n");  // ASP 2
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, float_buf);  
	SendString(STDOUT, "\n");  
	ReadUntil(STDIN, ':', buf, 8192);

	ftoa(AlumRate, float_buf);
	SendString(STDOUT, "3\n");  // alum rate menu
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "0\n");  // ASP 0
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, float_buf);  
	SendString(STDOUT, "\n");  
	ReadUntil(STDIN, ':', buf, 8192);

	SendString(STDOUT, "3\n");  // alum rate menu
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "1\n");  // ASP 1
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, float_buf);  
	SendString(STDOUT, "\n");  
	ReadUntil(STDIN, ':', buf, 8192);

	SendString(STDOUT, "3\n");  // alum rate menu
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "2\n");  // ASP 2
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, float_buf);  
	SendString(STDOUT, "\n");  
	ReadUntil(STDIN, ':', buf, 8192);

	SendString(STDOUT, "4\n");  // return to the main menu
	ReadUntil(STDIN, ':', buf, 8192);

	SendString(STDOUT, "5\n");  // disinfection menu
	ReadUntil(STDIN, ':', buf, 8192);

	ftoa(ChlorineRate, float_buf);
	SendString(STDOUT, "1\n");  // chlorine rate menu
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "0\n");  // disinfection tank 0
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, float_buf);  
	SendString(STDOUT, "\n");  
	ReadUntil(STDIN, ':', buf, 8192);

	SendString(STDOUT, "1\n");  // chlorine rate menu
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "1\n");  // disinfection tank 1
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, float_buf);  
	SendString(STDOUT, "\n");  
	ReadUntil(STDIN, ':', buf, 8192);

	SendString(STDOUT, "1\n");  // chlorine rate menu
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "2\n");  // disinfection tank 2
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, float_buf);  
	SendString(STDOUT, "\n");  
	ReadUntil(STDIN, ':', buf, 8192);

	SendString(STDOUT, "2\n");  // return to the main menu
	ReadUntil(STDIN, ':', buf, 8192);

}

int main(void) {
	unsigned int Hours = 0;
	char buf[8192];
	unsigned int type1_ip;
	unsigned int type1_reg;
	size_t tx_bytes;
	double Flow, Cbod, Tss, Tn, Tp;
	double PctAeration, GlycerinRate, AlumRate, FilterLoading, ChlorineMass, ChlorineRate;
	unsigned int StructAddr;
	unsigned int i;

	// negotiate a Type1 POV with the Competition Framework
	// we will control eip and edx
	// 2nd byte (f6) of ipmask is to deal with infrequent floating-point rounding error in Flow value calculation
	NegotiateType1Pov(0xfef6fefe, 0xfefefefe, EBP, &type1_ip, &type1_reg);
	// deal with 0x00 and 0x0a which interfere with this CB's POV
	type1_ip |= 0x01010101;
	type1_reg |= 0x01010101;

	// Read in the CB's initial output
	ReadUntil(STDIN, ':', buf, 8192);

	// turn on all of the filters
	SendString(STDOUT, "4\n");  // filters menu
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "1\n");  // change active filter count menu
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "0\n");  // Filter 0
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "2\n");  // All on
	ReadUntil(STDIN, ':', buf, 8192);

	SendString(STDOUT, "1\n");  // change active filter count menu
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "1\n");  // Filter 1
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "4\n");  // All on
	ReadUntil(STDIN, ':', buf, 8192);

	SendString(STDOUT, "1\n");  // change active filter count menu
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "2\n");  // Filter 2
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "4\n");  // All on
	ReadUntil(STDIN, ':', buf, 8192);

	SendString(STDOUT, "2\n");  // Return to the main menu
	ReadUntil(STDIN, ':', buf, 8192);

	// run the plant for 24 hours
	while (Hours < 24) { 
		// Read and parse the plant status
		SendString(STDOUT, "2\n");  // return to the main menu
		ReadUntil(STDIN, ':', buf, 8192);
		SendString(2, buf);
		SendString(2, "\n");
		ParsePlantStatus(buf, &Flow, &Cbod, &Tss, &Tn, &Tp);

		// Calculate the best operational parameters
		PctAeration = (Cbod/3.0/24.0*2.0 + Tn/3.0/24.0*4.6) / 0.45 / 0.188 / 4800.0 * 100.0;
		GlycerinRate = Tn/3.0/24.0*6.5/9.78;
		AlumRate = Tp/3.0/24.0*0.9/0.49;

                // Calculate the Chlorine Rate (0-100%) that will get us to a final concentration of 4mg/l
                ChlorineRate = (Flow/3.0 * 8.34 * 13.0 / (76.1 * 0.12 * 24.0)) / 6.0 * 100.0;

                if (ChlorineRate > 100.0) {
                    ChlorineRate = 100.0;
		}

		// Set the parameters
		SetParameters(PctAeration, GlycerinRate, AlumRate, ChlorineRate);

		// Run a simulation step
		SendString(STDOUT, "8\n");  // Run Simulation Step
		ReadUntil(STDIN, ':', buf, 8192);

		Hours++;
	}

	// Set the valve 4 name, overwriting the first valve output pointer
	// to the Effluent plant system and the subsequent Flow double
	SendString(STDOUT, "7\n");  // rename menu
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "7\n");  // valves menu
	ReadUntil(STDIN, ':', buf, 8192);
	SendString(STDOUT, "4\n");  // rename valve 4
	ReadUntil(STDIN, ':', buf, 8192);
	// change the valve output pointer such that the new fake structure
	// is positioned over saved EBP and EIP from SimulateEffluent()
	StructAddr = 0xbaaaafac - 128;
	SendString(STDOUT, "AAA");
	for (i = 0; i < 31; i++) {
		SendBytes(STDOUT, (char *)&StructAddr, 4);
	}
	// overwrite Flow double
	SendBytes(STDOUT, (char *)&type1_reg, 4);
	SendBytes(STDOUT, (char *)&type1_ip, 4);
	SendString(STDOUT, "\n");
	ReadUntil(STDIN, ':', buf, 8192);

	SendString(STDOUT, "8\n");  // return to the main menu
	ReadUntil(STDIN, ':', buf, 8192);

	SendString(STDOUT, "9\n");  // end the simulation
	ReadUntil(STDIN, ':', buf, 8192);
}
