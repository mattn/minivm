svm: main.c codegen.c vm.c state.c node.c y.tab.c lex.yy.c
	cc -o svm main.c state.c node.c y.tab.c lex.yy.c

y.tab.c y.tab.h: parser.y node.c node.h
	yacc -dvy $<

lex.yy.c lex.yy.h: lexer.l
	lex --header-file=lex.yy.h $<

test:
	@bash test/test.sh

clean:
	rm -f svm y.tab.c y.tab.h y.output lex.yy.c lex.yy.h

.PHONY: test clean
