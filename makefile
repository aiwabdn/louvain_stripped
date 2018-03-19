IDIR = ./include
SDIR = ./src
ODIR = ./obj

CXX = g++
CXXFLAGS = -I$(IDIR)
LDFLAGS = -shared
LIBS = -llouv
LIBPATH = -L$(ODIR)

_DEPS = graph.h graph_binary.h louvain.h quality.h shimalik.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = graph.o graph_binary.o louvain.o quality.o shimalik.o louv.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_MAIN = main_convert.o
MAINOBJ = $(patsubst %,$(ODIR)/%,$(_MAIN))

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CXX) -fPIC -o $@ -c $< $(CXXFLAGS)

$(ODIR)/liblouv.so: $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(ODIR)/* *~ convert $(INCDIR)/*~
