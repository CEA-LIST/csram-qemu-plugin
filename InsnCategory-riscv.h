#ifndef RISCVCATEGORY
#define RISCVCATEGORY 1

/* RISCV instructions categories */
/* Categories values enumeration */
typedef enum {
COUNT_TBD,    COUNT_STACK,  COUNT_LD,   COUNT_ST,   COUNT_NOP,   COUNT_BR,   COUNT_IOP,
COUNT_CSTGEN, COUNT_BIT,    COUNT_CTRL, COUNT_FLOP,
}  CountType;

/* Categories names  */
char *categoryNames[] = {
"COUNT_TBD",   "COUNT_STACK", "COUNT_LD",   "COUNT_ST", "COUNT_NOP", "COUNT_BR", "COUNT_IOP",
"COUNT_CSTGEN","COUNT_BIT",   "COUNT_CTRL", "COUNT_FLOP",
};
/* Category counter array  */
/* Usefull macros */
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
uint64_t riscvStats[ARRAY_SIZE (categoryNames)];
#undef ARRAY_SIZE
/* Structure for instruction detection & classification */
typedef struct {
const char *name; CountType what; uint32_t mask; uint32_t pattern;
} InsnClass;

/* RISCV Instruction based on v2.2 specs */
char *riscvRegNames[] = {
/* zero*/ "x0",   /* x1 */  "ra", /* x2 */  "sp",  /* x3 */  "gp",
/* x4 */  "tp",   /* x5 */  "t0", /* x6 */  "t1",  /* x7 */  "t2",
/* x8 */  "s0/fp", /* x9 */ "s1", /* x10 */ "a0",  /* x11 */ "a1",
/* x12 */ "a2",   /* x13 */ "a3", /* x14 */ "a4",  /* x15 */ "a5",
/* x16 */ "a6",   /* x17 */ "a7", /* x18 */ "s2",  /* x19 */ "s3",
/* x20 */ "s4",   /* x21 */ "s5", /* x22 */ "s6",  /* x23 */ "s7",
/* x24 */ "s8",   /* x25 */ "s9", /* x26 */ "s10", /* x27 */ "s11",
/* x28 */ "t3",   /* x29 */ "t4", /* x30 */ "t5",  /* x31 */ "t6",
};

static InsnClass riscv16_insn_class [] = {
/* Table 12.4 instruction listing Quadrant 0*/
  {"C.SW",       COUNT_ST   , 0xE003, 0xC000}, // MaskConvert.py 110 XXX XXX XX XXX 00
  {"Illegal   ", COUNT_TBD  , 0xFFFF, 0x0000}, // MaskConvert.py 000 0 00000 00 000 00
  {"C.ADDI4SPN", COUNT_STACK, 0xE003, 0x0000}, // MaskConvert.py 000 XXXXXXXX XXX 00
  {"C.FLD",      COUNT_LD   , 0xE003, 0x2000}, // MaskConvert.py 001 XXX XXX XX XXX 00
  {"C.LW",       COUNT_LD   , 0xE003, 0x4000}, // MaskConvert.py 010 XXX XXX XX XXX 00
  {"C.FLW",      COUNT_LD   , 0xE003, 0x6000}, // MaskConvert.py 011 XXX XXX XX XXX 00
  {"C.FSD",      COUNT_ST   , 0xE003, 0xA000}, // MaskConvert.py 101 XXX XXX XX XXX 00
  {"C.FSW",      COUNT_ST   , 0xE003, 0xE000}, // MaskConvert.py 111 XXX XXX XX XXX 00
/* Table 12.5 instruction listing Quadrant 1*/
  {"C.NOP",      COUNT_NOP   , 0xFFFF, 0x0001}, // MaskConvert.py 000 0 00000 00000 01
  {"C.ADDI",     COUNT_IOP   , 0xE003, 0x0001}, // MaskConvert.py 000 X XXXXX XXXXX 01
  {"C.JAL",      COUNT_BR    , 0xE003, 0x2001}, // MaskConvert.py 001 X XXXXX XXXXX 01
  {"C.LI",       COUNT_CSTGEN, 0xE003, 0x4001}, // MaskConvert.py 010 X XXXXX XXXXX 01
  {"C.ADDI16SP", COUNT_STACK , 0xEF83, 0x6001}, // MaskConvert.py 011 X 00010 XXXXX 01
  {"C.LUI",      COUNT_CSTGEN, 0xE003, 0x6001}, // MaskConvert.py 011 X XXXXX XXXXX 01
  {"C.SRLI",     COUNT_BIT   , 0xEC03, 0x8001}, // MaskConvert.py 100 X 00 XXX XXXXX 01
  {"C.SRAI",     COUNT_BIT   , 0xEC03, 0x8401}, // MaskConvert.py 100 X 01 XXX XXXXX 01
  {"C.ANDI",     COUNT_IOP   , 0xEC03, 0x8801}, // MaskConvert.py 100 X 10 XXX XXXXX 01
  {"C.SUB",      COUNT_IOP   , 0xFC63, 0x8c01}, // MaskConvert.py 100 0 11 XXX 00 XXX 01
  {"C.XOR",      COUNT_BIT   , 0xFC63, 0x8c21}, // MaskConvert.py 100 0 11 XXX 01 XXX 01
  {"C.OR",       COUNT_BIT   , 0xFC63, 0x8c41}, // MaskConvert.py 100 0 11 XXX 10 XXX 01
  {"C.AND",      COUNT_BIT   , 0xFC63, 0x8c61}, // MaskConvert.py 100 0 11 XXX 11 XXX 01
  {"C.SUBW",     COUNT_IOP   , 0xFC63, 0x9c01}, // MaskConvert.py 100 1 11 XXX 00 XXX 01
  {"C.ADDW",     COUNT_IOP   , 0xFC63, 0x9c21}, // MaskConvert.py 100 1 11 XXX 01 XXX 01
  {"C.J",        COUNT_CTRL  , 0xE003, 0xa001}, // MaskConvert.py 101 X XX XXX XX XXX 01
  {"C.BEQZ",     COUNT_CTRL  , 0xE003, 0xc001}, // MaskConvert.py 110 X XX XXX XX XXX 01
  {"C.BNEQZ",    COUNT_CTRL  , 0xE003, 0xe001}, // MaskConvert.py 111 X XX XXX XX XXX 01
/* Table 12.6 instruction listing Quadrant 2*/
  {"C.SLLI",     COUNT_BIT ,  0xE003, 0x0002},  // MaskConvert.py 000 X XXXXX XXXXX 10
  {"C.FLDSP",    COUNT_LD  ,  0xE003, 0x2002},  // MaskConvert.py 001 X XXXXX XXXXX 10
  {"C.LWSP",     COUNT_LD  ,  0xE003, 0x4002},  // MaskConvert.py 010 X XXXXX XXXXX 10
  {"C.FLWSP",    COUNT_LD  ,  0xE003, 0x6002},  // MaskConvert.py 011 X XXXXX XXXXX 10
  {"C.JR",       COUNT_CTRL,  0xF07F, 0x8002},  // MaskConvert.py 100 0 XXXXX 00000 10
  {"C.MV",       COUNT_BIT ,  0xF003, 0x8002},  // MaskConvert.py 100 0 XXXXX XXXXX 10
  {"C.EBREAK",   COUNT_CTRL,  0xFFFF, 0x9002},  // MaskConvert.py 100 1 00000 00000 10
  {"C.JALR",     COUNT_CTRL,  0xF07F, 0x9002},  // MaskConvert.py 100 1 XXXXX 00000 10
  {"C.ADD",      COUNT_IOP ,  0xF003, 0x9002},  // MaskConvert.py 100 1 XXXXX XXXXX 10
  {"C.FSDSP",    COUNT_ST  ,  0xE003, 0xa002},  // MaskConvert.py 101 X XXXXX XXXXX 10
  {"C.SWSP",     COUNT_ST  ,  0xE003, 0xc002},  // MaskConvert.py 110 X XXXXX XXXXX 10
  {"C.FSWSP",    COUNT_ST  ,  0xE003, 0xe002},  // MaskConvert.py 111 X XXXXX XXXXX 10
};

static InsnClass riscv32_insn_class [] = {
  /*  RV32I base instruction set */
  {"SW",      COUNT_ST,     0x0000707f, 0x00002023 }, // MaskConvert.py XXXXXXX XXXXX XXXXX 010 XXXXX 0100011
  {"LUI",     COUNT_CSTGEN, 0x0000007F, 0x00000037 }, // MaskConvert.py XXXXXXXXXXXXXXXXXXXX XXXXX 0110111
  {"AUIPC",   COUNT_CSTGEN, 0x0000007F, 0x00000017 }, // MaskConvert.py XXXXXXXXXXXXXXXXXXXX XXXXX
  {"JAL",     COUNT_CTRL,   0x0000007F, 0x0000006f }, // MaskConvert.py XXXXXXXXXXXXXXXXXXXX XXXXX 1101111
  {"JALR",    COUNT_CTRL,   0x0000707f, 0x00000067 }, // MaskConvert.py XXXXXXXXXXXXXXXXX 000 XXXXX 1100111
  {"BEQ",     COUNT_CTRL,   0x0000707f, 0x00000063 }, // MaskConvert.py XXXXXXX XXXXX 000 XXXXX 1100011
  {"BNE",     COUNT_CTRL,   0x0000707f, 0x00001063 }, // MaskConvert.py XXXXXXX XXXXX 001 XXXXX 1100011
  {"BLT",     COUNT_CTRL,   0x0000707f, 0x00004063 }, // MaskConvert.py XXXXXXX XXXXX 100 XXXXX 1100011
  {"BGE",     COUNT_CTRL,   0x0000707f, 0x00005063 }, // MaskConvert.py XXXXXXX XXXXX 101 XXXXX 1100011
  {"BLTU",    COUNT_CTRL,   0x0000707f, 0x00006063 }, // MaskConvert.py XXXXXXX XXXXX 110 XXXXX 1100011
  {"BGEU",    COUNT_CTRL,   0x0000707f, 0x00007063 }, // MaskConvert.py XXXXXXX XXXXX 111 XXXXX 1100011
  {"LB",      COUNT_LD,     0x0000707f, 0x00000003 }, // MaskConvert.py XXXXXXXXXXXX XXXXX 000 XXXXX 0000011
  {"LH",      COUNT_LD,     0x0000707f, 0x00001003 }, // MaskConvert.py XXXXXXXXXXXX XXXXX 001 XXXXX 0000011
  {"LW",      COUNT_LD,     0x0000707f, 0x00002003 }, // MaskConvert.py XXXXXXXXXXXX XXXXX 010 XXXXX 0000011
  {"LBU",     COUNT_LD,     0x0000707f, 0x00004003 }, // MaskConvert.py XXXXXXXXXXXX XXXXX 100 XXXXX 0000011
  {"LHU",     COUNT_LD,     0x0000707f, 0x00005003 }, // MaskConvert.py XXXXXXXXXXXX XXXXX 101 XXXXX 0000011
  {"SB",      COUNT_ST,     0x0000707f, 0x00000023 }, // MaskConvert.py XXXXXXX XXXXX XXXXX 000 XXXXX 0100011
  {"SH",      COUNT_ST,     0x0000707f, 0x00001023 }, // MaskConvert.py XXXXXXX XXXXX XXXXX 001 XXXXX 0100011
  {"ADDI",    COUNT_IOP,    0x0000707f, 0x00000013 }, // MaskConvert.py XXXXXXXXXXXX XXXXX 000 XXXXX 0010011
  {"SLTI",    COUNT_BIT,    0x0000707f, 0x00002013 }, // MaskConvert.py XXXXXXXXXXXX XXXXX 010 XXXXX 0010011
  {"SLTIU",   COUNT_BIT,    0x0000707f, 0x00003013 }, // MaskConvert.py XXXXXXXXXXXX XXXXX 011 XXXXX 0010011
  {"XORI",    COUNT_BIT,    0x0000707f, 0x00004013 }, // MaskConvert.py  XXXXXXXXXXXX XXXXX 100 XXXXX 0010011
  {"ORI",     COUNT_BIT,    0x0000707f, 0x00006013 }, // MaskConvert.py  XXXXXXXXXXXX XXXXX 110 XXXXX 0010011
  {"ANDI",    COUNT_BIT,    0x0000707f, 0x00007013 }, // MaskConvert.py  XXXXXXXXXXXX XXXXX 111 XXXXX 0010011
  {"SLLI",    COUNT_BIT,    0xfe00707f, 0x00001013 }, // MaskConvert.py 0000000 XXXXX XXXXX 001 XXXXX 0010011
  {"SRLI",    COUNT_BIT,    0xfe00707f, 0x00005013 }, // MaskConvert.py  0000000 XXXXX XXXXX 101 XXXXX 0010011
  {"SRAI",    COUNT_BIT,    0xfe00707f, 0x40005013 }, // MaskConvert.py  0100000 XXXXX XXXXX 101 XXXXX 0010011
  {"ADD",     COUNT_IOP,    0xfe00707f, 0x00000033 }, // MaskConvert.py 0000000 XXXXX XXXXX 000 XXXXX 0110011
  {"SUB",     COUNT_IOP,    0xfe00707f, 0x40000033 }, // MaskConvert.py 0100000 XXXXX XXXXX 000 XXXXX 0110011
  {"SLL",     COUNT_BIT,    0xfe00707f, 0x00001033 }, // MaskConvert.py 0000000 XXXXX XXXXX 001 XXXXX 0110011
  {"SLT",     COUNT_BIT,    0xfe00707f, 0x00002033 }, // MaskConvert.py 0000000 XXXXX XXXXX 010 XXXXX 0110011
  {"SLTU",    COUNT_BIT,    0xfe00707f, 0x00003033 }, // MaskConvert.py 0000000 XXXXX XXXXX 011 XXXXX 0110011
  {"XOR",     COUNT_BIT,    0xfe00707f, 0x00004033 }, // MaskConvert.py 0000000 XXXXX XXXXX 100 XXXXX 0110011
  {"SRL",     COUNT_BIT,    0xfe00707f, 0x00005033 }, // MaskConvert.py 0000000 XXXXX XXXXX 101 XXXXX 0110011
  {"SRA",     COUNT_BIT,    0xfe00707f, 0x40005033 }, // MaskConvert.py 0100000 XXXXX XXXXX 101 XXXXX 0110011
  {"OR",      COUNT_BIT,    0xfe00707f, 0x00006033 }, // MaskConvert.py 0000000 XXXXX XXXXX 110 XXXXX 0110011
  {"AND",     COUNT_IOP,    0xfe00707f, 0x00007033 }, // MaskConvert.py 0000000 XXXXX XXXXX 111 XXXXX 0110011
  {"FENCE",   COUNT_CTRL,   0xf00fffff, 0x0000000f }, // MaskConvert.py 0000 XXXX XXXX 00000 000 00000 0001111
  {"FENCE.I", COUNT_CTRL,   0xffffffff, 0x0000100f }, // MaskConvert.py 0000 0000 0000 00000 001 00000 0001111
  {"ECALL",   COUNT_CTRL,   0xffffffff, 0x00000073 }, // MaskConvert.py 000000000000 00000 000 00000 1110011
  {"EBREAK",  COUNT_CTRL,   0xffffffff, 0x00100073 }, // MaskConvert.py 000000000001 00000 000 00000 1110011
  {"CSRRW",   COUNT_CTRL,   0x0000707f, 0x00001073 }, // MaskConvert.py XXXXXXXXXXX XXXXX 001 XXXXX 1110011
  {"CSRRS",   COUNT_CTRL,   0x0000707f, 0x00002073 }, // MaskConvert.py XXXXXXXXXXX XXXXX 010 XXXXX 1110011
  {"CSRRC",   COUNT_CTRL,   0x0000707f, 0x00003073 }, // MaskConvert.py XXXXXXXXXXX XXXXX 011 XXXXX 1110011
  {"CSRRWI",  COUNT_CTRL,   0x0000707f, 0x00005073 }, // MaskConvert.py XXXXXXXXXXX XXXXX 101 XXXXX 1110011
  {"CSRRSI",  COUNT_CTRL,   0x0000707f, 0x00006073 }, // MaskConvert.py XXXXXXXXXXX XXXXX 110 XXXXX 1110011
  {"CSRRCI",  COUNT_CTRL,   0x0000707f, 0x00007073 }, // MaskConvert.py XXXXXXXXXXX XXXXX 111 XXXXX 1110011
  //  {"",  , , COUNT_CTRL    }, // MaskConvert.py
  /* RV64I Base Instruction Set (in addition to RV32I)   */
  /* RV32M Standard Extension */
  /* RV64M Standard Extension (in addition to RV32M)  */
  {"MUL",    COUNT_IOP,   0xfe00707f, 0x02000033 }, // MaskConvert.py 0000001 XXXXX XXXXX 000 XXXXX 0110011
  {"MULH",   COUNT_IOP,   0xfe00707f, 0x02001033 }, // MaskConvert.py  0000001 XXXXX XXXXX 001 XXXXX 0110011
  {"MULHSU", COUNT_IOP,   0xfe00707f, 0x02002033 }, // MaskConvert.py  0000001 XXXXX XXXXX 010 XXXXX 0110011
  {"MULHU",  COUNT_IOP,   0xfe00707f, 0x02003033 }, // MaskConvert.py 0000001 XXXXX XXXXX 011 XXXXX 0110011
  {"DIV",    COUNT_IOP,   0xfe00707f, 0x02004033 }, // MaskConvert.py  0000001 XXXXX XXXXX 100 XXXXX 0110011
  {"DIVU",   COUNT_IOP,   0xfe00707f, 0x02005033 }, // MaskConvert.py  0000001 XXXXX XXXXX 101 XXXXX 0110011
  {"REM",    COUNT_IOP,   0xfe00707f, 0x02006033 }, // MaskConvert.py 0000001 XXXXX XXXXX 110 XXXXX 0110011
  {"REMU",   COUNT_IOP,   0xfe00707f, 0x02007033 }, // MaskConvert.py 0000001 XXXXX XXXXX 111 XXXXX 0110011
  /* RV32A Standard Extension */
  /* TBD */
  /* RV64A Standard Extension (in addition to RV32A)  */
  /* TBD */
  /* RV32F Standard Extension  */
  {"FLW",      COUNT_LD,   0x0000707f, 0x00002007 }, // MaskConvert.py XXXXXXXXXXXX XXXXX 010 XXXXX 0000111
  {"FSW",      COUNT_ST,   0x0000707f, 0x00002027 }, // MaskConvert.py XXXXXXX XXXXX XXXXX 010 XXXXX 0100111
  {"FMADD.S",  COUNT_FLOP, 0x0600007f, 0x00000043 }, // MaskConvert.py XXXXX 00 XXXXX XXXXX XXX XXXXX 1000011
  {"FMSUB.S",  COUNT_FLOP, 0x0600007f, 0x00000047 }, // MaskConvert.py XXXXX 00 XXXXX XXXXX XXX XXXXX 1000111
  {"FNMSUB.S", COUNT_FLOP, 0x0600007f, 0x0000004b }, // MaskConvert.py XXXXX 00 XXXXX XXXXX XXX XXXXX 1001011
  {"FNMADD.S", COUNT_FLOP, 0x0600007f, 0x0000004f }, // MaskConvert.py XXXXX 00 XXXXX XXXXX XXX XXXXX 1001111
  {"FADD.S",   COUNT_FLOP, 0xfe00007f, 0x00000053 }, // MaskConvert.py 0000000 XXXXX XXXXX XXX XXXXX 1010011
  {"FSUB.S",   COUNT_FLOP, 0xfe00007f, 0x08000053 }, // MaskConvert.py 0000100 XXXXX XXXXX XXX XXXXX 1010011
  {"FMUL.S",   COUNT_FLOP, 0xfe00007f, 0x10000053 }, // MaskConvert.py 0001000 XXXXX XXXXX XXX XXXXX 1010011
  {"FDIV.S",   COUNT_FLOP, 0xfe00007f, 0x18000053 }, // MaskConvert.py 0001100 XXXXX XXXXX XXX XXXXX 1010011
  {"FSQRT.S",  COUNT_FLOP, 0xfff0007f, 0x58000053 }, // MaskConvert.py 0101100 00000 XXXXX XXX XXXXX 1010011
  {"FSGNJ.S",  COUNT_CTRL, 0xfe00707f, 0x20000053 }, // MaskConvert.py 0010000 XXXXX XXXXX 000 XXXXX 1010011
  {"FSGNJN.S", COUNT_CTRL, 0xfe00707f, 0x20001053 }, // MaskConvert.py 0010000 XXXXX XXXXX 001 XXXXX 1010011
  {"FSGNJX.S", COUNT_CTRL, 0xfe00707f, 0x20002053 }, // MaskConvert.py 0010000 XXXXX XXXXX 010 XXXXX 1010011
  {"FMIN.S",   COUNT_CTRL, 0xfe00707f, 0x28000053 }, // MaskConvert.py 0010100 XXXXX XXXXX 000 XXXXX 1010011
  {"FMAX.S",   COUNT_CTRL, 0xfe00707f, 0x28001053 }, // MaskConvert.py 0010100 XXXXX XXXXX 001 XXXXX 1010011
  {"FCVT.W.S", COUNT_FLOP, 0xfff0007f, 0xc0000053 }, // MaskConvert.py 1100000 00000 XXXXX XXX XXXXX 1010011
  {"FCVT.WU.S",COUNT_FLOP, 0xfff0007f, 0xc0100053 }, // MaskConvert.py 1100000 00001 XXXXX XXX XXXXX 1010011
  {"FMV.X.W",  COUNT_BIT,  0xfff0707f, 0xe0000053 }, // MaskConvert.py 1110000 00000 XXXXX 000 XXXXX 1010011
  {"FEQ.S",    COUNT_CTRL, 0xfe00707f, 0xa0002053 }, // MaskConvert.py 1010000 XXXXX XXXXX 010 XXXXX 1010011
  {"FLT.S",    COUNT_CTRL, 0xfe00707f, 0xa0001053 }, // MaskConvert.py 1010000 XXXXX XXXXX 001 XXXXX 1010011
  {"FLE.S",    COUNT_CTRL, 0xfe00707f, 0xa0000053 }, // MaskConvert.py 1010000 XXXXX XXXXX 000 XXXXX 1010011
  {"FCLASS.S", COUNT_CTRL, 0xfff0707f, 0xe0001053 }, // MaskConvert.py 1110000 00000 XXXXX 001 XXXXX 1010011
  {"FCVT.S.W", COUNT_FLOP, 0xfff0007f, 0xd0000053 }, // MaskConvert.py 1101000 00000 XXXXX XXX XXXXX 1010011
  {"FCVT.S.WU",COUNT_FLOP, 0xfff0007f, 0xd0100053 }, // MaskConvert.py 1101000 00001 XXXXX XXX XXXXX 1010011
  {"FMV.W.X",  COUNT_BIT,  0xfff0707f, 0xf0000053 }, // MaskConvert.py 1111000 00000 XXXXX 000 XXXXX 1010011
  /* RV64F Standard Extension (in addition to RV32F)  */
  /* TBD */
  /* RV32D Standard Extension  */
  {"FLD",		COUNT_LD,   0x0000707f, 0x00003007}, // MaskConvert.py XXXXXXXXXXXX XXXXX 011 XXXXX 0000111
  {"FSD",		COUNT_ST,   0x0000707f, 0x00003027}, // MaskConvert.py XXXXXXX XXXXX XXXXX 011 XXXXX 0100111
  {"FMADD.D", 	COUNT_FLOP, 0x0600007f, 0x02000043}, // MaskConvert.py XXXXX 01 XXXXX XXXXX XXX XXXXX 1000011
  {"FMSUB.D", 	COUNT_FLOP, 0x0600007f, 0x02000047}, // MaskConvert.py XXXXX 01 XXXXX XXXXX XXX XXXXX 1000111
  {"FNMSUB.D",  COUNT_FLOP, 0x0600007f, 0x0200004b}, // MaskConvert.py XXXXX 01 XXXXX XXXXX XXX XXXXX 1001011
  {"FNMADD.D",  COUNT_FLOP, 0x0600007f, 0x0200004f}, // MaskConvert.py XXXXX 01 XXXXX XXXXX XXX XXXXX 1001111
  {"FADD.D", 	COUNT_FLOP, 0xfe00007f, 0x02000053}, // MaskConvert.py 0000001 XXXXX XXXXX XXX XXXXX 1010011
  {"FSUB.D", 	COUNT_FLOP, 0xfe00007f, 0x0a000053}, // MaskConvert.py 0000101 XXXXX XXXXX XXX XXXXX 1010011
  {"FMUL.D", 	COUNT_FLOP, 0xfe00007f, 0x12000053}, // MaskConvert.py 0001001 XXXXX XXXXX XXX XXXXX 1010011
  {"FDIV.D", 	COUNT_FLOP, 0xfe00007f, 0x1a000053}, // MaskConvert.py 0001101 XXXXX XXXXX XXX XXXXX 1010011
  {"FSQRT.D", 	COUNT_FLOP, 0xfff0007f, 0x5a000053}, // MaskConvert.py 0101101 00000 XXXXX XXX XXXXX 1010011
  {"FSGNJ.D", 	COUNT_CTRL, 0xfe00707f, 0x22000053}, // MaskConvert.py 0010001 XXXXX XXXXX 000 XXXXX 1010011
  {"FSGNJN.D",  COUNT_CTRL, 0xfe00707f, 0x22001053}, // MaskConvert.py 0010001 XXXXX XXXXX 001 XXXXX 1010011
  {"FSGNJX.D",  COUNT_CTRL, 0xfe00707f, 0x22002053}, // MaskConvert.py 0010001 XXXXX XXXXX 010 XXXXX 1010011
  {"FMIN.D", 	COUNT_CTRL, 0xfe00707f, 0x2a000053}, // MaskConvert.py 0010101 XXXXX XXXXX 000 XXXXX 1010011
  {"FMAX.D", 	COUNT_CTRL, 0xfe00707f, 0x2a001053}, // MaskConvert.py 0010101 XXXXX XXXXX 001 XXXXX 1010011
  {"FCVT.S.D",  COUNT_FLOP, 0xfff0007f, 0x40100053}, // MaskConvert.py 0100000 00001 XXXXX XXX XXXXX 1010011
  {"FCVT.D.S",  COUNT_FLOP, 0xfff0007f, 0x42000053}, // MaskConvert.py 0100001 00000 XXXXX XXX XXXXX 1010011
  {"FEQ.D", 	COUNT_BIT,  0xfe00707f, 0xa2002053}, // MaskConvert.py 1010001 XXXXX XXXXX 010 XXXXX 1010011
  {"FLT.D", 	COUNT_CTRL, 0xfe00707f, 0xa2001053}, // MaskConvert.py 1010001 XXXXX XXXXX 001 XXXXX 1010011
  {"FLE.D", 	COUNT_CTRL, 0xfe00707f, 0xa2000053}, // MaskConvert.py 1010001 XXXXX XXXXX 000 XXXXX 1010011
  {"FCLASS.D",  COUNT_CTRL, 0xfff0707f, 0xe2001053}, // MaskConvert.py 1110001 00000 XXXXX 001 XXXXX 1010011
  {"FCVT.W.D",  COUNT_CTRL, 0xfff0007f, 0xc2000053}, // MaskConvert.py 1100001 00000 XXXXX XXX XXXXX 1010011
  {"FCVT.WU.D", COUNT_FLOP, 0xfff0007f, 0xc2100053}, // MaskConvert.py 1100001 00001 XXXXX XXX XXXXX 1010011
  {"FCVT.D.W",  COUNT_FLOP, 0xfff0007f, 0xd2000053}, // MaskConvert.py 1101001 00000 XXXXX XXX XXXXX 1010011
  {"FCVT.D.WU", COUNT_BIT,  0xfff0007f, 0xd2100053},  // MaskConvert.py 1101001 00001 XXXXX XXX XXXXX 1010011
  /* RV64D Standard Extension (in addition to RV32D)  */
  /* TBD */
};

#endif /* #ifndef RISCVCATEGORY */