// SPDX-License-Identifier: GPL-2.0-only

#include "dml_test.h"

/**
 * amdgpu_dml_test_init() - Initialise KUnit Tests for DML
 *
 * It aggregates all KUnit Tests related to the Display Mode Library (DML).
 * The DML contains multiple modules, and to assure the modularity of the
 * tests, the KUnit Tests for a DML module are also gathered in a separated
 * module. Each KUnit Tests module is initiated in this function.
 *
 */
void amdgpu_dml_test_init(void)
{
	bw_fixed_test_init();
	display_mode_lib_test_init();
}

void amdgpu_dml_test_exit(void)
{
	display_mode_lib_test_exit();
	bw_fixed_test_exit();
}
