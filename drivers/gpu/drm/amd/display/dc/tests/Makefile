# SPDX-License-Identifier: GPL-2.0-only
#
# Makefile for the KUnit Tests for Display Core files
#

# Build tests as built-in to enable EXPORT_SYMBOL
DC_TESTS = dc_basics_fixpt31_32_test.o
AMD_DC_TESTS = $(addprefix $(AMDDALPATH)/dc/tests/,$(DC_TESTS))
obj-y += $(AMD_DC_TESTS)

# The test suites can be modules, though
obj-$(CONFIG_DC_KUNIT_TEST) += $(AMDDALPATH)/dc/tests/dc_tests.o
