
#include <stdio.h>
#include <stdlib.h>
#include "hg.h"

int enter_deck(int* deck)
{
    puts("Type the starting cards of the deck separated by spaces (for ten valued cards, type 10, for aces type 1). Type -1 when done and press enter.");
    printf("deck = ");
    int len = 0;
    while (1)
    {
        int x;
        scanf("%d", &x);
        if (x == -1)
            break;
        deck[len] = x;
        ++len;
    }
//    printf("deck = ");
//    print_arr_2(deck, 30);
//    printf("...\n");
    return len;
}

int get_tc(int* arr, int len)
{
    double x = 0;
    for (int i = 0; i < len; ++i) {
        int n = arr[i];
        if (n == 10 || n == 1)
            ++x;
        else if (n < 7)
            --x;
    }
    double tc = x * 52 / len;
    return (int)(tc + .5);
}

void print_arr_double(double* arr, int len)
{
    for (int i = 0; i < len; i++)
        printf("%f\n", arr[i]);
}

void print_arr(int* arr, int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

void print_arr_2(int* arr, int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
}

int sum(int* arr, int n)
{
    int x = 0;
    for (int i = 0; i < n; ++i)
        x += arr[i];
    return x;
}

void shuffle(int* arr, int n)
{
    for (int i = 0; i < n; ++i){
        int r = i + rand() % (n - i);
        int x = arr[i];
        arr[i] = arr[r];
        arr[r] = x;
    }
}

void get_deck(int* deck, int n)
{
    int k = 0;

    int arr[] = {1,2,3,4,5,6,7,8,9,10,10,10,10};

    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 4 * n; ++j) {
            deck[k] = arr[i];
            ++k;
        }
    }
    shuffle(deck, n*52);
}

int has_bj(int* hand)
{
    if ((hand[0] == 10 && hand[1] == 1) || (hand[0] == 1 && hand[1] == 10))
        return 1;
    else
        return 0;
}

int go_dealer(int* hand, int* deck, int len, int* deck_pos, int hit_17, int* dealer_len) {

    int s = sum(hand, len);
    int ace = 0;
    for (int i = 0; i < len; ++i) {
        if (hand[i] == 1) {
            ace = 1;
            break;
        }
    }
    if ((s > 7 && s < 12 && ace == 1) || (s == 7 && ace == 1 && hit_17 == 0)) {
        s += 10;
    }
    if (s > 16) {
        *dealer_len = len;
        return s;
    }
    hand[len] = deck[deck_pos[0]];
    deck_pos[0] += 1;
    return go_dealer(hand, deck, len+1, deck_pos, hit_17, dealer_len);
}

void test_go_dealer()
{
    while (1) {
        int deck[52];
        get_deck(deck, 1);
        int hand[32];
        int deck_pos[] = {2};
        int hit_17 = 1;
        hand[0] = deck[0];
        hand[1] = deck[1];
        int dealer_len[1];
        int s = go_dealer(hand, deck, 2, deck_pos, hit_17, dealer_len);
        print_arr(deck, 12);
        print_arr(hand, deck_pos[0]);
        printf("%d\n", s);
        printf("len = %d\n", dealer_len[0]);
        getchar();
    }
}

int compare_player_dealer(int* player, int len, int* dealer, int dealer_len, int no_bust)
{
    int dealer_sum = sum(dealer, dealer_len);
    if (dealer_sum < 17)
        dealer_sum += 10;
    if (has_bj(dealer)) {
        if (has_bj(player))
            return 2;
        else
            return 1;
    }
    if (has_bj(player))
        return 0;
    if (player[0] == -1)
        return 1;
    int player_sum = sum(player, len);
    int ace = 0;
    for (int i = 0; i < len; ++i) {
        if (player[i] == 1) {
            ace = 1;
            break;
        }
    }
    if (player_sum < 12 && ace == 1)
        player_sum += 10;

    if (player_sum > 22 && len == 3 && no_bust == 1) {
        if (dealer_sum > player_sum)
            return 2;
    }

    if (player_sum > 21){
        if (dealer_sum == 26 && dealer_len == 3)
            return 2;
        else
            return 1;
    }

    if (dealer_sum > 21)
        return 0;
    if (player_sum == dealer_sum)
        return 2;
    if (dealer_sum < player_sum)
        return 0;
    else
        return 1;

    return -2;
}

int get_hard_soft(int* player, int len)
{
    int s = sum(player, len);
    int ace = 0;
    for (int i = 0; i < len; ++i) {
        if (player[i] == 1) {
            ace = 1;
            break;
        }
    }
    if (ace == 0)
        return 0;
    if (s < 12)
        return 1;
    else
        return 0;
}

int get_rep_lens(int* arr_1, int* arr_2, int len_1)
{
    int x = 1;
    int j = 0;

    for (int i = 1; i < len_1; ++i) {
        if (arr_1[i] != arr_1[i-1]) {
            arr_2[j] = x;
            x = 1;
            ++j;
        }
        else
            ++x;
    }
    arr_2[j] = x;
    return j + 1;
}

double get_banker_results(int* action_arr, int* action_arr_totals, int display, int hand_num, int amount_bet)
{
    int cumsum_arr[32000];
    int len = 0;
    int total = 0;
    while (1) {
        if (action_arr_totals[len] == 0)
            break;
        total += action_arr[len];
        cumsum_arr[len] = total;
        ++len;
    }
    int best_pos = 0;
    double best_return = 0;
    for (int j = 0; j < len; ++j) {
        if (cumsum_arr[j] > best_return) {
            best_return  = cumsum_arr[j];
            best_pos = j;
        }
    }

    double ev = best_return / hand_num;

    int rep_list[32000];
    int rep_list_cumsum[32000];

    int len_2 = get_rep_lens(action_arr, rep_list, len);
    double pph_cumsum[32000]; // profit per hand accumulative sum
    int x = 0; //rep_list[0];
    for (int i = 0; i < len_2; ++i) {
        x += rep_list[i];
        pph_cumsum[i] = cumsum_arr[x-1] / (double)hand_num;
        rep_list_cumsum[i] = x;
    }

    printf("action covered\tprofit per hand\n");
    for (int i = 0; i < len_2; ++i) {
        printf("%d\t\t%.6f\n", rep_list_cumsum[i], pph_cumsum[i]);

    }

    if (best_pos < 2)
        best_pos = -1;

    printf("best amount = %d\n", best_pos+1);
    printf("profit per hand = %.6f\n", ev);
    ev /= amount_bet;
    printf("ev = %.6f\n\n*********\n\n", ev);

    return ev;
}

int get_basic_strat(int* player, int n, int upcard, int split_allowed, int no_bust)
{
    /*
    player: list
    upcard: int
    n: length of player

    return values:
        0: stand
        1: hit
        2: double
        3: split
        4: surrender
    */
    int u = upcard;
    int s = sum(player, n);
    int soft = get_hard_soft(player, n);

    if (n == 2 && player[0] == 1 && player[1] == 1 && split_allowed == 1)
        return 3;

    if (n == 2 && player[0] == player[1] && split_allowed == 1) {
        int x = player[0];
        if (x == 2 || x == 3 || x == 7) {
            if (u >= 2 && u <= 7)
                return 3;
        }
        if (x == 4) {
            if (u == 5 || u == 6)
                return 3;
        }
        if (x == 6) {
            if (u >= 2 && u <= 6)
                return 3;
        }
        if (x == 8) {
            if (u == 1)
                return 3;
            else
                return 3;
        }
        if (x == 9) {
            if (u != 7 && u != 10 && u != 1)
                return 3;
        }
    }
    if (soft == 0) {
        if (s < 9)
            return 1;
        if (s == 9) {
            if (u >= 2 && u <= 6 && n == 2)
                return 2;
            else
                return 1;
        }
        if (s == 10) {
            if (u == 1 || u == 10 || n > 2)
                return 1;
            else
                return 2;
        }
        if (s == 11) {
            if (n == 2)
                return 2;
            else
                return 1;
        }
        if (s == 12) {
            if (u == 4 || u == 5 || u == 6)
                return 0;
            else
                return 1;
        }
        if (s == 13 || s == 14) {
            if (u >= 2 && u <= 6)
                return 0;
            else
                return 1;
        }
        if (s == 15) {
            if (u == 10 || u == 1)
                return 1;
            else {
                if (u >= 2 && u <= 6)
                    return 0;
                else
                    return 1;
            }
        }
        if (s == 16) {
            if (u == 1 || u == 10)
                return 4;
            if (u >= 2 && u <= 6)
                return 0;
            else
                return 1;
        }
        if (s == 17) {
            if (u == 1)
                return 4;
            else
                return 0;
        }
        if (s >= 18)
            return 0;
    }
    else {
        if (n > 2) {
            if (s < 8)
                return 1;
            if (s == 8 && (u == 9 || u == 10 || u == 1))
                return 1;
            else
                return 0;
            if (s > 8)
                return 0;
        }
        if (s == 2)
            return 1;
        if (s == 3 || s == 4) {
            if (u == 5 || u == 6)
                return 2;
            else
                return 1;
        }
        if (s == 5 || s == 6) {
            if (u >= 4 && u <=6)
                return 2;
            else
                return 1;
        }
        if (s == 7) {
            if (u >= 3 && u <= 6)
                return 2;
            else
                return 1;
        }
        if (s == 8) {
            if (u >= 2 && u <= 6)
                return 2;
            else if (u == 2 || u == 7 || u == 8)
                return 0;
            else
                return 1;
        }
        if (s == 9 && u == 6)
            return 2;
        if (s > 8)
            return 0;
    }
    return -2;
}

void split_aces(int result[32][32], int result_lens[32], int* result_len, int result_pos, int* split_count, int* deck, int* deck_pos, int m)
{
    if (result_lens[result_pos] == 0)
        return;

    int c = deck[*deck_pos];
    deck_pos[0] += 1;

    int len = result_lens[result_pos];

    if (c != 1 || *split_count == m){
        result[result_pos][len] = c;
        ++result_lens[result_pos];
        split_aces(result, result_lens, result_len, result_pos+1, split_count, deck, deck_pos, m);
    }
    else {
        split_count[0] += 1;
        result[*result_len][0] = 1;
        result_lens[*result_len] = 1;
        result_len[0] += 1;
        split_aces(result, result_lens, result_len, result_pos, split_count, deck, deck_pos, m);
    }
}

void test_split_aces()
{
    int result[32][32];
    result[0][0] = 1;
    result[1][0] = 1;
    int result_len[1] = {2};
    int result_pos = 0;
    int result_lens[32];
    for (int i = 0; i < 32; ++i)
        result_lens[i] = 0;
    result_lens[0] = 1;
    result_lens[1] = 1;

    int deck[52*8];
    get_deck(deck, 8);
    int deck_pos[1] = {0};
    int m = 3;

    int split_count[] = {1};

    deck[0] = 2;
    deck[1] = 1;
    deck[2] = 6;
    deck[3] = 1;
    deck[4] = 3;
    deck[5] = 7;

    print_arr(deck, 20);

    split_aces(result, result_lens, result_len, result_pos, split_count, deck, deck_pos, m);

    print_arr(result_lens, 32);
    for (int i = 0; i < *result_len; ++i)
        print_arr(result[i], result_lens[i]);
}

void show_basic_strat()
{
    int player[8];
    player[0] = 6;
    char* actions[] = {"S", "H", "D", "P", "R"};
    for (int i = 2; i < 11; ++i) {
        player[1] = i;
        print_arr(player, 2);
        for (int u = 1; u < 11; ++u) {
            int x = get_basic_strat(player, 2, u, 1, 0);
            printf("dealer = %d, %s\n", u, actions[x]);
        }
    }

    for (int i = 1; i < 11; ++i) {
        player[0] = i;
        player[1] = i;
        print_arr(player, 2);
        for (int u = 1; u < 11; ++u) {
            int x = get_basic_strat(player, 2, u, 0, 0);
            printf("dealer = %d, %s\n", u, actions[x]);
        }
    }

    for (int i = 1; i < 11; ++i) {
        player[0] = 1;
        player[1] = i;
        print_arr(player, 2);
        for (int u = 1; u < 11; ++u) {
            int x = get_basic_strat(player, 2, u, 1, 0);
            printf("dealer = %d, %s\n", u, actions[x]);
        }
    }

    puts("******************");
    for (int i = 2; i < 11; ++i) {
        player[0] = 2;
        player[1] = 2;
        player[2] = i;
        print_arr(player, 3);
        for (int u = 1; u < 11; ++u) {
            int x = get_basic_strat(player, 3, u, 1, 0);
            printf("dealer = %d, %s\n", u, actions[x]);
        }
    }

    for (int i = 1; i < 11; ++i) {
        player[0] = 1;
        player[1] = 1;
        player[2] = i;
        print_arr(player, 3);
        for (int u = 1; u < 11; ++u) {
            int x = get_basic_strat(player, 3, u, 1, 0);
            printf("dealer = %d, %s\n", u, actions[x]);
        }
    }
}

void reset_results(int result_lens[32], int* result_len, int* split_count)
{
    for (int i = 0; i < 32; ++i)
        result_lens[i] = 0;
    result_len[0] = 0;
    split_count[0] = 0;
}

void go_player(int result[32][32], int result_lens[32], int* result_len, int* split_count, int* deck, int* deck_pos, int m, int* player, int player_len, int* dealer)
{
    int split_allowed = 1;

    if (split_count[0] == m)
        split_allowed = 0;
    int upcard = dealer[0];
    if (player[0] == 1 && player[1] == 1 && player_len == 2) {
        result[0][0] = 1;
        result[1][0] = 1;
        result_len[0] = 2;
        int result_pos = 0;

        result_lens[0] = 1;
        result_lens[1] = 1;

        split_aces(result, result_lens, result_len, result_pos, split_count, deck, deck_pos, 3);
        return;
    }

    int action;

    if (player_len == 1)
        action = 1;
    else
        action = get_basic_strat(player, player_len, upcard, split_allowed, 0);

    if (action == 0) {
        for (int i = 0; i < player_len; ++i) {
            result[*result_len][i] = player[i];
        }
        result_lens[*result_len] = player_len;
        result_len[0] += 1;
    }

    if (action == 4) {
        result[*result_len][0] = -1;
         for (int i = 0; i < player_len; ++i)
            result[*result_len][i+1] = player[i];
        result_lens[*result_len] = player_len + 1;
        result_len[0] += 1;
    }

    if (action == 2) {
        int x = deck[*deck_pos];
        deck_pos[0] += 1;
        player[player_len] = x;
        player_len += 1;
        for (int i = 0; i < player_len; ++i) {
            result[*result_len][i] = player[i];
            result[*result_len+1][i] = player[i];
        }
        result_lens[*result_len] = player_len;
        result_lens[*result_len+1] = player_len;
        result_len[0] += 2;
    }

    if (action == 1) {
        int x = deck[*deck_pos];
        deck_pos[0] += 1;
        player[player_len] = x;
        player_len += 1;

        go_player(result, result_lens, result_len, split_count, deck, deck_pos, m, player, player_len, dealer);
    }

    if (action == 3) {
        split_count[0] += 1;
        go_player(result, result_lens, result_len, split_count, deck, deck_pos, m, player, 1, dealer);
        go_player(result, result_lens, result_len, split_count, deck, deck_pos, m, player, 1, dealer);
    }
}

void test_go_player()
{
    int deck[52*8];
    get_deck(deck, 8);
    deck[0] = 8;
    for (int i = 0; i < 10; ++i)
        deck[i] = 8;
    deck[0] = 10;
    deck[1] = 8;
    deck[2] = 3;

    int player[32] = {9,9};
    printf("player = ");
    scanf("%d%d", &player[0], &player[1]);
    print_arr(player, 2);
    int dealer[2] = {7, 6};
    printf("dealer = ");
    scanf("%d", dealer);
    int result[32][32];
    int result_lens[32];
    int result_len[1];
    int split_count[1];
    reset_results(result_lens, result_len, split_count);
    int deck_pos[1] = {0};
    int player_len = 2;
    print_arr(deck, 10);
    go_player(result, result_lens, result_len, split_count, deck, deck_pos, 3, player, player_len, dealer);
    print_arr(result_lens, 32);
    for (int i = 0; i < *result_len; ++i)
        print_arr(result[i], result_lens[i]);
}

double sim(int sims, int pen, int deck_num, double bj_pay, int* bj_bets, int hand_num, int bank_total_start, int debug, int custom_deck)
{
    int action_arr[64000];
    int action_arr_totals[64000];
    for (int i = 0; i < 64000; ++i) {
        action_arr[i] = 0;
        action_arr_totals[i] = 0;
    }
    int hit_17 = 1;

    int deck[52*8];
    get_deck(deck, deck_num);
    int deck_pos[1] = {0};
    *deck_pos = 0;

    int dealer[32];
    int player[32];

    int result[32][32];
    int result_lens[32];
    int result_len[1];
    int split_count[1];
    int total = 0;

    char* outcomes[] = {"wins", "loses", "ties"};
    for (int i = 0; i < sims; ++i) {
        if (debug == 1 && custom_deck == 0) {
            printf("\n *** press enter for new hand *** \n");
            getchar();
        }

        int banker_results[32];
        int banker_results_len = 0;

        if (deck_pos[0] >= 52*deck_num-pen) {
            get_deck(deck, deck_num);
            deck_pos[0] = 0;
        }

        if (debug == 1) {
            if (custom_deck == 1)
                enter_deck(deck);
            printf("deck = ");
            for (int q = 0; q < 30; ++q)
                printf("%d ", deck[deck_pos[0]+q]);
            printf("...\n");
        }
        dealer[0] = deck[deck_pos[0]];
        dealer[1] = deck[deck_pos[0]+1];

        deck_pos[0] += 2;
        int dealer_len[1];
//        int dealer_sum = go_dealer(dealer, deck, 2, deck_pos, hit_17, dealer_len);
        go_dealer(dealer, deck, 2, deck_pos, hit_17, dealer_len);
        if (debug == 1) {
            printf("\ndealer: ");
            for (int q = 0; q < dealer_len[0]; ++q)
                printf("%d ", dealer[q]);
            printf("(upcard %d)", dealer[0]);
            printf("\n\n");
        }
        int bank_total = bank_total_start;

        for (int j = 0; j < hand_num; ++j) {
            int bet = bj_bets[j];
            player[0] = deck[deck_pos[0]];
            player[1] = deck[deck_pos[0]+1];
            deck_pos[0] += 2;

            reset_results(result_lens, result_len, split_count);
            int player_len = 2;

            if (has_bj(dealer)) {
                for (int ii = 0; ii < player_len; ++ii) {
                    result[*result_len][ii] = player[ii];
                }
                result_lens[*result_len] = player_len;
                result_len[0] += 1;
            }
            else {
                go_player(result, result_lens, result_len, split_count, deck, deck_pos, 3, player, player_len, dealer);
            }
            int player_bj = has_bj(player);
            for (int k = 0; k < *result_len; ++k) {
                int winner = compare_player_dealer(result[k], result_lens[k], dealer, dealer_len[0], 0);
                if (debug == 1) {
                    printf("player %d: ", j+1);
                    if (result[k][0] == -1) {
                        print_arr(result[k]+1, result_lens[k]-1);
                        printf("(player %d surrenders ", j+1);
                    }
                    else {
                        print_arr(result[k], result_lens[k]);
                        printf("(player %d %s ", j+1, outcomes[winner]);
                    }
                }
                bet = bj_bets[j];
                if (player_bj == 1) {
                    double x = bet*bj_pay;
                    bet = x;
                }
                if (result[k][0] == -1)
                    bet = bet / 2;
                if (debug == 1)
                    printf("%d, ", bet);
                if (bank_total < bet)
                    bet = bank_total;
                if (winner == 2)
                    bet = 0;
                bank_total -= bet;
                if (winner == 0) {
                    if (bet != 0) {
                        banker_results[banker_results_len] = -bet;
                        ++banker_results_len;
                    }
                    total -= bet;
                    if (debug == 1) {
                        printf("banker loses %d and has %d left in bank)\n\n", bet, bank_total);
                    }
                }
                else {
                    if (bet != 0) {
                        banker_results[banker_results_len] = bet;
                        ++banker_results_len;
                    }
                    total += bet;
                    if (debug == 1) {
                        printf("banker wins %d and has %d left in bank)\n\n", bet, bank_total);
                    }
                }
            }
        }

        int p = 0;

        for (int q = 0; q < banker_results_len; ++q) {
            int x = banker_results[q];
            int r = 1;
            if (x < 0) {
                x = -x;
                r = -1;
            }
            for (int qq = 0; qq < x; ++qq) {
                action_arr[p] += r;
                ++action_arr_totals[p];
                ++p;
            }
        }
        if (debug == 1) {
            printf("conclusion:\n");
            printf("banker profits by action: ");
            print_arr(banker_results, banker_results_len);
            printf("banker hand result: %d\n", sum(banker_results, banker_results_len));
            printf("banker net result: %d\n", total);
        }
    }
    get_banker_results(action_arr, action_arr_totals, 1, sims, sum(bj_bets, hand_num));
    double total_bet = 0;
    for (int i = 0; i < hand_num; ++i)
        total_bet += bj_bets[i];
    total_bet *= sims;
    double ev1 = total / total_bet;
    return ev1;
}
