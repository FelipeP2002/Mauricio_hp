#include<iostream>
#include<cmath>
#include <fstream>
#include<cstdlib>

using ptr= double(double, double,double);
double f1(double x, double y, double t);
double f2(double x, double y, double t);
// double Fsol1(double t);
// double Fsol2(double t);
void RandK(ptr fu1,ptr fu2, double &x,double &y, double t,double h);
void Euler(ptr fu1,ptr fu2, double &x,double &y, double t,double h);


int main(int argc, char **argv){

    const double h{std::atof(argv[1])};
    int Nmax{std::atoi(argv[2])};
    int ii=0;
    double x_0=1.0;//condiciones inicales no olvidar
    double y_0=0.0;
    double t_0=0.0;

    std::ofstream sol("RyKS.txt");
    sol.precision(10);

    while (ii<=Nmax){
           sol<<t_0<<"\t";
           sol<<x_0<<"\t";
           sol<<y_0<<"\n";
           RandK(f1,f2,x_0,y_0,t_0,h);
           t_0+=h;
           ii++;
    }
    sol.close();

    x_0=1.0;//condiciones inicailes no olvidar
    y_0=0.0;
    t_0=0.0;
    ii=0;
    

    std::ofstream solu("EulerS.txt");
    solu.precision(10);
    
    while (ii<=Nmax){
        solu<<t_0<<"\t";
        solu<<x_0<<"\t";
        solu<<y_0<<"\n";
        Euler(f1, f2, x_0, y_0 ,t_0 ,h);
        t_0+=h;
        ii++;
    }
    solu.close();

    return 0;
}



double f1(double x, double y, double t){return -x/2+y/2 ;}
double f2(double x, double y, double t){return -x/4 ;}


void RandK(ptr fu1,ptr fu2, double &x,double &y, double t,double h){

    double k1x=fu1(x,y,t);
    double k1y=fu2(x,y,t);
    double k2x=fu1(x+h*k1x/2,y+h*k1y/2,t+h/2);
    double k2y=fu2(x+h*k1x/2,y+h*k1y/2,t+h/2);
    double k3x=fu1(x+h*k2x/2,y+h*k1y/2,t+h/2);
    double k3y=fu2(x+h*k2x/2,y+h*k1y/2,t+h/2);
    double k4x=fu1(x+h*k3x,y+h*k3y,t+h);
    double k4y=fu2(x+h*k3x,y+h*k3y,t+h);
    
    y += (k1y+2*k2y+2*k3y+k4y)*h/6;
    x += (k1x+2*k2x+2*k3x+k4x)*h/6;
}


void Euler(ptr fu1,ptr fu2, double &x,double &y, double t,double h){

    y += h*fu2(x,y,t);
    x += h*fu1(x,y,t);

}

