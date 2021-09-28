#!/bin/sh

gcc ./proj_1_base_case.c -o proj_1_base
./proj_1_base

gcc ./proj_1_multithreading.c -o proj_1_multithreading
./proj_1_multithreading

gcc ./proj_1_multitasking.c -o proj_1_multitasking
./proj_1_multitasking
