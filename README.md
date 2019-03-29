# baremetal-rpi

This repo contains bare metal examples to run on Raspberry Pi 3B+.

Sample projects in directories starting with a number are compiled with [AArch64 ELF bare-metal target (aarch64-elf) GNU Toolchain](https://developer.arm.com/tools-and-software/open-source-software/gnu-toolchain/gnu-a/downloads).

This repo is complementary to my bare metal programming blog posts at https://metebalci.com .

* c232hm-ddhsl-0.cfg and rpi3.cfg are config files for debugging through JTAG with openocd.
* 99-c232.rules is udev rules (to be copied to /etc/udev/rules.d) that can be used in order to use openocd without sudo.
* You can use a64dis project to disassemble the a64 binaries. It uses [Capstone framework](https://github.com/aquynh/capstone).
