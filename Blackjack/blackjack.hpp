#ifndef BLACKJACK_HPP
#define BLACKJACK_HPP

#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <random>



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
	
public:

	Player()
		: hand {}
		
	{}

	void addCard(const Card& card)
	{
		hand.push_back(card);
	}

	void printHand()
	{
		for (const auto& card : hand)
		{
			std::cout << card << ' ';
		}
		std::cout << '\n';
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
};









































#endif