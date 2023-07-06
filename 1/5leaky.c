
#include <stdio.h>
#include <stdlib.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))

int main()
{
    int orate, cap, nsec, ch;
    printf("\nEnter bucket size: ");
    scanf("%d", &cap);
    printf("\nEnter output rate: ");
    scanf("%d", &orate);

    int i = 0, count = 0, inp;
    do
    {
        printf("\nEnter number of packets coming at second %d: ", i + 1);
        scanf("%d", &inp);
        if (inp > cap)
        {
            printf("\nBucket overflow");
            printf("\nPacket Discarded");
            exit(0);
        }
        printf("\nEnter 1 to continue or 0 to quit: ");
        scanf("%d", &ch);
        i++;
        count += inp;
        count = MIN(count, cap);
        printf("\nSecond\tReceived\tSent\tDropped\tRemained");
        printf("\n%d\t%d\t\t%d\t%d\t%d", i, inp, MIN(count, orate), inp - MIN(count, orate), cap - count);
    } while (ch);

    return 0;
}
