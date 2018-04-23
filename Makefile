#Michelle Godwin (mlg160030@utdallas.edu)
#CS3377.502
#Project #6
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses

EXECFILE = program6

OBJS = program6.o

#For building the project
all: $(EXECFILE)

#For keeping the folder clean
clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*

tidy:
	rm -f $(OBJS) *.P *~ \#*

#For build object files
$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

