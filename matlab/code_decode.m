function x()

yn = zeros(64,1);
y_coded = [];
y_decoded = [];

[y,Fs] = audioread('muestra.wav');
soundsc(y);
csvwrite('file.csv',y)

[y,Fs] = audioread('C:\Users\parisfe\Desktop\Maestria\adquisicion y proc datos\Proyecto2\matlab\muestra.wav');

y_mono = sum(y, 2) / size(y, 2);


% codec
for n = 64:64:length(y_mono)
    yn = y_mono(n-63:n); % take blocks of 64 samples   
    Y = rfft(yn,64); % code
    if isempty(y_coded)
        y_coded = Y;
    else
        y_coded = cat(1,y_coded,Y); % concatenate y_tmp to output
    end
end

% decodec
for i = 33:33:length(y_coded)
    yn_coded = y_coded(i-32:i); % take blocks of 64 samples
    y_temp = irfft(yn_coded,64); % decode
    if isempty(y_decoded)
        y_decoded = y_temp;
    else
        y_decoded = cat(1,y_decoded,y_temp); % concatenate y_tmp to output
    end
end

disp('length y_coded: ');
disp(length(y_coded));

disp('length y: ');

disp(length(y));     
soundsc(y_decoded)
audiowrite('decodec2_32.wav',y_decoded,Fs);

disp(length(y));

disp('length y_decoded: ');
disp(length(y_decoded)); 

%ym = y_mono(7500:10500);
%yd = y_decoded(7500:10500);

figure(1)
title('Single-Sided Amplitude Spectrum')
plot(y_mono)
figure(2)
title("Decoded samples")
plot(y_decoded)

csvwrite('in_samples.csv',y)
csvwrite('coded_samples.csv',y_coded)
csvwrite('in_samples_mono.csv',y_mono)
csvwrite('decoded_samples.csv',y_decoded)

audiowrite('C:\Users\parisfe\Desktop\Maestria\adquisicion y proc datos\Proyecto2\matlab\out.wav',y_decoded,Fs);

