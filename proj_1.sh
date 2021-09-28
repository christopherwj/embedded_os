#!/bin/sh

gcc ./proj_1_base_case.c -o proj_1_base.o
./proj_1_base.o

gcc ./proj_1_multithreading.c -o proj_1_multithreading.o
./proj_1_multithreading.o

gcc ./proj_1_multitasking.c -o proj_1_multitasking.o
./proj_1_multitasking.o
