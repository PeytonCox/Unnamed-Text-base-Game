#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <vector>
#include <windows.h>

using namespace std;

void gamePrint(COORD);
void enemyAI(COORD);
void playerAttack(COORD);

int xMax = 32;
int yMax = 16;

//Player Coordinate info
DWORD dw;
COORD player;
COORD pastPlayer;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

//Enemy Coordinate info
COORD e1;
COORD e1Past;

//coin and point coordinates
COORD coin;
COORD pointCoord;

COORD playerDisplay;

int points = 0;

int main() {
	srand((unsigned)time(NULL));

	int invalidMove = 0;
	coin.X = (rand() % xMax);
	coin.Y = (rand() % yMax);
	e1.X = 1;
	e1.Y = 1;
	e1.X = (rand() % xMax);
	e1.Y = (rand() % yMax);
	pointCoord.Y = yMax + 2;
	pointCoord.X = 7;
	playerDisplay.Y = pointCoord.Y + 1;
	playerDisplay.X = 15;

	char move = 'w';
	player.X = xMax / 2;
	player.Y = yMax / 2;

	gamePrint(player);

	//Pre-print stats
	cout << endl << endl;
	cout << "\rCoins: " << points << endl;
	cout << "Player Coords: ";

	while (move != 'q') {


		move = _getch();

		if (move == 'e') {
			playerAttack(player);
		}
		else if (move == 'w' && player.Y > 0) {
			pastPlayer.X = player.X;
			pastPlayer.Y = player.Y;
			player.Y--;
		}
		else if (move == 's' && player.Y < yMax-1) {
			pastPlayer.X = player.X;
			pastPlayer.Y = player.Y;
			player.Y++;
		}
		else if (move == 'a' && player.X > 0) {
			pastPlayer.X = player.X;
			pastPlayer.Y = player.Y;
			player.X--;
		}
		else if (move == 'd' && player.X != xMax-1) {
			pastPlayer.X = player.X;
			pastPlayer.Y = player.Y;
			player.X++;
		}
		else { /*Place Holder*/ }

		//coin calculations
		if (player.X == coin.X && player.Y == coin.Y) {
			coin.X = (rand() % xMax);
			coin.Y = (rand() % yMax);
			points++;
			//pointCoord.X++;
			SetConsoleCursorPosition(hStdOut, pointCoord);
			cout << points << endl;
		}



		WriteConsoleOutputCharacter(hStdOut, L"#", 1, pastPlayer, &dw);
		WriteConsoleOutputCharacter(hStdOut, L"X", 1, player, &dw);
		e1Past.X = e1.X;
		e1Past.Y = e1.Y;
		enemyAI(player);
		WriteConsoleOutputCharacter(hStdOut, L"#", 1, e1Past, &dw);
		WriteConsoleOutputCharacter(hStdOut, L"E", 1, e1, &dw);

		WriteConsoleOutputCharacter(hStdOut, L"O", 1, coin, &dw);

		//Handles player coordinate printing
		SetConsoleCursorPosition(hStdOut, playerDisplay);
		cout << "           " << endl;
		SetConsoleCursorPosition(hStdOut, playerDisplay);
		cout << player.X+1 << "," << player.Y+1 << endl;

		//WILL FIX LATER, DO NOT FORGET PLS AND THANK YOU
		/*cout << endl << endl;
		cout << "Points: " << points << endl;
		cout << "X Coord: " << player.X << endl;
		cout << "y Coord: " << player.Y << endl;
		cout << endl << "Coin X: " << coin.X << "  Y: " << coin.Y << endl;
		cout << "Enemy X: " << e1.X << "  Y: " << e1.Y << endl;*/

	}

}


void gamePrint(COORD player) {

	system("cls");

	int y, x;

	for (y = 1; y <= yMax; y++) {
		for (x = 1; x <= xMax; x++) {
			if (player.X == x && player.Y == y && player.X == coin.X && player.Y == coin.Y) {
				cout << "X";
				coin.X = (rand() % xMax);
				coin.Y = (rand() % yMax);
				points++;
			}
			/*else if (player.X == x && player.Y == y) {
				cout << "X";
			}*/
			/*else if (coin.X == x && coin.Y == y) {
				cout << "O";
			}*/
			/*else if (e1.X == x && e1.Y == y) {
				cout << "E";
			}*/
			else {
				cout << "#";
			}
		}
		cout << endl;
	}


	_sleep(100);
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	cin.clear(); // Clear flags indicating errors on stream	
}

void playerAttack(COORD player) {


	COORD temp1, temp2, temp3, temp4;

	temp1.X = player.X+1;
	temp1.Y = player.Y+1;
	WriteConsoleOutputCharacter(hStdOut, L"%", 1, temp1, &dw);

	temp2.X = player.X-1;
	temp2.Y = player.Y+1;
	WriteConsoleOutputCharacter(hStdOut, L"%", 1, temp2, &dw);

	temp3.X = player.X+1;
	temp3.Y = player.Y-1;
	WriteConsoleOutputCharacter(hStdOut, L"%", 1, temp3, &dw);

	temp4.X = player.X-1;
	temp4.Y = player.Y-1;
	WriteConsoleOutputCharacter(hStdOut, L"%", 1, temp4, &dw);


	
	_sleep(500);

	if ((temp1.X == e1.X && temp1.Y == e1.Y) || (temp2.X == e1.X && temp2.Y == e1.Y) || (temp3.X == e1.X && temp3.Y == e1.Y) || (temp4.X == e1.X && temp4.Y == e1.Y)) {
		e1.X = (rand() % xMax);
		e1.Y = (rand() % yMax);
	}

	WriteConsoleOutputCharacter(hStdOut, L"#", 1, temp1, &dw);
	WriteConsoleOutputCharacter(hStdOut, L"#", 1, temp2, &dw);
	WriteConsoleOutputCharacter(hStdOut, L"#", 1, temp3, &dw);
	WriteConsoleOutputCharacter(hStdOut, L"#", 1, temp4, &dw);

	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

void enemyAI(COORD player) {


	//ENEMY AI, REENABLE
	int xDist, yDist;
	if (e1.X > player.X) {
		xDist = e1.X - player.X;
	}
	else if (e1.X < player.X) {
		xDist = player.X - e1.X;
	}
	else {
		xDist = 0;
	}

	if (e1.Y > player.Y) {
		yDist = e1.Y - player.Y;
	}
	else if (e1.Y < player.Y) {
		yDist = player.Y - e1.Y;
	}
	else {
		yDist = 0;
	}

	if (yDist == 0 && xDist == 1) {
		cout << "YOU LOSE!" << endl;
		system("pause");
		exit(0);
	}
	else if (yDist == 1 && xDist == 0) {
		cout << "YOU LOSE!" << endl;
		system("pause");
		exit(0);
	}
	if (xDist > yDist && player.X > e1.X && xDist != 0) {
		e1.X++;
	}
	else if (xDist > yDist && player.X < e1.X && xDist != 0) {
		e1.X--;
	}
	else if (yDist > xDist && player.Y > e1.Y && yDist != 0) {
		e1.Y++;
	}
	else if (yDist > xDist && player.Y < e1.Y && yDist != 0) {
		e1.Y--;
	}
}

//Coming back to later
/*void shop(){
}*/
