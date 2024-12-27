#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double initialY;  
double initialX;  

double preygrate;  
double predationrate;  
double deathrate;  
double cfactor;  

#define steps 1000 
#define dt 0.01  

double dxdt(double x, double y) {
    return preygrate * x - predationrate * x * y;
}

double dydt(double x, double y) {
    return cfactor * x * y - deathrate * y;
}

int main() {

    printf("Enter initial value for prey: ");
    scanf("%lf", &initialX);
    printf("Enter initial value for predator: ");
    scanf("%lf", &initialY);
    printf("Enter prey growth rate: ");
    scanf("%lf", &preygrate);
    printf("Enter predation rate: ");
    scanf("%lf", &predationrate);
    printf("Enter death rate: ");
    scanf("%lf", &deathrate);
    printf("Enter conversion factor: ");
    scanf("%lf", &cfactor);

    double x = initialX;
    double y = initialY;

    FILE *graph = popen("gnuplot -persist", "w");
    if (!graph) {
        printf("Error opening gnuplot\n");
        return 1;
    }

    fprintf(graph, "set title 'Lotka-Volterra Predator-Prey Model'\n");
    fprintf(graph, "set xlabel 'Prey'\n");
    fprintf(graph, "set ylabel 'Predator'\n");
    fprintf(graph, "plot '-' with lines title 'Trajectory'\n");

    for (int i = 0; i < steps; i++)
    {
        fprintf(graph, "%lf %lf\n", x, y);
        
        double k1x = dt * dxdt(x, y);
        double k1y = dt * dydt(x, y);
        
        double k2x = dt * dxdt(x + 0.5 * k1x, y + 0.5 * k1y);
        double k2y = dt * dydt(x + 0.5 * k1x, y + 0.5 * k1y);
        
        x += k2x;
        y += k2y;

        fprintf(graph, "%lf %lf\n", x, y);
    
      
    }
    fflush(graph);

    pclose(graph);

    return 0;
}
