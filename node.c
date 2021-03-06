#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "state.h"
#include "y.tab.h"

node* new_cons(state* s, node* car, node* cdr) {
  node* n = new_node(s);
  n->car = car;
  n->cdr = cdr;
  return n;
}

node* append(node* n, node* m) {
  node* k = n;
  while (k->cdr != NULL) {
    k = k->cdr;
  }
  k->cdr = m;
  return n;
}

node* new_uop(state* s, int op, node* n) {
  return new_cons(s, nint(NODE_UNARYOP), new_cons(s, nint(op), n));
}

node* new_binop(state* s, int op, node* lhs, node* rhs) {
  return new_cons(s, nint(NODE_BINOP), new_cons(s, nint(op), new_cons(s, lhs, rhs)));
}

void print_uop(node* n, int indent) {
  switch (intn(n->car)) {
    case NOT: printf("(!)"); break;
    case PLUS: printf("(+)"); break;
    case MINUS: printf("(-)"); break;
    default:
      printf("unknown unary operator %d", intn(n->car));
      exit(1);
  }
  print_node(n->cdr, indent + 2);
}

void print_binop(node* n, int indent) {
  switch (intn(n->car)) {
    case OR: printf("(||)"); break;
    case AND: printf("(&&)"); break;
    case PLUS: printf("(+)"); break;
    case MINUS: printf("(-)"); break;
    case TIMES: printf("(*)"); break;
    case DIVIDE: printf("(/)"); break;
    case GT: printf("(>)"); break;
    case GE: printf("(>=)"); break;
    case EQEQ: printf("(==)"); break;
    case NEQ: printf("(!=)"); break;
    case LT: printf("(<)"); break;
    case LE: printf("(<=)"); break;
    default:
      printf("unknown binary operator %d", intn(n->car));
      exit(1);
  }
  print_node(n->cdr->car, indent + 2);
  print_node(n->cdr->cdr, indent + 2);
}

void print_node(node* n, int indent) {
  int i;
  if (n == NULL)
    return;
  if (indent != 0)
    printf("\n");
  for (i = 0; i < indent; i++) {
    printf(" ");
  }
  printf("(");
  switch (intn(n->car)) {
    case NODE_FUNCTION: {
      node* m = n->cdr->cdr->car;
      printf("func %s (", (char*)n->cdr->car);
      while (m != NULL) {
        printf("%s", (char*)m->car);
        m = m->cdr;
        if (m != NULL)
          printf(", ");
      }
      printf(")");
      print_node(n->cdr->cdr->cdr, indent + 2);
      break;
    }
    case NODE_RETURN:
      printf("return (");
      print_node(n->cdr, indent + 2);
      printf(")");
      break;
    case NODE_STMTS:
      n = n->cdr;
      while (n != NULL) {
        print_node(n->car, indent + 2);
        n = n->cdr;
      }
      break;
    case NODE_ASSIGN:
      printf("let %s", (char*)n->cdr->car);
      print_node(n->cdr->cdr, indent + 2);
      break;
    case NODE_IF:
      printf("if");
      print_node(n->cdr->car, indent + 2);
      print_node(n->cdr->cdr->car, indent + 2);
      if (n->cdr->cdr->cdr != NULL) {
        printf("\n");
        for (i = 0; i < indent; i++) {
          printf(" ");
        }
        printf("else");
        print_node(n->cdr->cdr->cdr, indent + 2);
      }
      break;
    case NODE_WHILE:
      printf("while");
      print_node(n->cdr->car, indent + 2);
      print_node(n->cdr->cdr, indent + 2);
      break;
    case NODE_BREAK:
      printf("break");
      break;
    case NODE_CONTINUE:
      printf("continue");
      break;
    case NODE_PRINT:
      printf("print");
      print_node(n->cdr, indent + 2);
      break;
    case NODE_FCALL: {
      node* m;
      printf("call %s", (char*)n->cdr->car);
      m = n->cdr->cdr;
      while (m != NULL) {
        print_node(m->car, indent + 2);
        m = m->cdr;
      }
      break;
   }
    case NODE_UNARYOP:
      print_uop(n->cdr, indent);
      break;
    case NODE_BINOP:
      print_binop(n->cdr, indent);
      break;
    case NODE_BOOL:
      if ((intptr_t)n->cdr == 1)
        printf("bool true");
      else
        printf("bool false");
      break;
    case NODE_DOUBLE:
      printf("double %lf", strtod((char*)n->cdr, NULL));
      break;
    case NODE_LONG:
      printf("long %ld", atol((char*)n->cdr));
      break;
    case NODE_IDENTIFIER:
      printf("identifier %s", (char*)n->cdr);
      break;
    default:
      printf("Unknown node %d", intn(n->car));
      exit(1);
  }
  printf(")");
  if (indent == 0)
    printf("\n");
}
