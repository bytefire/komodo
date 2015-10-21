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

int setup_komodo_test_suite(void) {
	CU_pSuite pSuite = NULL;
	pSuite = CU_add_suite("Komodo Test Suite", init_komodo_test_suite, clean_komodo_test_suite);
	if (NULL == pSuite) {
		return -1;
	}

	if ((NULL == CU_add_test(pSuite, "test of format 6", test_format6)) ||
		(NULL == CU_add_test(pSuite, "test of format 7", test_format7)) ||
		(NULL == CU_add_test(pSuite, "test of format 8", test_format8))) {
		return -1;
	}

	return 0;
}


