#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>

using namespace std;

//general gameplay
char grid[3][3] = { '1','2','3','4','5','6','7','8','9' };
int turn = 0;

char player = 'X';
char playerOne = 'X';
char playerTwo = 'O';
char tie = 'T';
char unfinished = 'U';

void Draw(char inGrid[3][3])
{
	system("cls");

	//Draw the array in a grid pattern
	for (int i = 0; i < 3; i++)
	{
		for (int x = 0; x < 3; x++)
		{
			cout << inGrid[i][x] << " ";
		}
		cout << endl;
	}
	cout << "Turn: " << turn << endl;
}

char Win(char inGrid[3][3])
{
	//check all wining positions and return the player if someone has won

	//Horizontal
	if (inGrid[0][0] == inGrid[0][1] &&
		inGrid[0][0] == inGrid[0][2])
		return inGrid[0][0];

	if (inGrid[1][0] == inGrid[1][1] &&
		inGrid[1][0] == inGrid[1][2])
		return inGrid[1][0];

	if (inGrid[2][0] == inGrid[2][1] &&
		inGrid[2][0] == inGrid[2][2])
		return inGrid[2][0];

	//Vertical
	if (inGrid[0][0] == inGrid[1][0] &&
		inGrid[0][0] == inGrid[2][0])
		return inGrid[0][0];

	if (inGrid[0][1] == inGrid[1][1] &&
		inGrid[0][1] == inGrid[2][1])
		return inGrid[0][1];

	if (inGrid[0][2] == inGrid[1][2] &&
		inGrid[0][2] == inGrid[2][2])
		return inGrid[0][2];

	//Diagonal
	if (inGrid[0][0] == inGrid[1][1] &&
		inGrid[0][0] == inGrid[2][2])
		return inGrid[0][0];

	if (inGrid[2][0] == inGrid[1][1] &&
		inGrid[2][0] == inGrid[0][2])
		return inGrid[2][0];

	//Tie
	int openTiles = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int x = 0; x < 3; x++)
		{
			if ((inGrid[i][x] != playerOne && inGrid[i][x] != playerTwo))
				openTiles++;
		}
	}

	if (openTiles > 0)
		return unfinished;

	return tie;
}

int Recursive(char inArray[3][3], int depth, char inPlayer)
{
	char gameState = Win(inArray);
	char tempGrid[3][3] = { '1','2','3','4','5','6','7','8','9' };

	if (gameState == unfinished)
	{
		vector<int> values;
		vector<int> indexes;

		for (int i = 0; i < 3; i++)
		{
			for (int x = 0; x < 3; x++)
			{
				memcpy(tempGrid, inArray, 9);
				if (tempGrid[i][x] != playerOne && tempGrid[i][x] != playerTwo)
				{
					tempGrid[i][x] = inPlayer;

					int value = Recursive(tempGrid, depth + 1, (inPlayer == playerOne) ? playerTwo : playerOne);
					int index = i * 3 + x;

					values.push_back(value);
					indexes.push_back(index);
				}
			}
		}

		if (inPlayer == playerTwo)
		{
			//returns what index to move to if it's the first function call 
			int maxIndex = max_element(values.begin(), values.end()) - values.begin();
			if (depth == 0)
				return indexes[maxIndex];
			//or returns value of the move playerTwo made if it's in recursion
			else
				return values[maxIndex];
		}
		else
		{
			//returns value of the moves for playerOne 
			int minIndex = min_element(values.begin(), values.end()) - values.begin();
			return values[minIndex];
		}
	}
	//if game's over in the recursive game return the value of the moves
	else if (Win(inArray) == playerTwo)
		return 10 - depth;
	else if (Win(inArray) == playerOne)
		return depth - 10;
	else if (Win(inArray) == tie)
		return 0;
}

int Minmax()
{
	return Recursive(grid, 0, playerTwo);
}

void Input()
{
	int a;

	//take input a from console or Minimax function, make it into a 2d index and set it to what player is set to
	if (player == playerTwo)
		a = Minmax();
	else
	{
		cin >> a;
		a--;

		int i = a / 3;
		int x = a % 3;

		//redo input if not  satisfactory
		while (grid[i][x] == playerOne || grid[i][x] == playerTwo || a < 0)
		{
			cout << "enter a valid position 1-9" << endl;

			cin >> a;
			a--;

			i = a / 3;
			x = a % 3;
		}
	}

	int x = a / 3;
	int y = a % 3;

	grid[x][y] = player;
}

void SwitchPlayer()
{
	//switch player each turn
	player = (player == playerOne) ? playerTwo : playerOne;
}

int main()
{
	while (Win(grid) == unfinished)
	{
		turn++;
		Draw(grid);
		Input();
		SwitchPlayer();
	}
	Draw(grid);

	cout << "Winner is: " << Win(grid) << endl;
	return 0;
}
