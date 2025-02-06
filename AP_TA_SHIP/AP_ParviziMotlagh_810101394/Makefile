PROJECT_NAME := MK.out
CC        := g++ -std=c++11
SRCDIR    := src
HEADERDIR := include
BUILDDIR  := build
TARGET    := $(PROJECT_NAME)

SOURCES   := $(SRCDIR)/main.cpp $(SRCDIR)/feature_tree.cpp $(SRCDIR)/feature_node.cpp $(SRCDIR)/mandatory_node.cpp $(SRCDIR)/optional_node.cpp $(SRCDIR)/or_node.cpp $(SRCDIR)/xor_node.cpp 
HEADERS   := $(HEADERDIR)/feature_tree.hpp $(HEADERDIR)/feature_node.hpp $(HEADERDIR)/mandatory_node.hpp $(HEADERDIR)/optional_node.hpp $(HEADERDIR)/or_node.hpp $(HEADERDIR)/xor_node.hpp $(HEADERDIR)/manual.hpp
OBJECTS   := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .o,$(basename $(SOURCES))))
DEPS      := $(OBJECTS:.o=.d)
INC       := -I $(HEADERDIR)

all: $(TARGET)

clean:
	@rm -rf $(BUILDDIR) $(TARGET)
	@echo "Cleaned build files."

$(TARGET): $(BUILDDIR) $(OBJECTS)
	@echo "Linking object files..."
	@$(CC) $(OBJECTS) -o $(TARGET)
	@echo "$(TARGET) has been created!"

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(INC) -c $< -o $@

-include $(DEPS)

.PHONY: clean all
