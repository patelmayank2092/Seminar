#include<iostream>
#include<vector>
#include"Grid_int.h"
#include"Grid.h"
#include"Solver.h"
#include<sys/time.h>
#include<omp.h>

int main(int argc, char *argv[])
{

int l_Level = std::stoi(argv[1]);
//int n_Vcycle= std::stoi(argv[2]);


//std::cout<< "l = " << l_Level << std::endl;

/*
struct timeval x;
gettimeofday(&x,NULL);



Solver S(l_Level);

double start=x.tv_sec + 1e-6*x.tv_usec;

S.Simulation();

gettimeofday(&x,NULL);
double end=x.tv_sec + 1e-6*x.tv_usec;

std::cout<<(end-start)<<" seconds"<<std::endl;
*/

struct timeval t0, t;
gettimeofday(&t0, NULL);

Solver S(l_Level);
std::vector<double> u = S.Simulation();
gettimeofday(&t, NULL);
std::cout << "Wall clock time of MG execution: " <<((int64_t)(t.tv_sec - t0.tv_sec) * (int64_t)1000000 +(int64_t)t.tv_usec - (int64_t)t0.tv_usec) * 1e-3<< " ms" << std::endl;
Grid_int G(l_Level);
std::vector<double> u_exact=G.U_exact();
int n=sqrt(u_exact.size());

S.store(n,u,u_exact);

return 0;

}
