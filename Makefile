CXX=g++
IDIR=$(PWD)/include
ODIR=$(PWD)/obj
SDIR=$(PWD)/src
DEPS=$(IDIR)/flow_board.h
CXXFLAGS=-pthread -std=c++17 -O3 -Wall -Wextra -g -I$(IDIR)

.PHONY: all
all: $(ODIR)/main

$(ODIR)/main: $(ODIR)/main.o $(ODIR)/flow_board.o
	$(CXX) $(CXXFLAGS) -o $@ $^
$(ODIR)/main.o: $(SDIR)/main.cpp $(SDIR)/flow_board.cpp $(IDIR)/flow_board.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(ODIR)/flow_board.o: $(SDIR)/flow_board.cpp $(IDIR)/flow_board.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf $(ODIR)/*
