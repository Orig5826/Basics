clc

x = [25,27,31,33,35]';
y = [110,115,155,160,180]';
X = [x ones(5,1)];

# A = inv(X'*X)*X'*y
A = (X'*X)\(X'*y)

a = A(1,1);
b = A(2,1);
y1 = a*x + b;

scatter(x,y);
grid on
hold on;
plot(x,y1);
hold on;
