/* Autogenerated C file */
/* Generation date / time : 2023-04-17 17:08:01.752525 */
#ifndef CXRAM_VM_C
#define CXRAM_VM_C
/* Autogenerated CXRAM opcodes simulation from ISA-2.0/csram-opcodes-v2.0.5.csv */
#include <inttypes.h>
#include <stdbool.h>
#include "cxram-vm.h"
uint32_t cxram_emulate(uint64_t cxram_insn, h2_cxram_array_t h2_cxram_tiles, h2_cxram_line_t *cxramReg, bool cxram_trace)
{
  uint32_t cxram_opcode, cxram_src1, cxram_src2, cxram_dest, wordSize;
  uint32_t imm8, imm16, imm32;
  char type;
  h2_cxram_line_t *in1, *in2, *res;

  cxram_src1 = cxram_insn & 0xFFFF;
  cxram_src2 = (cxram_insn >> 16) & 0xFFFF;
  cxram_dest = (cxram_insn >> 34) & 0xFFFF;

  cxram_opcode = (cxram_insn >> 50) & 0xFF;
  if (cxram_trace)
	printf("cxram_emulation_cb OPCODE %d\n", cxram_opcode);

  switch (cxram_opcode)
  {
   case OP__cm_bcast8:   case OP__cm_bcast16:   case OP__cm_bcast32:
    imm8 = cxram_insn & 0xFF;
    imm16 = cxram_insn & 0xFFFF;
    imm32 = cxram_insn & 0xFFFFFFFF;
    type = 'u';
    break;
   case OP__cm_copy:   case OP__cm_hswap32:   case OP__cm_hswap64:   case OP__cm_slli8:   case OP__cm_slli16:
   case OP__cm_slli32:   case OP__cm_srli8:   case OP__cm_srli16:   case OP__cm_srli32:   case OP__cm_not:
   case OP__cm_redor:   case OP__cm_abs8:   case OP__cm_abs16:   case OP__cm_abs32:
    imm8 = (cxram_insn >> 16) & 0xFF;
    imm16 = (cxram_insn >> 16) & 0xFFFF;
    imm32 = (cxram_insn >> 16) & 0xFFFFFFFF;
    type = 'i';
    break;
  default:
    imm8 = 0xFF;
    imm16 = 0xFFFF;
    imm32 = 0xFFFFFFFF;
    type = 'r';
  }

	in1 = &h2_cxram_tiles[cxram_src1];
	in2 = &h2_cxram_tiles[cxram_src2];
	res = &h2_cxram_tiles[cxram_dest];
	if (cxram_trace) {
		printf("\n");
		wordSize = getWordSize(cxram_opcode);
		if (type == 'u')
			printf("imm32 = %d\n", imm32);
		else if (type == 'i'){
			printf("imm16 = %d\n", imm16);
			printVector("in", CXRAM_VECLEN * 8 / wordSize, wordSize, in1);
		} else {
			printVector("in1", CXRAM_VECLEN * 8 / wordSize, wordSize, in1);
			printVector("in2", CXRAM_VECLEN * 8 / wordSize, wordSize, in2);
		}
		printVector("res", CXRAM_VECLEN * 8 / wordSize, wordSize, res);
 	}
	execute_cxram_emulate(cxram_opcode, in1, in2, res, cxramReg, imm32, imm16, imm8, cxram_trace);
	if (cxram_trace)
		printVector("res", CXRAM_VECLEN * 8 / wordSize, wordSize, res);
	return cxram_opcode;
}
	
void execute_cxram_emulate(int opcode, h2_cxram_line_t *src1, h2_cxram_line_t *src2, h2_cxram_line_t *dest, h2_cxram_line_t *cxramReg, uint32_t imm32, uint16_t imm16, uint8_t imm8, bool cxram_trace)
{
int i;
switch (opcode)
  {
  case OP__cm_copy:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_copy\n");
  for (i=0; i < 16; i++) 
    dest->i32[i]  =  (src1->i32[i]);
  break;
  case OP__cm_hswap32:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_hswap32\n");
  for (i = 0; i < 4; i++) 
    _hswap32(dest, src1);
  break;
  case OP__cm_hswap64:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_hswap64\n");
  for (i = 0; i < 2 ; i++) 
    _hswap64(dest, src1);
  break;
  case OP__cm_copyeq8:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_copyeq8\n");
  for (i = 0; i < 16; i++) 
    dest->i8[i]  =  ( (src2->i8[i]  & CMP_FLAG_EQ ) ? src1->i8[i] : dest->i8[i]);
  break;
  case OP__cm_copyeq16:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_copyeq16\n");
  for (i = 0; i < 8; i++) 
    dest->i16[i]  =  ( (src2->i16[i]  & CMP_FLAG_EQ ) ? src1->i16[i] : dest->i16[i]);
  break;
  case OP__cm_copyeq32:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_copyeq32\n");
  for (i = 0; i < 4; i++) 
    dest->i32[i]  =  ( (src2->i32[i]  & CMP_FLAG_EQ ) ? src1->i32[i] : dest->i32[i]);
  break;
  case OP__cm_copygeq8:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_copygeq8\n");
  for (i = 0; i < 16; i++) 
    dest->i8[i]  =  ( (src2->i8[i]  & CMP_FLAG_GEQ) ? src1->i8[i] : dest->i8[i]);
  break;
  case OP__cm_copygeq16:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_copygeq16\n");
  for (i = 0; i < 8; i++) 
    dest->i16[i]  =  ( (src2->i16[i]  & CMP_FLAG_GEQ) ? src1->i16[i] : dest->i16[i]);
  break;
  case OP__cm_copygeq32:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_copygeq32\n");
  for (i = 0; i < 4; i++) 
    dest->i32[i]  =  ( (src2->i32[i]  & CMP_FLAG_GEQ) ? src1->i32[i] : dest->i32[i]);
  break;
  case OP__cm_copygt8:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_copygt8\n");
  for (i = 0; i < 16; i++) 
    dest->i8[i]  =  ( (src2->i8[i]  & CMP_FLAG_GT ) ? src1->i8[i] : dest->i8[i]);
  break;
  case OP__cm_copygt16:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_copygt16\n");
  for (i = 0; i < 8; i++) 
    dest->i16[i]  =  ( (src2->i16[i]  & CMP_FLAG_GT ) ? src1->i16[i] : dest->i16[i]);
  break;
  case OP__cm_copygt32:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_copygt32\n");
  for (i = 0; i < 4; i++) 
    dest->i32[i]  =  ( (src2->i32[i]  & CMP_FLAG_GT ) ? src1->i32[i] : dest->i32[i]);
  break;
  case OP__cm_copyleq8:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_copyleq8\n");
  for (i = 0; i < 16; i++) 
    dest->i8[i]  =  ( (src2->i8[i]  & CMP_FLAG_LEQ) ? src1->i8[i] : dest->i8[i]);
  break;
  case OP__cm_copyleq16:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_copyleq16\n");
  for (i = 0; i < 8; i++) 
    dest->i16[i]  =  ( (src2->i16[i]  & CMP_FLAG_LEQ) ? src1->i16[i] : dest->i16[i]);
  break;
  case OP__cm_copyleq32:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_copyleq32\n");
  for (i = 0; i < 4; i++) 
    dest->i32[i]  =  ( (src2->i32[i]  & CMP_FLAG_LEQ) ? src1->i32[i] : dest->i32[i]);
  break;
  case OP__cm_copylt8:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_copylt8\n");
  for (i = 0; i < 16; i++) 
    dest->i8[i]  =  ( (src2->i8[i]  & CMP_FLAG_LT ) ? src1->i8[i] : dest->i8[i]);
  break;
  case OP__cm_copylt16:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_copylt16\n");
  for (i = 0; i < 8; i++) 
    dest->i16[i]  =  ( (src2->i16[i]  & CMP_FLAG_LT ) ? src1->i16[i] : dest->i16[i]);
  break;
  case OP__cm_copylt32:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_copylt32\n");
  for (i = 0; i < 4; i++) 
    dest->i32[i]  =  ( (src2->i32[i]  & CMP_FLAG_LT ) ? src1->i32[i] : dest->i32[i]);
  break;
  case OP__cm_copyneq8:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_copyneq8\n");
  for (i = 0; i < 16; i++) 
    dest->i8[i]  =  (~(src2->i8[i]  & CMP_FLAG_EQ ) ? src1->i8[i] : dest->i8[i]);
  break;
  case OP__cm_copyneq16:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_copyneq16\n");
  for (i = 0; i < 8; i++) 
    dest->i16[i]  =  (~(src2->i16[i]  & CMP_FLAG_EQ ) ? src1->i16[i] : dest->i16[i]);
  break;
  case OP__cm_copyneq32:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_copyneq32\n");
  for (i = 0; i < 4; i++) 
    dest->i32[i]  =  (~(src2->i32[i]  & CMP_FLAG_EQ ) ? src1->i32[i] : dest->i32[i]);
  break;
  case OP__cm_bcast8:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_bcast8\n");
  for (i = 0; i < 16; i++) 
    dest->i8[i]  = imm8;
  break;
  case OP__cm_bcast16:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_bcast16\n");
  for (i = 0; i < 8; i++) 
    dest->i16[i]  = imm16;
  break;
  case OP__cm_bcast32:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_bcast32\n");
  for (i = 0; i < 4; i++) 
    dest->i32[i]  = imm32;
  break;
  case OP__cm_slli8:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_slli8\n");
  for (i = 0; i < 16; i++) 
    dest->i8[i]  =  (src1->i8[i] << imm8);
  break;
  case OP__cm_slli16:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_slli16\n");
  for (i = 0; i < 8; i++) 
    dest->i16[i]  =  (src1->i16[i] << imm16);
  break;
  case OP__cm_slli32:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_slli32\n");
  for (i = 0; i < 4; i++) 
    dest->i32[i]  =  (src1->i32[i] << imm32);
  break;
  case OP__cm_srli8:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_srli8\n");
  for (i = 0; i < 16; i++) 
    dest->i8[i]  =  (src1->i8[i] >> imm8);
  break;
  case OP__cm_srli16:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_srli16\n");
  for (i = 0; i < 8; i++) 
    dest->i16[i]  =  (src1->i16[i] >> imm16);
  break;
  case OP__cm_srli32:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_srli32\n");
  for (i = 0; i < 4; i++) 
    dest->i32[i]  =  (src1->i32[i] >> imm32);
  break;
  case OP__cm_not:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_not\n");
  for (i=0; i < 16; i++) 
    dest->i32[i]  =  ~src1->i32[i];
  break;
  case OP__cm_redor:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_redor\n");
  for (i=0; i < 16; i++) 
    _redor(dest, src1);
  break;
  case OP__cm_and:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_and\n");
  for (i=0; i < 16; i++) 
    dest->i32[i]  =  (src1->i32[i]  & src2->i32[i]);
  break;
  case OP__cm_or:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_or\n");
  for (i=0; i < 16; i++) 
    dest->i32[i]  =  (src1->i32[i]  | src2->i32[i]);
  break;
  case OP__cm_xor:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_xor\n");
  for (i=0; i < 16; i++) 
    dest->i32[i]  =  (src1->i32[i]  ^ src2->i32[i]);
  break;
  case OP__cm_nand:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_nand\n");
  for (i=0; i < 16; i++) 
    dest->i32[i]  = ~(src1->i32[i]  & src2->i32[i]);
  break;
  case OP__cm_nor:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_nor\n");
  for (i=0; i < 16; i++) 
    dest->i32[i]  = ~(src1->i32[i]  | src2->i32[i]);
  break;
  case OP__cm_xnor:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_xnor\n");
  for (i=0; i < 16; i++) 
    dest->i32[i]  = ~(src1->i32[i]  ^ src2->i32[i]);
  break;
  case OP__cm_abs8:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_abs8\n");
  for (i = 0; i < 16; i++) 
    dest->i8[i]  =  src1->i8[i] > 0 ? src1->i8[i] : - src1->i8[i];;
  break;
  case OP__cm_abs16:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_abs16\n");
  for (i = 0; i < 8; i++) 
    dest->i16[i]  =  src1->i16[i] > 0 ? src1->i16[i] : - src1->i16[i];;
  break;
  case OP__cm_abs32:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_abs32\n");
  for (i = 0; i < 4; i++) 
    dest->i32[i]  =  src1->i32[i] > 0 ? src1->i32[i] : - src1->i32[i];;
  break;
  case OP__cm_adds8:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_adds8\n");
  for (i = 0; i < 16; i++) 
    dest->i8[i]  =  (uint64_t) src1->i8[i] > (uint64_t)src2->i8[i] ? max_val(dest->i8[i]) : (src1->i8[i] + src2->i8[i]);
  break;
  case OP__cm_adds16:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_adds16\n");
  for (i = 0; i < 8; i++) 
    dest->i16[i]  =  (uint64_t) src1->i16[i] > (uint64_t)src2->i16[i] ? max_val(dest->i16[i]) : (src1->i16[i] + src2->i16[i]);
  break;
  case OP__cm_adds32:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_adds32\n");
  for (i = 0; i < 4; i++) 
    dest->i32[i]  =  (uint64_t) src1->i32[i] > (uint64_t)src2->i32[i] ? max_val(dest->i32[i]) : (src1->i32[i] + src2->i32[i]);
  break;
  case OP__cm_add8:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_add8\n");
  for (i = 0; i < 16; i++) 
    dest->i8[i]  =  (src1->i8[i]  + src2->i8[i]);
  break;
  case OP__cm_add16:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_add16\n");
  for (i = 0; i < 8; i++) 
    dest->i16[i]  =  (src1->i16[i]  + src2->i16[i]);
  break;
  case OP__cm_add32:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_add32\n");
  for (i = 0; i < 4; i++) 
    dest->i32[i]  =  (src1->i32[i]  + src2->i32[i]);
  break;
  case OP__cm_sub8:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_sub8\n");
  for (i = 0; i < 16; i++) 
    dest->i8[i]  =  (src1->i8[i]  - src2->i8[i]);
  break;
  case OP__cm_sub16:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_sub16\n");
  for (i = 0; i < 8; i++) 
    dest->i16[i]  =  (src1->i16[i]  - src2->i16[i]);
  break;
  case OP__cm_sub32:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_sub32\n");
  for (i = 0; i < 4; i++) 
    dest->i32[i]  =  (src1->i32[i]  - src2->i32[i]);
  break;
  case OP__cm_subs8:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_subs8\n");
  for (i = 0; i < 16; i++) 
    dest->i8[i]  =  (uint64_t)src1->i8[i] < (uint64_t)src2->i8[i] ? 0 : (src1->i8[i] - src2->i8[i]);
  break;
  case OP__cm_subs16:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_subs16\n");
  for (i = 0; i < 8; i++) 
    dest->i16[i]  =  (uint64_t)src1->i16[i] < (uint64_t)src2->i16[i] ? 0 : (src1->i16[i] - src2->i16[i]);
  break;
  case OP__cm_subs32:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_subs32\n");
  for (i = 0; i < 4; i++) 
    dest->i32[i]  =  (uint64_t)src1->i32[i] < (uint64_t)src2->i32[i] ? 0 : (src1->i32[i] - src2->i32[i]);
  break;
  case OP__cm_cmp8:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_cmp8\n");
  for (i = 0; i < 16; i++) 
    dest->i8[i] = ((src1->i8[i] == src2->i8[i]) << CMP_SHAM_EQ) | ((src1->i8[i]  < src2->i8[i]) << CMP_SHAM_LT) | ((src1->i8[i]  > src2->i8[i]) << CMP_SHAM_GT);
  break;
  case OP__cm_cmp16:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_cmp16\n");
  for (i = 0; i < 8; i++) 
    dest->i16[i] = ((src1->i16[i] == src2->i16[i]) << CMP_SHAM_EQ) | ((src1->i16[i]  < src2->i16[i]) << CMP_SHAM_LT) | ((src1->i16[i]  > src2->i16[i]) << CMP_SHAM_GT);
  break;
  case OP__cm_cmp32:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_cmp32\n");
  for (i = 0; i < 4; i++) 
    dest->i32[i] = ((src1->i32[i] == src2->i32[i]) << CMP_SHAM_EQ) | ((src1->i32[i]  < src2->i32[i]) << CMP_SHAM_LT) | ((src1->i32[i]  > src2->i32[i]) << CMP_SHAM_GT);
  break;
  case OP__cm_mul8:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_mul8\n");
  for (i = 0; i < 16; i++) 
    dest->i8[i]  =  (src1->i8[i]  * src2->i8[i]);
  break;
  case OP__cm_mul16:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_mul16\n");
  for (i = 0; i < 8; i++) 
    dest->i16[i]  =  (src1->i16[i]  * src2->i16[i]);
  break;
  case OP__cm_mul32:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_mul32\n");
  for (i = 0; i < 4; i++) 
    dest->i32[i]  =  (src1->i32[i]  * src2->i32[i]);
  break;
  case OP__cm_fmac8:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_fmac8\n");
  for (i = 0; i < 16; i++) 
    dest->i8[i] +=  (src1->i8[i]  * src2->i8[i]);
  break;
  case OP__cm_fmac16:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_fmac16\n");
  for (i = 0; i < 8; i++) 
    dest->i16[i] +=  (src1->i16[i]  * src2->i16[i]);
  break;
  case OP__cm_fmac32:
  if (cxram_trace) printf ("Decode CxRAM operation _cm_fmac32\n");
  for (i = 0; i < 4; i++) 
    dest->i32[i] +=  (src1->i32[i]  * src2->i32[i]);
  break;
  default: printf ("Unknown opcode 0x%x (0x%x)\n", opcode >> 3, opcode & 0x7);
  exit(-1);
  break;
  }
}
uint32_t getWordSize(uint32_t cxram_opcode)
{
  switch (cxram_opcode)
  {
   case OP__cm_copyeq8:   case OP__cm_copygeq8:   case OP__cm_copygt8:   case OP__cm_copyleq8:   case OP__cm_copylt8:
   case OP__cm_copyneq8:   case OP__cm_bcast8:   case OP__cm_slli8:   case OP__cm_srli8:   case OP__cm_abs8:
   case OP__cm_adds8:   case OP__cm_add8:   case OP__cm_sub8:   case OP__cm_subs8:   case OP__cm_cmp8:
   case OP__cm_mul8:   case OP__cm_fmac8:
    return 8;
    break;
   case OP__cm_copyeq16:   case OP__cm_copygeq16:   case OP__cm_copygt16:   case OP__cm_copyleq16:   case OP__cm_copylt16:
   case OP__cm_copyneq16:   case OP__cm_bcast16:   case OP__cm_slli16:   case OP__cm_srli16:   case OP__cm_abs16:
   case OP__cm_adds16:   case OP__cm_add16:   case OP__cm_sub16:   case OP__cm_subs16:   case OP__cm_cmp16:
   case OP__cm_mul16:   case OP__cm_fmac16:
    return 16;
    break;
   case OP__cm_hswap32:   case OP__cm_copyeq32:   case OP__cm_copygeq32:   case OP__cm_copygt32:   case OP__cm_copyleq32:
   case OP__cm_copylt32:   case OP__cm_copyneq32:   case OP__cm_bcast32:   case OP__cm_slli32:   case OP__cm_srli32:
   case OP__cm_abs32:   case OP__cm_adds32:   case OP__cm_add32:   case OP__cm_sub32:   case OP__cm_subs32:
   case OP__cm_cmp32:   case OP__cm_mul32:   case OP__cm_fmac32:
    return 32;
    break;
  default:
    return 32;
  }
}

void printVector (char * vectorName, int vectorLen, int wordSize, h2_cxram_line_t *vectorValues)
{
  switch (wordSize)
	{
	case 8:  printVector8 (vectorName, vectorLen, vectorValues); break;
	case 16: printVector16(vectorName, vectorLen, vectorValues); break;
	case 32: printVector32(vectorName, vectorLen, vectorValues); break;
	default: printf ("printVector with incorrect wordSize %d\n", wordSize); exit (-1); break;
	}
}

void printVector8(char * vectorName, int vectorLen, h2_cxram_line_t *vectorValues)
{
  int i;
  printf("%s:", vectorName);
  for (i = 0; i < vectorLen; i++)
	printf("%3d ", (int) vectorValues->i8[i]);
  printf("\n");
}

void printVector16(char * vectorName, int vectorLen, h2_cxram_line_t *vectorValues)
{
  int i;
  printf("%s:", vectorName);
  for (i = 0; i < vectorLen; i++)
	printf("%4d ", (int) vectorValues->i16[i]);
  printf("\n");
}

void printVector32(char * vectorName, int vectorLen, h2_cxram_line_t *vectorValues)
{
  int i;
  printf("%s:", vectorName);
  for (i = 0; i < vectorLen; i++)
	printf("%8d ", (int) vectorValues->i32[i]);
  printf("\n");
}
	
#endif
/* End of generated file cxram-vm.c */