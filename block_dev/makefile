CC := g++
CFLAGS := -Wall -g
LDFLAGS := -lpng -g
HEADERS := block.h
SOURCES := block.o main.o
EXE := test_block

ALL: ${EXE} clean

%.o: %.c ${HEADERS} makefile
	${CC} -c ${CFLAGS} -o $@ $<

${EXE}: ${SOURCES}
	$(CC) ${CFLAGS} ${SOURCES} -o ${EXE}

clean:
	rm *.o

clear:
	rm ${EXE}