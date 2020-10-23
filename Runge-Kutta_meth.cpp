#include<iostream>
#include<cmath>
#include<vector>
#include <fstream>
#include<cstdlib>

using ptr= double(double, double);
double f(double X, double t);
void RandK(ptr fun, std::vector<double> &s,double h);

int main(int argc, char **argv){

    const double h{std::atof(argv[1])};
    int Nmax{std::atoi(argv[2])};
    int ii=1;
    std::vector<double> info{0};
    info.resize(6);
    info[0]=18;//x
    info[1]=0.0;//tiempo

    std::ofstream sol("RyK.txt");
    sol.precision(10);
    while (ii<=Nmax){
        RandK(f,info,h);
        //info[1]+=h;
        if(ii%10==0){
            sol<<info[1]<<"\t";
            sol<<info[2]<<"\t";            
            sol<<info[3]<<"\t";
            sol<<info[4]<<"\t";
            sol<<info[5]<<"\t";
            sol<<info[0]<<"\n";
        }
        ++ii;   
    }
    sol.close();

    return 0;
}

double f(double X, double t){
return 4*X*std::log(75/X)/5;
}


void RandK(ptr fun, std::vector<double> &s ,double h){
    double x =s[0];
    double t =s[1];
    s[2]=fun(x,t);//M_1
    s[3]=fun(x+h*s[2]/2,t+h/2);//M_2
    s[4]=fun(x+h*s[3]/2,t+h/2);//M_3
    s[5]=fun(x+h*s[4],t+h);//M_4
   
    s[0] +=(s[2]+2*s[3]+2*s[4]+s[5])*h/6;
    s[1] +=h;
}

