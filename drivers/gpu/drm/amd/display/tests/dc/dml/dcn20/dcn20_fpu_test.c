// SPDX-License-Identifier: MIT
/*
 * KUnit tests for dml/dcn20/dcn20_fpu.h
 *
 * Copyright (C) 2022, Magali Lemes <magalilemes00@gmail.com>
 */

#include "dcn20_fpu_test.h"

/**
 * DOC: Unit tests for AMDGPU DML dcn20/dcn20_fpu.h
 */

/**
 * dcn20_cap_soc_clocks_test - KUnit test for dcn20_cap_soc_clocks
 * @test: represents a running instance of a test.
 */
void dcn20_cap_soc_clocks_test(struct kunit *test)
{
	struct dcn20_cap_soc_clocks_test_case *test_param =
		(struct dcn20_cap_soc_clocks_test_case *)test->param_value;
	int i;

	DC_FP_START();
	dcn20_cap_soc_clocks(&test_param->bb, test_param->max_clocks);
	DC_FP_END();

	/* Check if no clock limit is higher than the specified maximum */
	for (i = 0; i < test_param->bb.num_states; i++) {
		KUNIT_EXPECT_EQ(test, test_param->bb.clock_limits[i].dcfclk_mhz,
				test_param->expected_clock_limits[i].dcfclk_mhz);
		KUNIT_EXPECT_EQ(test, test_param->bb.clock_limits[i].fabricclk_mhz,
				test_param->expected_clock_limits[i].fabricclk_mhz);
		KUNIT_EXPECT_EQ(test, test_param->bb.clock_limits[i].dispclk_mhz,
				test_param->expected_clock_limits[i].dispclk_mhz);
		KUNIT_EXPECT_EQ(test, test_param->bb.clock_limits[i].dppclk_mhz,
				test_param->expected_clock_limits[i].dppclk_mhz);
		KUNIT_EXPECT_EQ(test, test_param->bb.clock_limits[i].phyclk_mhz,
				test_param->expected_clock_limits[i].phyclk_mhz);
		KUNIT_EXPECT_EQ(test, test_param->bb.clock_limits[i].socclk_mhz,
				test_param->expected_clock_limits[i].socclk_mhz);
		KUNIT_EXPECT_EQ(test, test_param->bb.clock_limits[i].dscclk_mhz,
				test_param->expected_clock_limits[i].dscclk_mhz);
		KUNIT_EXPECT_EQ(test, test_param->bb.clock_limits[i].dram_speed_mts,
				test_param->expected_clock_limits[i].dram_speed_mts);
	}

	KUNIT_EXPECT_EQ(test, test_param->clock_states, test_param->bb.num_states);
}
EXPORT_SYMBOL_FOR_TESTS_ONLY(dcn20_cap_soc_clocks_test);

static struct _vcs_dpi_soc_bounding_box_st original_dcn2_1_soc;
static struct _vcs_dpi_ip_params_st original_dcn2_1_ip;

int dcn20_fpu_dcn21_update_bw_bounding_box_test_init(struct kunit *test)
{
	/* Store original dcn2_1_soc dcn2_1_ip and in a temporary struct */
	memcpy(&original_dcn2_1_soc, &dcn2_1_soc, sizeof(struct _vcs_dpi_soc_bounding_box_st));
	memcpy(&original_dcn2_1_ip, &dcn2_1_ip, sizeof(struct _vcs_dpi_ip_params_st));

	return 0;
}
EXPORT_SYMBOL_FOR_TESTS_ONLY(dcn20_fpu_dcn21_update_bw_bounding_box_test_init);

void dcn20_fpu_dcn21_update_bw_bounding_box_test_exit(struct kunit *test)
{
	/* Restore original dcn2_1_soc and dcn2_1_ip */
	memcpy(&dcn2_1_soc, &original_dcn2_1_soc, sizeof(struct _vcs_dpi_soc_bounding_box_st));
	memcpy(&dcn2_1_ip, &original_dcn2_1_ip, sizeof(struct _vcs_dpi_ip_params_st));
}
EXPORT_SYMBOL_FOR_TESTS_ONLY(dcn20_fpu_dcn21_update_bw_bounding_box_test_exit);

/**
 * dcn21_update_bw_bounding_box_test - KUnit test for dcn21_update_bw_bounding_box
 * @test: represents a running instance of a test.
 */
void dcn21_update_bw_bounding_box_test(struct kunit *test)
{
	struct dcn21_update_bw_bounding_box_test_case *test_param =
		(struct dcn21_update_bw_bounding_box_test_case *)test->param_value;
	int i;

	DC_FP_START();
	dcn21_update_bw_bounding_box(&test_param->dc, &test_param->bw_params);
	DC_FP_END();

	KUNIT_EXPECT_EQ(test, test_param->dc.res_pool->res_cap->num_timing_generator,
			dcn2_1_ip.max_num_otg);
	KUNIT_EXPECT_EQ(test, test_param->dc.res_pool->pipe_count, dcn2_1_ip.max_num_dpp);
	KUNIT_EXPECT_EQ(test, test_param->bw_params.num_channels, dcn2_1_soc.num_chans);

	for (i = 0; i <= test_param->clocks_to_compare; i++) {
		KUNIT_EXPECT_EQ(test, test_param->expected_clock_limits[i].state,
				dcn2_1_soc.clock_limits[i].state);
		KUNIT_EXPECT_EQ(test, test_param->expected_clock_limits[i].dcfclk_mhz,
				dcn2_1_soc.clock_limits[i].dcfclk_mhz);
		KUNIT_EXPECT_EQ(test, test_param->expected_clock_limits[i].fabricclk_mhz,
				dcn2_1_soc.clock_limits[i].fabricclk_mhz);
		KUNIT_EXPECT_EQ(test, test_param->expected_clock_limits[i].dispclk_mhz,
				dcn2_1_soc.clock_limits[i].dispclk_mhz);
		KUNIT_EXPECT_EQ(test, test_param->expected_clock_limits[i].dppclk_mhz,
				dcn2_1_soc.clock_limits[i].dppclk_mhz);
		KUNIT_EXPECT_EQ(test, test_param->expected_clock_limits[i].phyclk_mhz,
				dcn2_1_soc.clock_limits[i].phyclk_mhz);
		KUNIT_EXPECT_EQ(test, test_param->expected_clock_limits[i].socclk_mhz,
				dcn2_1_soc.clock_limits[i].socclk_mhz);
		KUNIT_EXPECT_EQ(test, test_param->expected_clock_limits[i].dscclk_mhz,
				dcn2_1_soc.clock_limits[i].dscclk_mhz);
		KUNIT_EXPECT_EQ(test, test_param->expected_clock_limits[i].dram_speed_mts,
				dcn2_1_soc.clock_limits[i].dram_speed_mts);
	}

	if (test_param->bw_params.clk_table.num_entries)
		KUNIT_EXPECT_EQ(test, test_param->bw_params.clk_table.num_entries,
				dcn2_1_soc.num_states);
}
EXPORT_SYMBOL_FOR_TESTS_ONLY(dcn21_update_bw_bounding_box_test);
