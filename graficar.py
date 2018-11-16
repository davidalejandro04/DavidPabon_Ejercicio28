import numpy as np
import matplotlib.pyplot as plt
import sys
import glob

path='../DavidPabon_Ejercicio27/integralN*.dat';

files = glob.glob(path)   

data_=[]

for file in files:     
	archivo=list(np.genfromtxt(file))
	data_.append(archivo)

data_=np.array(data_)
data=[]
for i in data_:
	data.append(i)	
data=np.array(data).reshape(-1,1)
plt.plot(data)
plt.title('Error')
plt.savefig('error.pdf')
plt.close()

