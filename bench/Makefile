CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -g -O0
CPPFLAGS := -MMD -MP
LDFLAGS  :=
LDLIBS   := -pthread

SRCS  := $(wildcard *.cc)
OBJS  := $(SRCS:.cc=.o)
DEPS  := $(SRCS:.cc=.d)
TARGET := test

.PHONY: all clean rebuild

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

rebuild: clean all

-include $(DEPS)
