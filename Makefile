CC=g++

HDRDIR = hdr
OBJDIR = obj
SRCDIR = src
EIGENDIR = 3rd/eigen
PLOTDIR = plotting

LINKEDLIBS =  

FLAGS = -Wall -Wextra -std=c++20 -O2 -g -I$(HDRDIR) -I$(EIGENDIR)

_HDRFILES = Solvers.hpp \
			InitParams.hpp 
HDRFILES = $(patsubst %,$(HDRDIR)/%,$(_HDRFILES))

_OBJFILES = main.o \
			InitParams.o \
			Solver.o \
			ExplicitEulerSolver.o \
			TrapezoidalSolver.o \
			InitParams.o
OBJFILES = $(patsubst %,$(OBJDIR)/%,$(_OBJFILES))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HDRFILES)
	$(CC) -c -o $@ $< $(FLAGS)

main: $(OBJFILES)
	$(CC) -o $@ $^ $(FLAGS) $(LINKEDLIBS) 

.PHONY: run plot clean

run:
	@echo "Running program..."
	@./main
	@echo "Program finished"

plot:
	gnuplot -persist -e "filename='results_euler.txt'" $(PLOTDIR)/phase.p
	gnuplot -persist -e "filename='results_euler.txt'" $(PLOTDIR)/energy.p
	gnuplot -persist -e "filename='results_trapezoidal.txt'" $(PLOTDIR)/phase.p
	gnuplot -persist -e "filename='results_trapezoidal.txt'" $(PLOTDIR)/energy.p

clean:
	@rm $(OBJDIR)/*.o  > /dev/null 2>&1 && echo "Object files removed" || echo "No object files to remove"
	@rm main >/dev/null 2>&1 && echo "Binary removed" || echo "No binary to remove"
	@rm *.txt>/dev/null 2>&1 && echo "Result files removed" || echo "No result files to remove"