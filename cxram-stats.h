/* Autogenerated C file */
/* Generation date / time : 2023-04-17 17:08:01.809776 */
#ifndef CXRAM_STATS_H
#define CXRAM_STATS_H
/* Autogenerated CXRAM count instruction from ISA-2.0/csram-v2.0.5.json */
#define ARRAY_SIZE(x)  sizeof(x) / sizeof((x)[0])
typedef enum{
COUNT_ARITH,COUNT_LOGIC,COUNT_MEM
} CxRAMCountType;

char *categoryNamesCxRAM[] ={
"COUNT_ARITH","COUNT_LOGIC","COUNT_MEM"
};

typedef struct {const char *name; CxRAMCountType what; uint32_t opcode;} CxRAMClass;
static CxRAMClass cxramInsnClass [] = {
{"_cm_copy", COUNT_MEM, (0xC0)},
{"_cm_hswap32", COUNT_MEM, (0x81)},
{"_cm_hswap64", COUNT_MEM, (0xC1)},
{"_cm_copyeq8", COUNT_MEM, (0x18)},
{"_cm_copyeq16", COUNT_MEM, (0x58)},
{"_cm_copyeq32", COUNT_MEM, (0x98)},
{"_cm_copygeq8", COUNT_MEM, (0x19)},
{"_cm_copygeq16", COUNT_MEM, (0x59)},
{"_cm_copygeq32", COUNT_MEM, (0x99)},
{"_cm_copygt8", COUNT_MEM, (0x1A)},
{"_cm_copygt16", COUNT_MEM, (0x5A)},
{"_cm_copygt32", COUNT_MEM, (0x9A)},
{"_cm_copyleq8", COUNT_MEM, (0x1B)},
{"_cm_copyleq16", COUNT_MEM, (0x5B)},
{"_cm_copyleq32", COUNT_MEM, (0x9B)},
{"_cm_copylt8", COUNT_MEM, (0x1C)},
{"_cm_copylt16", COUNT_MEM, (0x5C)},
{"_cm_copylt32", COUNT_MEM, (0x9C)},
{"_cm_copyneq8", COUNT_MEM, (0x1D)},
{"_cm_copyneq16", COUNT_MEM, (0x5D)},
{"_cm_copyneq32", COUNT_MEM, (0x9D)},
{"_cm_bcast8", COUNT_MEM, (0x10)},
{"_cm_bcast16", COUNT_MEM, (0x50)},
{"_cm_bcast32", COUNT_MEM, (0x90)},
{"_cm_slli8", COUNT_LOGIC, (0x20)},
{"_cm_slli16", COUNT_LOGIC, (0x60)},
{"_cm_slli32", COUNT_LOGIC, (0xA0)},
{"_cm_srli8", COUNT_LOGIC, (0x21)},
{"_cm_srli16", COUNT_LOGIC, (0x61)},
{"_cm_srli32", COUNT_LOGIC, (0xA1)},
{"_cm_not", COUNT_LOGIC, (0xE2)},
{"_cm_redor", COUNT_LOGIC, (0xE3)},
{"_cm_and", COUNT_LOGIC, (0xE8)},
{"_cm_or", COUNT_LOGIC, (0xE9)},
{"_cm_xor", COUNT_LOGIC, (0xEA)},
{"_cm_nand", COUNT_LOGIC, (0xEB)},
{"_cm_nor", COUNT_LOGIC, (0xEC)},
{"_cm_xnor", COUNT_LOGIC, (0xED)},
{"_cm_abs8", COUNT_ARITH, (0x30)},
{"_cm_abs16", COUNT_ARITH, (0x70)},
{"_cm_abs32", COUNT_ARITH, (0xB0)},
{"_cm_adds8", COUNT_ARITH, (0x48)},
{"_cm_adds16", COUNT_ARITH, (0x88)},
{"_cm_adds32", COUNT_ARITH, (0xC8)},
{"_cm_add8", COUNT_ARITH, (0x38)},
{"_cm_add16", COUNT_ARITH, (0x78)},
{"_cm_add32", COUNT_ARITH, (0xB8)},
{"_cm_sub8", COUNT_ARITH, (0x39)},
{"_cm_sub16", COUNT_ARITH, (0x79)},
{"_cm_sub32", COUNT_ARITH, (0xB9)},
{"_cm_subs8", COUNT_ARITH, (0x49)},
{"_cm_subs16", COUNT_ARITH, (0x89)},
{"_cm_subs32", COUNT_ARITH, (0xC9)},
{"_cm_cmp8", COUNT_ARITH, (0x3A)},
{"_cm_cmp16", COUNT_ARITH, (0x7A)},
{"_cm_cmp32", COUNT_ARITH, (0xBA)},
{"_cm_mul8", COUNT_ARITH, (0x3B)},
{"_cm_mul16", COUNT_ARITH, (0x7B)},
{"_cm_mul32", COUNT_ARITH, (0xBB)},
{"_cm_fmac8", COUNT_ARITH, (0x3C)},
{"_cm_fmac16", COUNT_ARITH, (0x7C)},
{"_cm_fmac32", COUNT_ARITH, (0xBC)},
};
uint64_t cxramInsnStats[ARRAY_SIZE (cxramInsnClass)];    /* Indididual instruction count */
uint64_t cxramCategoryStats[ARRAY_SIZE (categoryNames)]; /* Instruction category count */
#endif
/* End of generated file cxram-stats.h */