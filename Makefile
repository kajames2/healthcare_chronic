CC := g++
SRCDIR := src
BUILDDIR := build
TESTDIR := test
TARGET := fast_dp_fitness

SRCEXT := cc
SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
TESTS := $(shell find $(TESTDIR) -type f -name "*.$(SRCEXT)")
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TESTOBJECTS := $(patsubst $(TESTDIR)/%,$(BUILDDIR)/%,$(TESTS:.$(SRCEXT)=.o))
CFLAGS := -Wall -g -std=c++17 -O3 -fopenmp
LIB := -Wl,--start-group -lgtest -lgtest_main -lpthread -lboost_filesystem-mt -lboost_system-mt -lboost_program_options-mt -Llib/ -Wl,--end-group 
INC := -I include -I lib

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $(CFLAGS) $(TARGET).$(SRCEXT) $(INC) $^ $(LIB) -o bin/$(TARGET)"; $(CC) $(CFLAGS) $(TARGET).$(SRCEXT) $(INC) $^ $(LIB) -o bin/$(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
tests_main: $(TESTOBJECTS) $(OBJECTS)
	$(CC) $(CFLAGS) tests_main.cc $(INC)  $(TESTOBJECTS) $(OBJECTS) -o bin/tests_main $(LIB)

$(BUILDDIR)/%.o: $(TESTDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	@echo " Making $(@D)"
	@echo " $(CC) $(CFLAGS) $(INC) $(LIB) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) $(LIB) -c -o $@ $<

.PHONY: clean
