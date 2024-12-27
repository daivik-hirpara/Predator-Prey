#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define sizeX 20
#define sizeY 20
#define ecell '.'
#define fcell 'F'
#define scell 'S'

float fishratio;
float sharkratio;
int fbreedt;
int sbreedt;
int sstarvet;

double dxdt(double x, double y, double alpha, double beta) {
    return alpha * x - beta * x * y;
}

double dydt(double x, double y, double delta, double gamma) {
    return delta * x * y - gamma * y;
}

void initialize(char grid[][sizeY])
{
    int i, j;
    for (i = 0; i < sizeX; i++){
        for (j = 0; j < sizeY; j++){
            grid[i][j] = ecell;
        }
    }
}

void populategrid(char grid[][sizeY]){
    int i, j;
    int fcount = fishratio * sizeX * sizeY;
    int scount = sharkratio * sizeX * sizeY;

    while (fcount > 0) {
        i = rand() % sizeX;
        j = rand() % sizeY;
        if (grid[i][j] == ecell) {
            grid[i][j] = fcell;
            fcount--;
        }
    }

    while (scount > 0) {
        i = rand() % sizeX;
        j = rand() % sizeY;
        if (grid[i][j] == ecell) {
            grid[i][j] = scell;
            scount--;
        }
    }
}

void print(char grid[][sizeY]) {
    int i, j;
    for (i = 0; i < sizeX; i++) {
        for (j = 0; j < sizeY; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}

void update(char grid[][sizeY], int timestep) {
    int i, j;
    char newgrid[sizeX][sizeY];

    double alpha = 0.4;
    double beta = 0.1;
    double delta = 0.1;
    double gamma = 0.104;

    for (i = 0; i < sizeX; i++) {
        for (j = 0; j < sizeY; j++) {
            int fneighbors = 0;
            int sneighbors = 0;

            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = (i + di + sizeX) % sizeX;
                    int nj = (j + dj + sizeY) % sizeY;

                    if (grid[ni][nj] == fcell) {
                        fneighbors++;
                    } else if (grid[ni][nj] == scell) {
                        sneighbors++;
                    }
                }
            }

            if (grid[i][j] == fcell) {
                double x = fneighbors;
                double y = sneighbors;

                double k1x = dxdt(x, y, alpha, beta);
                double k1y = dydt(x, y, delta, gamma);
                double k2x = dxdt(x + 0.5 * k1x, y + 0.5 * k1y, alpha, beta);
                double k2y = dydt(x + 0.5 * k1x, y + 0.5 * k1y, delta, gamma);

                x += k2x;
                y += k2y;

                if (x < 2) {
                    newgrid[i][j] = ecell;
                } else {
                    newgrid[i][j] = fcell;
                }

                if (timestep % fbreedt == 0 && newgrid[i][j] == fcell) {
                    int ni = (i + rand() % 3 - 1 + sizeX) % sizeX;
                    int nj = (j + rand() % 3 - 1 + sizeY) % sizeY;
                    if (grid[ni][nj] == ecell) {
                        newgrid[ni][nj] = fcell;
                    }
                }
            } else if (grid[i][j] == scell) {
                double x = fneighbors;
                double y = sneighbors;

                double k1x = dxdt(x, y, alpha, beta);
                double k1y = dydt(x, y, delta, gamma);
                double k2x = dxdt(x + 0.5 * k1x, y + 0.5 * k1y, alpha, beta);
                double k2y = dydt(x + 0.5 * k1x, y + 0.5 * k1y, delta, gamma);

                x += k2x;
                y += k2y;

                if (y < 2) {
                    newgrid[i][j] = ecell;
                } else {
                    newgrid[i][j] = scell;
                }

                if (timestep % sbreedt == 0 && newgrid[i][j] == scell) {
                    int ni = (i + rand() % 3 - 1 + sizeX) % sizeX;
                    int nj = (j + rand() % 3 - 1 + sizeY) % sizeY;
                    if (grid[ni][nj] == ecell) {
                        newgrid[ni][nj] = scell;
                    }
                }

                if (timestep % sstarvet == 0) {
                    newgrid[i][j] = ecell;
                }
            } else {
                newgrid[i][j] = ecell;
            }
        }
    }

    for (i = 0; i < sizeX; i++) {
        for (j = 0; j < sizeY; j++) {
            grid[i][j] = newgrid[i][j];
        }
    }
}

int main() {

    float fishratio_input, sharkratio_input;
    int fbreedt_input, sbreedt_input, sstarvet_input;

    printf("Enter fish ratio: ");
    scanf("%f", &fishratio_input);

    printf("Enter shark ratio: ");
    scanf("%f", &sharkratio_input);

    printf("Enter fish breed time: ");
    scanf("%d", &fbreedt_input);

    printf("Enter shark breed time: ");
    scanf("%d", &sbreedt_input);

    printf("Enter shark starvation time: ");
    scanf("%d", &sstarvet_input);
    
    fishratio = fishratio_input;
    sharkratio = sharkratio_input;
    fbreedt = fbreedt_input;
    sbreedt = sbreedt_input;
    sstarvet = sstarvet_input;

    char grid[sizeX][sizeY];
    int timestep;

    srand(time(NULL));

    initialize(grid);
    populategrid(grid);

    for (timestep = 1; timestep <= 30; timestep++) {
        printf("Time Step: %d\n", timestep);
        print(grid);
        update(grid, timestep);
        printf("\n");
    }

    return 0;
}
