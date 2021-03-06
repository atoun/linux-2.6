/*
 * (C) Copyright 2007
 *     Theobroma Systems <www.theobroma-systems.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * Partially based on
 *
 * linux/arch/m68knommu/kernel/setup.c
 */

/*
 * This file handles the architecture-dependent parts of system setup
 */

#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <linux/fb.h>
#include <linux/module.h>
#include <linux/console.h>
#include <linux/genhd.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/platform_device.h>
#include <linux/major.h>
#include <linux/initrd.h>
#include <linux/bootmem.h>
#include <linux/seq_file.h>
#include <linux/root_dev.h>
#include <linux/init.h>
#include <linux/linkage.h>

#include <asm/setup.h>
#include <asm/irq.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/thread_info.h>
#include <asm/sections.h>

unsigned int kernel_mode = PT_MODE_KERNEL;

/* this is set first thing as the kernel is started
 * from the arguments to the kernel. */
unsigned long asmlinkage _kernel_arg_cmdline; /* address of the commandline parameters */
unsigned long asmlinkage _kernel_arg_initrd_start;
unsigned long asmlinkage _kernel_arg_initrd_end;

static char __initdata cmd_line[COMMAND_LINE_SIZE];

extern void setup_early_printk(void);


/* from mm/init.c */
extern void bootmem_init(void);
extern void paging_init(void);

unsigned int cpu_frequency;
//unsigned int sdram_start;
//unsigned int sdram_size;

void __init machine_early_init(char *cmdline, unsigned long p_initrd_start,
		unsigned long p_initrd_end)
{
	/* clear bss section */
	memset(__bss_start, 0, __bss_stop - __bss_start);

#ifndef CONFIG_CMDLINE_BOOL
	if (cmdline) {
		strlcpy(cmd_line, cmdline, COMMAND_LINE_SIZE);
	}
#else
	strlcpy(cmd_line, CONFIG_CMDLINE, COMMAND_LINE_SIZE);
#endif
	initrd_start = p_initrd_start;
	initrd_end = p_initrd_end;
}

void __init setup_arch(char **cmdline_p)
{
	/*
	 * init "current thread structure" pointer
	 */
	lm32_current_thread = (struct thread_info*)&init_thread_union;

	cpu_frequency = (unsigned long)CONFIG_CPU_CLOCK;
	//sdram_start = (unsigned long)CONFIG_MEMORY_START;
	//sdram_size = (unsigned long)CONFIG_MEMORY_SIZE;

	/* Save unparsed command line copy for /proc/cmdline */
	memcpy(boot_command_line, *cmdline_p, COMMAND_LINE_SIZE);
	*cmdline_p = cmd_line;

#ifdef CONFIG_DUMMY_CONSOLE
	conswitchp = &dummy_con;
#endif

#ifdef CONFIG_EARLY_PRINTK
	setup_early_printk();
#endif

	/*
	 * Init boot memory
	 */
	bootmem_init();

	/*
	 * Get kmalloc into gear.
	 */
	paging_init();
}

/*
 *	Get CPU information for use by the procfs.
 */

static int show_cpuinfo(struct seq_file *m, void *v)
{
    char *cpu, *mmu, *fpu;
    u_long clockfreq;

    cpu = "lm32";
    mmu = "none";
    fpu = "none";

    clockfreq = (loops_per_jiffy*HZ)*5/4;

    seq_printf(m, "CPU:\t\t%s\n"
		   "MMU:\t\t%s\n"
		   "FPU:\t\t%s\n"
		   "Clocking:\t%lu.%1luMHz\n"
		   "BogoMips:\t%lu.%02lu\n"
		   "Calibration:\t%lu loops\n",
		   cpu, mmu, fpu,
		   clockfreq/1000000,(clockfreq/100000)%10,
		   (loops_per_jiffy*HZ)/500000,((loops_per_jiffy*HZ)/5000)%100,
		   (loops_per_jiffy*HZ));

	return 0;
}

static void *c_start(struct seq_file *m, loff_t *pos)
{
	return *pos < NR_CPUS ? (void *)(*pos + 1) : NULL;
}

static void *c_next(struct seq_file *m, void *v, loff_t *pos)
{
	++*pos;
	return c_start(m, pos);
}

static void c_stop(struct seq_file *m, void *v)
{
}

const struct seq_operations cpuinfo_op = {
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo,
};
