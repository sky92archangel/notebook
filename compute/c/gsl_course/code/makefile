GCC=gcc 

LIB=/home/sky92/workspace/clib/GSL/lib # gsl lib path

INCLUDE=/home/sky92/workspace/clib/GSL/include # gsl include path

FLAGS=-lgsl -lgslcblas -lm # gsl flags

gslstudy: gslstudy.c
	$(GCC) -o gslstudy gslstudy.c -I$(INCLUDE) -L$(LIB) $(FLAGS)

clean:
	rm -f gslstudy
