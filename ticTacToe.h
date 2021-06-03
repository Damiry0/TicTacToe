#pragma once
#include <iostream>
#include <tuple> 

class tic_tac_toe
{
	int size_;
	char** board_;
	int points_to_win_;
	bool player_tour_;
	
	
	bool check_single_winner(char player_symbol);
	bool check_winner();
	void draw_board();
	bool draw();
	int min_max_ai(int poziom, char gracz, int Glebokosc);

	public:
	
	tic_tac_toe() = delete; // just in case to not allow the user to create a board without specificing arguments
	explicit tic_tac_toe(int size,int points);
	~tic_tac_toe();
	
	void game();
};

