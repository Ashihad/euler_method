hdrdir = hdr
objdir = obj
srcdir = src
eigen = 3rd/eigen

VPATH = $(hdrdir):$(objdir):$(srcdir)

objfiles = $(objdir)/main.o $(objdir)/logic.o

linkedlibs = -lm

flags = -Wall -Wextra -std=c++20 -O2

main: main.o logic.o
	g++ $(objfiles) $(linkedlibs) -o main

main.o: main.cpp logic.cpp
	g++ -c $(srcdir)/main.cpp -I$(hdrdir) -I$(eigen) $(flags) -o $(objdir)/main.o

logic.o: logic.cpp
	g++ -c $(srcdir)/logic.cpp -I$(hdrdir) -I$(eigen) $(flags) -o $(objdir)/logic.o

clean:
	@rm $(objdir)/*  > /dev/null 2>&1 || echo "No files to remove" 