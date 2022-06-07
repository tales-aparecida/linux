# SPDX-License-Identifier: GPL-2.0-only
#
# Makefile for the KUnit Tests for DML
#

DML_TESTS = dml_test.o

ifdef CONFIG_BW_FIXED_KUNIT_TEST
DML_TESTS += calcs/bw_fixed_test.o
endif

ifdef CONFIG_DISPLAY_MODE_LIB_KUNIT_TEST
DML_TESTS += display_mode_lib_test.o
endif

AMD_DAL_DML_TESTS = $(addprefix $(AMDDALPATH)/amdgpu_dm/tests/,$(DML_TESTS))

AMD_DISPLAY_FILES += $(AMD_DAL_DML_TESTS)
