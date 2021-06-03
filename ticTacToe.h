#pragma once
#include <iostream>
#include <tuple> 

class tic_tac_toe
{
	int size_; //wymiary tablicy
	char** board_; // dynamicznie alokowana tablica dwuwymiarowa
	int points_to_win_; // ilosc potrzebnych symboli w linii do zwycienstwa
	bool player_tour_; // tura gracza-true tura komputera-false
	
	bool check_single_winner(char player_symbol);
	bool check_winner();
	void draw_board();
	bool draw();
	int min_max_ai(int level, char player_symbol, int depth);
	
	public:
	tic_tac_toe() = delete; // dla pewnosci usuniety zostal domyslny konstruktor
	explicit tic_tac_toe(int size, int points);
	~tic_tac_toe();
	void game();
};

