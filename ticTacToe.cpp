#include "ticTacToe.h"


tic_tac_toe::tic_tac_toe(const int size, const int points)
{
	size_ = size;
	board_ = new char*[size];
	for (auto i = 0; i < size; ++i)
	{
		board_[i] = new char[size];
	}
	points_to_win_ = points;

	for (auto i = 0; i < this->size_; i++)
	{
		for (auto j = 0; j < this->size_; j++)
		{
			board_[i][j] = ' ';
		}
	}
	player_tour_ = true;
}

tic_tac_toe::~tic_tac_toe()
{
	for (auto i = 0; i < size_; ++i)
	{
		delete[] board_[i];
	}
	delete[] board_;
}

void tic_tac_toe::draw_board()
{
	std::cout << "  ";
	for (auto i = 0; i < size_; i++)
	{
		std::cout << " " << i << " ";
	}
	std::cout << '\n';
	for (auto i = 0; i < this->size_; i++)
	{
		std::cout << i << " ";
		for (auto j = 0; j < this->size_; j++)
		{
			std::cout << "|" << board_[i][j] << "|";
		}
		std::cout << '\n';
	}
}

bool tic_tac_toe::draw()
{
	for(auto i=0;i<size_;i++)
	{
		for (auto j=0;j<size_;j++)
		{
			if (board_[i][j] == ' ')return false;
		}
	}
	return true;
}

void tic_tac_toe::game()
{
	while (1)
	{
		if (player_tour_ == true)
		{
			system("CLS");
			draw_board();
			std::cout << "\n Gdzie chcesz postawic X ? \n Wybierz rzad:";
			int row;
			std::cin >> row;
			while (row >= size_)
			{
				std::cout << " Wprowadz wartosc ponownie:";
				std::cin >> row;
			}
			std::cout << " Wybierz kolumne:";
			int column;
			std::cin >> column;
			while (column >= size_)
			{
				std::cout << " Wprowadz wartosc ponownie:";
				std::cin >> column;
			}
			board_[row][column] = 'X';
			system("CLS");
			draw_board();
			player_tour_ = false;
			if (check_winner())break;
		}
		else
		{
			system("CLS");
			min_max_ai(0, 'O', 3);
			draw_board();
			player_tour_ = true;
			if(check_winner())break;
		}
	}
}


int tic_tac_toe::min_max_ai(int poziom, char gracz, int Glebokosc)
{
	int licz = 0, wiersze=0, kolumny=0;
	for (int i = 0; i < size_; ++i)
	{
		for (int j = 0; j < size_; ++j)
		{
			if (board_[i][j] == ' ')
			{
				board_[i][j] = gracz;
				kolumny = j;
				wiersze = i;
				licz++;
				bool test = check_single_winner(gracz);
				board_[i][j] = ' ';
				if (test)
				{
					if (!poziom)
						board_[i][j] = gracz;
					return gracz == 'X' ? -1 : 1;
				}
			}
		}
	}
	//czy jest remis
	if (licz == 1)
	{
		if (!poziom)
			board_[wiersze][kolumny] = gracz;
		return 0;
	}
	// wybór najbardziej korzystnego ruchu
	int V, VMax;
	VMax = (gracz == 'X' ? size_ - 1 : -size_ + 1);
	for (int i = 0; i < Glebokosc; ++i)
	{
		for (int j = 0; j < Glebokosc; ++j)
		{
			if (board_[i][j] == ' ')
			{
				board_[i][j] = gracz;
				V = min_max_ai(poziom + 1, (gracz == 'X' ? 'O' : 'X'), Glebokosc);
				board_[i][j] = ' ';
				if (((gracz == 'X') && (V < VMax)) || ((gracz == 'O') && V > VMax))
				{
					wiersze = i;
					kolumny = j;
					VMax = V;
				}
			}
		}
	}
	if (!poziom)
		board_[wiersze][kolumny] = gracz;
	return VMax;


	
	/*if (check_single_winner('X')) return 1;
	if (check_single_winner('O')) return -1;
	if (draw()) return 0;
	if (depth == 3) return 0;

	int score = player == AI ? INT_MIN : INT_MAX;
	
	for (auto i = 0; i < this->size_; i++)
	{
		for (auto j = 0; j < this->size_; j++)
		{
			if(board_[i][j]==' ')
			{
				tic_tac_toe tmp = *this;
			}
		}
	}
	return mx;*/
	
	/*if(maximizingPlayer)
	{
		auto best_val = -1000;
		for(auto i=0;i<2;i++)
		{
			auto value = min_max_ai(node, depth + 1, alpha, beta, false);
			best_val = std::max(best_val, value);
			alpha = std::max(alpha, best_val);

			if (beta <= alpha) break;
		}
		return best_val;
	}
	auto best_val = 1000;
	for (auto i = 0; i < 2; i++)
	{
		auto value = min_max_ai(2*node+i, depth + 1, alpha, beta, true);
		best_val = std::min(best_val, value);
		beta = std::min(beta, best_val);
		if (beta <= alpha) break;
	}
	return best_val;*/
}




bool tic_tac_toe::check_single_winner(char player_symbol)
{
	auto playerpoints = 0;

	// row
	for (auto i = 0; i < this->size_; i++)
	{
		for (auto j = 0; j < this->size_; j++)
		{
			if (board_[i][j] == player_symbol) playerpoints++;
		}
		if (playerpoints == points_to_win_)
		{
		
			return true;
		}
		playerpoints = 0;
	}

	//column
	for (auto i = 0; i < this->size_; i++)
	{
		for (auto j = 0; j < this->size_; j++)
		{
			if (board_[j][i] == player_symbol) playerpoints++;
		}
		if (playerpoints == points_to_win_)
		{
			
			return true;
		}
		playerpoints = 0;
	}

	//main diagonals
	for (auto i = 0; i < this->size_ - 1; i++)
	{
		if (board_[i][i] == board_[i + 1][i + 1] && board_[i + 1][i + 1] == player_symbol)
		{
			playerpoints++;
			if (playerpoints == (points_to_win_ - 1))
			{
				
				return true;
			}

		}
		else { playerpoints = 0; }
	}
	for (auto i = 0; i < this->size_ - 1; ++i)
	{
		if (board_[i][this->size_ - 1 - i] == board_[i + 1][this->size_ - 1 - (i + 1)] && board_[i + 1][this->size_ - 1 - (i + 1)] == player_symbol)
		{
			playerpoints++;
			if (playerpoints == points_to_win_ - 1)
			{
				
				return true;
			}
		}
		else
			playerpoints = 0;
	}
	// rest of diagonals
	
	if (points_to_win_ < size_)
	{

		for (auto i = 1; i <= size_ - points_to_win_; i++)
		{
			for (auto j = 0; j < size_ - i - 1; ++j)
			{
				if (board_[i + j][j] == board_[i + j + 1][j + 1] && board_[i + j + 1][j + 1] == player_symbol)
				{
					playerpoints++;
					if (playerpoints == points_to_win_ - 1)
					{
					
						return true;
					}
				}
				else
					playerpoints = 0;
			}
		}
		
		for (auto i = 1; i <= size_ - points_to_win_; i++)
		{
			for (auto j = 0; j < size_ - i - 1; ++j)
			{
				if (board_[j][j + i] == board_[j + 1][j + 1 + i] && board_[j + 1][i + j + 1] == player_symbol)
				{
					playerpoints++;
					if (playerpoints == points_to_win_ - 1)
					{
					
						return true;
					}
				}
				else
					playerpoints = 0;
			}
		}

		for (auto i = 1; i < size_ - 1; ++i)
		{
			for (auto j = 0; j <= size_ - points_to_win_ - i; ++j)
			{
				if (board_[size_ - (i + j) - 1][size_ - (size_ - j)] == board_[size_ - (i + j) - 1 - 1][size_ - (size_ - j) + 1] && board_[size_ - (i + j) - 1 - 1][size_ - (size_ - j) + 1] == player_symbol)
				{
					playerpoints++;
					if (playerpoints == points_to_win_ - 1)
					{
				
						return true;
					}
				}
				else
					playerpoints = 0;
			}
		}

		for (auto i = 1; i <= size_ - points_to_win_; ++i)
		{
			for (auto j = size_ - i - 1; j >= 1; --j)
			{
				if (board_[i + j][size_ - 1 - j] == board_[i + j - 1][size_ - j] && board_[i + j - 1][size_ - j] == player_symbol)
				{
					playerpoints++;
					if (playerpoints == points_to_win_ - 1)
					{
				
						return true;
					}
				}
				else
					playerpoints = 0;
			}
		}
	}
	

	return false;
	}





	bool tic_tac_toe::check_winner()
	{
		if (check_single_winner('X'))
		{
			std::cout << "Wygral gracz 'X'";
			return true;
		}
		else if (check_single_winner('O'))
		{
			std::cout << "Wygral gracz 'O'";
			return true;
		}
		return false;
	}
