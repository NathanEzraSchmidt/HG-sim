#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hg.h"

int main()
{

//    int a[24];
//    int pp=0;
//    while (1)
//    {
//        int x;
//        scanf("%d", &x);
//        if (x == -1)
//            break;
//        a[pp] = x;
//        pp++;
//    }
//    print_arr(a,pp);
//    return 0;
    srand(time(NULL));

    int bj_bets[16];

    printf("print mode? (enter 0 or 1): ");

    int debug;
    scanf("%d", &debug);
    if (debug == 0) {
        while (1){
            int n;
            printf("number of bets = ");
            scanf("%d", &n);
            for (int i = 0; i < n; ++i) {
                printf("bet %d = ", i+1);
                scanf("%d", &bj_bets[i]);
            }
            puts("simulating 1,000,000 hands...\n");
            sim(1000000, 50, 8, 1.2, bj_bets, n, sum(bj_bets, n), 0);
        }
    }
    else {
        while (1){
            int n;
            printf("number of bets = ");
            scanf("%d", &n);
            for (int i = 0; i < n; ++i) {
                printf("bet %d = ", i+1);
                scanf("%d", &bj_bets[i]);
            }
            int bank_total;
            printf("bank size = ");
            scanf("%d", &bank_total);
            printf("number of hands simulated = ");
            int hand_num;
            scanf("%d", &hand_num);
            sim(hand_num, 50, 8, 1.2, bj_bets, n, bank_total, 1);
        }
    }
    return 0;
}
