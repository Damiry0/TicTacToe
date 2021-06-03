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
	end_game_ = false;
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
	while (end_game_ == false)
	{
		if (player_tour_ == true)
		{
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
			check_winner();
		}
		else
		{
			system("CLS");
			auto [row, column] = ai();
			board_[row][column] = 'O';
			draw_board();
			player_tour_ = true;
			check_winner();
		}
	}
}


int tic_tac_toe::min_max_ai(char node,int depth,int alpha,int beta,bool maximizingPlayer)
{
	
	
	if (depth == 3) return 0;
	if (check_single_winner('X')) return 1;
	if (check_single_winner('O')) return -1;
	if (draw()) return 0;

	node = (node == 'X') ? 'O' : 'X';
	int mx = (node == 'X') ? alpha : beta;
	for (auto i = 0; i < this->size_; i++)
	{
		for (auto j = 0; j < this->size_; j++)
		{
			if(board_[i][j]==' ')
			{
				board_[i][j] = node;
				auto m = min_max_ai(node, depth + 1, alpha, beta, !maximizingPlayer);
				board_[i][j] = ' ';
				if ((node == 'O') && (m < mx) || (node == 'X') && (m > mx)) mx = m;
			}
		}
	}
	return mx;
	
	if(maximizingPlayer)
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
	return best_val;
}

std::tuple<int,int> tic_tac_toe::ai()
{
	int row=0, column=0;
	int alpha = 22222;
	int beta = -22222;
	int mx = beta;
	int m = alpha;
	for (auto i = 0; i < this->size_; i++)
	{
		for (auto j = 0; j < this->size_; j++)
		{
			if(board_[i][j]==' ')
			{
				board_[i][j] = 'O';
				m = min_max_ai('O',0,alpha,beta,true);
				board_[i][j] = ' ';
				if(m>mx)
				{
					mx = m;
					row = i;
					column = j;
				}
				if (m == 1) return { row,column };
			}
		}
	}
	return { row,column };
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
			this->end_game_ = true;
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
			this->end_game_ = true;
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
				this->end_game_ = true;
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
				this->end_game_ = true;
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
						this->end_game_ = true;
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
						this->end_game_ = true;
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
						this->end_game_ = true;
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
						this->end_game_ = true;
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

	void tic_tac_toe::check_winner()
	{
		if (check_single_winner('X')) std::cout << "Gracz wygral";
		else if (check_single_winner('O')) std::cout << "Bot wygral";
	}
