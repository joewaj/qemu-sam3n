/*
 * Atmel SAM3N Peripherals (Cortex-M3)
 *
 * Copyright (c) 2013 Ingenieurbuero Weinhardt.
 * Author: Joerg Weinhardt
 *
 * This code is licensed under the GPL.
 */

#include "hw/boards.h"
#include "exec/address-spaces.h"
#include "hw/arm/arm.h"

static void sam3n_init(const char *kernel_filename, const char *cpu_model)
{
    qemu_irq *pic;
    int      sram_size;
    int      flash_size;

    sram_size  = 8;  /* in kB? */
    flash_size = 32; /* in kB? */

    MemoryRegion *address_space_mem = get_system_memory();

    pic = armv7m_init(address_space_mem,
                     flash_size, sram_size, kernel_filename, cpu_model);

    pic = pic; // to prevent compiler complaints

    fprintf(stderr, "sam3n_init:\n");
}

static void sam3n1b_init(QEMUMachineInitArgs *args)
{
    const char *cpu_model = args->cpu_model;
    const char *kernel_filename = args->kernel_filename;
    sam3n_init(kernel_filename, cpu_model);
}

static QEMUMachine sam3n1b_machine = {
    .name = "sam3n1b",
    .desc = "Atmel SAM3N1B",
    .init = sam3n1b_init,
    DEFAULT_MACHINE_OPTIONS,
};

static void sam3n_machine_init(void)
{
    qemu_register_machine(&sam3n1b_machine);
}

machine_init(sam3n_machine_init);

