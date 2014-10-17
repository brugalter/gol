//
//  written by ryan holman
//



#include <stdio.h>
#include <time.h>


#define ROWS 24 
#define COLS 70 

int generation = 0;
int population = 0;
int populationMax = 0;
int populationMin = 0;
int tempGrid[ROWS][COLS];

int getUserInput();
void initGrid(int, int, int[ROWS][COLS]);
void proccessGeneration(int, int, int[ROWS][COLS]);
int countNeighbors(int, int, int[ROWS][COLS], int x, int y);
void printGrid(int, int, int[ROWS][COLS]);
void sleep(unsigned int);


int main()

{
    srand((unsigned int) time(NULL));
    int grid[ROWS][COLS];
    initGrid(ROWS, COLS, grid);
    printGrid(ROWS, COLS, grid);

    int i, g;

    g = getUserInput();
    for(i = 0; i < g; i++)
    {
        generation++;
        proccessGeneration(ROWS, COLS, grid);
        printGrid(ROWS, COLS, grid);
        sleep(99999);
        putchar('\n');
    }



    return 0;

}


// *************************************
int getUserInput()
{
    int g;
    printf("thanks for playing, ");

    printf("please enter how many generations you would like to see: ");
    while (!scanf("%d", &g)) {
      printf("\nnumbers only please\n");
      printf("please enter how many generations you would like to see: ");
      while (getchar() != '\n');
    }

    return g;
}
// **************************************
void initGrid(int rows, int cols, int g[rows][cols])
{
    int i, j, k;
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            /*
                [-1][-1][-1][-1][-1][-1]
                [-1][  ][  ][  ][  ][-1]
                [-1][  ][  ][  ][  ][-1]
                [-1][-1][-1][-1][-1][-1]
            */
            if((i == 0 || i == (rows - 1)) || (j == 0 || j == (cols - 1)))
                g[i][j] = -1;
            else
            {
                k = rand() % 3;
                if(k == 0)
                {
                    g[i][j] = 1;
                    population++;
                }
                else g[i][j] = 0;
            }
        }
    }

    proccessGeneration(rows,cols, g);
}
// **************************************
void proccessGeneration(int rows, int cols, int g[rows][cols])
{
    int i, j, neighbors;
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            if(g[i][j] == -1) continue;
            neighbors = countNeighbors(rows, cols, g, i, j);

            if (g[i][j] == 1 && (neighbors > 3 || neighbors < 2))
            {
                tempGrid[i][j] = 0;
            }
            else if ((g[i][j] == 0) && (neighbors == 3))
            {
                tempGrid[i][j] = 1;
            }

        }
    }
    population = 0;
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            if (g[i][j] == -1) continue;
            if (tempGrid[i][j] == 1) population++;
            g[i][j] = tempGrid[i][j];
        }
    }
    if (population > populationMax) populationMax = population;
    if ((population < populationMin) || (population == 0)) populationMin = population;
}
// **************************************
int countNeighbors(int rows, int cols, int g[rows][cols],int y, int x)
{
    int i, j, neighbors = 0;
    for(i = y - 1; i < y + 2; i++)
    {
        for(j = x - 1; j < x + 2; j++)
        {
            if(i == y && j == x) continue;
            if(g[i][j] != -1) neighbors += g[i][j];
        }
    }

    return neighbors;
}
// **************************************
void printGrid(int rows, int cols, int g[rows][cols])
{
    int i, j;
    system("clear");
    printf("WELCOME TO MY GAME OF LIFE -- %d\n", generation);
    printf("Current Population %d  MAX %d MIN %d\n", population
                                                   , populationMax
                                                   , populationMin);
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            switch (g[i][j])
            {
                case  0:
                    printf(" ");
                    break;
                case  1:
                    printf("O");
                    break;
                case -1:
                    printf("X");
                    break;
                default:
                    break;
            }
        }
        putchar('\n');
    }

}
// **************************************
void sleep(unsigned int mill)

{

	clock_t start = clock();

	while(clock() - start < mill) { }

}
