#include <iostream>
#include <conio.h>
#include <iomanip>
#include <stdlib.h>
#include <ctime>
#include <cstring>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;



//Structures
struct snake_coordinates
{
	int snakeX;
	int snakeY;
}snake_head;

struct fruit_coordinates
{
	int FruitX;
	int FruitY;
}Fruit;

struct snake_body_coordinates
{
	int X;
	int Y;
}Snake_body;


//Enumeration
enum game_hardness
{
	EASY = 0,
	HARD
}game_dificullty;


//Functions
void Select_difficulty();
void snake_game();
void border();
void Input_direction();
void game_end();
void Fruit_generator();
void snake_size_and_direction();
void snake_from_other_side(string);
void highscore_from_file();
void highscore_to_file();


//Global Variables 
const int rowSize = 15;
const int colSize = 15;
int score = 0;
int user_entered = 0;
string snake_direction = "right";
char snake_head_char = '<';
int snake_size = 0;
string Store_driection[9999];
int snake_speed = 81;
char game_border[rowSize][colSize] = {};
int high_score = 0;

int main()
{
	//First Time Menu
	cout << "\t\t~`*`~-:WELCOME TO SNAKE GAME:-~`*`~\n" << endl;
	cout << "Coded by: Asfand Yar && Uzair Ashfaq\n" << endl;
	cout << "\n~-:Game Controls:-~\nW,A,S,D ~~~> Movement\nSpace\t~~~> Pause\n" << endl;
	//Playing The Snake Game
	snake_game();

	_getch();
}

void Select_difficulty()
{
	char user_dificullty;

	cout << "Press 1 For ~-:EASY:-~\t\t~~~~> Border Collision Is OFF\nPress 2 For ~-:HARD:-~\t\t~~~~> Border Collision Is ON\nSelect Game dificulty : ";

	//Defining The Difficulty For the Game
	do
	{
		user_dificullty = _getch();
	} while (user_dificullty != '1' && user_dificullty != '2');

	if (user_dificullty == '1')
	{
		game_dificullty = EASY;
	}
	else if (user_dificullty == '2')
	{
		game_dificullty = HARD;
	}

	//Count Down Before Game
	for (int i = 3; i > 0; i--)
	{
		system("CLS");
		cout << "Game Starting in " << i << " . . . ." << endl;
		Sleep(1000);

	}

	system("CLS");
}


void highscore_from_file()
{

	//Taking Highscore from Highscore File (FOR HARD MODE).
	if (game_dificullty == HARD)
	{
		ifstream highscore_file("highscore for hard.txt");
		if (highscore_file.is_open())
		{
			highscore_file >> high_score;
		}

		//If File Is Not Present Crearting A New One And Storing 0 In It.
		else
		{
			ofstream create_highscore_file("highscore for hard.txt");
			create_highscore_file << 0;
			create_highscore_file.close();
		}
		highscore_file.close();
	}

	//Taking Highscore from Highscore File (FOR EASY MODE).
	if (game_dificullty == EASY)
	{
		ifstream highscore_file("highscore for easy.txt");
		if (highscore_file.is_open())
		{
			highscore_file >> high_score;
		}
		//If File Is Not Present Crearting A New One And Storing 0 In It.
		else
		{
			ofstream create_highscore_file("highscore for easy.txt");
			create_highscore_file << 0;
			create_highscore_file.close();
		}
		highscore_file.close();
	}
}

void snake_game()
{
	srand(time(0));

	//Calling Functions.
	Select_difficulty();
	highscore_from_file();

	//Resetting All Values Before Each New Game.
	snake_head.snakeX = rowSize / 2;
	snake_head.snakeY = 1;
	Fruit.FruitX = 1 + rand() % (rowSize - 2);
	Fruit.FruitY = 1 + rand() % (colSize - 2);

	snake_direction = "right";
	score = 0;
	snake_head_char = '<';
	snake_size = 0;
	snake_speed = 81;


	//Getting Each Frame of Snake Game
	while (true)
	{

		//Creating And Printing The Border And Snake.
		border();
		cout << "\nSCORE : " << score << "\t\t\tHIGH SCORE : " << high_score << endl;

		//Taking Input From User And Changing Direction Of Snake Accordingly.
		Input_direction();


		//sleep function suspends the program's execution temporarily for a period of time.
		Sleep(snake_speed);

		system("CLS");

		//Border Collision Is Active For HARD Mode.
		if (game_dificullty == HARD)
		{
			if (snake_head.snakeY == colSize - 1 || snake_head.snakeY == 0 || snake_head.snakeX == 0 || snake_head.snakeX == rowSize - 1)
			{
				game_end();
			}
		}
	}

}

void Input_direction()
{
	//Checking To See If Any Key Was Pressed
	if (_kbhit())
	{
		//Storing The Key Press In (user_entered)
		user_entered = _getch();

		switch (user_entered)
		{
		case'w' | 'W':

			if (snake_direction != "down")
			{
				snake_direction = "up";
				snake_head_char = 'v';
			}
			break;
		case'a' | 'A':
			if (snake_direction != "right")
			{
				snake_direction = "left";
				snake_head_char = '>';
			}
			break;
		case's' | 'S':
			if (snake_direction != "up")
			{
				snake_direction = "down";
				snake_head_char = '^';
			}
			break;
		case'd' | 'D':
			if (snake_direction != "left")
			{
				snake_direction = "right";
				snake_head_char = '<';
			}
			break;
		case' ':
			//For Pausing The Game.
			char pause_input;
			cout << "~~> Press Space To Un-Pause.... " << endl;
			do
			{
				pause_input = _getch();
			} while (pause_input != ' ');
		default:
			break;
		}
	}

	//Comparing Directions And Changing Co-ordinates Accordingly.
	if (snake_direction == "up")
	{
		snake_head.snakeX--;
	}
	else if (snake_direction == "left")
	{
		snake_head.snakeY--;
	}
	else if (snake_direction == "down")
	{
		snake_head.snakeX++;
	}
	else if (snake_direction == "right")
	{
		snake_head.snakeY++;
	}

	//comparing snake's head co-ordinates with fruit co-ordinates.
	Fruit_generator();

	//Storing All Previous Directions Of Snake.
	for (int index = snake_size; index > 0; index--)
	{
		Store_driection[index] = Store_driection[index - 1];
	}
	Store_driection[0] = snake_direction;
}

void border()
{

	for (int row = 0; row < rowSize; row++)
	{
		for (int col = 0; col < colSize; col++)
		{

			if (row == 0 || row == rowSize - 1 || col == 0 || col == colSize - 1)
			{
				//Creating The Border
				if (row == 0 || row == rowSize - 1)
				{
					game_border[row][col] = char(205);
				}
				if (col == 0 || col == colSize - 1)
				{
					game_border[row][col] = char(186);
				}

				game_border[0][0] = char(201);
				game_border[rowSize - 1][0] = char(200);
				game_border[0][colSize - 1] = char(187);
				game_border[rowSize - 1][colSize - 1] = char(188);

			}

			else
			{
				//Putting Spaces Inside The Borders
				game_border[row][col] = ' ';
			}
		}
	}

	//Passing Snake Head Thorugh Border For EASY Mode.
	snake_from_other_side("Border");

	//Increasing Snake's Size And Moving Snake's Body.
	snake_size_and_direction();

	////If Snake Eats Fruit, Generate a New One.
	Fruit_generator();

	//Putting Snake And Fruit In The Borders.
	game_border[snake_head.snakeX][snake_head.snakeY] = snake_head_char;
	game_border[Fruit.FruitX][Fruit.FruitY] = '@';


	//Printing The Border
	for (int row = 0; row < rowSize; row++)
	{
		cout << "\t";
		for (int col = 0; col < colSize; col++)
		{
			cout << setw(2) << game_border[row][col];
		}
		cout << endl;
	}
}

void Fruit_generator()
{

	//If Snake's Co-ordinates become equal to Fruit's Co-ordinates, Make A New One.
	if (snake_head.snakeX == Fruit.FruitX && snake_head.snakeY == Fruit.FruitY)
	{
		srand(time(0));

		//Generating New Co-ordinates Unless There Is A Space On the Co-ordinate.
		//So That Fruit Never Generates Inside Snake's Body.
		do
		{
			Fruit.FruitX = 1 + rand() % (rowSize - 2);
			Fruit.FruitY = 1 + rand() % (colSize - 2);

		} while (game_border[Fruit.FruitX][Fruit.FruitY] != ' ');

		//Increasing Score, Snake Speed And Snake's Size Whenever It Eats The Fruit.
		score += 10;
		snake_size++;
		if (snake_speed > 0)
		{
			snake_speed -= 3;
		}
	}
}

void snake_size_and_direction()
{

	//Giving Current Location Of Head To the Body.
	//Body Is Formed From This Reference Location.
	Snake_body.X = snake_head.snakeX;
	Snake_body.Y = snake_head.snakeY;

	for (int index = 0; index < snake_size; index++)
	{

		if (Store_driection[index] == "right")
		{
			Snake_body.Y--;
		}
		else if (Store_driection[index] == "up")
		{
			Snake_body.X++;
		}
		else if (Store_driection[index] == "down")
		{
			Snake_body.X--;
		}
		else if (Store_driection[index] == "left")
		{
			Snake_body.Y++;
		}

		//Snake Body Passes Through Border For EASY Mode.
		if (game_dificullty == EASY)
		{
			snake_from_other_side("Body_shape");
		}

		//Printing Snake Body.
		game_border[Snake_body.X][Snake_body.Y] = 'o';

		//If Snake Head Collides With It's Own Body. It Dies.
		if (snake_head.snakeX == Snake_body.X && snake_head.snakeY == Snake_body.Y)
		{
			game_end();
		}

	}

}

void game_end()
{
	cout << "\a";
	cout << "Collision Detected\n*****GAME OVER*****";
	cout << "\nYour SCORE : " << score << endl;

	//Putting HighScore In the File (IF: Score > High Score).
	highscore_to_file();


	//Replay Or Exit Game Choice.
	char Answer;
	cout << "\n\n\n" << endl;
	cout << "\nPress Y To play Again!!\nPress N To Exit!!" << endl;
	do
	{
		Answer = _getch();
	} while (Answer != 'y' && Answer != 'Y' && Answer != 'N' && Answer != 'n');
	if (Answer == 'Y' || Answer == 'y')
	{
		system("CLS");
		snake_game();
	}
	else
	{
		cout << "\n\n*~*~*~*~*~Game Ended~*~*~*~*~*" << endl;
		exit(0);
	}
}

void highscore_to_file()
{

	if (game_dificullty == EASY)
	{
		//Putting Highscore in File (EASY Mode) If Current Score is More Than Previous Highscore.
		if (score > high_score)
		{
			ofstream update_highscore("highscore for easy.txt");
			update_highscore << score;
			update_highscore.close();
			cout << "\n~`*`~-:CONGRATS YOU HAVE SET A NEW HIGHSCORE:-~`*`~" << endl;
			cout << "NEW HIGH SCORE " << score << endl;
		}
		//If Score Is less Than HighScore, Showing The Previous Highscore.
		else
		{
			cout << "HIGH SCORE " << high_score << endl;
		}

	}

	if (game_dificullty == HARD)
	{
		//Putting Highscore in File (HARD Mode) If Current Score is More Than Previous Highscore.
		if (score > high_score)
		{
			ofstream update_highscore("highscore for hard.txt");
			update_highscore << score;
			update_highscore.close();
			cout << "*******CONGRATS!!!*******\nYOU HAVE SET A NEW HIGHSCORE" << endl;
			cout << "NEW HIGH SCORE " << score << endl;
		}
		//If Score Is less Than HighScore, Showing The Previous Highscore.
		else
		{
			cout << "HIGH SCORE " << high_score << endl;
		}

	}

}

void snake_from_other_side(string call)
{

	if (call == "Body_shape")
	{
		//For Snake's BODY To Go Through Border.
		if (Snake_body.Y == 0)
		{
			Snake_body.Y = colSize - 2;
		}
		else if (Snake_body.Y == colSize - 1)
		{
			Snake_body.Y = 1;
		}
		else if (Snake_body.X == rowSize - 1)
		{
			Snake_body.X = 1;
		}
		else if (Snake_body.X == 0)
		{
			Snake_body.X = rowSize - 2;
		}
	}


	else if (call == "Border" && game_dificullty == EASY)
	{
		//For Snake's HEAD To Go Through Border.
		if (snake_head.snakeY == colSize - 1)
		{
			snake_head.snakeY = 1;
		}
		else if (snake_head.snakeY == 0)
		{
			snake_head.snakeY = colSize - 2;
		}
		else if (snake_head.snakeX == rowSize - 1)
		{
			snake_head.snakeX = 1;
		}
		else if (snake_head.snakeX == 0)
		{
			snake_head.snakeX = rowSize - 2;
		}
	}

}
