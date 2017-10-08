PROGRAM=PROG
BINDIR = bin
SRC = src
OBJ = obj
INC = include

# Auxilary headers
SNOWGOOSE=$(ROOT)snowgoose
COMPI=$(ROOT)COMPI
OPTITEST=$(ROOT)OPTITEST
NUC=$(ROOT)NUC
EXTRA_INC = -I../  -I$(SNOWGOOSE) -I$(COMPI) -I$(OPTITEST) -I$(NUC)



CC     = g++
CLINK  = $(CC) 
C_LIB  = -lm
CFLAGS = -std=c++14 -Wall -O3 -I${INC} ${EXTRA_INC} -fopenmp
CLINKFLAGS= -O3 -fopenmp


OBJS = ${OBJ}/main.o \
	${OBJ}/CPU_GO_DFS.o \
	${OBJ}/CPU_GO_FULL_SPLIT.o \
	${OBJ}/CPU_GO_FULL_SPLIT_00.o \
	${OBJ}/CPU_GO_FULL_SPLIT_OMP.o \
	${OBJ}/boxes_sort.o \

${BINDIR}/${PROGRAM}: crdir ${OBJS}
	${CLINK} ${CLINKFLAGS} -o ${BINDIR}/${PROGRAM} ${OBJS} ${C_LIB}

crdir:
	mkdir -p obj
	mkdir -p bin
	
${OBJ}/main.o: ${SRC}/main.cpp ${INC}/interval.h ${INC}/test_func_with_lib.h 
	$(CC) $(CFLAGS) -c ${SRC}/main.cpp -o ${OBJ}/main.o
${OBJ}/CPU_GO_DFS.o: ${SRC}/CPU_GO_DFS.cpp 
	$(CC) $(CFLAGS) -c ${SRC}/CPU_GO_DFS.cpp -o ${OBJ}/CPU_GO_DFS.o
${OBJ}/CPU_GO_FULL_SPLIT.o: ${SRC}/CPU_GO_FULL_SPLIT.cpp 
	$(CC) $(CFLAGS) -c ${SRC}/CPU_GO_FULL_SPLIT.cpp -o ${OBJ}/CPU_GO_FULL_SPLIT.o
${OBJ}/CPU_GO_FULL_SPLIT_00.o: ${SRC}/CPU_GO_FULL_SPLIT_00.cpp 
	$(CC) $(CFLAGS) -c ${SRC}/CPU_GO_FULL_SPLIT_00.cpp -o ${OBJ}/CPU_GO_FULL_SPLIT_00.o
${OBJ}/CPU_GO_FULL_SPLIT_OMP.o: ${SRC}/CPU_GO_FULL_SPLIT_OMP.cpp 
	$(CC) $(CFLAGS) -c ${SRC}/CPU_GO_FULL_SPLIT_OMP.cpp -o ${OBJ}/CPU_GO_FULL_SPLIT_OMP.o
${OBJ}/boxes_sort.o: ${SRC}/boxes_sort.cpp 
	$(CC) $(CFLAGS) -c ${SRC}/boxes_sort.cpp -o ${OBJ}/boxes_sort.o


clean:
	rm -rf ${OBJ}
	rm -rf bin
cleanall:
	rm -f ${OBJ}/*.o ${BINDIR}/${PROGRAM}
