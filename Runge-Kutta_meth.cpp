#include<iostream>
#include<cmath>
#include <fstream>
#include<cstdlib>

using ptr= double(double, double);
double f(double X, double t);
double RandK(ptr fun, double x, double t,double h);

int main(int argc, char **argv){

    const double h{std::atof(argv[1])};
    int Nmax{std::atoi(argv[2])};
    int ii=0;
    double x_0=1.0;
    double t_0=0.0;

    std::ofstream sol("RyK.txt");
    sol.precision(10);

    while (ii<=Nmax){
           sol<<t_0<<"\t";
           sol<<x_0<<"\n";
           x_0=RandK(f, x_0,t_0 ,h);
           t_0+=h;
           ii++;
    }
    sol.close();

    return 0;
}

double f(double X, double t){

return 1-t+4*X;
}


double RandK(ptr fun, double x, double t,double h){

    double K1=fun(x,t);
    double K2=fun(x+h*K1/2,t+h/2);
    double K3=fun(x+h*K2/2,t+h/2);
    double K4=fun(x+h*K3,t+h);
    
    return x+(K1+2*K2+2*K3+K4)*h/6;
}

