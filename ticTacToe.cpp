#include "ticTacToe.h"

/// <summary>
/// Konstruktor parametryczny dla kolka i krzyzyk
/// </summary>
/// <param name="size">Wymiary planszy</param> 
/// <param name="points">Wymagane punkty do zwycienstwa</param> 
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
/// <summary>
/// Destruktor kolka i krzyzyk, zwalnia zaalokowana pamiec tablicy
/// </summary>
tic_tac_toe::~tic_tac_toe()
{
	for (auto i = 0; i < size_; ++i)
	{
		delete[] board_[i];
	}
	delete[] board_;
}
/// <summary>
/// Metoda rysujaca tablice 
/// </summary>
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
/// <summary>
/// Metoda sprawdzajaca remis
/// </summary>
/// <returns></returns>
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
/// <summary>
/// Metoda uruchumiaja gre
/// </summary>
void tic_tac_toe::game()
{
	while (check_full_board())
	{
		if (player_tour_ == true)
		{
			system("CLS");
			draw_board();
			int column=0,row=0;
			do
			{
				std::cout << "\n Gdzie chcesz postawic X ? \n Wybierz rzad:";
				std::cin >> row;
				std::cout << " Wybierz kolumne:";
				std::cin >> column;
			}
			while (row >= size_ || column >= size_ || board_[row][column] != ' ');
			board_[row][column] = 'X';
			system("CLS");
			draw_board();
			player_tour_ = false;
			if (check_winner())break;
		}
		else
		{
			system("CLS");
			min_max_ai(0, 'O',3);
			draw_board();
			player_tour_ = true;
			if(check_winner())break;
		}
	}
}


/// <summary>
/// Algorytm minmax pelniacy funkcje AI 
/// </summary>
/// <param name="level"></param>
/// <param name="player_symbol">Symbol uzywany przez komputer</param>
/// <param name="depth">Glebokosc przeszukania drzewa binarnego</param>
/// <returns></returns>
int tic_tac_toe::min_max_ai(const int level, const char player_symbol, const int depth)
{
	auto temp = 0, rows=0, columns=0;
	// minimalizowanie strat
	for (auto i = 0; i < size_; ++i)
	{
		for (auto j = 0; j < size_; ++j)
		{
			if (board_[i][j] == ' ')
			{
				board_[i][j] = player_symbol;
				columns = j;
				rows = i;
				temp++;
				board_[i][j] = ' ';
				if (check_single_winner(player_symbol))
				{
					if (!level)
						board_[i][j] = player_symbol;
					return player_symbol == 'X' ? -1 : 1;
				}
			}
		}
	}
	//sprawdzanie remisu
	if (temp == 1)
	{
		if (!level)
			board_[rows][columns] = player_symbol;
		return 0;
	}
	// maksymalizowanie korzysci
	auto v_max = (player_symbol == 'X' ? size_ - 1 : -size_ + 1);
	for (auto i = 0; i < depth; ++i)
	{
		for (auto j = 0; j < depth; ++j)
		{
			if (board_[i][j] == ' ')
			{
				board_[i][j] = player_symbol;
				auto V = min_max_ai(level + 1, (player_symbol == 'X' ? 'O' : 'X'), depth);
				board_[i][j] = ' ';
				if (((player_symbol == 'X') && (V < v_max)) || ((player_symbol == 'O') && V > v_max))
				{
					rows = i;
					columns = j;
					v_max = V;
				}
			}
		}
	}
	if (!level)
		board_[rows][columns] = player_symbol;
	return v_max;


	
	/*if (check_single_winner('X')) return 1;
	if (check_single_winner('O')) return -1;
	if (draw()) return 0;
	if (depth == 3) return 0;

	int score = player == AI ? INT_MIN : INT_MAX;  // doesnt work
	
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
	return x;*/
}



/// <summary>
/// Sprawdzanie czy zaszedl warunek zwycienstwa
/// </summary>
/// <param name="player_symbol"></param>
/// <returns></returns>
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
	/// <summary>
	/// Wyswietlenie informacji o zwyciescy
	/// </summary>
	/// <returns></returns>
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

bool tic_tac_toe::check_full_board()
{
	for (auto i = 0; i < this->size_; i++)
	{
		for (auto j = 0; j < this->size_; j++)
		{
			if (board_[i][j] == ' ') return true;
		}
	}
	std::cout << "Plansza pelna. Koniec gry!";
	return false;
}
