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
| `simulations/q4_thompson_sampling.py` | Thompson sampling on 6 arms, T = 10 000: regret, posterior means and posterior variances |
| `simulations/q5_algorithm_comparison.py` | ε-greedy, UCB1 and Thompson sampling, averaged over 300 runs |
| `simulations/q6_probability_matching.py` | Monte Carlo estimate of P(arm i is optimal), compared with Thompson sampling's pull frequencies (correlation) for T = 500, 1000, 5000 |
| `simulations/q7_gaussian_vs_bernoulli.py` | Normal–Normal Thompson sampling on a Gaussian bandit (σ² = 1), compared with the Bernoulli case; 300 runs |
| `simulations/q5_q6_q7_bandit_comparisons.ipynb` | Q5–Q7 in one notebook, with outputs |

Run any script with `python3 <file>.py`. It needs NumPy and Matplotlib, plus SciPy for Q3.
Every script uses a fixed random seed and reproduces the figures and numbers in the report. The scripts write
their figures to the current folder, so run them from `report/` to update the report.

The review checked every answer against the assignment text (19 pages, in Persian).

## Corrections

**Simulations**
- **Q7 (Gaussian rewards).**
  - The assignment asks for Thompson sampling on a *Gaussian* bandit (means 0.2, 0.5, 0.9, known σ² = 1) with the Normal–Normal model, compared with the Bernoulli case.
  - The script now does exactly that, over 300 runs.
  - *Result:* regret 34.9 for the Gaussian bandit against 7.7 for the Bernoulli bandit.
  - The difference comes from the noise level. The Lai–Robbins constants Σ Δ/KL are 7.86 and 1.30, so the Gaussian problem is about six times harder.
  - An extra run applies the Gaussian model to Bernoulli rewards (misspecified). Its regret, 33.2, shows that the wrong model cannot use the lower noise.
  - (An earlier revision of this review had replaced the Gaussian rewards with binary ones. That did not match the assignment and has been reverted.)
- **Q6 (probability matching).**
  - The Monte Carlo estimate now uses 20 000 samples, as the assignment asks.
  - The script reports the correlation between the estimated probabilities and the pull frequencies for each T, averaged over 100 runs.
  - The largest gap falls from 0.073 to 0.011 as T grows from 500 to 5000.
  - A stricter test is added: the share of pulls against the average of π<sub>i</sub>(t) over the run, which agree to within 0.006.
- **Q5 (algorithm comparison).**
  - *Problem:* a single run with separate random streams.
  - *Fix:* now 300 runs on common random rewards, with 95 % confidence bands.
  - *Result:* UCB1 has a larger regret than ε-greedy at T = 2000 (100.8 against 89.7), but it grows only logarithmically. A longer run shows UCB1 overtaking ε-greedy before T = 5000.
- **Q4.** Added the plot of posterior variances that the assignment asks for, and log time axes.
- **Q1, Q2, Q3.** Figures are now saved, and fixed seeds are used. Q1 adds the theoretical line 0.3 t for the uniform policy. Q2 prints the table of p̂ₙ and bₙ and uses a log axis.

**Report**
- 39 sentences had been commented out with `%` and were missing from the PDF. They are restored.
- **Theory Q1:** rewritten for the examples in the assignment (two new drugs and a standard drug, banners, nightly movie suggestions), including why pure exploitation or pure exploration fails in each.
- **Theory Q4:** stated correctly as Chebyshev's inequality, P(\|μ̂ − μ\| ≥ ε) ≤ μ(1 − μ)/(nε²).
- **Theory Q7:**
  - Answered part by part.
  - Policy A commits to the worse arm with probability 0.35, so its expected regret is about 105, against 150 for B and 15 for C (T = 1000).
  - The old text compared the policies the wrong way round.
- **Theory Q8:**
  - The confidence statement is now P(\|Y − μ\| < c) ≥ 1 − δ (an inequality, not an equality).
  - The choice δ = 2t⁻⁴ is derived.
  - The UCB bonus is explained through N<sub>i</sub>(t).
- **Theory Q10:** the full derivation, including the normalising constant, replaces "follows the same logic".
- **Theory Q13:** the answer used Beta(2, 3) (mean 0.4) instead of the Beta(3, 2) (mean 0.6) given in the assignment. It is corrected and adds P(θ₁ > θ₂) ≈ 0.41.
- **Theory Q16:** Beta(100, 100) slows learning and makes early choices nearly uniform; it does not cause under-exploration.
- **Theory Q3, Q9, Q14, Q15:** smaller technical wording fixes. For example, the posterior *equals* (not "is proportional to") a Beta distribution, and the posterior variance shrinks as 1/N<sub>i</sub>, not 1/t.
- **Simulation Q1–Q4:** the discussions now use the measured numbers. The text for Q2 said p(n) ≥ b(n), but Hoeffding's inequality gives p(n) ≤ b(n).
- **Simulation Q5–Q7:** the discussions are rewritten for the corrected simulations.

**Files**
- The scripts were renamed from `CHW1`–`CHW6/main.py` to names that match the question numbers.
- Raw strings remove Python's invalid-escape warnings.
- Figure names no longer contain `:`, which Windows does not allow in file names.
