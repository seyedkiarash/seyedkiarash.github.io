import numpy as np
import matplotlib.pyplot as plt

TRUE_MEANS = np.array([0.2, 0.5, 0.9])   # Bernoulli arms: rewards are 0 or 1
K = len(TRUE_MEANS)
T = 5000
RUNS = 200
PRIOR_VAR = 10.0            # Gaussian prior N(0, 10) on each mean
ASSUMED_NOISE_VAR = 1.0     # variance the Gaussian model assumes for each reward


def gaussian_ts(rewards, rng):
    """Thompson sampling with a Normal likelihood (known variance) and Normal prior,
    applied to the same binary rewards as the Bernoulli version: a misspecified model."""
    mean = np.zeros(K)
    var = np.full(K, PRIOR_VAR)
    counts = np.zeros(K)
    regret = np.zeros(T)
    total = 0.0
    for t in range(T):
        arm = int(np.argmax(rng.normal(mean, np.sqrt(var))))
        r = rewards[t, arm]
        post_var = 1.0 / (1.0 / var[arm] + 1.0 / ASSUMED_NOISE_VAR)
        mean[arm] = post_var * (mean[arm] / var[arm] + r / ASSUMED_NOISE_VAR)
        var[arm] = post_var
        counts[arm] += 1
        total += TRUE_MEANS.max() - TRUE_MEANS[arm]
        regret[t] = total
    return regret, counts


def bernoulli_ts(rewards, rng):
    """Thompson sampling with the Beta-Bernoulli model (correctly specified)."""
    alphas = np.ones(K)
    betas = np.ones(K)
    counts = np.zeros(K)
    regret = np.zeros(T)
    total = 0.0
    for t in range(T):
        arm = int(np.argmax(rng.beta(alphas, betas)))
        r = rewards[t, arm]
        alphas[arm] += r
        betas[arm] += 1 - r
        counts[arm] += 1
        total += TRUE_MEANS.max() - TRUE_MEANS[arm]
        regret[t] = total
    return regret, counts


def main():
    rng = np.random.default_rng(42)
    reg_g = np.zeros((RUNS, T)); reg_b = np.zeros((RUNS, T))
    cnt_g = np.zeros((RUNS, K)); cnt_b = np.zeros((RUNS, K))
    for run in range(RUNS):
        # Both algorithms see exactly the same binary reward table in this run.
        rewards = (rng.random((T, K)) < TRUE_MEANS).astype(float)
        reg_g[run], cnt_g[run] = gaussian_ts(rewards, rng)
        reg_b[run], cnt_b[run] = bernoulli_ts(rewards, rng)

    fig, axes = plt.subplots(1, 3, figsize=(18, 5))
    t = np.arange(1, T + 1)
    for reg, label in [(reg_g, "Gaussian TS (misspecified)"), (reg_b, "Bernoulli TS")]:
        m = reg.mean(axis=0); e = 1.96 * reg.std(axis=0, ddof=1) / np.sqrt(RUNS)
        axes[0].plot(t, m, label=label, linewidth=2)
        axes[0].fill_between(t, m - e, m + e, alpha=0.2)
    axes[0].set_title(f"Average Cumulative Regret ({RUNS} runs)", fontsize=14)
    axes[0].set_xlabel("Time Step (t)"); axes[0].set_ylabel("Cumulative Regret")
    axes[0].legend(); axes[0].grid(True, alpha=0.3)

    x = np.arange(K); width = 0.35
    axes[1].bar(x - width / 2, cnt_g.mean(axis=0), width, label="Gaussian TS", alpha=0.8)
    axes[1].bar(x + width / 2, cnt_b.mean(axis=0), width, label="Bernoulli TS", alpha=0.8)
    axes[1].set_title("Average Arm Selections per Run", fontsize=14)
    axes[1].set_xticks(x)
    axes[1].set_xticklabels([f"Arm {i + 1}\n($\\mu$={TRUE_MEANS[i]})" for i in range(K)])
    axes[1].set_yscale("log"); axes[1].legend()

    window = 100
    for reg, label in [(reg_g, "Gaussian TS"), (reg_b, "Bernoulli TS")]:
        inst = np.diff(np.insert(reg.mean(axis=0), 0, 0))
        axes[2].plot(np.convolve(inst, np.ones(window) / window, mode="valid"), label=label, alpha=0.8)
    axes[2].set_title(f"Average Instantaneous Regret ({window}-step MA)", fontsize=14)
    axes[2].set_xlabel("Time Step (t)"); axes[2].legend(); axes[2].grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig("Q7-gaussian_vs_bernoulli.png", dpi=200, bbox_inches="tight")
    plt.show()

    print(f"{'Algorithm':<28} | {'Regret at T':<14} | Best-arm share")
    print("-" * 62)
    for reg, cnt, label in [(reg_g, cnt_g, "Gaussian TS (misspecified)"), (reg_b, cnt_b, "Bernoulli TS")]:
        f = reg[:, -1]
        print(f"{label:<28} | {f.mean():6.1f} ± {1.96 * f.std(ddof=1) / np.sqrt(RUNS):4.1f} | {cnt[:, 2].mean() / T * 100:5.1f}%")


if __name__ == "__main__":
    main()
