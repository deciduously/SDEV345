.PHONY: all clean help

CXX=clang++
FLAGS=-std=c++17 -Wall -Wextra -Werror -pedantic -c -g

BUILDDIR=build
SOURCEDIR=src
EXEC=insertion-sort

SOURCES:=$(wildcard $(SOURCEDIR)/*.cpp)
OBJ:=$(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

all: dir $(BUILDDIR)/$(EXEC)

dir:
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/$(EXEC): $(OBJ)
	$(CXX) $^ -o $@

$(OBJ): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CXX) $(FLAGS) $< -o $@

clean:
	rm -rf $(BUILDDIR)/*.o $(BUILDDIR)/$(EXEC)

help:
	@echo "Usage: make {all|clean|help}" 1>&2 && false
