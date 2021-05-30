#include <stdio.h>
#include <math.h>


void Integrationsverfahren(double* x, double* f, double lower_limit, double upper_limit, int steps){
    
    double h = (upper_limit-lower_limit)/steps;

    for (size_t i = 0; i < steps; i++)
    {
        x[i+1] = x[i] +h*f[i];
    }
    
}

void DGL_Verfahren(double* x, double* y_0, double anfangszeit, double endzeit, int steps){

    double y[steps];

    for (size_t i = 0; i < steps; i++)
    {
        y[i+1] = x[i];
    }
    
    double dy[steps];

    for (size_t i = 1; i < steps; i++)
    {
        dy[i] = y[i+1];
    }
    
    Integrationsverfahren(y, dy, anfangszeit, endzeit, steps);

}




void SIR_Model(){


}
