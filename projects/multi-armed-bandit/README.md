# Multi-Armed Bandit (Probability and Statistics project)

Team project for Probability and Statistics in Engineering (Dr. Mohammad Hossein Yassaee,
Department of Electrical Engineering, Sharif University of Technology, Fall 2025). It studies the
multi-armed bandit problem in theory and in simulation:

- the exploration–exploitation trade-off and the definition of regret;
- concentration bounds (Chebyshev, Hoeffding) and the UCB rule;
- Beta–Bernoulli Bayesian updating;
- Thompson sampling, including its link to probability matching and the effect of the prior.

| Path | Contents |
| --- | --- |
| `report/project.pdf` | Report: 16 theory questions and 7 simulation questions (source: `project.tex` plus figures) |
| `simulations/q1_uniform_vs_greedy.py` | Cumulative regret of uniform and greedy policies, 3 Bernoulli arms, averaged over 500 runs |
| `simulations/q2_hoeffding_bound.py` | Empirical P(\|mean − μ\| ≥ 0.1) against the Hoeffding bound |
| `simulations/q3_beta_posterior.py` | Beta posterior after 0, 5, 20, 100 and 200 observations |
| `simulations/q4_thompson_sampling.py` | Thompson sampling on 6 arms: regret and posterior means |
| `simulations/q5_algorithm_comparison.py` | ε-greedy, UCB1 and Thompson sampling, averaged over 300 runs |
| `simulations/q6_probability_matching.py` | Checks that Thompson sampling pulls each arm as often as the posterior says it is optimal |
| `simulations/q7_gaussian_vs_bernoulli.py` | Gaussian and Bernoulli Thompson sampling on the same binary rewards, 200 runs |
| `simulations/q5_q6_q7_bandit_comparisons.ipynb` | Q5–Q7 in one notebook, with outputs |

Run any script with `python3 <file>.py`. It needs NumPy and Matplotlib, plus SciPy for Q3.
Q1–Q4 have no fixed random seed, so their curves change slightly from run to run. Q5–Q7 use a fixed seed and
reproduce the numbers in the report exactly.

## Corrections

**Simulations**
- **Q7 (Gaussian against Bernoulli Thompson sampling).**
  - *Error:* the Gaussian algorithm was given rewards drawn from N(μ, 1), while the Bernoulli algorithm got 0/1 rewards. The two were solving different, unequally noisy problems, so the comparison did not test the likelihood model.
  - *Fix:* both algorithms now see the same binary rewards, averaged over 200 runs.
  - *Result:* regret 34.4 against 7.8. The misspecified Gaussian model assumes a reward variance of 1 instead of at most 0.25, so its posteriors stay too wide and it explores too much.
- **Q5 (algorithm comparison).**
  - *Problem:* a single run with separate random streams.
  - *Fix:* now 300 runs on common random rewards, with 95 % confidence bands.
  - *Result:* UCB1 has a larger regret than ε-greedy at T = 2000 (100.8 against 89.7), but grows only logarithmically. A longer run shows ε-greedy overtaking it before T = 5000.
- **Q6 (probability matching).**
  - *Problem:* the old test compared the share of pulls with π<sub>i</sub> at the *end* of the run, using a correlation that is near 1 for almost any algorithm.
  - *Fix:* the new test compares the share of pulls with the average of π<sub>i</sub>(t) over the same steps, which is what probability matching predicts. They agree to within 0.001–0.004.

**Report**
- 39 sentences had been commented out with `%` and were missing from the PDF. They are restored.
- **Theory Q4:** stated correctly as Chebyshev's inequality, P(\|μ̂ − μ\| ≥ ε) ≤ μ(1 − μ)/(nε²).
- **Theory Q8:** the confidence statement is now P(\|Y − μ\| < c) ≥ 1 − δ (an inequality, not an equality). The explanation of the UCB bonus is corrected.
- **Theory Q3, Q9, Q14, Q15:** smaller technical wording fixes, e.g. the posterior *equals* (not "is proportional to") a Beta distribution, and the posterior variance shrinks as 1/N<sub>i</sub>, not 1/t.
- **Simulation Q2:** the text said p(n) ≥ b(n). Hoeffding's inequality, and the plot, give p(n) ≤ b(n).
- **Simulation Q5–Q7:** the discussions are rewritten for the corrected simulations.

**Files**
- The scripts were renamed from `CHW1`–`CHW6/main.py` to names that match the question numbers.
- Raw strings remove Python's invalid-escape warnings.
- Figure names no longer contain `:`, which Windows does not allow in file names.
