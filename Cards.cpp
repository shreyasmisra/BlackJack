#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <Windows.h>
#include "card_struct.h"
using namespace std;

const int MAX_HITS = 5;
const int DEALER_MIN_SUM = 17;
const string PLAYER_NAME = "Player";
const string DEALER_NAME = "Dealer";
const double mSecs = 3000.0;

bool equals(const Card& c1, const Card& c2) {
    return (c1.rank == c2.rank && c1.suit == c2.suit);
}

Deck merge(const Deck& d1, const Deck& d2)
{
    Deck result(d1.cards.size() + d2.cards.size());
    int i = 0;
    int j = 0;
    Card winner;

    for (int k = 0; k < result.cards.size(); k++) {
      
        if (i==d1.cards.size()) {
            winner = d2.cards[j];
            result.cards[k] = winner;
            j++;
        }
        else if (j==d2.cards.size()) {
            winner = d1.cards[i];
            result.cards[k] = winner;
            i++;
        }

        else if (d1.cards[i].isGreater(d2.cards[j])) {
            winner = d2.cards[j];
            result.cards[k] = winner;
            j++;
        }
        else if (d2.cards[j].isGreater(d1.cards[i])) {
            winner = d1.cards[i];
            result.cards[k] = winner;
            i++;
        }
    }
    return result;
}

Deck mergeSort(const Deck& deck)
{
    if (deck.cards.size() == 0 || deck.cards.size() == 1) return deck;

    int mid = deck.cards.size() / 2;
    int size = deck.cards.size();
    
    Deck sub1 = deck.subDeck(0, mid-1);
    Deck sub2 = deck.subDeck(mid, size-1);
    
    sub1 = mergeSort(sub1);
    sub2 = mergeSort(sub2);

    Deck result = merge(sub1, sub2);
    return result;
}

int checkWinner(int x, int d) {
    /*
    Checks the total counts of the dealer and the player to figure out who won.
    To improve - add more logic.
    */
    
    if (x == 21 && d != 21) {
        cout << "You got a BlackJack! You Won!\n\n";
        return 0;
    }
    else if (x > 21) {
        cout << "You went over 21. You lost.\n\n";
        return 0;
    }
    else if (x > d && x < 21) {
        cout << "You beat the dealer. You won!\n\n";
        return 0;
    }
    else if (d > x && d < 21) {
        cout << "The dealer beat you. You lost. Try again.\n\n";
        return 0;
    }
    else if (d > 21 && x < 21) {
        cout << "The dealer bust. You won!\n\n";
        return 0;
    }
    else if (d == x && x<=21) {
        cout << "Both have BlackJacks! It is a tie.\n\n";
        return 0;
    }
    else {
        cout << "The dealer won. You lost.\n\n";
        return 0;
    }
    return -1;
}

void askUser() {
    /*
    User input query.
    */

    cout << "What would you like to do?\n";
    cout << "Stand: \t0" << "\n";
    cout << "Hit: \t1" << "\n";
}

void showHand(const Deck& subDeck, string name = PLAYER_NAME) {
    /*
    Shows the complete hand of either the dealer or the player.
    */

    if (name == DEALER_NAME) {
        cout << "Dealer's hand ---------\n\n";
        subDeck.printDealerHand(true);
        int sum = subDeck.countHand();
        cout << "\nTotal dealer sum = \t" << sum << "\n\n";
    }
    else {
        cout << "Player's hand is------\n\n";
        subDeck.print();
        int sum = subDeck.countHand();
        cout << "\nTotal player sum = \t" << sum << "\n\n";
    }
}

void playBlackJack(const Deck& deck) {
    /*
    To improve -
        1) Add doubling down.
        2) Keep a check on the money.
        3) Make a continuous deck, instead of re-shuffling after each game.
    */

    int playerIn, player_sum, dealer_sum;
    bool gameOver = false;
    int numHits = 0;

    Deck player = deck.subDeck(0, 1); 
    Deck dealer = deck.subDeck(2, 3); 

    showHand(player);

    bool both = false;
    cout << "Dealer's hand ---------\n\n";
    dealer.printDealerHand(both);
    dealer_sum = dealer.countHand();

    while (gameOver == false) {
        askUser();
        cin >> playerIn;
        if (playerIn == 0) {
            cout << "\nYou have chosen to stand.---------------\n\n";
            showHand(player);
            player_sum = player.countHand();
            gameOver = true;
        }
        if (playerIn == 1) {
            if (numHits > MAX_HITS) {
                cout << "\nYou cannot get any more cards.-------------------\n\n";
                showHand(player);
                gameOver = true;
                break;
            }
            player.addCard(dealer, deck);
            player_sum = player.countHand();
            showHand(player);
            if (player_sum > 21) {
                cout << "\nYou went over 21.-----------------\n\n";
                gameOver = true;
                break;
            }
            if (player_sum == 21) {
                cout << "\nYou got a BlackJack!\n\n";
                gameOver = true;
                break;
            }
            cout << "\nDealer's hand ---------\n\n";
            dealer.printDealerHand(both);
        }
    }

    showHand(dealer, DEALER_NAME);

    while (dealer_sum < DEALER_MIN_SUM) {
        dealer.addCard(player, deck);
        dealer_sum = dealer.countHand();
        showHand(dealer, DEALER_NAME);
    }
    cout << "Dealer cannot take anymore cards.\n\n";

    checkWinner(player_sum, dealer_sum);
}

int main()
{
    srand(time(NULL));

    Deck deck;
    int numTimes = 2;
    
    for (int i = 0; i < numTimes; i++) {
        cout << "\n\n------------------- NEW GAME-------------------\n\n";
        deck.shuffleDeck();
        playBlackJack(deck);
        Sleep(mSecs);
    }

    deck = mergeSort(deck);
    
    return 0;
}
