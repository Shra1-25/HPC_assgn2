all: MMult1 val_test01_solved val_test02_solved omp_solved2 omp_solved3 omp_solved4 omp_solved5 omp_solved6 jacobi2D-omp gs2D-omp

MMult1: MMult1.cpp
	g++ -std=c++11 -fopenmp -O3 -march=native MMult1.cpp -o MMult1
val_test01_solved: val_test01_solved.cpp
	g++ -std=c++11 val_test01_solved.cpp -o val_test01_solved
val_test02_solved: val_test02_solved.cpp
	g++ -std=c++11 val_test02_solved.cpp -o val_test02_solved
omp_solved2: omp_solved2.c
	gcc -fopenmp omp_solved2.c -o omp_solved2
omp_solved3: omp_solved3.c
	gcc -fopenmp omp_solved3.c -o omp_solved3
omp_solved4: omp_solved4.c
	gcc -fopenmp omp_solved4.c -o omp_solved4
omp_solved5: omp_solved5.c
	gcc -fopenmp omp_solved5.c -o omp_solved5
omp_solved6: omp_solved6.c
	gcc -fopenmp omp_solved6.c -o omp_solved6
jacobi2D-omp: jacobi2D-omp.c
	g++ -std=c++11 -fopenmp -O3 jacobi2D-omp.c -o jacobi2D-omp -lm
gs2D-omp: gs2D-omp.c
	g++ -std=c++11 -fopenmp -O3 gs2D-omp.c -o gs2D-omp -lm
clean:
	rm -f MMult1 *~
	rm -f val_test01_solved *~
	rm -f val_test02_solved *~
	rm -f omp_solved2 *~
	rm -f omp_solved3 *~
	rm -f omp_solved4 *~
	rm -f omp_solved5 *~
	rm -f omp_solved6 *~
	rm -f jacobi2D-omp *~
	rm -f gs2D-omp *~
