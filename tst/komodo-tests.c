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

void test_two_plus_two(void)
{
	CU_ASSERT((2 + 2) == 4);
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

	// opcode = ...
}

int setup_komodo_test_suite(void) {
	CU_pSuite pSuite = NULL;
	pSuite = CU_add_suite("Komodo Test Suite", init_komodo_test_suite, clean_komodo_test_suite);
	if (NULL == pSuite) {
		return -1;
	}

	if ((NULL == CU_add_test(pSuite, "test of two_plus_two()", test_two_plus_two)) ||
		(NULL == CU_add_test(pSuite, "test of format 6", test_format6)) ||
		(NULL == CU_add_test(pSuite, "test of format 7", test_format7))) {
		return -1;
	}

	return 0;
}


