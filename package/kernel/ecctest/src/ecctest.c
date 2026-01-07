#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/clk.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/mod_devicetable.h>
#include <linux/delay.h>

#define DRIVER_AUTHOR "Your Name <your.email@example.com>"
#define DRIVER_DESC   "A simple hello world kernel module"

#define	DATA_ERR_INJECT_LO 0x00
#define	DATA_ERR_INJECT_HI 0x04
#define ERR_DETECT 	0x40
#define ERR_SBE 	0x58
#define ADDR_ERR_INJ 	0x0C
#define ERR_INJECT 	0x08

uint32_t run_sbe_data_err_inj_test(uint32_t startAddr)
{
    printk("Testing data error injection method\n\r");

    uint32_t sbetOriginal;
    uint32_t sbetForTest = 0x2;
    uint32_t failCount = 0;
    uint32_t i;

    u32 val = 0;
    void __iomem *base;
    void __iomem *base_mem;
    base = ioremap(0x4e301100, 0x64);
    base_mem = ioremap(startAddr, 0x320);

    sbetOriginal = (readl(base + ERR_SBE) >> 16) & 0xFF;

    writel((sbetForTest << 16), base + ERR_SBE);

    writel(0x8000000D, base + ERR_DETECT);

    writel(0x00000001, base + DATA_ERR_INJECT_LO);

    val = readl(base + ERR_INJECT);
    val |= 0x00002000;
    writel(val, base + ERR_INJECT);

    val = readl(base + ERR_INJECT);
    val |= 0x00000100;
    writel(val, base + ERR_INJECT);

    asm("DSB sy");

    for (i = 0; i < 0x800; i += 8)
        writel((uint32_t)(base_mem + i), base_mem + i);

    asm("DSB sy");

    writel(0x00000000, base + ERR_INJECT);

    asm("DSB sy");

    for (i = 0; i < 0x800; i += 8) {
        if (readl(base_mem + i) != (uint32_t)(base_mem + i)) {
            printk("**FAIL! Memory read failed!\n\r");
            printk("  data: 0x%x\n\r", (uint32_t)base_mem + i);
            failCount++;
            break;
        }
    }

    asm("DSB sy");

    if (failCount == 0)
        printk("Memory read passed after single-bit error injection \n\r");

    if (((readl(base + ERR_DETECT)) & 0x4) != 0x4) {
        printk("**FAIL! Single bit error test failed \n\r");
        printk(" ERR_DETECT: 0x%08X\n\r", readl(base + ERR_DETECT));
        printk(" ERR_SBE: 0x%08X \n\r", readl(base + ERR_SBE));
        failCount++;
    } else {
        printk("ECC error detect passed! \n\r");
        printk("ERR_DETECT: 0x%08X \n\r", readl(base + ERR_DETECT));
    }

    writel(0x8000000D, (base + ERR_DETECT));

    if (((readl(base + ERR_DETECT)) & 0x4) == 0x4) {
        printk("**FAIL! ERR_DETECT not properly cleared\n\r");
        printk("ERR_DETECT=0x%08X\n\r", readl(base + ERR_DETECT));
        failCount++;
    }

    writel((sbetOriginal << 16), base + ERR_SBE);

    if (failCount != 0)
        return 1;

    return 0;
}

uint32_t run_sbe_addr_err_inj_test(uint32_t addr)
{
    printk("Testing address error injection method\n\r");

    uint32_t readData;
    uint32_t sbetOriginal;
    uint32_t sbetForTest = 0x1;
    uint32_t failCount = 0;
    void __iomem *base;
    void __iomem *base_mem;
    base = ioremap(0x4e301100, 0x64);
    base_mem = ioremap(addr, 0x4);

    writel(0x8000000D, base + ERR_DETECT);

    sbetOriginal = (readl(base + ERR_SBE) >> 16) & 0xFF;

    writel((sbetForTest << 16), base + ERR_SBE);

    writel(addr, base + ADDR_ERR_INJ);

    writel(0x80600100, base + ERR_INJECT);

    writel(0x12345678, base_mem);

    asm("DSB sy");

    readData = readl(base_mem);

    asm("DSB sy");
    if (readData != 0x12345678) {
        printk("**FAIL! Memory read failed!\n\r");
        printk("  data: 0x%x\n\r", readData);
        failCount++;
    } else {
        printk("Memory read passed after single-bit error injection \n\r");
    }

    if (((readl(base + ERR_DETECT)) & 0x4) != 0x4) {
        printk("**FAIL! Single bit error test failed \n\r");
        printk("  ERR_DETECT: 0x%08X\n\r", readl(base + ERR_DETECT));
        printk("  ERR_SBE: 0x%08X \n\r", readl(base + ERR_SBE));
        failCount++;
    } else {
        printk("  ECC error detect passed! \n\r");
    }

    writel(0x00000000, base + ERR_INJECT);

    writel(0x8000000D, (base + ERR_DETECT));

    if (((readl(base + ERR_DETECT)) & 0x4) == 0x4) {
        printk("**FAIL! ERR_DETECT not properly cleared\n\r");
        printk("ERR_DETECT=0x%08X\n\r", readl(base + ERR_DETECT));
        failCount++;
    }

    writel((sbetOriginal << 16), base + ERR_SBE);

    if (failCount != 0)
        return 1;

    return 0;
}

static int __init ecctest_init(void)
{
    pr_info("=================================\n");
    pr_info("ECC test from kernel module!\n");
    pr_info("Module loaded successfully\n");
    run_sbe_addr_err_inj_test(0xb6000000);
    pr_info("=================================\n");
    return 0;
}

static void __exit ecctest_exit(void)
{
    pr_info("=================================\n");
    pr_info("Goodbye from kernel module!\n");
    pr_info("Module unloaded successfully\n");
    pr_info("=================================\n");
}

module_init(ecctest_init);
module_exit(ecctest_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION("1.0.0");
