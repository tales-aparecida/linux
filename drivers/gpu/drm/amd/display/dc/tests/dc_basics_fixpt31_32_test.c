// SPDX-License-Identifier: MIT
/* Unit tests for dc/basics/fixpt31_32.c
 */

#include "dc_basics_fixpt31_32_test.h"
#include "fixed31_32.h"
#include "vdso/limits.h"

static const struct fixed31_32 dc_fixpt_minus_one = { -0x100000000LL };

void dc_fixpt_from_int_test(struct kunit *test)
{
	struct fixed31_32 res;

	res = dc_fixpt_from_int(0);
	KUNIT_EXPECT_EQ(test, res.value, dc_fixpt_zero.value);

	res = dc_fixpt_from_int(1);
	KUNIT_EXPECT_EQ(test, res.value, dc_fixpt_one.value);

	res = dc_fixpt_from_int(-1);
	KUNIT_EXPECT_EQ(test, res.value, -dc_fixpt_one.value);

	res = dc_fixpt_from_int(INT_MAX);
	KUNIT_EXPECT_EQ(test, res.value, 0x7FFFFFFF00000000LL);

	res = dc_fixpt_from_int(INT_MIN);
	KUNIT_EXPECT_EQ(test, res.value, 0x8000000000000000LL); /* implicit negative signal */
}
EXPORT_SYMBOL(dc_fixpt_from_int_test);

void dc_fixpt_from_fraction_test(struct kunit *test)
{
	struct fixed31_32 res;

	/* Assert signal works as expected */
	res = dc_fixpt_from_fraction(1LL, 1LL);
	KUNIT_EXPECT_EQ(test, res.value, dc_fixpt_one.value);

	res = dc_fixpt_from_fraction(-1LL, 1LL);
	KUNIT_EXPECT_EQ(test, res.value, -dc_fixpt_one.value);

	res = dc_fixpt_from_fraction(1LL, -1LL);
	KUNIT_EXPECT_EQ(test, res.value, -dc_fixpt_one.value);

	res = dc_fixpt_from_fraction(-1LL, -1LL);
	KUNIT_EXPECT_EQ(test, res.value, dc_fixpt_one.value);

	/* Assert that the greatest parameter values works as expected */
	res = dc_fixpt_from_fraction(LLONG_MAX, LLONG_MAX);
	KUNIT_EXPECT_EQ(test, res.value, dc_fixpt_one.value);

	res = dc_fixpt_from_fraction(LLONG_MIN, LLONG_MIN);
	KUNIT_EXPECT_EQ(test, res.value, dc_fixpt_one.value);

	/* Edge case using the smallest fraction possible without LSB rounding */
	res = dc_fixpt_from_fraction(1, 1LL << (FIXED31_32_BITS_PER_FRACTIONAL_PART));
	KUNIT_EXPECT_EQ(test, res.value, dc_fixpt_epsilon.value);

	/* Edge case using the smallest fraction possible with LSB rounding */
	res = dc_fixpt_from_fraction(1, 1LL << (FIXED31_32_BITS_PER_FRACTIONAL_PART + 1));
	KUNIT_EXPECT_EQ(test, res.value, dc_fixpt_epsilon.value);

	/* Assert an nil numerator is a valid input */
	res = dc_fixpt_from_fraction(0LL, LLONG_MAX);
	KUNIT_EXPECT_EQ(test, res.value, 0LL);

	/* Edge case using every bit of the decimal part without rounding */
	res = dc_fixpt_from_fraction(8589934590LL, 8589934592LL);
	KUNIT_EXPECT_EQ(test, res.value, 0x0FFFFFFFFLL);

	res = dc_fixpt_from_fraction(-8589934590LL, 8589934592LL);
	KUNIT_EXPECT_EQ(test, res.value, -0x0FFFFFFFFLL);

	/* Edge case using every bit of the decimal part then rounding LSB */
	res = dc_fixpt_from_fraction(8589934591LL, 8589934592LL);
	KUNIT_EXPECT_EQ(test, res.value, dc_fixpt_one.value);

	res = dc_fixpt_from_fraction(-8589934591LL, 8589934592LL);
	KUNIT_EXPECT_EQ(test, res.value, -dc_fixpt_one.value);
	/*  A repeating decimal in binary representation that doesn't round up the LSB */
	res = dc_fixpt_from_fraction(4, 3);
	KUNIT_EXPECT_EQ(test, res.value, 0x0000000155555555LL);

	res = dc_fixpt_from_fraction(-4, 3);
	KUNIT_EXPECT_EQ(test, res.value, -0x0000000155555555LL);

	/* A repeating decimal in binary representation that rounds up the LSB */
	res = dc_fixpt_from_fraction(5, 3);
	KUNIT_EXPECT_EQ(test, res.value, 0x00000001AAAAAAABLL);

	res = dc_fixpt_from_fraction(-5, 3);
	KUNIT_EXPECT_EQ(test, res.value, -0x00000001AAAAAAABLL);
}
EXPORT_SYMBOL(dc_fixpt_from_fraction_test);

void dc_fixpt_mul_test(struct kunit *test)
{
	struct fixed31_32 res;
	struct fixed31_32 arg;

	/* Assert signal works as expected */
	res = dc_fixpt_mul(dc_fixpt_one, dc_fixpt_one);
	KUNIT_EXPECT_EQ(test, res.value, dc_fixpt_one.value);

	res = dc_fixpt_mul(dc_fixpt_minus_one, dc_fixpt_one);
	KUNIT_EXPECT_EQ(test, res.value, dc_fixpt_minus_one.value);

	res = dc_fixpt_mul(dc_fixpt_one, dc_fixpt_minus_one);
	KUNIT_EXPECT_EQ(test, res.value, dc_fixpt_minus_one.value);

	res = dc_fixpt_mul(dc_fixpt_minus_one, dc_fixpt_minus_one);
	KUNIT_EXPECT_EQ(test, res.value, dc_fixpt_one.value);

	/* Assert that the greatest parameter values works as expected */
	arg.value = LONG_MAX;
	res = dc_fixpt_mul(arg, dc_fixpt_one);
	KUNIT_EXPECT_EQ(test, res.value, arg.value);

	arg.value = LONG_MIN;
	res = dc_fixpt_mul(arg, dc_fixpt_one);
	KUNIT_EXPECT_EQ(test, res.value, arg.value);

	arg.value = LONG_MAX;
	res = dc_fixpt_mul(dc_fixpt_one, arg);
	KUNIT_EXPECT_EQ(test, res.value, arg.value);

	arg.value = LONG_MIN;
	res = dc_fixpt_mul(dc_fixpt_one, arg);
	KUNIT_EXPECT_EQ(test, res.value, arg.value);

	/* Assert it doesn't round LSB as expected */
	arg.value = 0x7FFFFFFF7fffffffLL;
	res = dc_fixpt_mul(arg, dc_fixpt_epsilon);
	KUNIT_EXPECT_EQ(test, res.value, 0x000000007FFFFFFF);

	/* Assert it rounds LSB as expected */
	arg.value = 0x7FFFFFFF80000000LL;
	res = dc_fixpt_mul(arg, dc_fixpt_epsilon);
	KUNIT_EXPECT_EQ(test, res.value, 0x0000000080000000);
}
EXPORT_SYMBOL(dc_fixpt_mul_test);

void dc_fixpt_sqr_test(struct kunit *test)
{
	struct fixed31_32 res;
	struct fixed31_32 arg;

	arg.value = dc_fixpt_one.value;
	res = dc_fixpt_sqr(arg);
	KUNIT_EXPECT_EQ(test, res.value, dc_fixpt_one.value);

	arg.value = dc_fixpt_minus_one.value;
	res = dc_fixpt_sqr(arg);
	KUNIT_EXPECT_EQ(test, res.value, dc_fixpt_one.value);

	arg.value = 0;
	res = dc_fixpt_sqr(arg);
	KUNIT_EXPECT_EQ(test, res.value, 0);

	/* Test some recognizable values */
	arg = dc_fixpt_from_int(100);
	res = dc_fixpt_sqr(arg);
	KUNIT_EXPECT_EQ(test, res.value, dc_fixpt_from_int(10000).value);

	arg = dc_fixpt_from_fraction(1, 100);
	res = dc_fixpt_sqr(arg);
	KUNIT_EXPECT_EQ(test, res.value, dc_fixpt_from_fraction(1, 10000).value);

	/* LSB rounding */
	arg = dc_fixpt_from_fraction(3, 2);
	res = dc_fixpt_sqr(arg);
	KUNIT_EXPECT_EQ(test, res.value, dc_fixpt_from_fraction(9, 4).value + 1LL);
}
EXPORT_SYMBOL(dc_fixpt_sqr_test);

void dc_fixpt_recip_test(struct kunit *test)
{
	struct fixed31_32 res;
	struct fixed31_32 arg;

	/* Assert 1/1 works as expected */
	res = dc_fixpt_recip(dc_fixpt_one);
	KUNIT_EXPECT_EQ(test, res.value, dc_fixpt_one.value);

	/* Assert smallest parameters works as expected. */
	arg.value = 3LL;
	res = dc_fixpt_recip(arg);
	KUNIT_EXPECT_EQ(test, res.value, 0x5555555555555555LL);

	arg.value = -3LL;
	res = dc_fixpt_recip(arg);
	KUNIT_EXPECT_EQ(test, res.value, -0x5555555555555555LL);
}
EXPORT_SYMBOL(dc_fixpt_recip_test);
