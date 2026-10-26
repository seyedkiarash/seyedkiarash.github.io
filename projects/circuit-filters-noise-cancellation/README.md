# Active Filters and Analog Noise Cancellation (Circuit Theory project)

Team project for Circuit Theory (Dr. Rouhollah Amiri, Department of Electrical Engineering,
Sharif University of Technology, Fall 2025). The project has three parts:

1. **State-variable (Sharif analog) filter.** A three-op-amp filter gives high-pass, band-pass and
   low-pass outputs at once. The task was to derive its transfer functions and design it for
   f<sub>c</sub> = 20 kHz and Q = 0.75. The bonus question adds a notch output.
2. **All-pass filters and analog noise cancellation.** First- and second-order all-pass filters are
   analysed and then used in a chain that removes noise from a music recording:
   - gain of 10;
   - a 45 µs all-pass delay stage;
   - summation with the noisy signal;
   - polarity inversion.
3. **High-frequency response of transistor amplifiers.** MOSFET and BJT high-frequency models,
   solved by hand.

| Path | Contents |
| --- | --- |
| `report/circuit-theory-project-report.pdf` | Full report: derivations (handwritten pages), simulation results and answers |
| `part1-state-variable-filter/` | LTspice schematic (`state_variable_filter.asc`) and screenshots, including the bonus notch filter |
| `part2-allpass-noise-cancellation/ltspice/` | LTspice schematics of the gain, all-pass delay and summer/inverter stages |
| `part2-allpass-noise-cancellation/simulink/` | Simulink/Simscape model of the whole chain, plus two scripts that load the audio into the workspace |
| `part2-allpass-noise-cancellation/audio/` | Input recordings (music + noise, isolated noise) and the Simulink output |
| `verification/` | ngspice netlists generated from the schematics, and a Python script that measures the noise reduction |

## Verification

The LTspice schematics were converted to ngspice netlists by `asc2cir.py`, with the OP747 modelled as a
1.8 MHz gain-bandwidth op-amp, and simulated again. The results match the design:

- **State-variable filter:** f<sub>0</sub> = 20.1 kHz and Q = 0.76 (targets 20 kHz and 0.75). With an
  ideal op-amp the results are 19.95 kHz and 0.75.
- **All-pass stage:** group delay of 44.9 µs below 3 kHz, which covers the noise band (below about 2 kHz).
  The magnitude is flat to within 0.05 dB below 1 kHz but dips by about 2 dB near 10 kHz, so the stage
  is not an exact all-pass at high frequencies. This has no effect on the low-frequency noise used here.
- **Noise cancellation:** `verification/anc_check.py` finds that the noise inside the recording is
  10.06 × the isolated noise. The Simulink output reduces it by about **33 dB**, and the signal-to-noise
  ratio rises from 8.4 dB to 41.9 dB. A Python model of the same transfer functions reproduces the
  Simulink output to within 0.5 %.

## Notes on the files

- **Duplicates and generated files.** The original folder held two versions of the Simulink model and of its
  loading scripts. The newer one was kept: it was at the project root and uses the `part2_audio_files` folder.
  Simulink cache files (`slprj/`, `.slxc`) and LTspice output files (`.raw`, `.log`) are not included.
- **Renamed files.** Schematics and screenshots were renamed by function (e.g. `Draft17.asc` →
  `stage3_allpass_delay_45us.asc`).
- **Loader scripts.** They now find the audio relative to their own folder instead of an absolute `D:\` path.
  The *To Multimedia File* block inside the model still writes to the original desktop path.
- **`output_after_cancellation.wav`** ends about 11 ms early, because the archive copy was incomplete.
  Its header was repaired so the file plays.
- **Bonus notch filter.** Only screenshots exist; the `.asc` file in the bonus folder was a copy of the part 1
  schematic.
