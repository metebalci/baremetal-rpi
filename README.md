# baremetal-rpi

This repo contains bare metal source codes to run on Raspberry Pi 3B+.

They are compiled with [AArch64 ELF bare-metal target (aarch64-elf) GNU Toolchain](https://developer.arm.com/tools-and-software/open-source-software/gnu-toolchain/gnu-a/downloads).

These are used in my bare metal programming blog posts at https://metebalci.com

c232hm-ddhsl-0.cfg and rpi3.cfg are config files for debugging through JTAG with openocd.

99-c232.rules is udev rules (to be copied to /etc/udev/rules.d) to use openocd without sudo.

You can use a64dis project to disassemble the a64 binaries. It uses [Capstone framework](https://github.com/aquynh/capstone).
