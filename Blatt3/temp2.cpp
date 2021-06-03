#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm> 


typedef struct{

    double alpha = 0, beta = 0, delta = 0, N = 0, gamma = 0;

} Parameter;

typedef struct{

    double S = 0, I = 0, R = 0, V = 0;

} Status;



void f(Status oldStatus, Parameter parameter, Status& newStatus){

    double Gamma = std::min(parameter.gamma,oldStatus.S);
    newStatus.S = - ((parameter.beta/parameter.N) * oldStatus.S * oldStatus.I) - (Gamma) + (parameter.delta * oldStatus.V);
    newStatus.I = ((parameter.beta/parameter.N) * oldStatus.S * oldStatus.I) - (parameter.alpha * oldStatus.I);
    newStatus.R = (parameter.alpha * oldStatus.I);
    newStatus.V = (Gamma) - (parameter.delta * oldStatus.V);

}


void rungeKuttaStep(Status oldStatus, Parameter parameter, Status& newStatus, double h){

    Status f_i;
    f(oldStatus, parameter, f_i);
    Status f_i1;

    Status rechnung = {

        .S = oldStatus.S + h*f_i.S,
        .I = oldStatus.I + h*f_i.I,
        .R = oldStatus.R + h*f_i.R,
        .V = oldStatus.V + h*f_i.V

    } ; 

    f(rechnung, parameter, f_i1);

    newStatus.S = oldStatus.S + h/2 * (f_i.S + f_i1.S);
    newStatus.I = oldStatus.I + h/2 * (f_i.I + f_i1.I);
    newStatus.R = oldStatus.R + h/2 * (f_i.R + f_i1.R);
    newStatus.V = oldStatus.V + h/2 * (f_i.V + f_i1.V);
}

int main(int argc, char const *argv[])
{
    Parameter SIR_P;
    SIR_P.alpha = 1.0/7.0;
    SIR_P.beta = 2.9/7.0;
    SIR_P.delta = 0;
    SIR_P.gamma = 0;
    SIR_P.N = 83000000;

    Status old;
    old.S = SIR_P.N - 5000;
    old.I = 5000;
    old.R = 0;
    old.V = 0;

    Status newSIR;

    while (old.I > 1)
    {
    
        rungeKuttaStep(old, SIR_P, old, 0.10);

        printf("%f %f %f %f \n",old.S, old.I, old.R, old.V);

    }
    return 0;
}
