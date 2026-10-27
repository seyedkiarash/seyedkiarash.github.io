import numpy as np
import matplotlib.pyplot as plt

TRUE_PROBS = np.array([0.1, 0.3, 0.7, 0.2, 0.5])   # arm 3 (0.7) is the best
T = 2000
RUNS = 300
EPSILON = 0.1


def run_once(algorithm, rewards, rng):
    """One run of one algorithm. rewards[t, i] is the reward arm i would give at step t,
    so every algorithm faces exactly the same random outcomes (common random numbers)."""
    k = len(TRUE_PROBS)
    counts = np.zeros(k)
    values = np.zeros(k)
    alphas = np.ones(k)
    betas = np.ones(k)
    regret = np.zeros(T)
    total = 0.0
    best = TRUE_PROBS.max()
    for t in range(T):
        if algorithm == "epsilon_greedy":
            if rng.random() < EPSILON:
                arm = rng.integers(k)
            else:
                arm = rng.choice(np.flatnonzero(values == values.max()))
        elif algorithm == "ucb":
            if t < k:
                arm = t
            else:
                arm = int(np.argmax(values + np.sqrt(2 * np.log(t + 1) / counts)))
        else:  # Thompson sampling with a Beta(1, 1) prior
            arm = int(np.argmax(rng.beta(alphas, betas)))
        r = rewards[t, arm]
        counts[arm] += 1
        values[arm] += (r - values[arm]) / counts[arm]
        alphas[arm] += r
        betas[arm] += 1 - r
        total += best - TRUE_PROBS[arm]
        regret[t] = total
    return regret


def main():
    rng = np.random.default_rng(42)
    names = {"epsilon_greedy": r"$\epsilon$-Greedy (0.1)", "ucb": "UCB1", "thompson": "Thompson Sampling"}
    curves = {a: np.zeros((RUNS, T)) for a in names}
    for run in range(RUNS):
        rewards = (rng.random((T, len(TRUE_PROBS))) < TRUE_PROBS).astype(float)
        for a in names:
            curves[a][run] = run_once(a, rewards, rng)

    t = np.arange(1, T + 1)
    plt.figure(figsize=(10, 6))
    for a, label in names.items():
        mean = curves[a].mean(axis=0)
        sem = curves[a].std(axis=0, ddof=1) / np.sqrt(RUNS)
        plt.plot(t, mean, label=label)
        plt.fill_between(t, mean - 1.96 * sem, mean + 1.96 * sem, alpha=0.2)
    plt.xlabel("Steps (t)")
    plt.ylabel(f"Average cumulative regret ({RUNS} runs)")
    plt.title("Comparison of Bandit Algorithms: Cumulative Regret")
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.savefig("Q5-bandit_algorithms_comparison.png", dpi=200, bbox_inches="tight")
    plt.show()

    for a, label in names.items():
        final = curves[a][:, -1]
        print(f"{label:<26} regret at T={T}: {final.mean():6.1f} ± {1.96 * final.std(ddof=1) / np.sqrt(RUNS):4.1f}")


if __name__ == "__main__":
    main()
