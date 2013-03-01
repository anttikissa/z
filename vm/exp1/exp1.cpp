#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;
typedef unsigned int uint32;

const uint32 data_size = 1024;
const uint32 code_size = 1024;

byte m[data_size] = {
	0x01,
	0x02,
	0x03
};

uint32 code[code_size] = {
	0x00000001,
	0x02000002,
	0x0f000000,
};

const int opcode_bits = 8;
const int opcode_mask = (1 << opcode_bits) - 1;
const int a_bits = 12;
const int a_mask = (1 << a_bits) - 1;
const int b_bits = 12;
const int b_mask = (1 << b_bits) - 1;

const int op_add = 0x00;
const int op_sub = 0x01;
const int op_mul = 0x02;
const int op_div = 0x03;

const int op_exit = 0x0f;

void fail(const char* msg) {
	printf("%s\n", msg);
	exit(1);
}

int main() {
	uint32 pc = 0;

	while (true) {
		if (pc >= code_size) {
			fail("invalid pc");
		}

		unsigned int instr = code[pc++];
		unsigned int b = instr & b_mask;
		unsigned int a = (instr >> b_bits) & b_mask;
		unsigned int opcode = (instr >> (a_bits + b_bits)) & opcode_mask;

		printf("instr: %08x, op: %02x, a: %03x, b: %03x\n", instr, opcode, a, b);

		if (a >= data_size) {
			fail("invalid memory access (a)");
		}

		byte* a_mem = &m[a];
		byte b_immediate;
		byte* b_mem;
		// Immediate?
		if (b & (1 << 11)) {
			b_immediate = b & ((1 << 11) - 1);
			b_mem = &b_immediate;
		} else {
			if (b >= data_size) {
				fail("invalid memory access (b)");
			}
			b_mem = &m[b];
		}
		
		switch (opcode) {
			case op_exit:
				printf("exit value: %d\n", *b_mem);
				return 0;
			case op_add:
				*a_mem += *b_mem;
				break;
			case op_sub:
				*a_mem -= *b_mem;
				break;
			case op_mul: 
				*a_mem *= *b_mem;
				break;
			case op_div: 
				*a_mem /= *b_mem;
				break;
			default:
				fail("invalid instruction\n");
				break;
		}
	}
}
