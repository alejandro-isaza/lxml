CXX ?= g++

INCLUDES = -I/usr/include/libxml2
CXXFLAGS = -std=c++11 -O2 -Wall -g

SRC_EXT    = cpp
BUILD_PATH = ../build
BIN_NAME   = liblxml.a

SRCS = $(wildcard *.$(SRC_EXT))
OBJS = $(SRCS:%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
DEPS = $(OBJS:.o=.d)

.PHONY: all dirs clean

all: dirs $(BIN_NAME)

# Create the directories used in the build
dirs:
	@mkdir -p $(dir $(OBJS))

# Create static library
$(BIN_NAME): $(OBJS)
	@echo "Archiving library $@"
	@ar -rs $@ $^

clean:
	rm -f $(OBJS) $(DEPS) $(BIN_NAME)

# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
$(BUILD_PATH)/%.o: %.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@
