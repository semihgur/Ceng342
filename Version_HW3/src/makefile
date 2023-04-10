IDIR =../include
CC=mpicc
CFLAGS=-I$(IDIR) -lstdc++ -lmpi_cxx -g -Wall
ARGS=-n 4
ARGS_SIZE=1017
ARGS_FILENAME=Output.txt
TESTARGS=4

ODIR=obj
EXECDIR=../bin
_DEPS = hellomake.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = 19050111017.o hellofunc.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

19050111017: $(OBJ)
	$(CC) -o $(EXECDIR)/$@ $^ $(CFLAGS)
	mpirun $(ARGS) $(EXECDIR)/$@ $(ARGS_SIZE) $(ARGS_SIZE) $(ARGS_FILENAME)

testcompile: mpiTest.cpp
	$(CC) $^ -o $(EXECDIR)/$@ $(CFLAGS)

testrun: testcompile
	mpirun -np $(TESTARGS) $(EXECDIR)/$^

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(EXECDIR)/*