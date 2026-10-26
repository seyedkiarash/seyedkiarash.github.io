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
| `simulations/q6_probability_matching.py` | Thompson sampling selection frequencies against Monte Carlo P(arm is optimal) |
| `simulations/q5_q6_q7_bandit_comparisons.ipynb` | ε-greedy, UCB and Thompson sampling compared (Q5); Q6 again; Gaussian against Bernoulli Thompson sampling (Q7) |

Run any script with `python3 <file>.py`. It needs NumPy and Matplotlib, plus SciPy for Q3.
Q1–Q4 have no fixed random seed, so their curves change slightly from run to run. Q5–Q7 use `seed(42)` and
reproduce the numbers in the report exactly.

## Changes made when organizing the project

**Files**
- The scripts were renamed from `CHW1`–`CHW6/main.py` to names that match the question numbers.
- Two LaTeX labels were made raw strings to remove Python's invalid-escape warnings.
- The notebook now saves its figures as `Q5-…png` and `Q7-…png`. The old names contained `:`, which Windows does not allow in file names.
- No other code changed.

**Report text**
- 39 sentences of the report had been commented out with `%` and were missing from the PDF. They are restored; for example, Theory Question 7 now explains the 100-round exploration phase that its last sentence refers to.

**Report corrections**
- *Theory Question 4:* the concentration inequality is now stated as Chebyshev's inequality,
  P(\|μ̂ − μ\| ≥ ε) ≤ μ(1 − μ)/(nε²).
- *Theory Question 8:* the explanation of the UCB bonus is reworded.
- *Simulation Question 2:* the text said p(n) ≥ b(n). The plot (and Hoeffding's inequality) show p(n) ≤ b(n), so the text was corrected.
- *Simulation Question 5:* the text grouped UCB with Thompson sampling as the better algorithms. In the plotted run of 2000 steps UCB still has the larger total regret, although its curve flattens. The paragraph now says so.
