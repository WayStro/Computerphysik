  //gcc -Wall -pedantic Zeta_slow.c -o Zeta_slow
 //./Zeta_slow
//Silas Mueller, Wayne Stroebel
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


double zetafunktion(double s,int genauigkeit, double* z)                       
{
    
    double x = 0;
    for (long int i = genauigkeit;(i > 0); i--)
    {
        x += 1/(pow(i, s));
        if (i < 100)
        {
            z[i] = x;
        }
    }
    return x;
}

int main(int argc, char const *argv[])
{
    
    double s = 2;                                                       //Wert fuer Zeta(s)
    int genauigkeit = 9;                                                //Genauigkeit if Form von 10^genauigkeit
    int N = pow(10, genauigkeit);
    double z[100];
    int y[100];
    for (int i = 1; i < 100; i++)                                      //Laufwert fuer Plot
    {
        y[i] = i;
    }
    
    printf("Zeta(2) = %.15f\n",zetafunktion(s,N,z));

    FILE* fp;
    fp = fopen("Zeta_slow_data.txt", "w");                              //oeffnet die Datei Zeta_slow_data.txt
    if(fp == NULL) {
        printf("Datei konnte nicht geoeffnet werden!\n");
        return 1;
    }

    for (unsigned int i = 1; i < 100; i++) {                              //schreibt zwischenergebnisse in Zeta_Slow.txt
        fprintf(fp, "%i %.16f \n",y[i],z[i]);
    }
    fclose(fp);

    return 0;
}

