
x = linspace(0,2*pi,32);
%Define y as the sine function evaluated at the values in x.

y = round(50*sin(x)) + 50;

[y,Fs] = audioread('muestra.wav');

yt = csvread('stest.csv');

sound(yt/1000);


N = length(y);
%Plot y versus the corresponding values in x.

subplot(4,1,1);
plot(y)

yf = rfft(y,N);
subplot(4,1,2);
plot(yf)

yr = irfft(yf,N);
subplot(4,1,3);
plot(yr)

[signal,Fs] = audioread('mono-32bit.wav');
subplot(4,1,4);
plot(signal(1:64))
sound(signal);
