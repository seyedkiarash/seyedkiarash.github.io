clear audio_data Fs N t
here=fileparts(mfilename('fullpath'));
[audio_data,Fs]=audioread(fullfile(here,'..','audio','input_isolated_noise.wav'));

if size(audio_data,2)>1
    audio_data=audio_data(:,1);
end

N=length(audio_data);
t=(0:N-1)'/Fs;
audio_input1.time=t;
audio_input1.signals.values=audio_data;
audio_input1.signals.dimensions=1;
disp('Done! Use "audio_input1" in the From Workspace block');
