#include <iostream>
#include "ticTacToe.h"

int main()
{
	int size, points;
	std::cout << "Podaj wymiary planszy:"; std::cin >> size;
	std::cout << "Podaj punkty do zdobycia:"; std::cin >> points;
	system("CLS");
	tic_tac_toe game(size, points);
	game.game();
}
