#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

using namespace std;

const int WIDTH = 20, HEIGHT = 20; //Width and Height of the play area
bool gameOver;
int x, y, fruitX, fruitY, score, nTail;
int tailX[100], tailY[100]; 
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {

	gameOver = false;
	x = WIDTH / 2;
	y = HEIGHT / 2;

	srand(time(NULL));
	fruitX = rand() % (WIDTH - 2) + 1;
	fruitY = rand() % (HEIGHT - 2) + 1;

	score = 0;
	dir = STOP;
	nTail = 0;

	return;

}

void Draw() {

	for (int i = 0; i < WIDTH + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == WIDTH - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < WIDTH + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score:" << score << endl;

	cout.flush();

	COORD pos = { 0, 0 };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);

}

void Input() {
	
	if (_kbhit()) {
	
		switch (_getch()) {
		
		case 'a':
			dir = LEFT;
			break;
		
		case 'd':
			dir = RIGHT;
			break;

		case 'w':
			dir = UP;
			break;

		case 's':
			dir = DOWN;
			break;

		case 'x':
			gameOver = true;
			break;
		}
	
	}

	return;

}

void Logic() {

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir) {
	case LEFT:
		x--;
		break;

	case RIGHT:
		x++;
		break;

	case UP:
		y--;
		break;

	case DOWN:
		y++;
		break;

	default:
		break;
	}

	if (x == WIDTH || x == -1 || y == HEIGHT || y == -1) {
	
		gameOver = true;
	
	}

	for (int i = 0; i < nTail; i++) {
	
		if (tailX[i] == x && tailY[i] == y) {
		
			gameOver = true;

		}
	
	}

	if (x == fruitX && y == fruitY) {
	
		score++;
		nTail++;

		srand(time(NULL));
		fruitX = rand() % (WIDTH-2) + 1;
		fruitY = rand() % (HEIGHT-2) + 1;
	
	}

	return;

}

int main() {

	int level = 1;
	Setup();

	while (gameOver == false) {

		if (score == 5) {
		
			level = 2;

		} else if (score == 10) {
		
			level = 3;
		
		} else if (score == 15) {
		
			level = 4;
		
		} else if (score == 20) {
		
			level = 5;

		}

		Draw();
		Input();
		Logic();
		Sleep(100 / level);

	}

	cout << endl << endl;
	cout << "GAMEOVER!" << endl;
	cout << "Final Score: " << score << endl;
	cout << "Level: " << level << endl << endl;
	cout << "Press Any Key to Continue....";
	cin;


	return (0);

}