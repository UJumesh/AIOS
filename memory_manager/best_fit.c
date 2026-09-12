#include <stdio.h>

int main()
{
    int block[100];
    int process[100];
    int allocation[100];

    int n, m;

    printf("AIOS Memory Manager - Best Fit\n");

    printf("\nEnter number of memory blocks: ");
    scanf("%d", &n);

    printf("Enter memory block sizes:\n");

    for(int i = 0; i < n; i++)
    {
        printf("Block %d: ", i + 1);
        scanf("%d", &block[i]);
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &m);

    printf("Enter process sizes:\n");

    for(int i = 0; i < m; i++)
    {
        printf("P%d: ", i + 1);
        scanf("%d", &process[i]);

        allocation[i] = -1;
    }

    // Best Fit
    for(int i = 0; i < m; i++)
    {
        int best = -1;

        for(int j = 0; j < n; j++)
        {
            if(block[j] >= process[i])
            {
                if(best == -1 || block[j] < block[best])
                {
                    best = j;
                }
            }
        }

        if(best != -1)
        {
            allocation[i] = best;

            block[best] =
                block[best] - process[i];
        }
    }

    printf("\n--- Best Fit Allocation ---\n");

    printf("\nProcess\tSize\tBlock\n");

    for(int i = 0; i < m; i++)
    {
        if(allocation[i] != -1)
        {
            printf("P%d\t%d\tBlock %d\n",
                   i + 1,
                   process[i],
                   allocation[i] + 1);
        }
        else
        {
            printf("P%d\t%d\tNot Allocated\n",
                   i + 1,
                   process[i]);
        }
    }

    return 0;
}