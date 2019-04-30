SUBMITFILES = sched_ule.c Makefile README
CFLAGS = -Wall -Werror -Wextra -pedantic -O3 -Wshadow

all: 
	cc -o myshell myshell.o lex.yy.o -lfl

benchmark : benchmark.o
	cc -o benchmark benchmark.o

benchmark.o : benchmark.c
	cc -c ${CFLAGS} benchmark.c

infer:
	make clean; infer-capture -- make benchmark; infer-analyze -- make 

clean:
	rm -fr *.o benchmark infer-out *.dSYM 

git-% :
	git add ${SUBMITFILES}
	git commit -m "$(@:git-%=%)"
	git push
