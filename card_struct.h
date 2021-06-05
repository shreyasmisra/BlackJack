#include <vector>
#include <iostream>

using namespace std;

struct Card;
struct Deck;

bool equals(const Card& c1, const Card& c2);
Deck merge(const Deck& d1, const Deck& d2);
Deck mergeSort(const Deck& deck);

struct Card {
	int suit, rank;

	Card();
	Card(int s, int r);
	void print() const;
	bool isGreater(const Card& c2) const;
};

struct Deck {
	vector<Card> cards;

	Deck(int n);
	Deck();

	void print() const;
	int find(const Card& c) const;
	void shuffleDeck();
	Deck subDeck(int, int) const;
	int countHand() const;
	void printDealerHand(bool) const;
	void addCard(const Deck& sub, const Deck& deck);
};