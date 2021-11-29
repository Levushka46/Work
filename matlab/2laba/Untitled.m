n=15; % количество точек дискретизации
x1=linspace(0, 5, n); x2=linspace(0, 5, n); 
y=zeros(n, n);for j=1:n
y(j,:)= -x1*x2(j)+x2.^2; end
surf(x1, x2, y) 
xlabel('x_1'); ylabel('x_2'); zlabel('y'); 
title('Искомая зависимость') 