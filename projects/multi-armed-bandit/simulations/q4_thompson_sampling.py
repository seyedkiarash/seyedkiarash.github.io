import numpy as np
import matplotlib.pyplot as plt

def main():
    MEANS=[0.2,0.5,0.8,0.3,0.1,0.6]
    OPTIMAL_MEAN=np.max(MEANS)
    K=len(MEANS)
    T=10000
    alphas=np.ones(K)
    betas=np.ones(K)
    regret=[]
    cumregret=0
    means_history=np.zeros((T,K))
    for t in range(T):
        theta=np.random.beta(alphas,betas)
        choosen_arm=np.argmax(theta)
        reward=np.random.binomial(1,MEANS[choosen_arm])
        if reward==1:
            alphas[choosen_arm]+=1
        else:
            betas[choosen_arm]+=1
        cumregret += OPTIMAL_MEAN-MEANS[choosen_arm]
        regret.append(cumregret)
        current_mean=alphas/(alphas+betas)
        means_history[t]=current_mean
    plt.figure(figsize=(12,6))
    plt.subplot(1,2,1)
    plt.plot(regret)
    plt.title("Cumulative Regret over Time")
    plt.xlabel("Time Step (t)")
    plt.grid(True,alpha=0.3)
    plt.subplot(1,2,2)
    for k in range(K):
        plt.plot(means_history[:,k],label=f'arm {k} ( {MEANS[k]})')
    plt.title("Convergence of Posterior Means")
    plt.xlabel("Time Step (t)")
    plt.ylabel("Estimated Mean (alpha / alpha+beta)")
    plt.legend()
    plt.grid(True,alpha=0.3)
    plt.show()

if __name__ == '__main__':
    main()