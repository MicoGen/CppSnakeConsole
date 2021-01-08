

#include <iostream>
// for observe user's press moving buttons
#include <conio.h>
using std::cout;
using std::endl;

bool gameOver;
const int wigth = 20;
const int height = 20;
int x, y;
int fruitX, fruitY;
int score;
int tailX[100], tailY[100];
int nTail;
enum eDirectionm {STOP = 0, UP, DOWN, LEFT, RIGHT};
eDirectionm dir;

void Setup() {
	gameOver = false;
	dir = STOP;
	x = wigth / 2 - 1;
	y = height / 2 - 2;
	fruitX = rand() % wigth;
	fruitY = rand() % height;
	score = 0;
}

void Draw() {
	system("cls");

	for (int i = 0; i < wigth + 1; i++) 
		cout << "#";	
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < wigth; j++) {
			if (j == 0 || j == wigth - 1)
				cout << "#";

			if (i == y && j == x)
				cout << "W";
			else if (i == fruitY && j == fruitX)
				cout << "f";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						cout << "+";
					}
				}
				if (print == false)
					cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < wigth + 1; i++)
		cout << "#";
	cout << endl;

	cout << "Score: " << score;
}

void Input() {
	// return true if user press someone button on keyboard
	if (_kbhit()) {
		// observe what button press the user
		switch (_getch())
		{
			case 'w': 
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'x':
				gameOver = true;
				break;
		}
	}
}

void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;

	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case UP:
		if (y == 0)
			break;
		y--;
		break;
	case DOWN:
		if (y == height - 1)
			break;
		y++;
		break;
	case LEFT:
		if (x == 0)
			break;
		x--;
		break;
	case RIGHT:
		if (x == wigth - 2)
			break;
		x++;
		break;
	case STOP:
		
		break;
	}

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			dir = STOP;
	}

	if (x == fruitX && y == fruitY)
	{
		score++;
		// create new fruit
		fruitX = rand() % wigth;
		fruitY = rand() % height;
		nTail++;
	}
		
}

int main()
{
	Setup();
	Draw();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
	}

}

