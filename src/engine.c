#include "engine.h"

#define MAX_LEN 64

char thumb_instruction[MAX_LEN];

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

static char *disassemble_mov_shift_reg(uint16_t opcode)
{
	uint16_t hold;
	int i = 0;

	// isolate opertion bits 11 and 12
	hold = ((opcode & 0x1800) >> 11);
	switch(hold){
		case 0:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s", "LSL ");
			break;
		case 1:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s", "LSR ");
			break;
		case 2:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s", "ASR ");
			break;
		default:
			snprintf(thumb_instruction, MAX_LEN, "%s", "ERROR: Unknown operation");
			return thumb_instruction;
	}

	// isolate rd bits 0-2
	hold = (opcode & 0x7);
	i += snprintf(thumb_instruction + i, MAX_LEN - i, "R%d, ", hold);

	// isolate rs bits 3-5
	hold = (opcode & 0x38);
	i += snprintf(thumb_instruction + i, MAX_LEN - i, "R%d, ", hold);

	// isolate offset bits 6-10
	hold = (opcode & 0x7C0);
	i += snprintf(thumb_instruction + i, MAX_LEN - i, "#%d", hold);

	return thumb_instruction;
}