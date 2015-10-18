#include <stdlib.h>
#include <CUnit/Basic.h>

#include "komodo-tests.h"

int init_komodo_test_suite(void)
{
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

int setup_komodo_test_suite(void) {
	CU_pSuite pSuite = NULL;
	pSuite = CU_add_suite("Komodo Test Suite", init_komodo_test_suite, clean_komodo_test_suite);
	if (NULL == pSuite) {
		return -1;
	}

	if ((NULL == CU_add_test(pSuite, "test of two_plus_two()", test_two_plus_two))) {
		return -1;
	}

	return 0;
}


