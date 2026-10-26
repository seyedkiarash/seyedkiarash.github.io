import numpy as np
import matplotlib.pyplot as plt

MEANS=[0.2,0.5,0.8]
OPTIMAL_MEAN=0.8
def pull_arm(i):
    return np.random.binomial(1,MEANS[i])
def uniform(T):
    r=[]
    for i in range(T):
        chosen_arm=np.random.randint(0,3)
        r.append(pull_arm(chosen_arm))
    return np.array(r)
def greedy(T):
    r=[]
    arm_count=np.zeros(3)
    arm_reward_sum=np.zeros(3)
    for t in range(T):
        chosen_arm=-1
        if t<3:
            chosen_arm=t
        else:
            eMeans=arm_reward_sum/arm_count
            max_Val=np.max(eMeans)
            c=np.where(eMeans==max_Val)[0]
            chosen_arm=np.random.choice(c)
        reward=pull_arm(chosen_arm)
        r.append(reward)
        arm_count[chosen_arm]+=1
        arm_reward_sum[chosen_arm]+=reward
    return np.array(r)

def main():
    T=1000
    N=500
    uni_regret = np.zeros((N, T))
    gre_regret = np.zeros((N, T))
    for i in range(N):
        uni_reward=uniform(T)
        gre_reward=greedy(T)
        OPTIMAL_R=OPTIMAL_MEAN*np.arange(1,T+1)
        actual_R_uni=np.cumsum(uni_reward)
        actual_R_gre=np.cumsum(gre_reward)
        uni_regret[i,:]=OPTIMAL_R-actual_R_uni
        gre_regret[i,:]=OPTIMAL_R-actual_R_gre
    mean_regret_uni=np.mean(uni_regret, axis=0)
    mean_regret_gre=np.mean(gre_regret, axis=0)
    plt.figure(figsize=(10,6))
    t=np.arange(1,T+1)
    plt.plot(t,mean_regret_uni,label="Uniform Strategy", color="blue")
    plt.plot(t,mean_regret_gre,label="Greedy Strategy", color="red")
    plt.xlabel("t")
    plt.ylabel("Average Cumulative Regret")
    plt.title(f"Regret Comparison: Uniform vs Greedy")
    plt.legend()
    plt.grid(True)
    plt.show()

if __name__=="__main__":
    main()