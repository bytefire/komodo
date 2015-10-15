#include "engine.h"

typedef enum instruction_type {
	INSTRUCTION_TYPE_UNKNOWN,
	INSTRUCTION_TYPE_SHIFT_MOV,
	INSTRUCTION_TYPE_ADD_SUB,
	INSTRUCTION_TYPE_MOV,
	INSTRUCTION_TYPE_ALU,
} instruction_type_t;

static typedef char *(*disassemble_func)(uint16_t);

static char *disassemble_mov_shift_reg(uint16_t opcode);
static char *disassemble_add_sub(uint16_t opcode);
static char *disassemble_mov_comp_add_sub_imm(uint16_t opcode);

// refer to "Format Summary" on page 5-2 in Thumb Instruction Set document,
// which is also available in this repo under doc/thumb-instruction-set.pdf
disassemble_func disassembler_vector[19];

void engine_init()
{
	disassembler_vector[0] = disassemble_mov_shift_reg;
	disassembler_vector[1] = disassemble_mov_shift_reg;
	disassembler_vector[2] = disassemble_mov_shift_reg;

	disassembler_vector[3] = disassemble_add_sub;

	disassembler_vector[4] = disassemble_mov_comp_add_sub_imm;
	disassembler_vector[5] = disassemble_mov_comp_add_sub_imm;
	disassembler_vector[6] = disassemble_mov_comp_add_sub_imm;
	disassembler_vector[7] = disassemble_mov_comp_add_sub_imm;
}

char *engine_get_assembly(uint16_t opcode)
{
	uint8_t opcode_identifier;
	// get five most significant bits of opcode
	opcode_identifier = ((opcode & 0xF800) >> 11);

	// index into disassembler_vector
	return disassembler_vector[opcode_identifier](opcode);
}

// TODO: define the disassembly functions
static char *disassemble_mov_shift_reg(uint16_t opcode)
{
	
}