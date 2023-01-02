#
# Author: Gagan Malvi <malvi@aospa.co>
# Date: 2022-12-22
#

CC := gcc
BINARIES_DIRECTORY := binaries
PROGRAMS := $(wildcard *.c)

# Flags to be passed to the C compiler.
OPENMP_CFLAGS := -fopenmp
EXTRA_CFLAGS := \
	-O3 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Werror \
	-Wno-unused-parameter \
	-Wno-unused-variable \
	-Wno-unused-function \
	-Wno-unused-label \
	-Wno-unused-value \
	-Wno-unused-result \
	-Wno-unused-but-set-variable \
	-Wno-missing-field-initializers \
	-Wno-missing-braces

all: 
	for program in $(PROGRAMS); do \
		echo -e "\033[0;34m[-]\033[0m Building: \033[0;31m$$program...\033[0m" ; \
		$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(OPENMP_CFLAGS) $$program -o $(BINARIES_DIRECTORY)/$${program%.*}; \
	done

clean:
	rm -rf $(BINARIES_DIRECTORY)/*