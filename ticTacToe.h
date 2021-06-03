#pragma once
#include <iostream>
#include <tuple> 

class tic_tac_toe
{
	int size_;
	char** board_;
	int points_to_win_;
	bool player_tour_;
	bool end_game_;
	
	bool check_single_winner(char player_symbol);
	void check_winner();
	void draw_board();
	bool draw();
	int min_max_ai(char node, int depth, int alpha, int beta, bool maximizingPlayer);
	std::tuple<int, int> ai();

	public:
	
	tic_tac_toe() = delete; // just in case to not allow the user to create a board without specificing arguments
	explicit tic_tac_toe(int size,int points);
	~tic_tac_toe();
	
	void game();
};

