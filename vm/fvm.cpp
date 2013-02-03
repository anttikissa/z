#include <stdio.h>
#include <vector>

using std::vector;

typedef int int32;
typedef unsigned char byte;

struct FVM {
	std::vector<byte> mem;
	std::vector<byte> code;

	int32 pc;
	int32 sp;

	FVM(const std::vector<byte>& program) {
		mem = std::vector<byte>(1024);
		code = program;
		sp = 0;
		pc = 0;
	}

	void run() {
		printf("Running...\n");
	}
};

int main() {
	//FVM fvm;
}
