
clc

function [J] = cost_function(X,y,theta)
  m = length(y);
  J = 1/(2*m) .* sum((X*theta - y).^2);
endfunction

function [J_history,theta] = gradient_descent(X,y,theta,alpha,iters)
   m = length(y);
   J_history = zeros(iters,1);
   for iter = 1:iters
     theta = theta - alpha * 1/m.*X'*(X*theta - y);
     J_history(iter) = cost_function(X,y,theta);
   end
endfunction

x = [25,27,31,33,35]';
y = [110,115,155,160,180]';
m = length(x);
X = [x ones(5,1)];

theta = [0,0]';
alpha = 0.0021;
iters = 400000;
[J,theta] = gradient_descent(X,y,theta,alpha,iters);
disp(theta);
