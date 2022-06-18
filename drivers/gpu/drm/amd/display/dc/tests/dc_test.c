// SPDX-License-Identifier: GPL-2.0-only

#include "dc_test.h"

/**
 * amd_dc_test_init() - Initialise KUnit Tests for Display Core
 *
 * It aggregates all KUnit Tests related to the Display Core (DC).
 * The DC contains multiple modules, and to assure the modularity of the
 * tests, the KUnit Tests for a DC module are also gathered in a separated
 * module. Each KUnit Tests module is initiated in this function.
 *
 */
void amd_dc_test_init(void)
{
	dc_basics_fixpt31_32_test_init();
}

void amd_dc_test_exit(void)
{
	dc_basics_fixpt31_32_test_exit();
}