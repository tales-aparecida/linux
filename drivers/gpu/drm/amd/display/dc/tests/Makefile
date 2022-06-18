# SPDX-License-Identifier: GPL-2.0-only
#
# Makefile for the KUnit Tests for Display Core files
#

DC_TESTS = dc_test.o

ifdef DC_BASICS_FIXPT31_32_KUNIT_TEST
DC_TESTS += dc_basics_fixpt31_32_test.o
endif

AMD_DC_TESTS = $(addprefix $(AMDDALPATH)/dc/basics/tests/,$(DC_TESTS))

AMD_DISPLAY_FILES += $(AMD_DC_TESTS)
