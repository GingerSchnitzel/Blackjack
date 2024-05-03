#ifndef BLACKJACK_HPP
#define BLACKJACK_HPP

#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <random>
#include <string>



namespace Cards
{

	enum Rank
	{
		rank_ace,
		rank_2,
		rank_3,
		rank_4,
		rank_5,
		rank_6,
		rank_7,
		rank_8,
		rank_9,
		rank_10,
		rank_jack,
		rank_queen,
		rank_king,

		max_ranks
	};


	enum Suit
	{
		suit_club,
		suit_diamond,
		suit_heart,
		suit_spade,

		max_suits
	};

	static constexpr std::array<Cards::Rank, Cards::max_ranks> allRanks{ rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, rank_10, rank_jack, rank_queen, rank_king };
	static constexpr std::array<Cards::Suit, Cards::max_suits> allSuits{ suit_club, suit_diamond, suit_heart, suit_spade };
	static constexpr std::array<int32_t, Cards::max_ranks> rankValues{ 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };

}

namespace Settings
{
	constexpr int32_t bust{ 21 };
	constexpr int32_t dealerStop{ 17 };
}


class Card;
int32_t rankValue(Cards::Rank rank);
std::vector<Card> makeDeck();

class Card
{
private:
	// need to be not-const in order to be able to be swapped around
	Cards::Rank rank;
	Cards::Suit suit;
	int32_t value;

public:
	Card(Cards::Rank rank, Cards::Suit suit)
		: rank{ rank }
		, suit{ suit }
		, value{ rankValue(rank) }
	{

	}

	Cards::Rank getRank() const
	{
		return rank;
	}

	Cards::Suit getSuit() const
	{
		return suit;
	}

	int32_t getValue() const
	{
		return value;
	}


	friend std::ostream& operator<<(std::ostream& out, const Card& card)
	{
		static constexpr std::array<char, Cards::max_ranks> ranks{ 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
		static constexpr std::array<char, Cards::max_suits> suits{ 'C', 'D', 'H', 'S' };

		out << ranks[card.rank] << suits[card.suit];
		return out;
	}

};

class Deck
{
private:
	std::vector<Card> cards;


public:
	Deck()
		: cards{ makeDeck() }
	{}

	//before calling this function it should be checked that the deck still has cards
	Card dealCard()
	{

		Card dealtCard{ cards.back() };
		cards.pop_back();
		return dealtCard;


	}

	void shuffle()
	{
		static std::random_device rd{};
		static std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
		static std::mt19937 engine(ss);
		std::shuffle(cards.begin(), cards.end(), engine);
	}



};


int32_t rankValue(Cards::Rank rank)
{
	return Cards::rankValues[rank];


}

std::vector<Card> makeDeck()
{
	std::vector<Card> cards{};
	for (const auto& i : Cards::allSuits)
	{
		for (const auto& j : Cards::allRanks)
		{
			cards.push_back(Card(j, i));
		}

	}
	return cards;
}




class Player
{
private:
	std::vector<Card> hand;
	std::string name;

public:

	Player(const std::string& name)
		: hand{}
		, name{ name }

	{}

	const std::string& getName () const
	{
		return name;
	}

	void addCard(const Card& card)
	{
		hand.push_back(card);
	}

	void printHand()
	{
		std::cout << name << "'s hand: ";

		for (const auto& card : hand)
		{
			std::cout << card << ' ';
		}
		std::cout << '\n';
	}

	void printFirstDealerHand()
	{
		std::cout << name << "'s hand: ";
		std::cout << hand[0] << ' ';
		std::cout << '?' << '\n';
	}

	int32_t calculateScore()
	{

		int32_t score{};
		for (const auto& card : hand)
		{
			score += card.getValue();
		}
		return score;
	}

	void printScore()
	{
		std::cout << name << "'s score is: " << calculateScore() << '\n';

	}

	bool goneBust()
	{
		if (calculateScore() > Settings::bust)
		{
			return true;
		}
		return false;
	}

};

namespace Settings
{

	bool dealerTurn(Deck& deck, Player& dealer)
	{
		dealer.printHand();
		dealer.printScore();
		while (dealer.calculateScore() < dealerStop)
		{
			Card card{ deck.dealCard() };
			dealer.addCard(card);
			std::cout << "The dealer flips a " << card << ".  They now have: " << dealer.calculateScore() << '\n';
		}

		if (dealer.goneBust())
		{
			std::cout << "The dealer went bust!\n";
			return true;
		}

		return false;
	}

}


namespace Session
{
	bool hitOrStand()
	{
		std::cout << "(H)it or (S)tand? \n";
		while (true)
		{
			char answer{};
			std::cin >> answer;

			if (std::cin.fail())
			{
				std::cin.clear();
				std::cout << "That wasn't a valid input. Please try again.\n";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			if (answer != 'H' && answer != 'S'  && answer != 'h' && answer != 's')
			{
				std::cout << "That wasn't a valid input. Please try again.\n";
				continue;
			}

			if (answer == 'H' || answer == 'h')
			{
				return true;
			}

			if (answer == 'S' || answer == 's')
			{
				return false;
			}

		}
	}
	bool playAgain()
	{
		std::cout << "Would you like to play again?";
		std::string answer;

		while (true)
		{
			std::cout << " y/n? ";

			std::getline(std::cin, answer);

			if (answer.length() != 1)
			{
				continue;
			}

			switch (answer[0])
			{
			case 'y':
			case'Y':
				std::cout << '\n';
				return true;

			case 'N':
			case'n':

				std::cout << "Thank you for playing! \n";
				return false;
			}
		}
	}

	void playBlackjack()
	{
		Deck deck{};
		deck.shuffle();

		Player dealer{ "Dealer" };
		Player player{ "Player" };

		dealer.addCard(deck.dealCard());
		player.addCard(deck.dealCard());

		player.addCard(deck.dealCard());
		dealer.addCard(deck.dealCard());

		dealer.printFirstDealerHand();
		player.printHand();
		player.printScore();

		while (player.calculateScore() < Settings::bust)
		{
			if (hitOrStand())
			{
				player.addCard(deck.dealCard());
				player.printHand();
				player.printScore();

			}
			else
			{
				break;
			}
		}

		if (player.goneBust())
		{
			std::cout << player.getName() << " went bust! \n";
			std::cout << "Dealer wins!\n";
			return;
		}

		if (Settings::dealerTurn(deck, dealer))
		{
			std::cout << player.getName() << " wins! \n";
			return;
		}

		if (dealer.calculateScore() > player.calculateScore())
		{
			std::cout << "Dealer wins!\n";
			return;
		}
		else
		{
			std::cout << player.getName() << " wins! \n";
			return;
		}


	}
}









































#endif