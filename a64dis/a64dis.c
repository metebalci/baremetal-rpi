#include <stdio.h>
#include <inttypes.h>

#include <capstone/capstone.h>

#define ADDRESS_OF_THE_FIRST_INSTRUCTION (0x80000)

int main(int argc, char* argv[]) {

	if (argc != 2) {
		printf("Usage: a64dis <binfile>\n");
		return 1;
	}

	long size = 0;

	FILE* fp = fopen(argv[1], "rb");

	if (fp == NULL) {
		printf("cannot open file\n");
		return 1;
	}

	if (fseek(fp, 0, SEEK_END) != 0) {
		printf("cannot seek end\n");
		fclose(fp);
		return 1;
	}

	size = ftell(fp);

	if (size == -1) {
		printf("cannot tell\n");
		fclose(fp);
		return 1;
	}

	if (fseek(fp, 0, SEEK_SET) != 0) {
		printf("cannot seek set\n");
		fclose(fp);
		return 1;
	}

	void* buffer = malloc(sizeof(uint8_t) * size);

	size_t read = fread(buffer, sizeof(uint8_t), size, fp);

	fclose(fp);

	if (read != size) {
		printf("file size and amount read is different\n");
		free(buffer);
		return 1;
	}

	csh capstone_handle;

	if (cs_open(CS_ARCH_ARM64, CS_MODE_ARM, &capstone_handle) != CS_ERR_OK) {
		return EXIT_FAILURE;
	}

	cs_option(capstone_handle, CS_OPT_DETAIL, CS_OPT_ON);

	cs_insn* instructions;
	size_t count = cs_disasm(capstone_handle, buffer, read, ADDRESS_OF_THE_FIRST_INSTRUCTION, 0, &instructions);

	if (count > 0) {

		for (size_t i = 0; i < count; i++) {

			printf("0x%"PRIx64":\t%s\t\t%s\n", 
					instructions[i].address, 
					instructions[i].mnemonic,
					instructions[i].op_str);

		}

		cs_free(instructions, count);

	} else {

		fprintf(stderr, "Failed to disassemble!\n");

	}

	cs_close(&capstone_handle);

	free(buffer);

	return EXIT_SUCCESS;

}
