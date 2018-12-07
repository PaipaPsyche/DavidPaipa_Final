all: set comp ex pyt clean

set:
	export OMP_NUM_THREADS=8

comp:
	gcc -fopenmp OPENMP_BAYES.c -o exec -lm
ex:
	./exec 1000 1 0
	
pyt:
	python plot1.py

clean:
	rm exec
	
