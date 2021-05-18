#include <stdlib.h>
#include <stdio.h>
#include <math.h>




//[[Rcpp::export]]
double Maschinenfehler_Double(){
  double k = 1;
  double x = 0;
  while (k == 1)
  {
    x += 0.000000000000000000001;
    k += x;
  }
  return x;
}

//[[Rcpp::export]]
float Maschinenfehler_Float(){
  float k = 1.0;
  float x = 0;
  for (int i = 0; k == 1.0; i++)
  {
    x += 0.000000001;
    k += x;
  }
  return x;
}

//[[Rcpp::export]]
void PPAbleitung_expf(float h,float x,float g,float* Werte_float){

  int temp = h / g;
  float Maschinenfehler = Maschinenfehler_Float();

  for (int i = 0; i < temp; i += 5){
    Werte_float[i] = h - i*g; 
    Werte_float[i+1] = (exp(x+(h - i*g))-exp(x))/(h - i*g);
    Werte_float[i+2] = (exp(x+(h - i*g))-exp(x))/(h - i*g)-exp(x);
    Werte_float[i+3] = 1 / ((h - i*g)) * 0.8164965809 * Maschinenfehler * exp(x);
    Werte_float[i+4] = Werte_float[i+2] - Werte_float[i+3];

  }
  return;

}

//[[Rcpp::export]]
void PPAbleitung_expd(double h,double x, double g, double* Werte_double){
  
  int temp = h / g;
  double Maschinenfehler = Maschinenfehler_Double();

  for (int i = 0; i < temp; i += 5){
    Werte_double[i] = h - i*g; 
    Werte_double[i+1] = (exp(x+(h - i*g))-exp(x))/(h - i*g);
    Werte_double[i+2] = (exp(x+(h - i*g))-exp(x))/(h - i*g)-exp(x);
    Werte_double[i+3] = 1 / ((h - i*g)) * 0.8164965809 * Maschinenfehler * exp(x);
    Werte_double[i+4] = Werte_double[i+2] - Werte_double[i+3];

  }
  return;
}

//[[Rcpp::export]]
void PPPAbleitung_expf(float h,float x,float g,float* Werte_float){

  int temp = h / g;
  float Maschinenfehler = Maschinenfehler_Float();

  for (int i = 0; i < temp; i += 5){
    Werte_float[i] = h - i*g; 
    Werte_float[i+1] = (exp(x+(h - i*g))-exp(x-(h - i*g)))/(2*(h - i*g));
    Werte_float[i+2] = (exp(x+(h - i*g))-exp(x-(h - i*g)))/(2*(h - i*g))-exp(x);
    Werte_float[i+3] = 1 / (2*(h - i*g)) * 0.8164965809 * Maschinenfehler * exp(x);
    Werte_float[i+4] = Werte_float[i+2] - Werte_float[i+3];

  }
  return;

}

//[[Rcpp::export]]
void PPPAbleitung_expd(double h,double x,double g,double* Werte_double){

  int temp = h / g;
  double Maschinenfehler = Maschinenfehler_Double();

  for (int i = 0; i < temp; i += 5){
    Werte_double[i] = h - i*g; 
    Werte_double[i+1] = (exp(x+(h - i*g))-exp(x-(h - i*g)))/(2*(h - i*g));
    Werte_double[i+2] = (exp(x+(h - i*g))-exp(x-(h - i*g)))/(2*(h - i*g))-exp(x);
    Werte_double[i+3] = 1 / (2*(h - i*g)) * 0.8164965809 * Maschinenfehler * exp(x);
    Werte_double[i+4] = Werte_double[i+2] - Werte_double[i+3];

  }
  return;

}

int main(){
  
  //2-Point Double

  double ppd_x_i = -1;
  double ppd_h_double_start = 0.0001;
  double ppd_Schrittweite_double = 0.000000001;
  int ppd_j = ppd_h_double_start / ppd_Schrittweite_double;
  const int ppd_Menge = ppd_j;
  
  //Speicher reservieren
  double ppd_Werte_Double[ppd_Menge];

  
  //erzeugen und zuweisen der Werte
  PPAbleitung_expd(ppd_h_double_start,ppd_x_i, ppd_Schrittweite_double,ppd_Werte_Double);
  
  

  //Ausgabe
  //oeffne die Datei Double_Daten.txt
  //h, Wert, ges_Fehler, Maschinenfehler, Verfahrensfehler
    FILE* ppd;
    ppd = fopen("PP_Double_Daten.txt", "w");                              
    if(ppd == NULL) {
      //Datei konnte nicht geoeffnet werden
      return -3;
    }
    
    // schreibe zwischenergebnisse in Double_Daten.txt
    for (int i = 0; i < ppd_Menge; i += 5) {                                
      fprintf(ppd, "%.20f %.20f %.20f %.20f %.20f \n", ppd_Werte_Double[i], ppd_Werte_Double[i+1], ppd_Werte_Double[i+2], ppd_Werte_Double[i+3], ppd_Werte_Double[i+4]);
    }
    fclose(ppd);
  

  //2-Point Float

  float ppf_x_i = -1;
  float ppf_h_float_start = 0.01;
  float ppf_Schrittweite_float = 0.00005;
  int ppf_j = ppf_h_float_start / ppf_Schrittweite_float;
  const int ppf_Menge = ppf_j;
  
  //Speicher reservieren
  float ppf_Werte_Float[ppf_Menge];

  
  //erzeugen und zuweisen der Werte
  PPAbleitung_expf(ppf_h_float_start,ppf_x_i, ppf_Schrittweite_float,ppf_Werte_Float);
  
  

  //Ausgabe
  //oeffne die Datei Double_Daten.txt
  //h, Wert, ges_Fehler, Maschinenfehler, Verfahrensfehler
    FILE* ppf;
    ppf = fopen("PP_Float_Daten.txt", "w");                              
    if(ppf == NULL) {
      //Datei konnte nicht geoeffnet werden
      return -3;
    }
    
    // schreibe zwischenergebnisse in Double_Daten.txt
    for (int i = 0; i < ppf_Menge; i += 5) {                                
      fprintf(ppf, "%.20f %.20f %.20f %.20f %.20f \n", ppf_Werte_Float[i], ppf_Werte_Float[i+1], ppf_Werte_Float[i+2], ppf_Werte_Float[i+3], ppf_Werte_Float[i+4]);
    }
    fclose(ppf);
  
  // 3-Point Double

  double pppd_x_i = -1;
  double pppd_h_double_start = 0.0001;
  double pppd_Schrittweite_double = 0.0000005;
  int pppd_j = pppd_h_double_start / pppd_Schrittweite_double;
  const int pppd_Menge = pppd_j;
  
  //Speicher reservieren
  double pppd_Werte_Double[pppd_Menge];

  
  //erzeugen und zuweisen der Werte
  PPPAbleitung_expd(pppd_h_double_start,pppd_x_i, pppd_Schrittweite_double,pppd_Werte_Double);
  
  

  //Ausgabe
  //oeffne die Datei Double_Daten.txt
  //h, Wert, ges_Fehler, Maschinenfehler, Verfahrensfehler
    FILE* pppd;
    pppd = fopen("PPP_Double_Daten.txt", "w");                              
    if(pppd == NULL) {
      //Datei konnte nicht geoeffnet werden
      return -3;
    }
    
    // schreibe zwischenergebnisse in Double_Daten.txt
    for (int i = 0; i < pppd_Menge; i += 5) {                                
      fprintf(pppd, "%.20f %.20f %.20f %.20f %.20f \n", pppd_Werte_Double[i], pppd_Werte_Double[i+1], pppd_Werte_Double[i+2], pppd_Werte_Double[i+3], pppd_Werte_Double[i+4]);
    }
    fclose(pppd);

  // 3-Point Float

  float pppf_x_i = -1;
  float pppf_h_double_start = 0.1;
  float pppf_Schrittweite_double = 0.0005;
  int pppf_j = pppf_h_double_start / pppf_Schrittweite_double;
  const int pppf_Menge = pppf_j;
  
  //Speicher reservieren
  float pppf_Werte_Double[pppf_Menge];

  
  //erzeugen und zuweisen der Werte
  PPPAbleitung_expf(pppf_h_double_start,pppf_x_i, pppf_Schrittweite_double,pppf_Werte_Double);
  
  

  //Ausgabe
  //oeffne die Datei Double_Daten.txt
  //h, Wert, ges_Fehler, Maschinenfehler, Verfahrensfehler
    FILE* pppf;
    pppf = fopen("PPP_Float_Daten.txt", "w");                              
    if(pppf == NULL) {
      //Datei konnte nicht geoeffnet werden
      return -3;
    }
    
    // schreibe zwischenergebnisse in Double_Daten.txt
    for (int i = 0; i < pppf_Menge; i += 5) {                                
      fprintf(pppf, "%.20f %.20f %.20f %.20f %.20f \n", pppf_Werte_Double[i], pppf_Werte_Double[i+1], pppf_Werte_Double[i+2], pppf_Werte_Double[i+3], pppf_Werte_Double[i+4]);
    }
    fclose(pppf);

  return 0;
}
