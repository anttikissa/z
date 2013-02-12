#include <stdio.h>

int main() {
	int i;
	for (i = 0; i < 128; i++) {
		printf("%04d %02x '%c'\n", i, i, (char) i);
	}
}
