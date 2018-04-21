function x()

%Y = rfft(y);
%y_t = irfft(Y);
%audiowrite('C:\Users\parisfe\Desktop\Maestria\adquisicion y proc datos\Proyecto2\decodec_32.wav',y_t,Fs);

yn = zeros(64,1);
y_coded = 0;
y_decoded = 0;
[y,Fs] = audioread('C:\Users\parisfe\Desktop\Maestria\adquisicion y proc datos\Proyecto2\muestra.wav');

% codec
for n = 64:64:length(y)
    yn = y(n-63:n); % take blocks of 64 samples
    
    Y = rfft(yn,64);  % code
    
    y_temp = irfft(Y,64); % decode
    y_decoded = cat(2,y_decoded,y_temp); % concatenate y_tmp to output
end

disp('length y_decoded: ');
disp(length(y_decoded));
disp('length y: ');
disp(length(y)); 

audiowrite('C:\Users\parisfe\Desktop\Maestria\adquisicion y proc datos\Proyecto2\decodec3_32.wav',y_decoded,Fs);