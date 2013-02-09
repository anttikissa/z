#include <stdio.h>

typedef long long int64;
typedef int int32;
//typedef int32 int;

#define PRINT_OFFSET(var, offset) \
	printf("data at %p: %p\n", &var + offset, (void *)*(&var + offset))

#define INFO() \
	PRINT_OFFSET(i, 13); \
	PRINT_OFFSET(i, 12); \
	PRINT_OFFSET(i, 11); \
	PRINT_OFFSET(i, 10); \
	PRINT_OFFSET(i, 9); \
	PRINT_OFFSET(i, 8); \
	PRINT_OFFSET(i, 7); \
	PRINT_OFFSET(i, 6); \
	PRINT_OFFSET(i, 5); \
	PRINT_OFFSET(i, 4); \
	PRINT_OFFSET(i, 3); \
	PRINT_OFFSET(i, 2); \
	PRINT_OFFSET(i, 1); \
	printf("First argument is at:\n"); \
	PRINT_OFFSET(i, 0); \
	PRINT_OFFSET(i, -1); \
	PRINT_OFFSET(i, -2); \
	PRINT_OFFSET(i, -3); \
	PRINT_OFFSET(i, -4); \
	PRINT_OFFSET(i, -5); \
	PRINT_OFFSET(i, -6); \
 \
    asm( \
        "movq %%rsp, %0;" \
        "movq %%rbp, %1;" \
        "movq %%rax, %2;" \
        "movq %%rbx, %3;" \
        "movq %%rcx, %4;" \
        "movq %%rdx, %5;" \
        :"=r"(esp), "=r"(ebp), "=r"(eax), "=r"(ebx), "=r"(ecx), "=r"(edx) \
        ); \
 \
    printf("esp is: %p\n", esp); \
    printf("ebp is: %p\n", ebp); \
/*    printf("eax is: %p\n", eax); \
    printf("ebx is: %p\n", ebx); \
    printf("ecx is: %p\n", ecx); \
    printf("edx is: %p\n", edx); */ \
    printf("\n");

void* esp;
void* ebp;
void* eax;
void* ebx;
void* ecx;
void* edx;

int f(int64 i, int64 j, int64 k) {
	int64 x = 0xffff000012345679;
	--x;
	int64 y = 0x5050505020202020;
	int64 z = 0x1020304050607080;
	int64 z1 = 0x1020304050607080;
	int64 z2 = 0x1020304050607080;
	int64 z3 = 0x1020304050607080;
	int64 z4 = 0x1020304050607080;
	int64 z5 = 0x1020304050607080;
	int64 z6 = 0x1020304050607080;
	int64 z7 = 0x1020304050607080;
	int64 z8 = 0x1020304050607080;
	int64 z9 = 0x1020304050607080;
	int64 z10 = 0x1020304050607080;
	int64 z11 = 0x1020304050607080;

	INFO();

	x = y = z;
	return 0x87654321;
}

int main(int i, char* argv[]) {
	printf("main is at %p\n", main);
	printf("   f is at %p\n", f);
	int x = 0x80;
	int y = 0xff;
	int z = -1;
	
	int result = f(1, 2, 3);

//	INFO();
	
	int k = x + y + z;
	return k + result;

	return 0;
}
