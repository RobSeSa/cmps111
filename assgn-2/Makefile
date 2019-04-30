SUBMITFILES = sched_ule.c benchmark.c Makefile README
CFLAGS = -Wall -Werror -Wextra -pedantic -O3 -Wshadow

all: benchmark

benchmark : benchmark.o printLoop.o
	cc -o benchmark benchmark.o printLoop.o

benchmark.o : benchmark.c printLoop.c
	cc -c ${CFLAGS} benchmark.c printLoop.c

infer:
	make clean; infer-capture -- make benchmark; infer-analyze -- make 

clean:
	rm -fr *.o benchmark infer-out *.dSYM 

git-% :
	git add ${SUBMITFILES}
	git commit -m "$(@:git-%=%)"
	git push
