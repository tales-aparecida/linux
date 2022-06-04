/* SPDX-License-Identifier: GPL-2.0 */
#ifndef DML_TEST_H_
#define DML_TEST_H_

#if defined (CONFIG_DISPLAY_MODE_LIB_KUNIT_TEST)
int display_mode_lib_test_init(void);
void display_mode_lib_test_exit(void);
#else
static inline int display_mode_lib_test_init(void) { return 0; }
static inline void display_mode_lib_test_exit(void) { }
#endif

#endif
