// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2020 Joris Offouga <offougajoris@gmail.com>

#include <common.h>
#include <init.h>
#include <environment.h>
#include <mach/bbu.h>
#include <io.h>
#include <mach/imx7-regs.h>
#include <linux/phy.h>
#include <mfd/imx7-iomuxc-gpr.h>
#include <partition.h>

#include <phy-id-list.h>

static int ar8035_phy_fixup(struct phy_device *dev)
{
	u16 val;

	/* To enable AR8031 ouput a 125MHz clk from CLK_25M */
	phy_write(dev, 0xd, 0x7);
	phy_write(dev, 0xe, 0x8016);
	phy_write(dev, 0xd, 0x4007);

	val = phy_read(dev, 0xe);
	val &= 0xffe3;
	val |= 0x18;
	phy_write(dev, 0xe, val);

	/* introduce tx clock delay */
	phy_write(dev, 0x1d, 0x5);
	val = phy_read(dev, 0x1e);
	val |= 0x0100;
	phy_write(dev, 0x1e, val);

	return 0;
}

static void mx7d_pico_init_fec1(void)
{
	void __iomem *gpr = IOMEM(MX7_IOMUXC_GPR_BASE_ADDR);
	uint32_t gpr1;

	gpr1 = readl(gpr + IOMUXC_GPR1);
	gpr1 &= ~(IMX7D_GPR1_ENET1_TX_CLK_SEL_MASK |
		  IMX7D_GPR1_ENET1_CLK_DIR_MASK);
	writel(gpr1, gpr + IOMUXC_GPR1);
}

static int mx7d_pico_coredevices_init(void)
{
	if (!of_machine_is_compatible("technexion,imx7d-pico"))
		return 0;

	mx7d_pico_init_fec1();

	phy_register_fixup_for_uid(0x004dd072, 0xffffffff,
				   ar8035_phy_fixup);

	imx6_bbu_internal_mmc_register_handler("mmc", "/dev/mmc0.boot0.barebox",
					       BBU_HANDLER_FLAG_DEFAULT);

	return 0;
}

coredevice_initcall(mx7d_pico_coredevices_init);
