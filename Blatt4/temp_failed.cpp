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





//Definition der Funktion F für DGLs

void f(Status oldStatus, Parameter parameter, Status& newStatus){

    newStatus.Phi = parameter.LM * (1 + parameter.eps * cos(oldStatus.Phi))*(1 + parameter.eps * cos(oldStatus.Phi)) / (parameter.a * parameter.a * (1 - parameter.eps * parameter.eps) * (1 - parameter.eps * parameter.eps)) ;  
    newStatus.Teta = -1/2 * parameter.alpha * parameter.alpha * pow((1 + parameter.eps*cos(oldStatus.Phi))/(1 - (parameter.eps * parameter.eps)), 3) * sin(2*(oldStatus.Teta - oldStatus.Phi));

}


//Einzelner Schritt des Runge Kutta Verfahrens

void rungeKuttaStep(Status oldStatus, Parameter parameter, Status& newStatus, double h){

    //Definition für f(x_i)
    Status f_i;
    f(oldStatus, parameter, f_i);

    //Definition für f(x_(i+1))
    Status f_i1;

    Status rechnung;

    rechnung.Phi = oldStatus.Phi + h*f_i.Phi;
    rechnung.Phi_pri = oldStatus.Phi_pri + h*f_i.Phi_pri;
    rechnung.Teta = oldStatus.Teta + h*f_i.Teta;
    rechnung.Teta_pri = oldStatus.Teta_pri + h*f_i.Teta_pri;

    f(rechnung, parameter, f_i1);

    //Rechenschritt
    newStatus.Phi = oldStatus.Phi + h/2 * (f_i.Phi + f_i1.Phi);
    newStatus.Phi_pri = oldStatus.Phi_pri + h/2 * (f_i.Phi_pri + f_i1.Phi_pri);
    newStatus.Teta = oldStatus.Teta + h/2 * (f_i.Teta + f_i1.Teta);
    newStatus.Teta_pri = oldStatus.Teta_pri + h/2 * (f_i.Teta_pri + f_i1.Teta_pri);

}


//Anwendung des Runge Kutta Verfahrens

//[[Rcpp::export]]
void Simulation(Status oldStatus, Parameter Phobos, Status& newStatus, double h, double Rounds)
{




    for (double i = 0; i < Rounds ; i+=h)
    {
        rungeKuttaStep(oldStatus, Phobos, oldStatus, h);
        printf("Teta = %f  Teta_pri = %f   Phi = %f   Phi_pri = %f \n", oldStatus.Teta, oldStatus.Teta_pri, oldStatus.Phi, oldStatus.Phi_pri);
    }
    
}




int main(int argc, char const *argv[])
{
    //Definition der Parameter
    Parameter Phobos;
    Phobos.a = 1;
    Phobos.alpha = 0.83;
    Phobos.T = 7 + 2/3; //Stunden
    Phobos.eps = 0.015;
    Phobos.LM = 1;
    
    //Anfangswerte
    Status old;
    old.Phi = 0;
    old.Phi_pri = 20;
    old.R = (1 - (Phobos.eps * Phobos.eps))/(1 + Phobos.eps*cos(old.Phi));
    old.Teta = 0;
    old.Teta_pri = 1;


    Simulation(old, Phobos, old, 0.01, 10);
    return 0;
}
