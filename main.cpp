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


		move = _getch(); //{auses the console until a key is hit and it returns a char for the value of the key pressed into "move"

		if (move == 'e') { //If 'e' is pressed, call the player "Attack" function
			playerAttack(player);
		}
		else if (move == 'w' && player.Y > 0) { //Moves the player up when 'w' is pressed
			pastPlayer.X = player.X;
			pastPlayer.Y = player.Y;
			player.Y--;
		}
		else if (move == 's' && player.Y < yMax-1) { //Moves the player down when 's' is pressed
			pastPlayer.X = player.X;
			pastPlayer.Y = player.Y;
			player.Y++;
		}
		else if (move == 'a' && player.X > 0) { //Moves the player left when 'a' is pressed
			pastPlayer.X = player.X;
			pastPlayer.Y = player.Y;
			player.X--;
		}
		else if (move == 'd' && player.X != xMax-1) { //Moves the player right when 'd' is pressed
			pastPlayer.X = player.X;
			pastPlayer.Y = player.Y;
			player.X++;
		}
		else { /*Place Holder*/ }

		//coin calculations
		if (player.X == coin.X && player.Y == coin.Y) {
			coin.X = (rand() % xMax); //These two lines regenerate the coordinates for the coin after it is collected
			coin.Y = (rand() % yMax); //^^
			points++; //increase the coin/points counter
			SetConsoleCursorPosition(hStdOut, pointCoord);//adjusts the print cursor to the score placement
			cout << points << endl; //replaces the old points with the updates number
		}


		/* THIS HANDLES ALL OF THE SCREEN MOVEMENT */
		WriteConsoleOutputCharacter(hStdOut, L"#", 1, pastPlayer, &dw); //This replaces the player's old position with a filler '#'
		WriteConsoleOutputCharacter(hStdOut, L"X", 1, player, &dw); //This inserts an 'X' into the player's new position
		e1Past.X = e1.X; //records the current player position for next time around
		e1Past.Y = e1.Y; //^^
		enemyAI(player);
		WriteConsoleOutputCharacter(hStdOut, L"#", 1, e1Past, &dw); //This replaces the Enemy's old position with a filler '#'
		WriteConsoleOutputCharacter(hStdOut, L"E", 1, e1, &dw); //This inserts an 'E' into the Enemy's new position

		WriteConsoleOutputCharacter(hStdOut, L"O", 1, coin, &dw); //Replaces the 'tile' with an 'O' to symbolize the coin

		//Handles player coordinate printing
		SetConsoleCursorPosition(hStdOut, playerDisplay);
		cout << "           " << endl;
		SetConsoleCursorPosition(hStdOut, playerDisplay);
		cout << player.X+1 << "," << player.Y+1 << endl;

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
