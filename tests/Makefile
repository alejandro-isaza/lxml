CXX ?= g++

INCLUDES = -I../src -I/usr/include/libxml2
CXXFLAGS = -std=c++11 -O2 -Wall -g
LDLIBS = -lxml2 -lboost_unit_test_framework-mt

SRC_EXT    = cpp
BUILD_PATH = ../build
BIN_NAME   = test-runner
LIB        = ../src/liblxml.a

SRCS = $(wildcard *.$(SRC_EXT))
OBJS = $(SRCS:%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
DEPS = $(OBJS:.o=.d)

.PHONY: all dirs test clean

all: test

test: dirs $(BIN_NAME)
	@./$(BIN_NAME)

# Create the directories used in the build
dirs:
	@mkdir -p $(dir $(OBJS))

# Compile executable
$(BIN_NAME): $(OBJS) $(LIB)
	@$(CXX) $(LDFLAGS) $(LDLIBS) -o $@ $^

# Main library dependency
$(LIB):
	$(MAKE) -C ../src liblxml.a

clean:
	rm -f $(OBJS) $(DEPS) $(BIN_NAME)

# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
$(BUILD_PATH)/%.o: %.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@
