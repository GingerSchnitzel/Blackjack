#ifndef BLACKJACK_HPP
#define BLACKJACK_HPP

#include <iostream>
#include <array>

namespace Deck
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

	static constexpr std::array allRanks{ rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, rank_10, rank_jack, rank_queen, rank_king };
	static constexpr std::array allSuits{ suit_club, suit_diamond, suit_heart, suit_spade };

}

class Card
{
private:
	const Deck::Rank rank;
	const Deck::Suit suit;

public:
	Card(Deck::Rank rank, Deck::Suit suit)
		: rank{ rank }
		, suit{ suit }
	{

	}

	int32_t value() const
	{
		static constexpr std::array<int32_t, Deck::max_ranks> rankValues{ 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
		return rankValues[rank];
	}

	friend std::ostream& operator<<(std::ostream& out, const Card& card)
	{
		static constexpr std::array<char, Deck::max_ranks> ranks{ 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
		static constexpr std::array<char, Deck::max_suits> suits{ 'C', 'D', 'H', 'S' };

		out << ranks[card.rank] << suits[card.suit];
		return out;
	}

};









































#endif