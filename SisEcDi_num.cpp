#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <cstdlib>

using ptr= double(double, double,double);
double f1(double x, double y, double t);
double f2(double x, double y, double t);
void RandK(ptr fu1,ptr fu2, std::vector<double> &s,double h);
void Euler(ptr fu1,ptr fu2, std::vector<double> &s,double h);


int main(int argc, char **argv){

    const double h{std::atof(argv[1])};
    int Nmax{std::atoi(argv[2])};
    int ii=-1;
    std::vector<double> info{0};
    info.resize(11);
    info[9]=1.0;//X sobre el vecotr
    info[10]=0.0;//Y sobre el vectr
    info[0]=0.0;//t_0 sobre el vector

    std::ofstream sol("RyKS.txt");
    sol.precision(8);
    sol<<"t"<<"\t";
    sol<<"M_1"<<"\t";
    sol<<"L_1"<<"\t";
    sol<<"M_2"<<"\t";
    sol<<"L_2"<<"\t";
    sol<<"M_3"<<"\t";
    sol<<"L_3"<<"\t";
    sol<<"M_4"<<"\t";
    sol<<"L_4"<<"\t";
    sol<<"U"<<"\t";
    sol<<"V"<<"\n";
    

    while (ii<Nmax){
        
        RandK(f1,f2,info,h);
        info[0]+=h;
        if(ii%100==0){
        sol<<info[0]<<"\t";
        sol<<info[1]<<"\t";
        sol<<info[2]<<"\t";
        sol<<info[3]<<"\t";
        sol<<info[4]<<"\t";
        sol<<info[5]<<"\t";
        sol<<info[6]<<"\t";
        sol<<info[7]<<"\t";
        sol<<info[8]<<"\t";
        sol<<info[9]<<"\t";
        sol<<info[10]<<"\n";
        }
        ii++;
    }
    sol.close();

    info[9]=1.0;//condiciones inicailes no olvidar
    info[10]=0.0;
    info[0]=0.0;
    ii=0;
    

    std::ofstream solu("EulerS.txt");
    solu.precision(10);
     while (ii<Nmax){
        
        Euler(f1,f2,info,h);
        info[0]+=h;
        if(ii%100==0){
        solu<<info[0]<<"\t";
        solu<<info[9]<<"\t";
        solu<<info[10]<<"\t";
        }
        ii++;
    }
    solu.close();

    return 0;
}



double f1(double x, double y, double t){return -x/2+y/2 ;}
double f2(double x, double y, double t){return -x/4 ;}


void RandK(ptr fu1,ptr fu2,std::vector<double> &s,double h){
    double x=s[9];
    double y=s[10];
    double t=s[0];
     s[1]=fu1(x,y,t);//M_1x
     s[2]=fu2(x,y,t);//M_1y
     s[3]=fu1(x+h*s[1]/2,y+h*s[2]/2,t+h/2);//M_2x
     s[4]=fu2(x+h*s[1]/2,y+h*s[2]/2,t+h/2);//M_2y
     s[5]=fu1(x+h*s[3]/2,y+h*s[4]/2,t+h/2);//M_3x
     s[6]=fu2(x+h*s[3]/2,y+h*s[4]/2,t+h/2);//M_3y
     s[7]=fu1(x+h*s[5],y+h*s[6],t+h);//M_4x
     s[8]=fu2(x+h*s[5],y+h*s[6],t+h);//M_4y
         
    s[10] += (s[2]+2*s[4]+2*s[6]+s[8])*h/6;
    s[9] += (s[1]+2*s[3]+2*s[5]+s[7])*h/6;
}


void Euler(ptr fu1,ptr fu2, std::vector<double> &s,double h){

    s[10] += h*fu2(s[9],s[10],s[0]);
    s[9] += h*fu1(s[9],s[10],s[0]);

}

