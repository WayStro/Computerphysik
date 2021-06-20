#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>


typedef struct 
{
    double R,Phi,Phi_pri,Teta,Teta_pri;   //pri steht für Ableitung
} Status;

typedef struct 
{
    double eps, T, a, alpha, LM;
} Parameter;

void f(Status oldStatus, Parameter parameter, Status& newStatus){

    newStatus.Phi = parameter.LM * 1./(oldStatus.R * oldStatus.R);
    newStatus.R = parameter.a * (1. - (parameter.eps * parameter.eps)) * parameter.eps * sin(oldStatus.Phi * 3.14/180.) / ( (1. + parameter.eps * cos(oldStatus.Phi * 3.14/180.)) * (1. + parameter.eps * cos(oldStatus.Phi))) * oldStatus.Phi_pri;
    newStatus.Teta_pri = -1./2. * pow(2.*3.14 / parameter.T, 2) * pow(parameter.alpha, 2) * pow(parameter.a/oldStatus.R, 3) * sin(2.*(oldStatus.Teta - oldStatus.Phi)* 3.14/180);
    newStatus.Teta = oldStatus.Teta_pri;

    // printf("%.10f %.10f %.10f %.10f \n", newStatus.Phi, newStatus.R, newStatus.Teta_pri, newStatus.Teta);
}

void Euler(Status oldStatus, Parameter parameter, Status& newStatus, double h) {

    Status f_i;
    f(oldStatus, parameter, f_i);

    //Definition für f(x_(i+1))
    Status f_i1;

    Status rechnung;
    rechnung.Phi = oldStatus.Phi + h*f_i.Phi;
    rechnung.R = oldStatus.R + h*f_i.R;
    rechnung.Teta_pri = oldStatus.Teta_pri + h*f_i.Teta_pri;
    rechnung.Teta = oldStatus.Teta + h*f_i.Teta;   

    f(rechnung, parameter, f_i1);

    //Rechenschritt
    newStatus.Phi = oldStatus.Phi + h/2. * (f_i.Phi + f_i1.Phi);
    newStatus.R = oldStatus.R + h/2. * (f_i.R + f_i1.R);
    newStatus.Teta_pri = oldStatus.Teta_pri + h/2. * (f_i.Teta_pri + f_i1.Teta_pri);
    newStatus.Teta = oldStatus.Teta + h/2. * (f_i.Teta + f_i1.Teta);

}


//[[Rcpp::export]]
void Simulation(Status oldStatus, Parameter Phobos, double h, double Rounds, FILE* fp)
{

    int k = 1;
    for (double i = 0; i < Rounds ; i+=h)
    {
        Euler(oldStatus, Phobos, oldStatus, h);



        
        // if (oldStatus.Phi >= k*2*M_PI)
        // {
            fprintf(fp, "%f  %f   %f   %f \n", oldStatus.Teta, oldStatus.Teta_pri, oldStatus.Phi, oldStatus.R);
            // k +=1;
        // }
        
        
    }   
}




int main(int argc, char const *argv[])
{
    //Definition der Parameter
    Parameter phobos;
    phobos.a = 1.;
    phobos.alpha = 0.83;
    phobos.T = 100.;
    phobos.eps = 0.3;
    phobos.LM = 0.5;

    
    //Anfangswerte
    Status old;
    old.Phi = 0;
    old.R = 1. - pow(phobos.eps, 2);
    old.Teta = 0;
    old.Teta_pri = 42;



    FILE* fp;

    fp=fopen("data.txt","w");
    if(fp==NULL){
        printf("missing file\n");
        return 1;
    }
    
    Simulation(old, phobos, 0.01, 100, fp);

    fclose(fp);

    

    return 0;
}
