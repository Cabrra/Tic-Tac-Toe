#include <iostream>
using namespace std;
#include <ctime>
#include <cctype>

#include "Console.h"
using namespace System;


void DrawBoard(char board[][3]);
void PlayerInput (bool aux[][3], char board [][3], char player);
void AIInput (bool aux[][3], char board [][3], char comp, char player);
bool MoveCheck(bool aux[][3], char board [][3], char player); // Win or lose function
char Select (void);
void Restart(void);

int main(){
	//Player = X OS = O
	srand(static_cast<unsigned int>(time(nullptr)));
	char board [3][3];
	bool aux[3][3];
	unsigned int moves, turn;
	bool win1, winA; //player 1 win= win1, AI win = winA
	char player, comp;
	while (true) { //restart loop.
		win1 = false;
		winA = false;
		moves = 9; // moves left
		turn = rand() % 2;
		if (0 == turn)
			turn = 2; // AI's turn
		else
			turn = 1; // player's turn
		for (int i = 0; i<3; i++) { // Inizialize array and aux.
			for (int j=0; j<3; j++) {
				aux[i][j] = true; // array of possible moves.
				board[i][j] = ' '; // fill board with blanck spaces.
			}
		}
		Console::Clear();
		player = Select();
		if (player == 'X')
			comp = 'O';
		else
			comp ='X';
		while (moves && !win1 && !winA) { //Game loop.
			DrawBoard(board);
			if (turn == 1) {
				PlayerInput(aux, board, player);
				moves = moves -1; // moves left
				turn = 2;
				win1 = MoveCheck(aux, board, player);
			} // End of player's turn.
			else{
				AIInput(aux, board, comp, player);
				moves = moves -1; // moves left
				turn = 1;
				winA = MoveCheck(aux, board, comp);
			}
		} //game loop
		DrawBoard(board);
		if (win1)
			cout<<"You won!! Congratulations!!\n\n";
		else if (winA)
			cout<< "Computer won!! Sorry.\n\n"; 
		else
			cout<< "It is a draw!!\n\n";
		Restart();
	}//repeat loop
	Console::Clear();
	system("pause");
	return 0;
}

void DrawBoard(char board[][3]){
	Console::Clear();
	for (int i = 0; i<3; i++) { // Display the actual game board
		Console::SetCursorPosition((Console::WindowWidth() - 31) / 2 , 20+i); // the board will display in the center
		cout<<"|";
		for (int j=0; j<3; j++) {
			cout<<board[i][j]; 
			cout<<"|";
		}
		cout<<"\n";
	}
}

void PlayerInput (bool aux[][3], char board[][3], char player){

	int row, column;

	cout<<"\nPlayer's turn:\n";

	while (true) { // Player validation
		do{ // Row 
			cout<<"Enter row (values 0 to 2): ";
			cin>>row;
			if (cin.fail() || cin.bad() || cin.eof()){
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				row = 5;
			}
		}while (row < 0 || row > 2);
		do{ //Column validation
			cout<<"Enter column (values 0 to 2): ";
			cin>> column;
			if (cin.fail() || cin.bad() || cin.eof()){
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				column = 5;
			}
		}while (column < 0 || column > 2);

		if (aux[row][column] == true) { // Check the moves
			aux[row][column] = false; //Update the possible moves
			board[row][column] = player; // enter moves
			break;
		}
		else
			cout<<"ERROR! Space already taken!!\n";
	}
}

void AIInput (bool aux[][3], char board [][3], char comp, char player){

	if (aux[1][1] == true){ // this is the best moves to win
		aux[1][1] = false;
		board[1][1] = comp;
	}
	else{ // check player's moves so far and block.

		if ( aux[0][0] == true && ((board[0][1] == player && board[0][2] == board[0][1]) || (board[1][0] == player && board[2][0] == board[1][0]) || (board[1][1] == player && board [2][2] == board[1][1]))){
			aux[0][0] = false;
			board[0][0] = comp;
		}
		else if (aux[0][1] == true && ((board[0][0] == player && board[0][2] == board[0][0]) || (board[1][1] == player && board[2][1] == board[1][1]))){
			aux[0][1] = false;
			board[0][1] = comp;
		}
		else if (aux[0][2] == true && ((board[0][1] == player && board[0][0] == board[0][1]) || (board[1][2] == player && board[2][2] == board[1][2]) || (board[1][1] == player && board [0][2] == board[1][1]))){
			aux[0][2] = false;
			board[0][2] = comp;
		}
		else if (aux[1][0] == true && ((board[1][1] == player && board[1][2] == board[1][1]) || (board[0][0] == player && board[2][0] == board[0][0]))){
			aux[1][0] = false;
			board[1][0] = comp;
		}
		// I don't need to check the [1][1] position because it would be the first move.
		else if (aux[1][2] == true && ((board[0][2] == player && board[2][2] == board[0][2]) || (board[1][0] == player && board[1][1] == board[1][0]))){
			aux[1][2] = false;
			board[1][2] = comp;
		}
		else if (aux[2][0] == true && ((board[0][0] == player && board[1][0] == board[0][0]) || (board[2][1] == player && board[2][2] == board[2][1]) || (board[1][1] == player && board[0][2] == board[1][1]))){
			aux[2][0] = false;
			board[2][0] = comp;
		}
		else if (aux[2][1] == true && ((board[1][1] == player && board[0][1] == board[1][1]) || (board[2][0] == player && board[2][2] == board[2][0]))){
			aux[2][1] = false;
			board[2][1] = comp;
		}
		else if ((aux[2][2] == true && ((board[2][0] == player && board[2][1] == board[2][0]) || (board[0][2] == player && board[1][2] == board[0][2]) || (board[1][1]) == player && board[0][0] == board[1][1]))){
			aux[2][2] = false;
			board[2][2] = comp;
		}
		else{
			int k, l;
			do{
				k = rand() % 3;
				l= rand() % 3;

			}while(aux[k][l] == false);
			aux[k][l] = false;
			board[k][l] = comp;
		}
	}

}

bool MoveCheck(bool aux[][3], char board [][3], char player){
	int count =0;

	for (int i = 0; i<3; i++){ // chech Vertical
		for(int j =0; j<3; j++){
			if ( board[j][i] == player)
				count++; 
			if (count == 3)
				return true;
		}
		count = 0;
	}


	for (int i = 0; i<3; i++){ // chech horizontal
		for(int j =0; j<3; j++){
			if ( board[i][j] == player)
				count++; 
			if (count == 3)
				return true;
		}
		count = 0;
	}

	if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || (board[0][2] == player && board[1][1] == player && board[2][0] == player)){
		return true; // Cross check
	}
	else
		return false;
}

char Select (void){
	char player;
	do{
		cout<< "Welcome to Tic Tac Toe game. Please pick your game letter (X or O): ";
		cin>>player;
		player = toupper (player);

		if (cin.fail() || cin.bad() || cin.eof() || sizeof player !=1 ){
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			player = 'a'; // invalid input to repeat the loop
		}
		if (player == 'X' || player == 'O')
			break;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}while (true);

	return player;
}

void Restart (void){
	char reset;
	do{
		cout<< "Do you want play again((Y)es/(N)o)? ";
		cin>> reset;
		reset = toupper (reset);

		if (cin.fail() || cin.bad() || cin.eof() || sizeof reset !=1){
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			reset = 'a'; // invalid input to repeat the loop
		}
		if (reset == 'Y' || reset == 'N')
			break;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}while (true);

	cin.clear();
	cin.ignore(INT_MAX, '\n');

	if (reset == 'N')
		exit(0);

}