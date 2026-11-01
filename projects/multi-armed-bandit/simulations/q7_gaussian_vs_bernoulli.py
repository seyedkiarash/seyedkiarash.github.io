import numpy as np
import matplotlib.pyplot as plt

TRUE_MEANS = np.array([0.2, 0.5, 0.9])
K = len(TRUE_MEANS)
T = 5000
RUNS = 300
SIGMA2 = 1.0        # known reward variance of the Gaussian bandit
PRIOR_MEAN = 0.0    # prior N(mu0, sigma0^2) on every arm's mean
PRIOR_VAR = 1.0


def gaussian_ts(rewards, rng):
    """Thompson sampling with the Normal-Normal model (known variance SIGMA2).
    After each reward X the posterior of the pulled arm is updated by
        1/s1^2 = 1/s0^2 + 1/sigma^2,   m1 = s1^2 (m0/s0^2 + X/sigma^2)."""
    mean = np.full(K, PRIOR_MEAN)
    var = np.full(K, PRIOR_VAR)
    counts = np.zeros(K)
    regret = np.zeros(T)
    total = 0.0
    for t in range(T):
        arm = int(np.argmax(rng.normal(mean, np.sqrt(var))))
        x = rewards[t, arm]
        post_var = 1.0 / (1.0 / var[arm] + 1.0 / SIGMA2)
        mean[arm] = post_var * (mean[arm] / var[arm] + x / SIGMA2)
        var[arm] = post_var
        counts[arm] += 1
        total += TRUE_MEANS.max() - TRUE_MEANS[arm]
        regret[t] = total
    return regret, counts


def bernoulli_ts(rewards, rng):
    """Thompson sampling with the Beta-Bernoulli model and a Beta(1, 1) prior."""
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


def kl_bernoulli(p, q):
    return p * np.log(p / q) + (1 - p) * np.log((1 - p) / (1 - q))


def lai_robbins_constant(kl):
    """sum over sub-optimal arms of Delta_i / KL(nu_i || nu*)."""
    best = TRUE_MEANS.max()
    return sum((best - m) / kl(m, best) for m in TRUE_MEANS if m < best)


def main():
    rng = np.random.default_rng(42)
    cases = {
        "gauss": "Gaussian bandit, Normal-Normal TS",
        "bern": "Bernoulli bandit, Beta-Bernoulli TS",
        "mis": "Bernoulli bandit, Normal-Normal TS (extra)",
    }
    reg = {c: np.zeros((RUNS, T)) for c in cases}
    cnt = {c: np.zeros((RUNS, K)) for c in cases}
    for run in range(RUNS):
        u = rng.random((T, K))
        z = rng.standard_normal((T, K))
        gauss_rewards = TRUE_MEANS + np.sqrt(SIGMA2) * z     # X ~ N(mu_i, 1)
        bern_rewards = (u < TRUE_MEANS).astype(float)       # X ~ Bernoulli(mu_i)
        reg["gauss"][run], cnt["gauss"][run] = gaussian_ts(gauss_rewards, rng)
        reg["bern"][run], cnt["bern"][run] = bernoulli_ts(bern_rewards, rng)
        reg["mis"][run], cnt["mis"][run] = gaussian_ts(bern_rewards, rng)

    c_gauss = lai_robbins_constant(lambda p, q: (p - q) ** 2 / (2 * SIGMA2))
    c_bern = lai_robbins_constant(kl_bernoulli)

    fig, axes = plt.subplots(1, 3, figsize=(18, 5))
    t = np.arange(1, T + 1)
    styles = {"gauss": "C0", "bern": "C1", "mis": "C2"}
    for c, label in cases.items():
        m = reg[c].mean(axis=0); e = 1.96 * reg[c].std(axis=0, ddof=1) / np.sqrt(RUNS)
        ls = "--" if c == "mis" else "-"
        axes[0].plot(t, m, ls, color=styles[c], label=label, linewidth=2)
        axes[0].fill_between(t, m - e, m + e, color=styles[c], alpha=0.2)
    axes[0].set_title(f"Average cumulative regret ({RUNS} runs)", fontsize=13)
    axes[0].set_xlabel("Time step (t)"); axes[0].set_ylabel("Cumulative regret")
    axes[0].legend(fontsize=9); axes[0].grid(True, alpha=0.3)

    t0 = 500   # reference lines start here, so their slopes can be compared with the curves
    tt = t[t0 - 1:]
    for c, const, name in (("gauss", c_gauss, "Gaussian"), ("bern", c_bern, "Bernoulli")):
        m = reg[c].mean(axis=0)
        axes[1].plot(t, m, color=styles[c], linewidth=2, label=cases[c])
        axes[1].plot(tt, m[t0 - 1] + const * np.log(tt / t0), ":", color=styles[c],
                     label=f"asymptotic Lai-Robbins slope, {name}: {const:.2f} per unit of ln t")
        slope = (m[-1] - m[t0 - 1]) / np.log(T / t0)
        print(f"{name}: measured slope d(regret)/d(ln t) between t={t0} and T: {slope:.2f}")
    axes[1].set_xscale("log")
    axes[1].set_title("Regret against ln t (log axis)", fontsize=13)
    axes[1].set_xlabel("Time step (t), log scale"); axes[1].legend(fontsize=8); axes[1].grid(True, alpha=0.3)

    x = np.arange(K); width = 0.27
    for j, c in enumerate(cases):
        axes[2].bar(x + (j - 1) * width, cnt[c].mean(axis=0), width, color=styles[c], label=cases[c], alpha=0.85)
    axes[2].set_title("Average pulls of each arm per run", fontsize=13)
    axes[2].set_xticks(x)
    axes[2].set_xticklabels([f"Arm {i + 1}\n($\\mu$={TRUE_MEANS[i]})" for i in range(K)])
    axes[2].set_yscale("log"); axes[2].legend(fontsize=8)

    plt.tight_layout()
    plt.savefig("Q7-gaussian_vs_bernoulli.png", dpi=200, bbox_inches="tight")
    plt.show()

    print(f"Lai-Robbins constant: Gaussian {c_gauss:.2f}, Bernoulli {c_bern:.2f}  (regret >~ c ln T)")
    print(f"{'Case':<44} | {'Regret at T':<14} | pulls of arms 1, 2 | best-arm share")
    print("-" * 100)
    for c, label in cases.items():
        f = reg[c][:, -1]
        n = cnt[c].mean(axis=0)
        print(f"{label:<44} | {f.mean():6.1f} ± {1.96 * f.std(ddof=1) / np.sqrt(RUNS):4.1f} | "
              f"{n[0]:6.1f}, {n[1]:6.1f}     | {n[2] / T * 100:5.1f}%")


if __name__ == "__main__":
    main()
