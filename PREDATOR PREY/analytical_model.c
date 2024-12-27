#include <stdio.h>

double dxdt(double x, double y, double alpha, double beta) {
    return alpha * x - beta * x * y;
}

double dydt(double x, double y, double delta, double gamma) {
    return delta * x * y - gamma * y;
}

int main() {
    double x0, y0;
    printf("Enter initial value for x: ");
    scanf("%lf", &x0);
    printf("Enter initial value for y: ");
    scanf("%lf", &y0);
    
    double alpha, beta, delta, gamma;
    printf("Enter value for alpha: ");
    scanf("%lf", &alpha);
    printf("Enter value for beta: ");
    scanf("%lf", &beta);
    printf("Enter value for delta: ");
    scanf("%lf", &delta);
    printf("Enter value for gamma: ");
    scanf("%lf", &gamma); 

    double xeq = gamma / delta;
    double yeq = alpha / beta;

    printf("Equilibrium points:\n");
    printf("x_eq = %.2lf\n", xeq);
    printf("y_eq = %.2lf\n\n", yeq);

    double dt = 0.01;  
    double x = x0, y = y0;

    printf("Phase trajectory:\n");
    printf("(x, y) = (%.2lf, %.2lf)\n", x, y);

    for (int i = 0; i < 100; i++) 
    {
        double k1x = dt * dxdt(x, y, alpha, beta);
        double k1y = dt * dydt(x, y, delta, gamma);

        double k2x = dt * dxdt(x + 0.5 * k1x, y + 0.5 * k1y, alpha, beta);
        double k2y = dt * dydt(x + 0.5 * k1x, y + 0.5 * k1y, delta, gamma);

        x += k2x;
        y += k2y;

        printf("(%.2lf, %.2lf)\n", x, y);
    }

    return 0;
}
