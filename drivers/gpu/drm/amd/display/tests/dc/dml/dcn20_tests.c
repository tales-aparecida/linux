// SPDX-License-Identifier: MIT
/* KUnit tests for dml/dcn20/
 */

#include <kunit/test.h>
#include "dcn20/dcn20_fpu_test.h"

static void dcn20_cap_soc_clocks_test_to_desc(struct dcn20_cap_soc_clocks_test_case *t, char *desc)
{
	strcpy(desc, t->desc);
}

static void dcn21_update_bw_bounding_box_test_to_desc(struct dcn21_update_bw_bounding_box_test_case *t, char *desc)
{
	strcpy(desc, t->desc);
}

struct dcn20_cap_soc_clocks_test_case dcn20_cap_soc_clocks_test_cases[] = {
	{
		.desc = "4-state bounding box clock limits ",
		.bb = {
			.clock_limits = {
				{
					.dcfclk_mhz = 506.0,
					.fabricclk_mhz = 506.0,
					.dispclk_mhz = 1284.0,
					.dppclk_mhz = 400.0,
					.phyclk_mhz = 810.0,
					.socclk_mhz = 506.0,
					.dscclk_mhz = 428.0,
					.dram_speed_mts = 1600.0,
				},
				{
					.dcfclk_mhz = 540.0,
					.fabricclk_mhz = 540.0,
					.dispclk_mhz = 1284.0,
					.dppclk_mhz = 1284.0,
					.phyclk_mhz = 810.0,
					.socclk_mhz = 540.0,
					.dscclk_mhz = 428.0,
					.dram_speed_mts = 8000.0,
				},
				{
					.dcfclk_mhz = 675.0,
					.fabricclk_mhz = 675.0,
					.dispclk_mhz = 1284.0,
					.dppclk_mhz = 1284.0,
					.phyclk_mhz = 810.0,
					.socclk_mhz = 675.0,
					.dscclk_mhz = 428.0,
					.dram_speed_mts = 10000.0,
				},
				{
					.dcfclk_mhz = 1265.0,
					.fabricclk_mhz = 1266.0,
					.dispclk_mhz = 1284.0,
					.dppclk_mhz = 1284.0,
					.phyclk_mhz = 810.0,
					.socclk_mhz = 1266.0,
					.dscclk_mhz = 428.0,
					.dram_speed_mts = 15000.0,
				},
			},
			.num_states = 4,
		},
		.max_clocks = {
			.dcfClockInKhz = 1265000,
			.uClockInKhz = 875000,
			.fabricClockInKhz = 0,
			.displayClockInKhz = 1284000,
			.dppClockInKhz = 0,
			.phyClockInKhz = 810000,
			.socClockInKhz = 1266000,
			.dscClockInKhz = 0,
		},
		.clock_states = 4,
		.expected_clock_limits = {
			{
				.dcfclk_mhz = 506.0,
				.fabricclk_mhz = 506.0,
				.dispclk_mhz = 1284.0,
				.dppclk_mhz = 400.0,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 506.0,
				.dscclk_mhz = 428.0,
				.dram_speed_mts = 1600.0,
			},
			{
				.dcfclk_mhz = 540.0,
				.fabricclk_mhz = 540.0,
				.dispclk_mhz = 1284.0,
				.dppclk_mhz = 1284.0,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 540.0,
				.dscclk_mhz = 428.0,
				.dram_speed_mts = 8000.0,
			},
			{
				.dcfclk_mhz = 675.0,
				.fabricclk_mhz = 675.0,
				.dispclk_mhz = 1284.0,
				.dppclk_mhz = 1284.0,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 675.0,
				.dscclk_mhz = 428.0,
				.dram_speed_mts = 10000.0,
			},
			{
				.dcfclk_mhz = 1265.0,
				.fabricclk_mhz = 1266.0,
				.dispclk_mhz = 1284.0,
				.dppclk_mhz = 1284.0,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 1266.0,
				.dscclk_mhz = 428.0,
				.dram_speed_mts = 14000.0,
			},
		},
	},
	{
		.desc = "One duplicate clock state",
		.bb = {
			.clock_limits = {
				{
					.dcfclk_mhz = 506.0,
					.fabricclk_mhz = 506.0,
					.dispclk_mhz = 1284.0,
					.dppclk_mhz = 400.0,
					.phyclk_mhz = 810.0,
					.socclk_mhz = 506.0,
					.dscclk_mhz = 428.0,
					.dram_speed_mts = 1600.0,
				},
				{
					.dcfclk_mhz = 675.0,
					.fabricclk_mhz = 675.0,
					.dispclk_mhz = 1284.0,
					.dppclk_mhz = 1284.0,
					.phyclk_mhz = 810.0,
					.socclk_mhz = 675.0,
					.dscclk_mhz = 428.0,
					.dram_speed_mts = 10000.0,
				},
				{
					.dcfclk_mhz = 675.0,
					.fabricclk_mhz = 675.0,
					.dispclk_mhz = 1284.0,
					.dppclk_mhz = 1284.0,
					.phyclk_mhz = 810.0,
					.socclk_mhz = 675.0,
					.dscclk_mhz = 428.0,
					.dram_speed_mts = 10000.0,
				},
				{
					.dcfclk_mhz = 1265.0,
					.fabricclk_mhz = 1266.0,
					.dispclk_mhz = 1284.0,
					.dppclk_mhz = 1284.0,
					.phyclk_mhz = 810.0,
					.socclk_mhz = 1266.0,
					.dscclk_mhz = 428.0,
					.dram_speed_mts = 15000.0,
				},
			},
			.num_states = 4,
		},
		.max_clocks = {
			.dcfClockInKhz = 1265000,
			.uClockInKhz = 875000,
			.fabricClockInKhz = 0,
			.displayClockInKhz = 1284000,
			.dppClockInKhz = 0,
			.phyClockInKhz = 810000,
			.socClockInKhz = 1266000,
			.dscClockInKhz = 0,
		},
		.clock_states = 3,
		.expected_clock_limits = {
			{
				.dcfclk_mhz = 506.0,
				.fabricclk_mhz = 506.0,
				.dispclk_mhz = 1284.0,
				.dppclk_mhz = 400.0,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 506.0,
				.dscclk_mhz = 428.0,
				.dram_speed_mts = 1600.0,
			},
			{
				.dcfclk_mhz = 675.0,
				.fabricclk_mhz = 675.0,
				.dispclk_mhz = 1284.0,
				.dppclk_mhz = 1284.0,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 675.0,
				.dscclk_mhz = 428.0,
				.dram_speed_mts = 10000.0,
			},
			{
				.dcfclk_mhz = 675.0,
				.fabricclk_mhz = 675.0,
				.dispclk_mhz = 1284.0,
				.dppclk_mhz = 1284.0,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 675.0,
				.dscclk_mhz = 428.0,
				.dram_speed_mts = 10000.0,
			},
		},
	},
	{
		.desc = "Zeroed max clocks",
		.bb = {
			.clock_limits = {
				{
					.dcfclk_mhz = 506.0,
					.fabricclk_mhz = 506.0,
					.dispclk_mhz = 1284.0,
					.dppclk_mhz = 400.0,
					.phyclk_mhz = 810.0,
					.socclk_mhz = 506.0,
					.dscclk_mhz = 428.0,
					.dram_speed_mts = 1600.0,
				},
			},
			.num_states = 1,
		},
		.max_clocks = {
			.dcfClockInKhz = 0,
			.uClockInKhz = 0,
			.fabricClockInKhz = 0,
			.displayClockInKhz = 0,
			.dppClockInKhz = 0,
			.phyClockInKhz = 0,
			.socClockInKhz = 0,
			.dscClockInKhz = 0,
		},
		.clock_states = 1,
		.expected_clock_limits = {
			{
				.dcfclk_mhz = 506.0,
				.fabricclk_mhz = 506.0,
				.dispclk_mhz = 1284.0,
				.dppclk_mhz = 400.0,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 506.0,
				.dscclk_mhz = 428.0,
				.dram_speed_mts = 1600.0,
			},
		},
	},
};

KUNIT_ARRAY_PARAM(dcn20_cap_soc_clocks,
	dcn20_cap_soc_clocks_test_cases,
	dcn20_cap_soc_clocks_test_to_desc);

static struct kunit_case dcn20_fpu_test_cases[] = {
	KUNIT_CASE_PARAM(dcn20_cap_soc_clocks_test, dcn20_cap_soc_clocks_gen_params),
	{  }
};

static struct kunit_suite dcn20_fpu_test_suite = {
	.name = "dml_dcn20_fpu",
	.test_cases = dcn20_fpu_test_cases,
};

struct dcn21_update_bw_bounding_box_test_case dcn21_update_bw_bounding_box_test_data[] = {
	{
		.desc = "5-entry bounding box clocks table",
		.dc = {
			.res_pool = &(struct resource_pool) {
				.pipe_count = 2,
				.res_cap = &(struct resource_caps) {
					.num_timing_generator = 3
				},
			},
		},
		.bw_params = {
			.num_channels = 1,
			.clk_table = {
				.entries = {
					{
						.voltage = 0,
						.dcfclk_mhz = 200,
						.fclk_mhz = 400,
						.memclk_mhz = 800,
						.socclk_mhz = 0,
					},
					{
						.voltage = 0,
						.dcfclk_mhz = 201,
						.fclk_mhz = 800,
						.memclk_mhz = 1600,
						.socclk_mhz = 0,
					},
					{
						.voltage = 0,
						.dcfclk_mhz = 553,
						.fclk_mhz = 1067,
						.memclk_mhz = 1067,
						.socclk_mhz = 0,
					},
					{
						.voltage = 0,
						.dcfclk_mhz = 602,
						.fclk_mhz = 1333,
						.memclk_mhz = 1600,
						.socclk_mhz = 0,
					},
					{
						.voltage = 0,
						.dispclk_mhz = 1372,
						.dppclk_mhz = 1372,
						.phyclk_mhz = 810,
						.phyclk_d18_mhz = 667,
						.dtbclk_mhz = 600,
					},
				},

				.num_entries = 5,
			},
		},
		.expected_clock_limits = {
			{
				.state = 0,
				.dcfclk_mhz = 200.0,
				.fabricclk_mhz = 400.0,
				.dispclk_mhz = 600.0,
				.dppclk_mhz = 400.0,
				.phyclk_mhz = 600.0,
				.socclk_mhz = 0.0,
				.dscclk_mhz = 205.67,
				.dram_speed_mts = 1600.0,
			},
			{
				.state = 1,
				.dcfclk_mhz = 200.0,
				.fabricclk_mhz = 400.0,
				.dispclk_mhz = 600.0,
				.dppclk_mhz = 400.0,
				.phyclk_mhz = 600.0,
				.socclk_mhz = 0.0,
				.dscclk_mhz = 205.67,
				.dram_speed_mts = 1600.0,
			},
			{
				.state = 2,
				.dcfclk_mhz = 201,
				.fabricclk_mhz = 800.0,
				.dispclk_mhz = 600.0,
				.dppclk_mhz = 400.0,
				.phyclk_mhz = 600.0,
				.socclk_mhz = 0.0,
				.dscclk_mhz = 205.67,
				.dram_speed_mts = 3200.0,
			},
			{
				.state = 3,
				.dcfclk_mhz = 553.0,
				.fabricclk_mhz = 1067.0,
				.dispclk_mhz = 757.89,
				.dppclk_mhz = 685.71,
				.phyclk_mhz = 600.0,
				.socclk_mhz = 0.0,
				.dscclk_mhz = 287.67,
				.dram_speed_mts = 2134.0,
			},
			{
				.state = 4,
				.dcfclk_mhz = 602.0,
				.fabricclk_mhz = 1333.0,
				.dispclk_mhz = 847.06,
				.dppclk_mhz = 757.89,
				.phyclk_mhz = 600.0,
				.socclk_mhz = 0.0,
				.dscclk_mhz = 318.334,
				.dram_speed_mts = 3200.0,
			},
			{
				.state = 5,
				.dcfclk_mhz = 0.0,
				.fabricclk_mhz = 0.0,
				.dispclk_mhz = 600.0,
				.dppclk_mhz = 400.0,
				.phyclk_mhz = 600.0,
				.socclk_mhz = 0.0,
				.dscclk_mhz = 205.67,
				.dram_speed_mts = 0.0,
			},
			{
				.state = 6,
				.dcfclk_mhz = 0.0,
				.fabricclk_mhz = 0.0,
				.dispclk_mhz = 600.0,
				.dppclk_mhz = 400.0,
				.phyclk_mhz = 600.0,
				.socclk_mhz = 0.0,
				.dscclk_mhz = 205.67,
				.dram_speed_mts = 0.0,
			},
		},
		.clocks_to_compare = 6,
	},
	{
		.desc = "0-entry bounding box clocks table",
		.dc = {
			.res_pool = &(struct resource_pool) {
				.pipe_count = 1,
				.res_cap = &(struct resource_caps) {
					.num_timing_generator = 2
				},
			},
		},
		.bw_params = {
			.num_channels = 3,
			.clk_table = { .num_entries = 0 },
		},
		.expected_clock_limits = {
			{
				.state = 0,
				.dcfclk_mhz = 400.0,
				.fabricclk_mhz = 400.0,
				.dispclk_mhz = 600.0,
				.dppclk_mhz = 400.00,
				.phyclk_mhz = 600.0,
				.socclk_mhz = 278.0,
				.dscclk_mhz = 205.67,
				.dram_speed_mts = 1600.0,
			},
			{
				.state = 1,
				.dcfclk_mhz = 464.52,
				.fabricclk_mhz = 800.0,
				.dispclk_mhz = 654.55,
				.dppclk_mhz = 626.09,
				.phyclk_mhz = 600.0,
				.socclk_mhz = 278.0,
				.dscclk_mhz = 205.67,
				.dram_speed_mts = 1600.0,
			},
			{
				.state = 2,
				.dcfclk_mhz = 514.29,
				.fabricclk_mhz = 933.0,
				.dispclk_mhz = 757.89,
				.dppclk_mhz = 685.71,
				.phyclk_mhz = 600.0,
				.socclk_mhz = 278.0,
				.dscclk_mhz = 287.67,
				.dram_speed_mts = 1866.0,
			},
			{
				.state = 3,
				.dcfclk_mhz = 576.00,
				.fabricclk_mhz = 1067.0,
				.dispclk_mhz = 847.06,
				.dppclk_mhz = 757.89,
				.phyclk_mhz = 600.0,
				.socclk_mhz = 715.0,
				.dscclk_mhz = 318.334,
				.dram_speed_mts = 2134.0,
			},
			{
				.state = 4,
				.dcfclk_mhz = 626.09,
				.fabricclk_mhz = 1200.0,
				.dispclk_mhz = 900.00,
				.dppclk_mhz = 847.06,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 953.0,
				.dscclk_mhz = 489.0,
				.dram_speed_mts = 2400.0,
			},
			{
				.state = 5,
				.dcfclk_mhz = 685.71,
				.fabricclk_mhz = 1333.0,
				.dispclk_mhz = 1028.57,
				.dppclk_mhz = 960.00,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 278.0,
				.dscclk_mhz = 287.67,
				.dram_speed_mts = 2666.0,
			},
			{
				.state = 6,
				.dcfclk_mhz = 757.89,
				.fabricclk_mhz = 1467.0,
				.dispclk_mhz = 1107.69,
				.dppclk_mhz = 1028.57,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 715.0,
				.dscclk_mhz = 318.334,
				.dram_speed_mts = 3200.0,
			},
			{
				.state = 7,
				.dcfclk_mhz = 847.06,
				.fabricclk_mhz = 1600.0,
				.dispclk_mhz = 1395.0,
				.dppclk_mhz = 1285.00,
				.phyclk_mhz = 1325.0,
				.socclk_mhz = 953.0,
				.dscclk_mhz = 489.0,
				.dram_speed_mts = 4266.0,
			},
			{
				.state = 8,
				.dcfclk_mhz = 847.06,
				.fabricclk_mhz = 1600.0,
				.dispclk_mhz = 1395.0,
				.dppclk_mhz = 1285.0,
				.phyclk_mhz = 1325.0,
				.socclk_mhz = 953.0,
				.dscclk_mhz = 489.0,
				.dram_speed_mts = 4266.0,
			},
		},
		.clocks_to_compare = 8,
	},
};

KUNIT_ARRAY_PARAM(dcn21_update_bw_bounding_box,
	dcn21_update_bw_bounding_box_test_data,
	dcn21_update_bw_bounding_box_test_to_desc);

static struct kunit_case dcn20_fpu_dcn21_update_bw_bounding_box_test_cases[] = {
	KUNIT_CASE_PARAM(dcn21_update_bw_bounding_box_test, dcn21_update_bw_bounding_box_gen_params),
	{  }
};

static struct kunit_suite dcn21_update_bw_bounding_box_test_suite = {
	.name = "dml_dcn20_fpu_dcn21_update_bw_bounding_box_test",
	.init = dcn20_fpu_dcn21_update_bw_bounding_box_test_init,
	.exit = dcn20_fpu_dcn21_update_bw_bounding_box_test_exit,
	.test_cases = dcn20_fpu_dcn21_update_bw_bounding_box_test_cases,
};

kunit_test_suites(&dcn20_fpu_test_suite, &dcn21_update_bw_bounding_box_test_suite);

MODULE_LICENSE("Dual MIT/GPL");
