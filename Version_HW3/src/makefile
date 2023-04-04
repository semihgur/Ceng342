IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -lstdc++
ARGS=5 6 solution.txt

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
	$(EXECDIR)/19050111017 $(ARGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(EXECDIR)/*