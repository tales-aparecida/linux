// SPDX-License-Identifier: MIT

#include <drm/drm_util.h>
#include <kunit/test.h>
#include "os_types.h"
#include "include/fixed31_32.h"

extern void dc_fixpt_from_int_test(struct kunit *test);
extern void dc_fixpt_from_fraction_test(struct kunit *test);
extern void dc_fixpt_mul_test(struct kunit *test);
extern void dc_fixpt_recip_test(struct kunit *test);
extern void dc_fixpt_sqr_test(struct kunit *test);
