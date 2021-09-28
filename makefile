# Flags common to all targets
CFLAGS = -Wall

# All Target
all:
	$(MAKE) base_case
	$(MAKE) multithreading
	$(MAKE) multitasking

# Main build target
base_case:
	gcc $(CFLAGS) proj_1_base_case.c -o "base_case"

multithreading:
	gcc $(CFLAGS) proj_1_multithreading.c -lpthread -mcmodel=medium -fno-unwind-tables -fno-asynchronous-unwind-tables -o "multithreading"

multitasking:
	gcc $(CFLAGS) proj_1_multitasking.c -g3 -O0 -o "multitasking"

# Other targets
debug: CFLAGS += -g
debug: all

clean:
	-$(RM) "base_case" "multithreading" "multitasking"

.PHONY: all clean base_case multitasking multithreading
