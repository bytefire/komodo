#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "engine.h"

int main()
{
	uint16_t opcode;

	engine_init();
	while(1)
	{
		printf("Enter opcode in hex: 0x");
		scanf("%hx", &opcode);

		printf(">>> Thumb assembly is: %s\n", engine_get_assembly(opcode));
	}

	return 0;
}