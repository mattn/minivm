#ifndef OPCODE_H
#define OPCODE_H

enum OP_CODE {
  OP_POP,
  OP_LET,
  OP_LET_LOCAL,
  OP_JMP,
  OP_JMP_IF_KEEP,
  OP_JMP_NOT,
  OP_JMP_NOT_KEEP,
  OP_UFCALL,
  OP_ALLOC,
  OP_RET,
  OP_PRINT,
  OP_FCALL,
  OP_UNOT,
  OP_UADD,
  OP_UMINUS,
  OP_ADD,
  OP_MINUS,
  OP_TIMES,
  OP_DIVIDE,
  OP_GT,
  OP_GE,
  OP_EQEQ,
  OP_NEQ,
  OP_LT,
  OP_LE,
  OP_LOAD_BOOL,
  OP_LOAD_LONG,
  OP_LOAD_DOUBLE,
  OP_LOAD_IDENT,
  OP_LOAD_LOCAL_IDENT,
};

#endif
