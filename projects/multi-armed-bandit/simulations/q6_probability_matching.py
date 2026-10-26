import numpy as np
import matplotlib.pyplot as plt

np.random.seed(42)
def estimate_optimal_probabilities(alphas, betas, num_samples=10000):
    k = len(alphas)
    samples = np.random.beta(alphas, betas, size=(num_samples, k))
    winners = np.argmax(samples, axis=1)
    probs = np.zeros(k)
    for i in range(k):
        probs[i] = np.mean(winners == i)
    return probs

def run_ts_and_compare(true_probs, T_list):
    k = len(true_probs)
    for T in T_list:
        alphas = np.ones(k)
        betas = np.ones(k)
        arm_counts = np.zeros(k)
        for t in range(T):
            theta = np.random.beta(alphas, betas)
            arm = np.argmax(theta)
            reward = 1 if np.random.random() < true_probs[arm] else 0
            alphas[arm] += reward
            betas[arm] += (1 - reward)
            arm_counts[arm] += 1
        estimated_probs = estimate_optimal_probabilities(alphas, betas)
        empirical_frequencies = arm_counts / T
        correlation = np.corrcoef(estimated_probs, empirical_frequencies)[0, 1]
        print(f"Results for T = {T}:")
        print(f"  True Probs: {true_probs}")
        print(f"  Estimated Optimal Probs (MC): {np.round(estimated_probs, 3)}")
        print(f"  Empirical Frequencies (TS): {np.round(empirical_frequencies, 3)}")
        print(f"  Correlation: {correlation:.4f}")
        print("-" * 30)

true_probabilities = [0.2, 0.5, 0.75, 0.4]
T_values = [500, 1000, 5000]
run_ts_and_compare(true_probabilities, T_values)