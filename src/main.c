#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
	uint16_t opcode;

	printf("*** Komodo Thumb 16-bit opcode to assembly converter ***\n");
	
	while(1)
	{
		printf("Enter opcode in hex: 0x");
		scanf("%hx", &opcode);

		printf(">>> number is: %d\n", opcode);
	}

	return 0;
}