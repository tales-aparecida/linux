// SPDX-License-Identifier: MIT
/* Unit tests for dc/basics/fixpt31_32.c
 */

#include <kunit/test.h>
#include "include/fixed31_32.h"

static void dc_fixpt_from_fraction_test(struct kunit *test)
{
	struct fixed31_32 res;

	/* A fraction of N/N should result in "1.0" */
	res = dc_fixpt_from_fraction(LLONG_MAX, LLONG_MAX);
	KUNIT_EXPECT_EQ(test,  0x1LL << FIXED31_32_BITS_PER_FRACTIONAL_PART, res.value);

	// res = dc_fixpt_from_fraction(1, MAX_I64);
	// KUNIT_EXPECT_EQ(test, 0LL, res.value);

	// res = dc_fixpt_from_fraction(0, MAX_I64);
	// KUNIT_EXPECT_EQ(test, 0LL, res.value);

	// /* Turn a repeating decimal to the fixed-point representation */

	// /* A repeating decimal that doesn't round up the LSB */
	// res = dc_fixpt_from_fraction(4, 3);
	// KUNIT_EXPECT_EQ(test, 22369621LL, res.value);     /* 0x1555555 */

	// res = dc_fixpt_from_fraction(-4, 3);
	// KUNIT_EXPECT_EQ(test, -22369621LL, res.value);    /* -0x1555555 */

	// res = dc_fixpt_from_fraction(99999997, 100000000);
	// KUNIT_EXPECT_EQ(test, 16777215LL, res.value);     /* 0x0FFFFFF */

	// /* A repeating decimal that rounds up the MSB */
	// res = dc_fixpt_from_fraction(5, 3);
	// KUNIT_EXPECT_EQ(test, 27962027LL, res.value);     /* 0x1AAAAAB */

	// res = dc_fixpt_from_fraction(-5, 3);
	// KUNIT_EXPECT_EQ(test, -27962027LL, res.value);    /* -0x1AAAAAB */

	// res = dc_fixpt_from_fraction(99999998, 100000000);
	// KUNIT_EXPECT_EQ(test, 1LL << BW_FIXED_BITS_PER_FRACTIONAL_PART, res.value);

	// /* Turn a terminating decimal to the fixed-point representation */
	// res = dc_fixpt_from_fraction(62609, 100);
	// KUNIT_EXPECT_EQ(test, 10504047165LL, res.value);  /* 0X272170A3D */

	// res = dc_fixpt_from_fraction(-62609, 100);
	// KUNIT_EXPECT_EQ(test, -10504047165LL, res.value); /* -0X272170A3D */
}

static void dc_fixpt_mul_test(struct kunit *test)
{
	// struct bw_fixed arg1;
	// struct bw_fixed arg2;
	// struct bw_fixed res;

	// res = bw_mul(bw_int_to_fixed(8), bw_int_to_fixed(10));
	// KUNIT_EXPECT_EQ(test, 1342177280LL, res.value);

	// res = bw_mul(bw_int_to_fixed(10), bw_int_to_fixed(5));
	// KUNIT_EXPECT_EQ(test, 838860800LL, res.value);

	// res = bw_mul(bw_int_to_fixed(-10), bw_int_to_fixed(7));
	// KUNIT_EXPECT_EQ(test, -1174405120LL, res.value);

	// arg1.value = MAX_I64;
	// arg2.value = MIN_I64;
	// res = bw_mul(arg1, arg2);
	// KUNIT_EXPECT_EQ(test, BW_FIXED_MAX_I32 + 1, res.value);

	// arg1.value = 1;
	// arg2.value = MAX_I64;
	// res = bw_mul(arg1, arg2);
	// KUNIT_EXPECT_EQ(test, BW_FIXED_MAX_I32 + 1, res.value);

	// arg1.value = 1;
	// arg2.value = MIN_I64;
	// res = bw_mul(arg1, arg2);
	// KUNIT_EXPECT_EQ(test, BW_FIXED_MIN_I32, res.value);

	// arg1.value = 0;
	// arg2.value = 0;
	// res = bw_mul(arg1, arg2);
	// KUNIT_EXPECT_EQ(test, 0, res.value);

	// arg1.value = 0;
	// arg2.value = MAX_I64;
	// res = bw_mul(arg1, arg2);
	// KUNIT_EXPECT_EQ(test, 0, res.value);

	// arg1.value = 0;
	// arg2.value = MIN_I64;
	// res = bw_mul(arg1, arg2);
	// KUNIT_EXPECT_EQ(test, 0, res.value);
}

/*
static void dc_fixpt_sqr_test(struct kunit *test)
{
	
}
*/
static void dc_fixpt_recip_test(struct kunit *test)
{
	// recip(v) == from_fraction(1, v)
}
/*
static void dc_fixpt_sinc_test(struct kunit *test)
{
	
}

static void dc_fixpt_cos_test(struct kunit *test)
{
	
}

static void dc_fixpt_exp_test(struct kunit *test)
{
	
}

static void dc_fixpt_log_test(struct kunit *test)
{
	
}
*/
/*
static void dc_fixpt_u4d19_test(struct kunit *test)
{
	
}

static void dc_fixpt_u3d19_test(struct kunit *test)
{
	
}

static void dc_fixpt_u2d19_test(struct kunit *test)
{
	
}

static void dc_fixpt_u0d19_test(struct kunit *test)
{
	
}

static void dc_fixpt_clamp_u0d14_test(struct kunit *test)
{
	
}

static void dc_fixpt_clamp_u0d10_test(struct kunit *test)
{
	
}

static void dc_fixpt_s4d19_test(struct kunit *test)
{
	
}
*/
static struct kunit_case dc_basics_fixpt31_32_test_cases[] = {
	KUNIT_CASE(dc_fixpt_from_fraction_test),
	KUNIT_CASE(dc_fixpt_mul_test),
	/*
	KUNIT_CASE(dc_fixpt_sqr_test),
	*/
	KUNIT_CASE(dc_fixpt_recip_test),
	/*
	KUNIT_CASE(dc_fixpt_sinc_test),
	KUNIT_CASE(dc_fixpt_cos_test),
	KUNIT_CASE(dc_fixpt_exp_test),
	KUNIT_CASE(dc_fixpt_log_test),
	*/
	/*
	KUNIT_CASE(dc_fixpt_u4d19_test),
	KUNIT_CASE(dc_fixpt_u3d19_test),
	KUNIT_CASE(dc_fixpt_u2d19_test),
	KUNIT_CASE(dc_fixpt_u0d19_test),
	KUNIT_CASE(dc_fixpt_clamp_u0d14_test),
	KUNIT_CASE(dc_fixpt_clamp_u0d10_test),
	KUNIT_CASE(dc_fixpt_s4d19_test),
	*/
	{  }
};

static struct kunit_suite dc_basics_fixpt31_32_test_suite = {
	.name = "dc_basics_fixpt31_32",
	.test_cases = dc_basics_fixpt31_32_test_cases,
};

static struct kunit_suite *dc_basics_fixpt31_32_test_suites[] = { &dc_basics_fixpt31_32_test_suite, NULL };


int dc_basics_fixpt31_32_test_init(void)
{
	pr_info("===> Running dc/basics/fixpt31_32 KUnit Tests");
	pr_info("**********************************************************");
	pr_info("**   NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE   **");
	pr_info("**                                                      **");
	pr_info("** dc/basics/fixpt31_32 KUnit Tests are being run.      **");
	pr_info("** This means that this is a TEST kernel and should not **");
	pr_info("** be used for production.                              **");
	pr_info("**                                                      **");
	pr_info("** If you see this message and you are not debugging    **");
	pr_info("** the kernel, report this immediately to your vendor!  **");
	pr_info("**                                                      **");
	pr_info("**********************************************************");

	return __kunit_test_suites_init(dc_basics_fixpt31_32_test_suites);
}

void dc_basics_fixpt31_32_test_exit(void)
{
	__kunit_test_suites_exit(dc_basics_fixpt31_32_test_suites);
}