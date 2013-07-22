/*
 * Atmel SAM3N Peripherals (Cortex-M3)
 *
 * Copyright (c) 2013 Ingenieurbuero Weinhardt.
 * Author: Joerg Weinhardt
 *
 * This code is licensed under the GPL.
 */

#include "hw/boards.h"

static void sam3n_init(const char *kernel_filename, const char *cpu_model)
{
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

