import numpy as np
import matplotlib.pyplot as plt


def Generate(n_samples):
    X=np.random.binomial(1,0.7,n_samples)
    X_mean=np.mean(X)
    return np.abs(X_mean-0.7)>=0.1
def takhmin(n,N):
    count=0.0
    for i in range(N):
        if Generate(n):
            count+=1
    return count/N
def main():
    n_val=[20,50,100,500]
    N=10000
    pn=[]
    bn=[]
    for i in n_val:
        pn.append(takhmin(i,N))
        bn.append(2*np.exp(-2*i*0.01))
    plt.figure(figsize=(8,4))
    plt.plot(n_val,pn,marker='o',label="p(n) from simulation")
    plt.plot(n_val,bn,marker='s',label="b(n) Hoeffding Bound")
    plt.xlabel("n")
    plt.title("checking hoeffding")
    plt.legend()
    plt.grid(True)
    plt.show()

if __name__=="__main__":
    main()