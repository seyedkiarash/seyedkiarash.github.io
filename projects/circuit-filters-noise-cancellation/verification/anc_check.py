"""Measure how much noise the analog cancellation chain removes from the project audio.

The noise inside the noisy recording is a scaled, slightly delayed copy of the isolated
noise. Fitting that copy gives an estimate of the clean music, against which the noise
left in the Simulink output is measured.
"""
from pathlib import Path

import numpy as np
from scipy.io import wavfile

AUDIO = Path(__file__).resolve().parent.parent / "part2-allpass-noise-cancellation" / "audio"


def load(name):
    fs, x = wavfile.read(AUDIO / name)
    x = x.astype(float)
    return fs, (x[:, 0] if x.ndim > 1 else x)


fs, mix = load("input_music_plus_noise.wav")
_, noise = load("input_isolated_noise.wav")
_, out = load("output_after_cancellation.wav")
n = min(len(mix), len(noise), len(out))
mix, noise, out = mix[:n], noise[:n], out[:n]

freqs = np.fft.rfftfreq(n, 1 / fs)
noise_f = np.fft.rfft(noise)
best = None
for tau in np.arange(0, 100e-6, 1e-6):
    shifted = np.fft.irfft(noise_f * np.exp(-2j * np.pi * freqs * tau), n)
    gain = (mix @ shifted) / (shifted @ shifted)
    resid = mix - gain * shifted
    if best is None or resid.std() < best[0].std():
        best = (resid, gain, tau)
music, gain, tau = best
noise_in = mix - music
scale = (out @ music) / (music @ music)
noise_out = out - scale * music

print(f"noise in the recording: {gain:.2f} x isolated noise, delayed {tau * 1e6:.0f} us")
print(f"SNR of the input : {20 * np.log10(music.std() / noise_in.std()):5.1f} dB")
print(f"SNR of the output: {20 * np.log10(scale * music.std() / noise_out.std()):5.1f} dB")
print(f"noise reduction  : {20 * np.log10(scale * noise_in.std() / noise_out.std()):5.1f} dB")
