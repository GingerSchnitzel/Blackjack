#include "blackjack.hpp"

int main()
{

	Card card{ Deck::rank_king, Deck::suit_diamond };
	std::cout << card;

    // Print one card
    Card card1{ Deck::rank_5, Deck::suit_heart };
    std::cout << card1 << '\n';

    // Print all cards
    for (auto suit : Deck::allSuits)
        for (auto rank : Deck::allRanks)
            std::cout << Card{ rank, suit } << ' ';
    std::cout << '\n';


	return 0;

}