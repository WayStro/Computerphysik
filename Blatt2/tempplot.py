##python3 convergenzplot.py
##Silas Mueller, Wayne Stroebel
##bitte zuerst Zeta_Borwein.c und Zeta_slow.c ausfuehren um die Daten.txt files zu erstellen

import matplotlib.pyplot as plt
import numpy as np

## PLOT DOUBLE DATEN ZWEIPUNKT

X1, Y1, Y2, Y3 = [], [], [], []

for line in open('PP_Double_Daten.txt', 'r'):
  values1 = [np.double(s) for s in line.split()] 
  X1.append(np.log(values1[0])) ## h Werte
  Y1.append(np.log10(values1[2])) ## Gesamt
  Y2.append(np.log10(values1[3])) ## Maschinen
  Y3.append(np.log10(values1[4])) ## Verfahren

plt.figure(111)
plt.xlabel("$\log_{10}{(h)}$")
plt.ylabel("$\log_{10}{(Fehler)}$")
plt.plot(X1, Y1, label=r'Gesamtfehler')
plt.plot(X1, Y2, label=r'Maschinenfehler')
plt.plot(X1, Y3, label=r'Verfahrensfehler')
plt.legend(loc='best',prop={'size':16})
plt.show()

## PLOT FLOAT DATEN ZWEIPUNKT

X1, Y1, Y2, Y3 = [], [], [], []

for line in open('PP_Float_Daten.txt', 'r'):
  values1 = [float(s) for s in line.split()] 
  X1.append(np.log10(values1[0])) ## h Werte
  Y1.append(np.log10(values1[2])) ## Gesamt
  Y2.append(np.log10(values1[3])) ## Maschinen
  Y3.append(np.log10(values1[4])) ## Verfahren

plt.figure(112)
plt.xlabel("$\log_{10}{(h)}$")
plt.ylabel("$\log_{10}{(Fehler)}$")
plt.plot(X1, Y1, label=r'Gesamtfehler')
plt.plot(X1, Y2, label=r'Maschinenfehler')
plt.plot(X1, Y3, label=r'Verfahrensfehler')
plt.legend(loc='best',prop={'size':16})
plt.show()


## PLOT DOUBLE DATEN DREIPUNKT

X1, Y1, Y2, Y3 = [], [], [], []

for line in open('PPP_Double_Daten.txt', 'r'):
  values1 = [float(s) for s in line.split()] 
  X1.append(np.log10(values1[0])) ## h Werte
  Y1.append(np.log10(values1[2])) ## Gesamt
  Y2.append(np.log10(values1[3])) ## Maschinen
  Y3.append(np.log10(values1[4])) ## Verfahren

plt.figure(113)
plt.xlabel("$\log_{10}{(h)}$")
plt.ylabel("$\log_{10}{(Fehler)}$")
plt.plot(X1, Y1, label=r'Gesamtfehler')
plt.plot(X1, Y2, label=r'Maschinenfehler')
plt.plot(X1, Y3, label=r'Verfahrensfehler')
plt.legend(loc='best',prop={'size':16})
plt.show()


## PLOT FLOAT DATEN DREIPUNKT

X1, Y1, Y2, Y3 = [], [], [], []

for line in open('PPP_Float_Daten.txt', 'r'):
  values1 = [float(s) for s in line.split()] 
  X1.append(np.log10(values1[0])) ## h Werte
  Y1.append(np.log10(values1[2])) ## Gesamt
  Y2.append(np.log10(values1[3])) ## Maschinen
  Y3.append(np.log10(values1[4])) ## Verfahren

plt.figure(114)
plt.xlabel("$\log_{10}{(h)}$")
plt.ylabel("$\log_{10}{(Fehler)}$")
plt.plot(X1, Y1, label=r'Gesamtfehler')
plt.plot(X1, Y2, label=r'Maschinenfehler')
plt.plot(X1, Y3, label=r'Verfahrensfehler')
plt.legend(loc='best',prop={'size':16})
plt.show()