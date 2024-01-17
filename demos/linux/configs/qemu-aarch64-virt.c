// demos/linux+freertos/configs/qemu-aarch64-virt.c
#include <config.h>

VM_IMAGE(linux_image, XSTR(BAO_DEMOS_WRKDIR_IMGS/linux.bin));

struct config config = { 
    
    CONFIG_HEADER

    .shmemlist_size = 1,
    .shmemlist = (struct shmem[]) {
        [0] = { .size = 0x00010000, }
    },  

    .vmlist_size = 1,
    .vmlist = { 
        {
            .image = {
                .base_addr = 0x60000000,
                .load_addr = VM_IMAGE_OFFSET(linux_image),
                .size = VM_IMAGE_SIZE(linux_image)
            },

            .entry = 0x60000000,
            
            .platform = {
                .cpu_num = 2,

                .region_num = 1,
                .regions =  (struct vm_mem_region[]) {
                    {
                        .base = 0x60000000,
                        .size = 0x20000000,
                    }
                },

                .ipc_num = 1,
                .ipcs = (struct ipc[]) {
                    {
                        .base = 0xf0000000,
                        .size = 0x00010000,
                        .shmem_id = 0,
                        .interrupt_num = 1,
                        .interrupts = (irqid_t[]) {52}
                    }
                },

                .dev_num = 2,
                .devs =  (struct vm_dev_region[]) {
                    {
                        /* PL011 */
                        .pa = 0x9000000,
                        .va = 0xff000000,
                        .size = 0x10000,
                        .interrupt_num = 1,
                        .interrupts = (irqid_t[]) {33}
                    },
                    {
                        /* Arch timer interrupt */
                        .interrupt_num = 1,
                        .interrupts = (irqid_t[]) {27}
                    },
                },
                
                .arch = {
                    .gic = {
                       .gicd_addr = 0x8000000,
                       .gicr_addr = 0x80A0000
                    }
                }
            },
        },

    },
};
