// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2020 Joris Offouga <offougajoris@gmail.com>

#include <io.h>
#include <common.h>
#include <mach/generic.h>
#include <asm/barebox-arm-head.h>
#include <asm/barebox-arm.h>
#include <asm/cache.h>
#include <mach/esdctl.h>

extern char __dtb_imx7d_pico_start[];

ENTRY_FUNCTION(start_imx7d_pico, r0, r1, r2)
{
	imx7_cpu_lowlevel_init();

	imx7d_barebox_entry(__dtb_imx7d_pico_start + get_runtime_offset());

}
