%[signal,Fs] = audioread('test.wav','native');
%plot(signal)
%sound(signal);
x = linspace(0,2*pi,32);
%Define y as the sine function evaluated at the values in x.

y = round(50*sin(x)) + 50;
N = length(y);
%Plot y versus the corresponding values in x.

subplot(3,1,1);
plot(y)

yf = rfft(y,N);
subplot(3,1,2);
plot(yf)

yr = irfft(yf,N);
subplot(3,1,3);
plot(yr)

figure
plot(smp)