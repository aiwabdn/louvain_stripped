IDIR = ./include
SDIR = ./src
ODIR = ./obj

CXX = g++
CXXFLAGS = -I$(IDIR)
LDFLAGS = -shared
LIBS = -llouv
LIBPATH = -L$(ODIR)

_DEPS = graph.h balmod.h candora.h devind.h devuni.h dp.h goldberg.h graph_binary.h louvain.h modularity.h owzad.h quality.h shimalik.h zahn.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = graph.o graph_binary.o louvain.o quality.o modularity.o zahn.o owzad.o goldberg.o condora.o devind.o devuni.o dp.o shimalik.o balmod.o louv.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_MAIN = main_convert.o
MAINOBJ = $(patsubst %,$(ODIR)/%,$(_MAIN))

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CXX) -fPIC -o $@ -c $< $(CXXFLAGS)

$(ODIR)/liblouv.so: $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(ODIR)/* *~ convert $(INCDIR)/*~
