#include <stdio.h>
#include <inttypes.h>

#include <capstone/capstone.h>

#define MAX_STDIN_BUFFER (1 << 24) // 16 MB
#define ADDRESS_OF_THE_FIRST_INSTRUCTION (0x80000)

int main(void) {

  uint8_t* buffer = (uint8_t*) calloc(sizeof(uint8_t), MAX_STDIN_BUFFER);

  size_t read = fread(buffer, sizeof(uint8_t), MAX_STDIN_BUFFER, stdin);

  if (read == MAX_STDIN_BUFFER) {
    fprintf(stderr, "stdin input is larger than %u\n", MAX_STDIN_BUFFER);
    free(buffer);
    return EXIT_FAILURE;
  }

  printf("size of input: %zu\n", read);

  csh capstone_handle;

  if (cs_open(CS_ARCH_ARM64, CS_MODE_ARM, &capstone_handle) != CS_ERR_OK) {
    return EXIT_FAILURE;
  }

  cs_option(capstone_handle, CS_OPT_DETAIL, CS_OPT_ON);

  cs_insn* instructions;
  size_t count = cs_disasm(capstone_handle, buffer, read, ADDRESS_OF_THE_FIRST_INSTRUCTION, 0, &instructions);

  if (count > 0) {

    printf("# of instructions: %zu\n", count);

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
