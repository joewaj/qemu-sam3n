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


static uint64_t int_per_read(void *opaque, hwaddr offset,
                          unsigned size)
{
//    ssys_state *s = (ssys_state *)opaque;

    fprintf(stderr, "sam3n int_per_read: %ld\n", (long) offset);

    return 0;
}

static void int_per_write(void *opaque, hwaddr offset,
                       uint64_t value, unsigned size)
{
   fprintf(stderr, "sam3n int_per_write: %ld\n", (long) offset);
}

static const MemoryRegionOps int_peripheral_ops = {
    .read = int_per_read,
    .write = int_per_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void sam3n_init(const char *kernel_filename, const char *cpu_model)
{
    qemu_irq      *pic;
    int           sram_size;
    int           flash_size;
    MemoryRegion  IoMem;

    sram_size  = 8;  /* in kB? */
    flash_size = 32; /* in kB? */

    fprintf(stderr, "sam3n_init: 1\n");

    MemoryRegion *address_space_mem = get_system_memory();

    pic = armv7m_init(address_space_mem,
                     flash_size, sram_size, kernel_filename, cpu_model);

    pic = pic; // to prevent compiler complaints

    // Create and initialze the internal peripherals
    memory_region_init_io(&IoMem, NULL, &int_peripheral_ops, NULL, "peripheral", 0x00100000);
    memory_region_add_subregion(get_system_memory(), 0x40000000, &IoMem);

    fprintf(stderr, "sam3n_init: 2\n");
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

