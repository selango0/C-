# Basic make file
#

CXX:=g++
STD:=-std=c++11
CFLAGS:=-Wall -Werror -Weffc++ -pedantic
DEBUG_FLAGS:=-g -O2

SRC:=$(wildcard *.cpp)
HEADERS:=$(wildcard *.h)
OBJ:=$(SRC:.cpp=.o)
TRGT:=main.exe

GMP_LIBS:=-lgmp -lgmpxx

TEST:=test/test.py

NAM:=$(shell echo "$(wordlist 4,5,$(shell finger $(USER)))" | sed -e 's/ /_/g')
DIR := $(lastword $(subst /, ,$(PWD)))
ZIP_FILE  = $(shell echo $(DIR)_$(NAM).zip | tr A-Z a-z)

ZIP:=$(wildcard *.zip)

$(TRGT): $(OBJ)
	$(CXX) $(STD) $(GMP_LIBS) $^ -o $@

clean:
	rm -f $(OBJ) $(TRGT) *.txt *.pyc

test: $(TEST) $(TRGT)
	@python $(TEST)

zip: clean
	zip -r $(ZIP_FILE) *

unzip: $(TAR)
	tar -xzvf $(TAR)

%.o: %.cpp $(HEADERS)
	$(CXX) $(STD) $(DEBUG_FLAGS) $(CFLAGS) -c $< -o $@

.PHONY:all clean test zip

