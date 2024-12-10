SRCS := $(wildcard src/*.cc)
CXXFlAGS := std=c++17 -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast -fmax-errors=3 -g
BUILD_DIR := ./build
EXEC := Phys-cube
LDFLAGS := -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
LIB := $(wildcard lib/*.o)

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/%.cc.o: %.cc
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIB) $^ -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
