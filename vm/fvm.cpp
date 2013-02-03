#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// For stat
#include <sys/stat.h>

#include <vector>

using std::vector;

typedef int int32;
typedef unsigned int uint32;
typedef unsigned char byte;

// opcodes

// 'HALT' in little endian
const uint32 HALT = 0x544c4148;

struct FVM {
	vector<byte> mem;
	vector<byte> code;

	uint32 pc;
	uint32 sp;

	FVM(const vector<byte>& program) {
		mem = vector<byte>(1024);
		code = program;
		sp = mem.size();
		pc = 0;
	}

	void run() {
		printf("Running...\n");
		while (step()) {
			step();
		}
	}

	void fail(const char* msg, ...) {
		va_list args;
		va_start(args, msg);
		vprintf(msg, args);
		va_end(args);
		exit(1);
	}

	uint32 read_instr() {
		if (pc < code.size()) {
			uint32 result = *(uint32*)(&code[pc]);
			pc += 4;
			return result;
		} else {
			fail("Failed to read instruction, pc %p, code size %p\n", pc, code.size());
			return 0;
		}
	}

	bool step() {
		uint32 instr = read_instr();

		if (instr == HALT) {
			printf("Halt at pc %p\n", (void*) pc);
		}
		
		return true;
	}
};

vector<byte> load(const char* filename) {
	struct stat buf;
	if (stat(filename, &buf)) {
		printf("%s: can't open file\n", filename);
		exit(1);
	}

	int filesize = buf.st_size;
	if (filesize < 4) {
		printf("%s: not a VM file (too short)\n", filename);
		exit(1);
	}

	size_t program_len = filesize - 4;
	vector<byte> result(program_len);

	if (FILE* f = fopen(filename, "r")) {
		byte header[4];
		size_t read = fread(&header, 4, 1, f);
		if (read != 1) {
			printf("%s: can't read header\n", filename);
			exit(1);
		}
		if (!strncmp((char *) &header, "FVM0", 4)) {
			read = fread(&result[0], program_len, 1, f);
			if (read != 1 && program_len > 0) {
				printf("%s: can't read file\n", filename);
				exit(1);
			}
		} else {
			printf("%s: invalid header (expected FVM0)\n", filename);
		}

		fclose(f);
	}

	return result;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Usage: fvm <file>\n");
		return 0;
	}

	for (int i = 1; i < argc; i++) {
		vector<byte> program = load(argv[i]);

		FVM fvm(program);
		fvm.run();
	}
}
