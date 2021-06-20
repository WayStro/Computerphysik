import matplotlib.pyplot as plt
import numpy as np

X1, Y1 = [], []

for line in open('data.txt', 'r'):
  values1 = [float(s) for s in line.split()] 
  X1.append(values1[0])
  Y1.append(100. / (2* np.pi) * values1[1])


plt.xlabel("Teta")
plt.ylabel("Tetadot")
plt.errorbar(X1, Y1, label=r'Kreis')
plt.legend(loc='best',prop={'size':16})
plt.show()

