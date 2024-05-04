#include "blackjack.hpp"

int main()
{
/*
	Player playerTest{"Player"};
	Card ace(Cards::rank_ace, Cards::suit_club);
	Card ten(Cards::rank_10, Cards::suit_club);
	playerTest.addCard(ace);
	playerTest.addCard(ace);
	playerTest.addCard(ace);
	playerTest.addCard(ten);

	playerTest.printScore();
*/

do
{ 
    Session::playBlackjack();
   
} while (Session::playAgain());

	return 0;

}