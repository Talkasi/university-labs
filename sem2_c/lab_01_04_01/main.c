#include <stdio.h>

#define NFLATS_ON_FLOOR 4
#define NFLATS_ON_ENTRANCE 36

int main(void)
{
    int n_flat;
    int n_floor, n_entrance;

    printf("Enter number of the flat: ");
    if (scanf("%d", &n_flat) != 1 || n_flat <= 0.0)
    {
        printf("Input error. Number of the flat should be bigger than zero.");
        return 1;
    }

    n_entrance = n_flat / NFLATS_ON_ENTRANCE + (n_flat % NFLATS_ON_ENTRANCE != 0);
    n_floor = (n_flat - (n_entrance - 1) * NFLATS_ON_ENTRANCE) / NFLATS_ON_FLOOR + (n_flat % NFLATS_ON_FLOOR != 0);

    printf("Number of the entrance: %d\nNumber of the floor: %d\n", n_entrance, n_floor);
    return 0;
}
