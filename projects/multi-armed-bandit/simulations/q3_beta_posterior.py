import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import beta

mu=0.7
T=200
X=np.random.binomial(1,mu,size=T)
curr_a=1
curr_b=1
cp=[0,5,20,100,200]
x_axis=np.linspace(0,1,1000)
cmap=plt.cm.viridis
plt.figure(figsize=(10,6))
for t in range(T+1):
    if t in cp:
        y=beta.pdf(x_axis,curr_a,curr_b)
        plt.plot(x_axis,y,label=f'Trials (t) = {t}',color=cmap(t/(T+1)),linewidth=2)
    if t<T:
        if X[t]==1:
            curr_a=curr_a+1
        else:
            curr_b=curr_b+1
plt.xlabel(r'Probability of Success ($\mu$)')
plt.title('Evolution of Beta Posterior Distribution')
plt.ylabel('PDF')
plt.axvline(x=mu,color='black',linestyle='--',alpha=0.5,label='True Mean (0.7)')
plt.legend()
plt.grid(True)
plt.show()