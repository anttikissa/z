#include <stdio.h>
#include <string.h>

typedef int bool;

// Utility to convert numbers into bits and vice versa
int main(int argc, char* argv[]) {
	char *cmd = argv[0];
	int cmdlen = strlen(cmd);
	bool unbits = cmdlen >= 6 && cmd[cmdlen-6] == 'u' && cmd[cmdlen-5] == 'n';

	if (argc == 1) {
		if (unbits) {
			printf("Usage: unbits (binary value)\n");
			printf("Example: 0010100110010010\n");
		} else {
			printf("Usage: bits (integer value | hex value)\n");
			printf("Example: bits 1234\n");
			printf("Example: bits 0xffff\n");

		}
		return 1;
	}

	unsigned int val = 0;
	if (unbits) {
		char c, *arg = argv[1];
		while ((c = *arg++)) {
			if (c == '_') continue;
			if (c != '0' && c != '1')
				return printf("Invalid input value '%c' at %ld\n", c, arg-argv[1]);
			val = (val << 1) | (c == '1');
		}
		printf("%d (0x%x)\n", val, val);
	} else {
		if (!sscanf(argv[1], "0x%x", &val)) {
			sscanf(argv[1], "%u", &val);
		}
//		printf("val %d\n", val);
		int i;
		for (i = 31; i >= 0; i--) {
			printf("%d", !!(val & (1 << i)));
			if (i % 4 == 0) {
				printf(" ");
			}
		}
		printf("\n");
	}

	return 0;
}
