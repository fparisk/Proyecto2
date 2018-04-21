function x=quantifier(y)
% get real and imag vectors
r = real(y);
im = imag(y);

% get max value
real_max= max(r);
imag_max= max(im);

% get min value
real_min= min(r);
imag_min= min(im);

r_rnd = round(r);
im_rnd = round(im);

x = complex(r_rnd,im_rnd);
m_max = max(x);
end