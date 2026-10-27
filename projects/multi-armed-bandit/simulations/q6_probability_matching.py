import numpy as np
import matplotlib.pyplot as plt

TRUE_PROBS = np.array([0.2, 0.5, 0.75, 0.4])
T_VALUES = [500, 1000, 5000]
MC_SAMPLES = 4000


def prob_optimal(alphas, betas, rng, n=MC_SAMPLES):
    """Monte Carlo estimate of pi_i = P(theta_i is the largest | history)."""
    samples = rng.beta(alphas, betas, size=(n, len(alphas)))
    return np.bincount(samples.argmax(axis=1), minlength=len(alphas)) / n


def run(T, rng):
    """Thompson sampling that also records pi(t), the posterior probability that each
    arm is optimal just before step t. Probability matching says
    P(A_t = i | history) = pi_i(t), so over a run the share of pulls of arm i must
    agree with the average of pi_i(t) over the same steps."""
    k = len(TRUE_PROBS)
    alphas = np.ones(k); betas = np.ones(k)
    pi_sum = np.zeros(k); counts = np.zeros(k)
    for _ in range(T):
        pi_sum += prob_optimal(alphas, betas, rng, n=1000)
        arm = int(np.argmax(rng.beta(alphas, betas)))
        r = float(rng.random() < TRUE_PROBS[arm])
        alphas[arm] += r; betas[arm] += 1 - r
        counts[arm] += 1
    return counts / T, pi_sum / T, prob_optimal(alphas, betas, rng)


def main():
    rng = np.random.default_rng(42)
    rows = []
    for T in T_VALUES:
        freq, avg_pi, final_pi = run(T, rng)
        rows.append((T, freq, avg_pi, final_pi))
        print(f"T = {T}")
        print(f"  share of pulls (TS)          : {np.round(freq, 3)}")
        print(f"  average of pi_i(t) over steps: {np.round(avg_pi, 3)}")
        print(f"  max |difference|             : {np.abs(freq - avg_pi).max():.3f}")
        print(f"  pi_i at the end of the run   : {np.round(final_pi, 3)}")

    fig, axes = plt.subplots(1, len(T_VALUES), figsize=(15, 4), sharey=True)
    x = np.arange(len(TRUE_PROBS)); w = 0.38
    for ax, (T, freq, avg_pi, _) in zip(axes, rows):
        ax.bar(x - w / 2, freq, w, label="share of pulls (TS)")
        ax.bar(x + w / 2, avg_pi, w, label=r"average $\pi_i(t)$")
        ax.set_yscale("log"); ax.set_ylim(1e-3, 1.2)
        ax.set_xticks(x); ax.set_xticklabels([f"arm {i + 1}\n$\\mu$={p}" for i, p in enumerate(TRUE_PROBS)])
        ax.set_title(f"T = {T}")
    axes[0].set_ylabel("fraction"); axes[0].legend()
    plt.suptitle("Probability matching: Thompson sampling picks each arm as often as it is believed optimal")
    plt.tight_layout()
    plt.savefig("Q6.png", dpi=200, bbox_inches="tight")
    plt.show()


if __name__ == "__main__":
    main()
