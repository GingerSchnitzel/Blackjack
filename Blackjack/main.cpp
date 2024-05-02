#include "blackjack.hpp"

int main()
{
    Deck deck{};
    std::cout << deck.dealCard() << ' ' << deck.dealCard() << ' ' << deck.dealCard() << '\n';

    deck.shuffle();
    std::cout << deck.dealCard() << ' ' << deck.dealCard() << ' ' << deck.dealCard() << '\n';

    Player player;
    player.addCard(deck.dealCard());
    player.addCard(deck.dealCard());


    player.printHand();
    int32_t score = player.calculateScore();
    std::cout << score << '\n';
   
   
	return 0;

}