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

int setup_komodo_test_suite(void) {
	CU_pSuite pSuite = NULL;
	pSuite = CU_add_suite("Komodo Test Suite", init_komodo_test_suite, clean_komodo_test_suite);
	if (NULL == pSuite) {
		return -1;
	}

	if ((NULL == CU_add_test(pSuite, "test of format 6", test_format6)) ||
		(NULL == CU_add_test(pSuite, "test of format 7", test_format7))) {
		return -1;
	}

	return 0;
}


