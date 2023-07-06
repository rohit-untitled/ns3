#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char g[] = "100000111";

void crc()
{
    char t[120], cs[120];
    int a, c, e;

    printf("enter the polynomial: ");
    scanf("%s", t);

    printf("generating polynomial is %s\n", g);

    a = strlen(t);
    strcpy(cs, t);

    for (e = 0; e < a; e++)
    {
        if (cs[e] == '1')
        {
            for (c = 1; c < strlen(g); c++)
            {
                cs[e + c] = (cs[e + c] == g[c]) ? '0' : '1';
            }
        }
    }

    printf("checksum is: %s\n", cs + a);

    strcpy(t + a, cs + a);

    printf("final codeword is: %s\n", t);
}

int main()
{
    crc();
    return 0;
}
