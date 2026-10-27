# Active Filters and Analog Noise Cancellation (Circuit Theory project)

Team project for Circuit Theory (Dr. Rouhollah Amiri, Department of Electrical Engineering,
Sharif University of Technology, Fall 2025). The project has three parts:

1. **Sharif Analog Filter (SAF).** A three-op-amp state-variable filter with high-pass, band-pass and
   low-pass outputs, designed for f<sub>c</sub> = 20 kHz and Q = 0.75. The bonus question adds a notch output.
2. **All-pass filters and analog noise cancellation.** First- and second-order all-pass filters, and a chain
   that removes noise from a music recording:
   - gain of 10;
   - a 45 µs all-pass delay;
   - summation with the noisy signal;
   - polarity inversion.
3. **High-frequency response of transistor amplifiers.** MOSFET and BJT models, f<sub>T</sub>, CS and CE
   bandwidth with the Miller effect, RF input matching and tuned loads.

| Path | Contents |
| --- | --- |
| `report/circuit-theory-project-report.pdf` | **Corrected and completed report**, with typed derivations, comparison tables and all required plots |
| `report/original-submission.pdf` | The report as originally submitted (handwritten solution pages) |
| `part1-state-variable-filter/` | `state_variable_filter.asc`, `saf_notch.asc` (bonus notch filter, rebuilt) and screenshots |
| `part2-allpass-noise-cancellation/ltspice/` | Gain, delay and summer/inverter stages; the delay stage as built and corrected |
| `part2-allpass-noise-cancellation/simulink/` | `anc_system.slx` (as submitted), `anc_system_corrected.slx`, and two scripts that load the audio |
| `part2-allpass-noise-cancellation/audio/` | The two input recordings, the Simulink output, and the output of the corrected circuit (Python model) |
| `verification/` | ngspice netlists, `anc_check.py` (noise-reduction measurement) and the scripts for the Part III plots |

## What the review corrected and completed

**Part I**
- The design itself was correct: R<sub>F</sub> = 8 kΩ and R<sub>G</sub> = R<sub>Q</sub> = 200 kΩ give f<sub>c</sub> = 19.89 kHz and Q = 0.75 exactly, with ideal op-amps.
- Added the comparison table and percentage differences that the assignment asks for. With a 1.8 MHz op-amp model, f<sub>c</sub> and Q are about 1 % higher.
- The notch filter of the bonus question existed only as a screenshot. It was rebuilt as `saf_notch.asc`, and the notch is 36 dB below the pass band.

**Part II**
- **Error found.** The 45 µs delay stage was not an all-pass filter. Its delay had been obtained by unbalancing R<sub>3</sub> (R<sub>41</sub>/R<sub>3</sub> = 3.56 instead of 4), so the gain fell by 2.1 dB near 10 kHz.
- **Correction.** R<sub>1</sub> = R<sub>2</sub> = 1.125 kΩ and R<sub>3</sub> = 1 kΩ. This gives a true all-pass response, H(s) = −((1 − sRC)/(1 + sRC))², flat within 0.04 dB to 20 kHz, with a delay of 4RC = 45 µs.
- **Simulink model.** The same values are fixed in `anc_system_corrected.slx`. It also saves `output_corrected.wav` next to the model instead of to a desktop path. Run the two loading scripts, then run the model, to regenerate the output.
- **Delay verified by transient tests** at 200 Hz – 5 kHz (table in the report).
- **Noise cancellation.** The Simulink output reduces the noise by 33.3 dB, and the signal-to-noise ratio rises from 8.4 dB to 41.6 dB. The corrected circuit gives the same result, because the noise lies below 2 kHz.
- **Limiting factor.** The recordings contain a delay of about 30 µs rather than 45 µs. A 30 µs design (R<sub>1</sub> = R<sub>2</sub> = 750 Ω) would reach about 44 dB.

**Part III**
- All numerical answers were correct.
- Added the missing plots: current gain on linear axes and as Bode plots (Task 4.2), and the amplifier Bode plots (Task 5.3).
- Noted that the assignment's CE gain formula omits the factor r<sub>π</sub>/(r<sub>x</sub> + r<sub>π</sub>). The exact gain is −23.9 instead of −25.5.

## Files removed or renamed when organizing
- Simulink caches (`slprj/`, `.slxc`) and LTspice output files (`.raw`, `.log`) are not included.
- The older Simulink version and the handwritten photos are kept only in the downloadable archive.
- Files were renamed by function (e.g. `Draft17.asc` → `stage3_allpass_delay_45us.asc`).
- The audio-loading scripts use paths relative to their own folder.
