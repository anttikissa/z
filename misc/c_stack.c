#include <stdio.h>

extern void * __libc_stack_end;

#define PRINT_OFFSET(var, offset) \
	printf("data at %p: %08x\n", &var + offset, *(&var + offset))

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
	printf("__libc_stack_end: %p\n", __libc_stack_end); \
    printf("\n");

void* esp;
void* ebp;
void* eax;
void* ebx;
void* ecx;
void* edx;

int f(int i, int j, int k) {
	int x = 0x12345679;
	--x;

	INFO();

	return 0x87654321;
}

int main(int i) {
	int x = 0x80;
	int y = 0xff;
	int z = -1;
	
	int result = f(1, 2, 3);

	INFO();
	
	int k = x + y + z;
	return k;

	return 0;
}
