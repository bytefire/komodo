#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>
#include "komodo-tests.h"

int main()
{
	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	if (setup_komodo_test_suite() == -1) { //setupBankTestSuite will add a test suite to the CUnit test registry see further on
		CU_cleanup_registry();

		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
}
