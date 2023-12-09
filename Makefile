CC=g++

HDRDIR = hdr
OBJDIR = obj
SRCDIR = src
EIGENDIR = 3rd/eigen
PLOTDIR = plotting

LINKEDLIBS =  

FLAGS = -Wall -Wextra -std=c++20 -O2 -g -I$(HDRDIR) -I$(EIGENDIR)

_HDRFILES = InitParams.hpp \
			Solver.hpp \
			ExplicitEulerSolver.hpp \
			ImplicitEulerSolver.hpp \
			TrapezoidalSolver.hpp
HDRFILES = $(patsubst %,$(HDRDIR)/%,$(_HDRFILES))

_OBJFILES = main.o \
			InitParams.o \
			Solver.o \
			ExplicitEulerSolver.o \
			ImplicitEulerSolver.o \
			TrapezoidalSolver.o 
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
	@gnuplot -persist -e 'filename1="results_expl_euler.txt"; filename2="results_impl_euler.txt"; filename3="results_trapezoidal.txt"' $(PLOTDIR)/phase.p
	@gnuplot -persist -e 'filename1="results_expl_euler.txt"; filename2="results_impl_euler.txt"; filename3="results_trapezoidal.txt"' $(PLOTDIR)/energies.p

clean:
	@rm $(OBJDIR)/*.o  > /dev/null 2>&1 && echo "Object files removed" || echo "No object files to remove"
	@rm main >/dev/null 2>&1 && echo "Binary removed" || echo "No binary to remove"
	@rm *.txt>/dev/null 2>&1 && echo "Result files removed" || echo "No result files to remove"