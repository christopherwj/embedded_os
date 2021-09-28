# Flags common to all targets
CFLAGS  = -std=c++11
CFLAGS += -Wall -Werror 

# All Target
all:
	$(MAKE) base_case
	$(MAKE) multithreading
	$(MAKE) multitasking

# Main build target
base_case:
	g++ $(CFLAGS) proj_1_base_case.c -o "base_case"

multithreading:
	g++ $(CFLAGS) proj_1_multithreading.c -lpthread -mcmodel=medium -fno-unwind-tables -fno-asynchronous-unwind-tables -o "multithreading"

multitasking:
	g++ $(CFLAGS) proj_1_multitasking.c -g3 -O0 -o "multitasking"

# Other targets
debug: CFLAGS += -g
debug: all

clean:
	-$(RM) "base_case" "multithreading" "multitasking"

.PHONY: all clean base_case multitasking multithreading
