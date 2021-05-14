# Definition of normal variables
CC := g++
LD := g++
SOURCES := $(wildcard *.cpp)
OBJECTIVES := $(patsubst %cpp, %o, $(SOURCES))
TARGET := ComputingAssignmentTwo # PUT YOUR INTENDED NAME HERE

all: $(TARGET) clean

# Link ALL dependency files to carry out ALL target files
$(TARGET): $(OBJECTIVES)
	$(LD) -o $@ $^ -lpthread

# Compile ALL objective files EACH BY EACH
%.o:%.c
	$(CC) -c $^ 
# Definition of phony targets
.PHONY: all clear clean directory
clear:
	rm -f $(OBJECTIVES) $(TARGET)
	rm -f *.dat
	rm -f *.o
	rm -f ../output/*
clean:
	rm -f ../output/*


	
