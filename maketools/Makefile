CC := g++
LD := g++
SOURCES := $(wildcard ./src/*.cpp)
OBJECTIVES := $(patsubst ./src/%cpp, %o, $(SOURCES))
CLEAN_CLEAR_OBJECTIVES := $(patsubst ./src/%cpp, ./out/%o, $(SOURCES))
TARGET := PutYourNameHere # PUT YOUR INTENDED NAME HERE

$(TARGET): $(OBJECTIVES)																		
		$(LD) -o $@ $^;											
		mv *.o out;	
		rm -f $(OBJECTIVES)

%.o:$(SOURCES)
	$(CC) -c $^

.PHONY: all
all:
	$(TARGET)

.PHONY: clear
clear:
	rm -f $(OBJECTIVES) $(CLEAN_CLEAR_OBJECTIVES) $(TARGET)

.PHONY: clean
clean:
	rm -f $(OBJECTIVES) $(CLEAN_CLEAR_OBJECTIVES)

.PHONY: dir
dir:
	bash make_dir.sh