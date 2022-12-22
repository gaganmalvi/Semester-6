#
# Author: Gagan Malvi <malvi@aospa.co>
# Date: 2022-12-22
#

BINARIES_DIRECTORY := binaries
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

introduction: 
	gcc -o $(BINARIES_DIRECTORY)/introduction introduction.c $(OPENMP_CFLAGS) $(EXTRA_CFLAGS)

dot-product:
	gcc -o $(BINARIES_DIRECTORY)/dot-product dot-product.c $(OPENMP_CFLAGS) $(EXTRA_CFLAGS)

vector-addition:
	gcc -o $(BINARIES_DIRECTORY)/vector-addition vector-addition.c $(OPENMP_CFLAGS) $(EXTRA_CFLAGS)

array-sum-sequential: 
	gcc -o $(BINARIES_DIRECTORY)/array-sum-sequential array-sum-sequential.c $(OPENMP_CFLAGS) $(EXTRA_CFLAGS)

all: 
	make dot-product
	make vector-addition
	make introduction

clean:
	rm -rf $(BINARIES_DIRECTORY)/*