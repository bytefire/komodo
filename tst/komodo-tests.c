#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "komodo-tests.h"
#include "engine.h"

int init_komodo_test_suite(void)
{
	engine_init();

	return 0;
}

int clean_komodo_test_suite(void)
{
	return 0;
}

void test_format6()
{
	uint16_t opcode = 0x4dd3;
	char *assembly = engine_get_assembly(opcode);

	CU_ASSERT(strcmp(assembly, "LDR R5, [PC, #844]") == 0);
}

void test_format7()
{
	uint16_t opcode = 0x5193;
	char *assembly = engine_get_assembly(opcode);

	CU_ASSERT(strcmp(assembly, "STR R3, [R2, R6]") == 0);

	opcode = 0x5561;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly, "STRB R1, [R4, R5]") == 0);

	opcode = 0x59c2;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly, "LDR R2, [R0, R7]") == 0);

	opcode = 0x5d8b;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly, "LDRB R3, [R1, R6]") == 0);
}

void test_format8()
{
	uint16_t opcode = 0x521c;
	char *assembly = engine_get_assembly(opcode);

	CU_ASSERT(strcmp(assembly, "STRH R4, [R3, R0]") == 0);

	opcode = 0x5ba9;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly, "LDRH R1, [R5, R6]") == 0);

	opcode = 0x567a;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly, "LDSB R2, [R7, R1]") == 0);

	opcode = 0x5ea3;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly, "LDSH R3, [R4, R2]") == 0);
}

void test_format9()
{
	uint16_t opcode = 0x60d5;
	char *assembly = engine_get_assembly(opcode);

	CU_ASSERT(strcmp(assembly, "STR R5, [R2, #12]") == 0);

	opcode = 0x6f6a;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly, "LDR R2, [R5, #116]") == 0);

	opcode = 0x7341;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly, "STRB R1, [R0, #13]") == 0);

	opcode = 0x7f65;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly, "LDRB R5, [R4, #29]") == 0);
}

void test_format10()
{
	uint16_t opcode = 0x870e;
	char *assembly = engine_get_assembly(opcode);

	CU_ASSERT(strcmp(assembly, "STRH R6, [R1, #56]") == 0);

	opcode = 0x88bc;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly, "LDRH R4, [R7, #4]") == 0);
}

void test_format11()
{
	uint16_t opcode = 0x947b;
	char *assembly = engine_get_assembly(opcode);

	CU_ASSERT(strcmp(assembly, "STR R4, [SP, #492]") == 0);

	opcode = 0x9fa8;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly, "LDR R7, [SP, #672]") == 0);
}

void test_format12()
{
	uint16_t opcode = 0xa28f;
	char *assembly = engine_get_assembly(opcode);

	CU_ASSERT(strcmp(assembly, "ADD R2, PC, #572") == 0);

	opcode = 0xae35;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly, "ADD R6, SP, #212") == 0);
}

void test_format13()
{
	uint16_t opcode = 0xb043;
	char *assembly = engine_get_assembly(opcode);

	CU_ASSERT(strcmp(assembly, "ADD SP, #268") == 0);

	opcode = 0xb09a;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly, "ADD SP, #-104") == 0);
}

void test_format14()
{
	uint16_t opcode = 0xb46c;
	char *assembly = engine_get_assembly(opcode);

	CU_ASSERT(strcmp(assembly, "PUSH {R2, R3, R5, R6}") == 0);

	opcode = 0xb51f;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly, "PUSH {R0, R1, R2, R3, R4, LR}") == 0);

	opcode = 0xbc04;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly, "POP {R2}") == 0);

	opcode = 0xbdf0;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly, "POP {R4, R5, R6, R7, PC}") == 0);
}

void test_format15()
{
	uint16_t opcode = 0xc0f8;
	char *assembly = engine_get_assembly(opcode);

	CU_ASSERT(strcmp(assembly, "STMIA R0!, {R3, R4, R5, R6, R7}") == 0);

	opcode = 0xcbf7;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly, "LDMIA R3!, {R0, R1, R2, R4, R5, R6, R7}") == 0);
}

void test_format16()
{
	uint16_t opcode = 0xd012;
	char *assembly = engine_get_assembly(opcode);

	CU_ASSERT(strcmp(assembly,
		"BEQ label ;label = PC + (36). Note that PC is curr instruction + 4 due to instruction prefetch.") == 0);

	opcode = 0xd1c2;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly,
		"BNE label ;label = PC + (-124). Note that PC is curr instruction + 4 due to instruction prefetch.") == 0);

	opcode = 0xd212;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly,
		"BCS label ;label = PC + (36). Note that PC is curr instruction + 4 due to instruction prefetch.") == 0);

	opcode = 0xd3c2;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly,
		"BCC label ;label = PC + (-124). Note that PC is curr instruction + 4 due to instruction prefetch.") == 0);

	opcode = 0xd412;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly,
		"BMI label ;label = PC + (36). Note that PC is curr instruction + 4 due to instruction prefetch.") == 0);

	opcode = 0xd5c2;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly,
		"BPL label ;label = PC + (-124). Note that PC is curr instruction + 4 due to instruction prefetch.") == 0);

	opcode = 0xd612;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly,
		"BVS label ;label = PC + (36). Note that PC is curr instruction + 4 due to instruction prefetch.") == 0);

	opcode = 0xd7c2;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly,
		"BVC label ;label = PC + (-124). Note that PC is curr instruction + 4 due to instruction prefetch.") == 0);

	opcode = 0xd812;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly,
		"BHI label ;label = PC + (36). Note that PC is curr instruction + 4 due to instruction prefetch.") == 0);

	opcode = 0xd9c2;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly,
		"BLS label ;label = PC + (-124). Note that PC is curr instruction + 4 due to instruction prefetch.") == 0);

	opcode = 0xda12;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly,
		"BGE label ;label = PC + (36). Note that PC is curr instruction + 4 due to instruction prefetch.") == 0);

	opcode = 0xdbc2;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly,
		"BLT label ;label = PC + (-124). Note that PC is curr instruction + 4 due to instruction prefetch.") == 0);

	opcode = 0xdc12;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly,
		"BGT label ;label = PC + (36). Note that PC is curr instruction + 4 due to instruction prefetch.") == 0);

	opcode = 0xddc2;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly,
		"BLE label ;label = PC + (-124). Note that PC is curr instruction + 4 due to instruction prefetch.") == 0);
}

void test_format17()
{
	uint16_t opcode = 0xdf12;
	char *assembly = engine_get_assembly(opcode);

	CU_ASSERT(strcmp(assembly, "SWI 18") == 0);
}

void test_format18()
{
	uint16_t opcode = 0xe006;
	char *assembly = engine_get_assembly(opcode);

	CU_ASSERT(strcmp(assembly,
		"B label ;label = PC + (12) - Note that PC = curr instruction + 4 due to instruction prefetch") == 0);

	opcode = 0xe7f4;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly,
		"B label ;label = PC + (-24) - Note that PC = curr instruction + 4 due to instruction prefetch") == 0);
}

void test_format19()
{
	uint16_t opcode = 0xf024;
	char *assembly = engine_get_assembly(opcode);

	CU_ASSERT(strcmp(assembly,
		"BL label ; where label = PC + 23-bit num in two's complement - 11 high bits of the number are 0x24")
			== 0);

	opcode = 0xf81b;
	assembly = engine_get_assembly(opcode);
	CU_ASSERT(strcmp(assembly,
		"BL label ; where label = PC + 23-bit num in two's complement - 12 low bits of the number are 0x36")
		== 0);
}

int setup_komodo_test_suite(void) {
	CU_pSuite pSuite = NULL;
	pSuite = CU_add_suite("Komodo Test Suite", init_komodo_test_suite, clean_komodo_test_suite);
	if (NULL == pSuite) {
		return -1;
	}

	if ((NULL == CU_add_test(pSuite, "test of format 6", test_format6)) ||
		(NULL == CU_add_test(pSuite, "test of format 7", test_format7)) ||
		(NULL == CU_add_test(pSuite, "test of format 8", test_format8)) ||
		(NULL == CU_add_test(pSuite, "test of format 9", test_format9)) ||
		(NULL == CU_add_test(pSuite, "test of format 10", test_format10)) ||
		(NULL == CU_add_test(pSuite, "test of format 11", test_format11)) ||
		(NULL == CU_add_test(pSuite, "test of format 12", test_format12)) ||
		(NULL == CU_add_test(pSuite, "test of format 13", test_format13)) ||
		(NULL == CU_add_test(pSuite, "test of format 14", test_format14)) ||
		(NULL == CU_add_test(pSuite, "test of format 15", test_format15)) ||
		(NULL == CU_add_test(pSuite, "test of format 16", test_format16)) ||
		(NULL == CU_add_test(pSuite, "test of format 17", test_format17)) ||
		(NULL == CU_add_test(pSuite, "test of format 18", test_format18)) ||
		(NULL == CU_add_test(pSuite, "test of format 19", test_format19))) {
		return -1;
	}

	return 0;
}


