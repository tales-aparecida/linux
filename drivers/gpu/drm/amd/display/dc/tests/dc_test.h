/* SPDX-License-Identifier: GPL-2.0 */
#ifndef DC_TEST_H_
#define DC_TEST_H_

#if defined (DC_FIXPT31_32_KUNIT_TEST)
int dc_basics_fixpt31_32_test_init(void);
void dc_basics_fixpt31_32_test_exit(void);
#else
static inline int dc_basics_fixpt31_32_test_init(void) { return 0; }
static inline void dc_basics_fixpt31_32_test_exit(void) { }
#endif

#endif /* DC_TEST_H_ */
