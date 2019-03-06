# Basic make file
#

CXX:=g++
STD:=-std=c++11
CFLAGS:=-Wall -Werror -Weffc++ -pedantic
DEBUG_FLAGS:=-g -O2

SRC:=$(wildcard *.cpp)
OBJ:=$(SRC:.cpp=.o)
TRGT:=main.exe

INCLUDES:=-isystem /usr/include/python2.7/
PYTHON_LIBDIR:=/usr/lib/x86_64-linux-gnu
PYTHON_LIB:=python2.7

TEST:=test/test.py

NAM:=$(shell echo "$(wordlist 4,5,$(shell finger $(USER)))" | sed -e 's/ /_/g')
DIR := $(lastword $(subst /, ,$(PWD)))
ZIP_FILE  = $(shell echo $(DIR)_$(NAM).zip | tr A-Z a-z)

ZIP:=$(wildcard *.zip)

$(TRGT): $(OBJ)
	$(CXX) -L$(PYTHON_LIBDIR) -l$(PYTHON_LIB) $^ -o $@

clean:
	rm -f $(OBJ) $(TRGT) *.txt *.pyc

test: $(TEST) $(TRGT)
	@python $(TEST)

zip: clean
	zip -r $(ZIP_FILE) *

unzip: $(TAR)
	tar -xzvf $(TAR)

%.o: %.cpp PythonVisualizer.h
	$(CXX) $(STD) $(DEBUG_FLAGS) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY:all clean test zip

