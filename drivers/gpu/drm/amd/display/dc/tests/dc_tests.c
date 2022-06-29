// SPDX-License-Identifier: MIT
/* Unit tests for dc/basics/fixpt31_32.c
 */

#include <kunit/test.h>
#include "dc_basics_fixpt31_32_test.h"

static struct kunit_case dc_basics_fixpt31_32_test_cases[] = {
	KUNIT_CASE(dc_fixpt_from_int_test),
	KUNIT_CASE(dc_fixpt_from_fraction_test),
	KUNIT_CASE(dc_fixpt_mul_test),
	KUNIT_CASE(dc_fixpt_sqr_test),
	KUNIT_CASE(dc_fixpt_recip_test),
	// KUNIT_CASE(dc_fixpt_sinc_test),
	// KUNIT_CASE(dc_fixpt_cos_test),
	// KUNIT_CASE(dc_fixpt_exp_test),
	// KUNIT_CASE(dc_fixpt_log_test),
	// KUNIT_CASE(dc_fixpt_u4d19_test),
	// KUNIT_CASE(dc_fixpt_u3d19_test),
	// KUNIT_CASE(dc_fixpt_u2d19_test),
	// KUNIT_CASE(dc_fixpt_u0d19_test),
	// KUNIT_CASE(dc_fixpt_clamp_u0d14_test),
	// KUNIT_CASE(dc_fixpt_clamp_u0d10_test),
	// KUNIT_CASE(dc_fixpt_s4d19_test),
	{  }
};

static struct kunit_suite dc_basics_fixpt31_32_test_suite = {
	.name = "dc_basics_fixpt31_32",
	.test_cases = dc_basics_fixpt31_32_test_cases,
};

kunit_test_suites(&dc_basics_fixpt31_32_test_suite);

MODULE_LICENSE("GPL");
