#include "blackjack.hpp"

int main()
{
do
{ 
    Session::playBlackjack();
   
} while (Session::playAgain());

	return 0;

}