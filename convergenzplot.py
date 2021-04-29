##python3 convergenzplot.py
##Silas Mueller, Wayne Stroebel


import matplotlib.pyplot as plt

X1, Y1 = [], []
X2, Y2 = [], []
for line in open('Zeta_slow_data.txt', 'r'):
  values1 = [float(s) for s in line.split()]
  X1.append(values1[0])
  Y1.append(values1[1])

for line in open('Zeta_Borwein_data.txt', 'r'):
    values2 = [float(s) for s in line.split()]
    X2.append(values2[0])
    Y2.append(values2[1])

plt.figure()
plt.xlabel("Schrittzahl $i$")
plt.ylabel("Wert $x_{i}$")
plt.plot(X1, Y1, label=r'Zeta_slow')
plt.plot(X2, Y2, label=r'Zeta_Borwein')
plt.legend(loc='best',prop={'size':16})
plt.savefig("Konvergenzverhalten.pdf")
plt.show()