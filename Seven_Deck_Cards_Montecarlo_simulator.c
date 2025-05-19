#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

//defining constants 
#define DECK_SIZE 52
#define HAND_SIZE 7
#define SIM_COUNT 1300000
//defining suits as a enum data  type
typedef enum {CLUBS, DIAMONDS, HEARTS, SPADES} suits;

//cards struct
typedef struct{
     suits suits;
    short value;
} cards;

//initializing deck
void initialize_deck(cards deck[]){
    int index = 0;
    int s;
    int v;
    for(s = 0; s < 4; s++){ //outer loop for suits
        for( v = 2; v <= 14; v++){  //inner loop for values
            deck[index].suits = (suits)s;
            deck[index].value = v;
            index++;

        }
    }
}

//shuffling function using fisher yates algorithm
void shuffle(cards deck[]){
    int i;
    int j;
    for(i = DECK_SIZE - 1; i > 0; i--){
        int j = rand() % (i + 1);
        cards temp = deck[i];   //swap function
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

//function to deal hand
void deal_hand(cards deck[], cards hand[]){
    int i = 0;
    for(i = 0; i <HAND_SIZE; i++){
        hand[i] = deck[i];
    }
}

//analyze hand-logic function 
void analyze_hand(cards hand[], int *no_pair, int *one_pair, int *two_pair, int *three_of_a_kind, int *full_house, int *four_of_a_kind){
    int i = 0;

    int freq[15] = {0}; //intializing values
    for( int i = 0; i <HAND_SIZE; i ++){    //counting freq of values
        freq[hand[i].value]++;
    }
    int pairs = 0, threes = 0, fours = 0;

    for(int i = 2; i <= 14; i++){
        if(freq[i]== 2) pairs++;
        else if (freq[i] == 3) threes++;
        else if (freq[i] == 4) fours++;
    }
    //making hand into a category
    if ( fours == 1) (*four_of_a_kind)++;
    else if (threes == 1 && pairs == 1) (*full_house)++;
    else if ( threes == 1 ) (*three_of_a_kind)++;
    else if ( pairs == 2 ) ( *two_pair)++;
    else if ( pairs == 1) ( *one_pair)++;
    else (*no_pair)++;
}

int main(){
    //declaring all the variable
    cards deck[DECK_SIZE];
    cards hand[HAND_SIZE];

    int no_pair = 0, one_pair = 0, two_pair = 0, three_of_a_kind = 0, full_house = 0, four_of_a_kind = 0;

    //seeding the rand()
    srand(time(NULL));

    for(int i = 0; i < SIM_COUNT; i++){
        initialize_deck(deck);
        shuffle(deck);
        deal_hand(deck, hand);
        analyze_hand(hand, &no_pair, &one_pair, &two_pair, &three_of_a_kind, &full_house, &four_of_a_kind);
    }

    //printing the stats
    printf(" out of all these %d simulations: \n", SIM_COUNT);
    printf(" no pair: %.4f\n", (float)no_pair / SIM_COUNT);
    printf(" one pair: %.4f\n", (float)one_pair / SIM_COUNT);
    printf(" two pair: %.4f\n",(float)two_pair / SIM_COUNT);
    printf(" three of a kind: %.4f\n", (float)three_of_a_kind / SIM_COUNT);
    printf(" full house: %.4f\n", (float)full_house / SIM_COUNT);
    printf(" four of kind : %.4f\n", (float)four_of_a_kind / SIM_COUNT);

    return 0;
}

