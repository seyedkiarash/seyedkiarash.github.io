import numpy as np
import matplotlib.pyplot as plt

def main():
    np.random.seed(0)
    MEANS=[0.2,0.5,0.8,0.3,0.1,0.6]
    OPTIMAL_MEAN=np.max(MEANS)
    K=len(MEANS)
    T=10000
    alphas=np.ones(K)
    betas=np.ones(K)
    regret=[]
    cumregret=0
    means_history=np.zeros((T,K))
    var_history=np.zeros((T,K))
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
        s=alphas+betas
        means_history[t]=alphas/s
        var_history[t]=alphas*betas/(s**2*(s+1))   # variance of Beta(alpha, beta)
    steps=np.arange(1,T+1)
    plt.figure(figsize=(18,5))
    plt.subplot(1,3,1)
    plt.plot(steps,regret,label="Thompson Sampling")
    # a log-shaped reference curve scaled to the final regret
    plt.plot(steps,regret[-1]*np.log(steps)/np.log(T),"--",color="gray",label=r"$c\,\ln t$ (reference)")
    plt.title("Cumulative Regret over Time")
    plt.xlabel("Time Step (t)")
    plt.legend()
    plt.grid(True,alpha=0.3)
    plt.subplot(1,3,2)
    for k in range(K):
        plt.plot(steps,means_history[:,k],label=f'arm {k+1} ($\\mu$={MEANS[k]})')
    plt.xscale("log")
    plt.title("Posterior Means")
    plt.xlabel("Time Step (t), log scale")
    plt.ylabel(r"$\alpha/(\alpha+\beta)$")
    plt.legend()
    plt.grid(True,alpha=0.3)
    plt.subplot(1,3,3)
    for k in range(K):
        plt.plot(steps,var_history[:,k],label=f'arm {k+1}')
    plt.xscale("log"); plt.yscale("log")
    plt.title("Posterior Variances (uncertainty)")
    plt.xlabel("Time Step (t), log scale")
    plt.ylabel(r"$\alpha\beta/((\alpha+\beta)^2(\alpha+\beta+1))$")
    plt.grid(True,which="both",alpha=0.3)
    plt.tight_layout()
    plt.savefig("Figure_4.png",dpi=200,bbox_inches="tight")
    plt.show()
    n=alphas+betas-2
    print(f"regret at T={T}: {regret[-1]:.1f}")
    for k in range(K):
        print(f"arm {k+1} (mu={MEANS[k]}): pulls {int(n[k]):5d}, posterior mean {means_history[-1,k]:.3f}, posterior sd {np.sqrt(var_history[-1,k]):.4f}")

if __name__ == '__main__':
    main()
