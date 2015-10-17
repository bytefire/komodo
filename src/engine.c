#include <string.h>
#include <stdio.h>

#include "engine.h"

#define MAX_LEN 128

char thumb_instruction[MAX_LEN];

typedef char *(*disassemble_func)(uint16_t);

static char *disassemble_mov_shift_reg(uint16_t opcode);
static char *disassemble_add_sub(uint16_t opcode);
static char *disassemble_mov_comp_add_sub_imm(uint16_t opcode);
static char *disassemble_alu_high_reg_decider(uint16_t opcode);
static char *disassemble_alu(uint16_t opcode);
static char *disassemble_high_reg_branch_exchange(uint16_t opcode);

static uint16_t isolate_bits(uint16_t src, uint8_t start_bit, uint8_t end_bit);

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

	disassembler_vector[8] = disassemble_alu_high_reg_decider;
}

char *engine_get_assembly(uint16_t opcode)
{
	uint8_t opcode_identifier;
	// get five most significant bits of opcode
	opcode_identifier = isolate_bits(opcode, 11, 15);
		// ((opcode & 0xF800) >> 11);

	// index into disassembler_vector
	return disassembler_vector[opcode_identifier](opcode);
}

static char *disassemble_mov_shift_reg(uint16_t opcode)
{
	uint16_t hold;
	int i = 0;

	memset(thumb_instruction, 0, MAX_LEN);
	// isolate opertion bits 11 and 12
	hold = isolate_bits(opcode, 11, 12);
		// ((opcode & 0x1800) >> 11);
	switch(hold){
		case 0:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "LSL");
			break;
		case 1:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "LSR");
			break;
		case 2:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "ASR");
			break;
		default:
			snprintf(thumb_instruction, MAX_LEN, "%s", "ERROR: Format 1: Unknown operation");
			return thumb_instruction;
	}

	// isolate rd bits 0-2
	hold = isolate_bits(opcode, 0, 2);
		//(opcode & 0x7);
	i += snprintf(thumb_instruction + i, MAX_LEN - i, "R%d, ", hold);

	// isolate rs bits 3-5
	hold = isolate_bits(opcode, 3, 5);
		// ((opcode & 0x38) >> 3);
	i += snprintf(thumb_instruction + i, MAX_LEN - i, "R%d, ", hold);

	// isolate offset bits 6-10
	hold = isolate_bits(opcode, 6, 10);
		// ((opcode & 0x7C0) >> 6);
	i += snprintf(thumb_instruction + i, MAX_LEN - i, "#%d", hold);

	return thumb_instruction;
}

static char *disassemble_add_sub(uint16_t opcode)
{
	uint16_t hold, is_immediate;
	int i = 0;
	
	memset(thumb_instruction, 0, MAX_LEN);
	// isolate op bit 9 - ADD or SUB
	hold = isolate_bits(opcode, 9, 9);
		// ((opcode & 0x0200) >> 9);
	if (hold == 0) {
		i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "ADD");
	} else {
		i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "SUB");
	}
	// isolate rd bits 0-2
	hold = isolate_bits(opcode, 0, 2);
		// (opcode & 0x7);
	i += snprintf(thumb_instruction + i, MAX_LEN - i, "R%d, ", hold);
	// isolate rs bits 3-5
	hold = isolate_bits(opcode, 3, 5);
		// ((opcode & 0x38) >> 3);
	i += snprintf(thumb_instruction + i, MAX_LEN - i, "R%d, ", hold);
	// isolate immediate flag bit 10
	is_immediate = isolate_bits(opcode, 10, 10);
		// ((opcode & 0x0400) >> 10);
	// isolate rn/offset bits 6-8
	hold = isolate_bits(opcode, 6, 8);
		// ((opcode & 0x1C0) >> 6);
	if (is_immediate) {
		i += snprintf(thumb_instruction + i, MAX_LEN - i, "#%d", hold);
	} else {
		i += snprintf(thumb_instruction + i, MAX_LEN - i, "R%d", hold);
	}

	return thumb_instruction;
}
static char *disassemble_mov_comp_add_sub_imm(uint16_t opcode)
{
	uint16_t hold;
	int i = 0;
	
	memset(thumb_instruction, 0, MAX_LEN);

	// isolate op bits 11-12
	hold = isolate_bits(opcode, 11, 12);
		// ((opcode & 0x1800) >> 11);
	switch (hold) {
		case 0:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "MOV");
			break;
		case 1:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "CMP");
			break;
		case 2:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "ADD");
			break;
		case 3:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "SUB");
			break;
		default:
			snprintf(thumb_instruction, MAX_LEN, "%s", "ERROR: Format 3: Unknown operation");
			return thumb_instruction;
	}
	// isolate rd bits 8-10
	hold = isolate_bits(opcode, 8, 10);
	i += snprintf(thumb_instruction + i, MAX_LEN - i, "R%d, ", hold);
	// isolate offset bits 0-7
	hold = isolate_bits(opcode, 0, 7);
	i += snprintf(thumb_instruction + i, MAX_LEN - i, "#%d", hold);
	
	return thumb_instruction;
}

static char *disassemble_alu_high_reg_decider(uint16_t opcode)
{
	uint16_t hold;
	
	// isolate bit 10 to see if it is alu or high_reg_branch_exchange instruction
	hold = isolate_bits(opcode, 10, 10);

	if (hold == 1){
		return disassemble_alu(opcode);
	} else {
		return disassemble_high_reg_branch_exchange(opcode);
	}
}

static char *disassemble_alu(uint16_t opcode)
{
	uint16_t hold;
	int i = 0;
	
	memset(thumb_instruction, 0, MAX_LEN);

	// isolate op bits 6-9
	hold = isolate_bits(opcode, 6, 9);
	// switch case on op
	switch (hold) {
		case 0:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "AND");
			break;
		case 1:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "EOR");
			break;
		case 2:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "LSL");
			break;
		case 3:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "LSR");
			break;
		case 4:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "ASR");
			break;
		case 5:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "ADC");
			break;
		case 6:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "SBC");
			break;
		case 7:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "ROR");
			break;
		case 8:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "TST");
			break;
		case 9:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "NEG");
			break;
		case 10:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "CMP");
			break;
		case 11:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "CMN");
			break;
		case 12:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "ORR");
			break;
		case 13:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "MUL");
			break;
		case 14:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "BIC");
			break;
		case 15:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "MVN");
			break;
		default:
			snprintf(thumb_instruction, MAX_LEN, "%s", "ERROR: Format 4: Unknown operation");
			return thumb_instruction;
	}

	// isolate rd bits 0-2
	hold = isolate_bits(opcode, 0, 2);
	i += snprintf(thumb_instruction + i, MAX_LEN - i, "R%d, ", hold);
	// isolate rs bits 3-5
	hold = isolate_bits(opcode, 3, 5);
	i += snprintf(thumb_instruction + i, MAX_LEN - i, "R%d", hold);

	return thumb_instruction;
}

static char *disassemble_high_reg_branch_exchange(uint16_t opcode)
{
	uint16_t hold;
	int i = 0;
	
	memset(thumb_instruction, 0, MAX_LEN);

	// isolate op bits 8-9
	hold = isolate_bits(opcode, 8, 9);

	// if h1 and h2 bits 6-7 are zero and op is 0, 1 or 2 then invalid instruction 
	if (((hold >= 0) && (hold <= 2)) && (isolate_bits(opcode, 6, 7) == 0)) {
		snprintf(thumb_instruction, MAX_LEN, "%s",
			"ERROR: Format 5: Both regs can't be low for ops ADD, CMP and MOV.");
		return thumb_instruction;	
	}

	// if op is 3 and h1 is 1 then invalid instruction
	if ((hold == 3) && (isolate_bits(opcode, 7, 7) == 1)) {
		snprintf(thumb_instruction, MAX_LEN, "%s",
			"ERROR: Format 5: H1 cannot be 1 for BX instruction.");
		return thumb_instruction;
	}

	switch (hold) {
		case 0:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "ADD");
			break;
		case 1:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "CMP");
			break;
		case 2:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "MOV");
			break;
		case 3:
			i += snprintf(thumb_instruction + i, MAX_LEN - i, "%s ", "BX");
			break;
	}

	// rd bits 0-2
	hold = isolate_bits(opcode, 0, 2);
	// if h1 bit 7 set then add 8 to rd
	if (isolate_bits(opcode, 7, 7) == 1)
		hold += 8;
	i += snprintf(thumb_instruction + i, MAX_LEN - i, "R%d, ", hold);
	// rs bit 3-5
	hold = isolate_bits(opcode, 3, 5);
	// if h2 bit 6 set then add 8 to rs
	if (isolate_bits(opcode, 6, 6) == 1)
		hold += 8;
	i += snprintf(thumb_instruction + i, MAX_LEN - i, "R%d", hold);

	return thumb_instruction;
}

/***** helper functions *****/
static uint16_t isolate_bits(uint16_t src, uint8_t start_bit, uint8_t end_bit)
{
	src = src << (15 - end_bit);
	src = src >> (start_bit + 15 - end_bit);

	return src;
}