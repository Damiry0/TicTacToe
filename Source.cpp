#include <iostream>
#include "ticTacToe.h"


/// <summary>
/// Wymagane uzycie C++17 ze wzgledu na uzycie tupli
/// </summary>
/// <returns></returns>
int main()
{
	int size, points;
	std::cout << "Podaj wymiary planszy:"; std::cin >> size;
	std::cout << "Podaj punkty do zdobycia:"; std::cin >> points;
	system("CLS");
	tic_tac_toe game(size, points);
	game.game();
}
