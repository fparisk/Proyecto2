function x()

yn = zeros(64,1);
y_coded = 0;
y_decoded = 0;
[y,Fs] = audioread('C:\Users\parisfe\Desktop\Maestria\adquisicion y proc datos\Proyecto2\muestra.wav');

% codec
for n = 64:64:length(y)
    yn = y(n-63:n); % take blocks of 64 samples   
    Y = rfft(yn,64); % code
    y_coded = cat(2,y_coded,Y); % concatenate y_tmp to y_coded
end

disp('length y_coded: ');
disp(length(y_coded));

% decodec
for i = 33:33:length(y_coded)
    yn_coded = y_coded(i-32:i); % take blocks of 64 samples
    y_temp = irfft(yn_coded,64); % decode
    y_decoded = cat(2,y_decoded,y_temp); % concatenate y_tmp to output 
end

disp('length y: ');
disp(length(y));     

audiowrite('C:\Users\parisfe\Desktop\Maestria\adquisicion y proc datos\Proyecto2\decodec2_32.wav',y_decoded,Fs);