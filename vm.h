#ifndef VM_H
#define VM_H

enum value_type {
  VT_BOOL,
  VT_LONG,
  VT_DOUBLE,
};

typedef struct value {
  int type;
  union {
    bool bval;
    long lval;
    double dval;
  };
} value;

#define TO_BOOL(val) (\
  val.type == VT_DOUBLE ? val.dval != 0.0 : \
  val.type == VT_LONG ? val.lval != 0 : \
  val.type == VT_BOOL ? val.bval : 0)

#define TO_LONG(val) (\
  val.type == VT_DOUBLE ? (long)val.dval : \
  val.type == VT_LONG ? val.lval : \
  val.type == VT_BOOL ? (val.bval ? 1 : 0) : 0)

#define TO_DOUBLE(val) (\
  val.type == VT_DOUBLE ? val.dval : \
  val.type == VT_LONG ? (double)val.lval : \
  val.type == VT_BOOL ? (val.bval ? 1.0 : 0.0) : 0.0)

typedef struct constant_value {
  union {
    bool bval;
    long lval;
    double dval;
  };
} constant_value;

typedef struct variable {
  char* name;
  value value;
} variable;

typedef struct env {
  uint16_t codesidx;
  uint16_t codeslen;
  uint32_t* codes;
  uint32_t constantsidx;
  uint32_t constantslen;
  constant_value* constants;
  uint32_t stackidx;
  value* stack;
  variable* variables;
  uint32_t variableslen;
  variable* local_variables;
  uint32_t local_variables_len;
  uint16_t func_pc;
  uint16_t while_pc;
} env;

typedef struct func {
  char* name;
  void (*func)(env*, value*, int);
} func;

#endif
