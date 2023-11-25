hdrdir = hdr
objdir = obj
srcdir = src
eigen = 3rd/eigen
plotdir = plotting
python_path = python_scripts

VPATH = $(hdrdir):$(objdir):$(srcdir)

objfiles = \
	$(objdir)/main.o \
	$(objdir)/Solver.o \
	$(objdir)/ExplicitEulerSolver.o \

linkedlibs = -lm

flags = -Wall -Wextra -std=c++20 -O2

main: main.o Solver.o ExplicitEulerSolver.o
	g++ $(objfiles) $(linkedlibs) -o main

main.o: main.cpp
	g++ -c $(srcdir)/main.cpp -I$(hdrdir) -I$(eigen) $(flags) -o $(objdir)/main.o

Solver.o:
	g++ -c $(srcdir)/Solver.cpp -I$(hdrdir) -I$(eigen) $(flags) -o $(objdir)/Solver.o

ExplicitEulerSolver.o: ExplicitEulerSolver.cpp
	g++ -c $(srcdir)/ExplicitEulerSolver.cpp -I$(hdrdir) -I$(eigen) $(flags) -o $(objdir)/ExplicitEulerSolver.o

run:
	./main

plot:
	gnuplot -persist $(plotdir)/phase.p $(plotdir)/energy.p

clean:
	@rm $(objdir)/*  > /dev/null 2>&1 || echo "No files to remove"
	@rm main