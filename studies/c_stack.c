#include <stdio.h>

#define PRINT_OFFSET(var, offset) \
	printf("data at %p: %08x\n", &var + offset, *(&var + offset))

void f(int i, int j, int k) {
	printf("first is %p\n", &i);
	printf("second is %p\n", &j);
	printf("third is %p\n", &k);

	PRINT_OFFSET(i, 13);
	PRINT_OFFSET(i, 12);
	PRINT_OFFSET(i, 11);
	PRINT_OFFSET(i, 10);
	PRINT_OFFSET(i, 9);
	PRINT_OFFSET(i, 8);
	PRINT_OFFSET(i, 7);
	PRINT_OFFSET(i, 6);
	PRINT_OFFSET(i, 5);
	PRINT_OFFSET(i, 4);
	PRINT_OFFSET(i, 3);
	PRINT_OFFSET(i, 2);
	PRINT_OFFSET(i, 1);
	PRINT_OFFSET(i, 0);
	PRINT_OFFSET(i, -1);
	PRINT_OFFSET(i, -2);
	PRINT_OFFSET(i, -3);
	PRINT_OFFSET(i, -4);
	PRINT_OFFSET(i, -5);
	PRINT_OFFSET(i, -6);
	PRINT_OFFSET(i, -7);
	PRINT_OFFSET(i, -8);
//	printf("data at %p: %08x\n", &i, *(&i));
}

int main() {
	int x = 0x80;
	int y = 0xff;
	int z = -1;
	
	f(1, 2, 3);

	int k = x + y + z;
	return k;

	return 0;
}
