#include "engine.h"

typedef enum instruction_type {
	INSTRUCTION_TYPE_UNKNOWN,
	INSTRUCTION_TYPE_SHIFT_MOV,
	INSTRUCTION_TYPE_ADD_SUB,
	INSTRUCTION_TYPE_MOV,
	INSTRUCTION_TYPE_ALU,
} instruction_type_t;

static instruction_type_t get_instruction_type(uint16_t opcode); 
static char *build_assembly_instruction(uint16_t opcode, instruction_type_t ins_type);

char *get_assembly(uint16_t opcode)
{
	
}

static instruction_type_t get_instruction_type(uint16_t opcode)
{
	// three MSBs are 0s and following two are not 1s then it's MOV_REG
	if ( ((opcode >> 13) == 0) && (((opcode & 0x1800) >> 11) != 3) )
	{
		return INSTRUCTION_TYPE_MOV_REG;
	}

	return INSTRUCTION_TYPE_UNKNOWN;
}

static char *build_assembly_instruction(uint16_t opcode, instruction_type_t ins_type)
{
	switch (ins_type) {
		case INSTRUCTION_TYPE_MOV_REG:
			return build_mov_reg(opcode);
	}
}