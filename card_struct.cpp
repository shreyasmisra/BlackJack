#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "card_struct.h"
using namespace std;

// Member functions for Card struct

Card::Card() {
	suit = 0;
	rank = 0;
}

Card::Card(int s, int r) {
	suit = s; rank = r;
}

void Card::print() const {
	vector<string> suits(4);
	vector<string> ranks(14);

	suits[0] = "Clubs";
	suits[1] = "Diamonds";
	suits[2] = "Hearts";
	suits[3] = "Spades";

	ranks[1] = "Ace";
	ranks[2] = "2";
	ranks[3] = "3";
	ranks[4] = "4";
	ranks[5] = "5";
	ranks[6] = "6";
	ranks[7] = "7";
	ranks[8] = "8";
	ranks[9] = "9";
	ranks[10] = "10";
	ranks[11] = "Jack";
	ranks[12] = "Queen";
	ranks[13] = "King";

	cout << ranks[rank] << "\t of \t" << suits[suit] << endl;
}

bool Card::isGreater(const Card& c2) const
{
	if (suit > c2.suit) return true;
	if (suit < c2.suit) return false;

	if (rank == 1 && c2.rank != 1) return true;
	if (rank != 1 && c2.rank == 1) return false;

	if (rank > c2.rank) return true;
	if (rank < c2.rank) return false;
	return false;
}

// Member functions for Deck struct.

Deck::Deck(int n)
{
	vector<Card> temp(n);
	cards = temp;
}

Deck::Deck () {
	vector <Card> tmp (52);
	cards = tmp;

	int i = 0;
	for (int suit = 0; suit < 4; suit++) {
		for (int r = 1; r < 14; r++) {
			cards[i].suit = suit;
			cards[i].rank = r;
			i++;
		}
	}
}

void Deck::print() const {
	for (int i = 0; i < cards.size(); i++) {
		cards[i].print();
	}
}

int Deck::find(const Card& c) const
{
	for (int i = 0; i < cards.size(); i++) {
		if (equals(cards[i], c)) return i;
	}
	return -1;
}

void Deck::shuffleDeck()
{
	for (int i = 0; i < cards.size(); i++) {
		int ind = rand() % (cards.size() - i) + i;
		Card tmp = cards[ind];
		cards[ind] = cards[i];
		cards[i] = tmp;
	}
}
Deck Deck::subDeck(int low, int high) const
{
	Deck sub(high - low + 1);

	for (int i = 0; i < sub.cards.size(); i++) {
		sub.cards[i] = cards[low + i];
	}
	return sub;
}

int Deck::countHand() const
{
	int sum = 0;
	for (int i = 0; i < cards.size(); i++) {
		if (cards[i].rank >= 11) {
			sum += 10;
		}
		else if (cards[i].rank == 1) {
			sum += 11;
			if (sum > 21) {
				sum -= 11;
				sum++;
			}
		}
		else {
			sum += cards[i].rank;
		}
	}
	return sum;
}

void Deck::printDealerHand(bool both=true) const
{	
	if (!both) {
		cout << "1: ";
		cards[0].print();
		cout << "2: CARD HIDDEN\n\n";
	}
	else {
		for (int i = 0; i < cards.size(); i++) {
			cout << i + 1 << ": ";
			cards[i].print();
		}
	}
}

void Deck::addCard(const Deck& sub, const Deck& deck) 
{
	int size = cards.size();
	int otherHandSize = sub.cards.size();
	
	int ind = size + otherHandSize;
	
	int randomInd = rand() % (deck.cards.size() - ind) + ind;
	
	Card randomCard = deck.cards[randomInd];

	cards.push_back(randomCard);
}