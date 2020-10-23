#include<iostream>
#include<cmath>
#include <fstream>
#include<cstdlib>

using ptr= double(double, double);
double f(double X, double t);
double Euler_meth(ptr fun, double x, double t,double h);
double MEGA_E_M(double x,double t, double h);


int main(int argc, char **argv){

    const double h{std::atof(argv[1])};
    int Nmax{std::atoi(argv[2])};
    int ii=0;
    double x_0=180;
    double t_0=0.0;

    std::ofstream sol("Euler.txt");
    sol.precision(10);

    while (ii<=Nmax){
        if(ii%100==0){
           sol<<t_0<<"\t";
           sol<<x_0<<"\n";}
           x_0=Euler_meth(f, x_0,t_0 ,h);
           t_0+=h;
           ii++;
    }
    sol.close();

    std::ofstream sol_M("Euler_mejorado.txt");
    sol_M.precision(10);

    x_0=180;
    t_0=0.0;
    ii=0;

    while (ii<=Nmax){
        if(ii%100==0){
           sol_M<<t_0<<"\t";
           sol_M<<x_0<<"\n";}
           x_0= MEGA_E_M(x_0,t_0 ,h);
           t_0+=h;
           ii++;
    }
    sol_M.close();

    return 0;
}

double f(double X, double t){
    double K=-0.01462445296579252;
    return K*(X-24);
}


double Euler_meth(ptr fun, double x, double t,double h){
return x+fun(x,t)*h;
}

double MEGA_E_M(double x,double t, double h){

     return x+(f(x,t)+f(Euler_meth(f,x,t,h),t+h))*h/2;
}
