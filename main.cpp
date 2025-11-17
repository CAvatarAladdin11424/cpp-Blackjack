#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>

using namespace std;

struct defineCard
{
	string suit;
	string face;
	int pointsValue;
	int cardStatus;
} Deck[53];

struct Player {
	int points;
	bool bust = 0;
	Player() = default;
	Player(int pts, bool bust) : points(pts), bust(bust) {}
};

struct Dealer {
	int points;
	Dealer() = default;
	Dealer(int pts) : points(pts) {}
};

void deal(Player& player, int& deckOrder) {
	//cout << deckOrder << endl;
	player.points += Deck[deckOrder].pointsValue;
	cout << "You receive a " << Deck[deckOrder].face << " of " << Deck[deckOrder].suit;
	deckOrder++;
	//cout << deckOrder << endl;
	player.points += Deck[deckOrder].pointsValue;
	cout << " and " << Deck[deckOrder].face << " of " << Deck[deckOrder].suit << "!" << endl;
	deckOrder++;
	cout << "Current points: " << player.points << endl;
}

void deal(Dealer& dealer, int& deckOrder) {
	dealer.points += Deck[deckOrder].pointsValue;
	cout << "The dealer recieves a " << Deck[deckOrder].face << " of " << Deck[deckOrder].suit << " and a ";
	deckOrder++;
	cout << Deck[deckOrder].face << " of " << Deck[deckOrder].suit << "!\n";
	dealer.points += Deck[deckOrder].pointsValue;
	cout << "Current points: " << dealer.points << endl;
	deckOrder++;
}

bool hit(Player& player, int& deckOrder) {
	cout << "\nYou tap the table..." << endl;
	player.points += Deck[deckOrder].pointsValue;
	cout << "You receive a " << Deck[deckOrder].face << " of " << Deck[deckOrder].suit << "!" << endl;
	cout << "Player points: " << player.points << endl << endl;
	deckOrder++;
	if (player.points > 21) {
		cout << "BUST!\n";
		return false;
	}
	return true;
}

bool hit(Dealer& dealer, int& deckOrder) {
	dealer.points += Deck[deckOrder].pointsValue;
	cout << "The dealer receives a " << Deck[deckOrder].face << " of " << Deck[deckOrder].suit << "!" << endl;
	deckOrder++;
	cout << "Dealer points: " << dealer.points << endl;
	if (dealer.points < 17)
		return false;
	return true;
}

int main() {
	srand(time(0));
	int New_Suit = 0;
	string faces[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	string suits[4] = { "Diamonds", "Clubs", "Hearts", "Spades" };
	string Status[3] = { "In Play", "In Deck", "Discard Pile" };
	int CardValue[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
	
	// Creates the cards and sets their value
	for (int x = 0; x < 52; x++) {
		Deck[x].face = faces[x % 13];
		Deck[x].suit = suits[x % 4];
		Deck[x].pointsValue = CardValue[x % 13];
		Deck[x].cardStatus = 1;
		//cout << "Face: " << Deck[x].face << "\tSuit: " << Deck[x].suit << "\tPtsVal: " << Deck[x].pointsValue << "\tCardStat: " << Deck[x].cardStatus << "\n";
		// Changes suits once the entire suit is covered.
		if (x + 1 % 13 == 0)
			New_Suit++;
	}

	// Shuffling cards
	for (int x = 0; x < 600; x++)
	{
		int a = rand() % 52;
		int b = rand() % 52;

		Deck[52].face = Deck[a].face;
		Deck[52].suit = Deck[a].suit;
		Deck[52].pointsValue = Deck[a].pointsValue;
		Deck[52].cardStatus = Deck[a].cardStatus;

		Deck[a].face = Deck[b].face;
		Deck[a].suit = Deck[b].suit;
		Deck[a].pointsValue = Deck[b].pointsValue;
		Deck[a].cardStatus = Deck[b].cardStatus;

		Deck[b].face = Deck[52].face;
		Deck[b].suit = Deck[52].suit;
		Deck[b].pointsValue = Deck[52].pointsValue;
		Deck[b].cardStatus = Deck[52].cardStatus;
	}

	cout << "Shuffled deck of cards.." << endl << endl;

	cout << endl << endl;
	
	// game start
	cout << "Let's play Blackjack!" << endl << endl;

	int playerCount = 1, cardOrder = 0;
	bool turn = true, dealerTurn = false, cont = true, flag = false;
	Player p1;
	Dealer dealer;
	char answer = ' ';


	while (cont) {
		p1.points = 0;
		dealer.points = 0;
		answer = ' ';

		// If deck is nearly empty, reshuffle all of the cards.
		if (cardOrder + 8 >= 52) {
			for (int x = 0; x < 600; x++)
			{
				int a = rand() % 52;
				int b = rand() % 52;

				Deck[52].face = Deck[a].face;
				Deck[52].suit = Deck[a].suit;
				Deck[52].pointsValue = Deck[a].pointsValue;
				Deck[52].cardStatus = Deck[a].cardStatus;

				Deck[a].face = Deck[b].face;
				Deck[a].suit = Deck[b].suit;
				Deck[a].pointsValue = Deck[b].pointsValue;
				Deck[a].cardStatus = Deck[b].cardStatus;

				Deck[b].face = Deck[52].face;
				Deck[b].suit = Deck[52].suit;
				Deck[b].pointsValue = Deck[52].pointsValue;
				Deck[b].cardStatus = Deck[52].cardStatus;
			}
			cardOrder = 0;
		}
		

		// dealing
		cout << "Dealing cards\n" << endl;
		deal(p1, cardOrder);

		// Player turn
		while (turn) {
			cout << "Do you want another card? [Y/N]" << endl;
			answer = _getch();
			if (answer == 'Y' || answer == 'y') {
				if (!hit(p1, cardOrder)) { // If player goes over 21, turn is over
					turn = false;
				}
			}
			else if (answer == 'N' || answer == 'n') // If player wants to stay, turn is over
				turn = false;
			else {
				cout << "Invalid answer, try again." << endl;
			}
		}
		turn = true;

		cout << "\nDealer's turn! Press any key to continue...\n\n";
		_getch();

		// Dealer turn
		dealerTurn = true;
		deal(dealer, cardOrder);

		cout << "\nPress any key to continue...\n";
		_getch();

		while (dealerTurn) {
			if (dealer.points < 17) { // Dealer must keep playing until they reach over 17
				cout << "The dealer takes a card...\n";
				hit(dealer, cardOrder);
			}
			else if (dealer.points >= 17 && dealer.points <= 21) { // When dealer is over 17, their turn is over
				dealerTurn = false;
				cout << "The dealer stops...\n";
			}
			else {
				cout << "THE DEALER BUSTS!" << endl;
				dealerTurn = false;
			}
			cout << "\nPress any key to continue...\n\n";
			_getch();
			
		}

		if (p1.points > 21 && dealer.points > 21)
			cout << "TIE!" << endl;
		else if (p1.points > 21 && dealer.points <= 21)
			cout << "Dealer wins!" << endl;
		else if (p1.points <= 21 && dealer.points > 21)
			cout << "Player wins!" << endl;
		else {
			if (p1.points < dealer.points)
				cout << "Dealer wins!" << endl;
			else if (p1.points > dealer.points)
				cout << "Player wins!" << endl;
			else
				cout << "TIE!" << endl;
		}

		cout << "\nPress any key to continue..." << endl;
		_getch();

		cout << "\nPlay another game? [Y/N]\n"; // Play another game?
		while (true) {
			answer = _getch();
			if (answer == 'y' || answer == 'Y') {
				cont = true;
				break;
			}
			else if (answer == 'n' || answer == 'N') {
				cont = false;
				break;
			}
			else {
				cout << "Invalid answer. Try again. Play another game?\n";
			}
		}
	}
}