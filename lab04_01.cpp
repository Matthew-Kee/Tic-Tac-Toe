/*
Student Name: Matthew Kee
Student Number: 20818491

SYDE 121 Lab: Assignment #4: Exercise #1
Filename: lab04_01

I hereby declare that this code, submitted for credit for the course
SYDE 121, is a product of my own efforts. This coded solution has
not beegn plagiarized from other sources and has not been knowingly
plagiarized by others.

Project: Exercise #1
Purpose: Simulate a game where two users can play multiple rounds of 4 by 4 
Tic Tac Toe, keeping score fof wins and ties and running until they no longer wish to play.
Due Date: Tuesday, October 8th, 2019
*/

/*
To test and debug my program, I ran through dozens of playthroughs, keeping track on pen and paper to see
if scores were saved appropriately, if first turn at beginning of each round alternated, and if the board array
and variables reset for each new round. I also tested if each vertical, horizontal, and diagonal winning combo
worked for both players, and if ties were processed properly when no spaces were left and no combos were found.

Additionally I tested that inputs were properly validated and that any exceptions were caught and did not result
in the program aborting. 
*/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


bool run_game();
// PURPOSE: Runs game
//     INPUTS: nothing to input
//     OUTPUTS: returns true when finished executing

void round_setup(int round_num, string& player_id, string* board_array);
// PURPOSE: Populates board_array with placeholder numbers, decides which player takes first turn
//     INPUTS: round_num - tracks how many rounds played this game
//			   player_id - the id for the player taking their turn
//			   board_array - the array that holds the state of the tic tac toe board
//     OUTPUTS: nothing to return

void take_input(string& player_id, string* board_array);
// PURPOSE: Takes in and validates move input from user
//     INPUTS: player_id - the id for the player taking their turn
//			   board_array - the array that holds the state of the tic tac toe board
//     OUTPUTS: nothing to return

void print_board(string* board_array);
// PURPOSE: Prints tic tac toe board to console
//     INPUTS: board_array - the array that holds the state of the tic tac toe board
//     OUTPUTS: nothing to return

void check_board(string* board_array, bool& round_over, int& round_num, int& x_score, int& y_score, int& num_of_ties);
// PURPOSE: Checks board for winning combo OR to see if no spots remain open
//     INPUTS: board_array - the array that holds the state of the tic tac toe board
//			   round_over - tracks if round is complete
//			   round_num - tracks how many rounds played this game
//			   x_score - X player's wins
//			   o_score - O player's wins
//			   num_of_ties - number of tied games so far
//     OUTPUTS: nothing to return

void end_round(int x_score, int o_score, int num_of_ties, bool& game_over);
// PURPOSE: Prints scores and determines if user wants to continue playing
//     INPUTS: x_score - X player's wins
//			   o_score - O player's wins
//			   num_of_ties - number of tied games so far
//			   game_over - tracks if user is done playing
//     OUTPUTS: nothing to return

// run tic tac toe game, if run_game returns true then end program
int main()
{
	if (run_game()) {
		return 0;
	}
}

// run tic tac toe game
bool run_game() {

	// initialize variables
	string player_id; // "X" or "O", keeps track of which player is taking their turn 
	string board_array[16] = {}; // array that holds data for each square of the tic tac toe board

	bool game_over = false; // tracks if user wants game to end
	bool round_over = false; // tracks if the round is over yet

	int round_num = 0; // how many rounds of tic tac toe have been played so far
	int x_score = 0; // score for X player
	int o_score = 0; // score for O player
	int num_of_ties = 0; // number of tie games so far

	// welcome user
	cout << "Welcome to Tic Tac Toe!" << endl;

	// setup game for first time
	round_setup(round_num, player_id, board_array);
	// print starting board
	print_board(board_array);

	// as long as the user wants to keep playing, run rounds
	while (game_over == false) {

		// if a round just finished and the user wnats to keep playing, reset up the board and print it again
		if (round_over == true) {
			round_setup(round_num, player_id, board_array);
			print_board(board_array);
			round_over = false;
		}

		// take input from user and insert an "X" or "O" at the chosen valid spot
		take_input(player_id, board_array);

		// after a move has been made, check if there is a winning combo or if there are no more spots available resulting in a tie
		check_board(board_array, round_over, round_num, x_score, o_score, num_of_ties);

		// if the round is over, ask user if they want to keep playing: if not, print scores and set game_over to true, exiting loop
		if (round_over == true) {
			end_round(x_score, o_score, num_of_ties, game_over);
		}
	}
	// if run_game executes, return true to main function
	return true;
}

// set up first turn and board for a new round of tic tac toe
void round_setup(int round_num, string& player_id, string* board_array) {

	// if an even number of rounds have been played, let X player take the first turn, else let O player take first turn
	if (round_num % 2 == 0) {
		player_id = "X";
	} 
	else {
		player_id = "O";
	}

	// output which player takes first turn
	cout << "New round! " << player_id << " player goes first!" << endl;

	// fill board_array with placeholder number values from 1 to 16 inclusive (one for each square on the board)
	for (int index = 0; index < 16; index++) {
		board_array[index] = to_string(index + 1);
	}
}

// prompt appropriate player to input their move, and validate that it is an int corresponding to an unoccupied square on the board, then place an "X" or "O"
void take_input(string& player_id, string* board_array){
	// initialize variables
	string player_input_string = ""; // holds user's input as a temporary string
	int player_input_int = 0; // holds user's input once confirmed an int
	bool input_is_valid = false; // tracks if user's input is valid

	// prompt appropriate player to input move, store input as a string, and echo back to them
	cout << player_id << " player please input your move: ";
	cin >> player_input_string;
	cout << "You inputted: " << player_input_string << endl;

	// validate input and assign an X or O to appropriate unoccupied board space from 1 to 16 inclusive, prompt user repeatedly until valid input is entered
	while (input_is_valid == false){

		// try converting player_input_string to an int, catch the exception if it cannot be converted to an int
		try {
			player_input_int = stoi(player_input_string);
		}
		catch (...) {
			// string could not be read properly as an int
		}

		if (player_input_int <= 16 && player_input_int >= 1 && board_array[player_input_int - 1] != "X" && board_array[player_input_int - 1] != "O") {
			input_is_valid = true;
			board_array[player_input_int - 1] = player_id;
		}
		else {
			// if input is invalid, clear previous input, and take all input until user hits enter
			cin.clear();
			cin.ignore(256, '\n');

			// prompt user for valid input, store input, and echo back
			cout << "Please input a valid move: ";
			cin >> player_input_string;
			cout << "You inputted: " << player_input_string << endl;
		}
	}

	// after each move, switch turns
	if (player_id == "O") {
		player_id = "X";
	}
	else {
		player_id = "O";
	}

	// print the updated game board
	print_board(board_array);
}

// print game board to console
void print_board(string* board_array) {

	// add a new line of space
	cout << endl;

	// print each element in board_array in 4 seperate rows and columns
	for (int index = 0; index < 16; index++) {
		cout << setw(5) << board_array[index];

		if ((index + 1) % 4 == 0) {
			cout << endl;
		}
	}
	// add a new line of space
	cout << endl;
}

// check to see if there's a winning combo or no more empty squares on board
void check_board(string* board_array, bool& round_over, int& round_num, int& x_score, int& o_score, int& num_of_ties){
	// initialize variables
	bool winning_combo = false; // tracks if a winning combo has been found
	string player_won = ""; // holds player_id of winning player (either "X" or "O")

	// check all 4 rows, all 4 columns, and each of the 2 diagonals to see if there are 4 values that are the same, then save the value ("X" or "O") to player_won
	for (int counter = 0; counter < 4; counter++) {

		// check each row for horizontal winning combos
		if (board_array[4 * counter] == board_array[4 * counter + 1] && board_array[4 * counter] == board_array[4 * counter + 2] && board_array[4 * counter] == board_array[4 * counter + 3]) {
			winning_combo = true;
			if (board_array[4 * counter] == "X") {
				player_won = "X";
			}
			else {
				player_won = "O";
			}
		}
		// check each column for vertical winning combos
		else if (board_array[counter] == board_array[counter + 4] && board_array[counter] == board_array[counter + 8] && board_array[counter] == board_array[counter + 12]) {
			winning_combo = true;
			if (board_array[counter] == "X") {
				player_won = "X";
			}
			else {
				player_won = "O";
			}
		}
		// check the diagonal beginning in the top left corner of the 4 by 4 for a diagonal winning combo
		else if (board_array[0] == board_array[5] && board_array[0] == board_array[10] && board_array[0] == board_array[15]) {
			winning_combo = true;
			if (board_array[0] == "X") {
				player_won = "X";
			}
			else {
				player_won = "O";
			}
		}
		// check the diagonal beginning in the top right corner of the 4 by 4 for a diagonal winning combo
		else if (board_array[3] == board_array[6] && board_array[3] == board_array[9] && board_array[3] == board_array[12]) {
			winning_combo = true;
			if (board_array[3] == "X") {
				player_won = "X";
			}
			else {
				player_won = "O";
			}
		}
	}

	// if a winning combo has been found, set round_over to true, increment round_num and increase score for winning player, announcing the win
	if (winning_combo == true) {
		round_over = true;
		round_num++;
		if (player_won == "X") {
			x_score++;
			cout << "X player won!" << endl;
		}
		else {
			o_score++;
			cout << "O player won!" << endl;
		}
	}
	// if a winning combo has not been found, check to see if there are any available spaces to play 
	else {

		// initialize variable
		bool spaces_available = false; // tracks if there are any spaces available, assume false

		// for each element of board_array, check if it is occupied by an "X" or "O"
		for (int index = 0; index < 16; index++) {

			// if any are found that are not occupied, then there exists an available space
			if (board_array[index] != "X" && board_array[index] != "O") {
				spaces_available = true;
			}
		}

		// if above loop iterates and finds no unoccupied spaces, then the board is full and it is a tie
		if (spaces_available == false) {
			// output tie message, end round and increment round_num and num_of_ties
			cout << "It's a tie!!!" << endl;
			round_over = true;
			round_num++;
			num_of_ties++;
		}
	}
}

// determine if user wishes to continue playing and output score if they do not
void end_round(int x_score, int y_score, int num_of_ties, bool& game_over) {

	// initialize variables
	string user_input = ""; // holds user input
	bool input_is_valid = false; // tracks if input is valid or not

	// ask user if they want to play again, hold input in user_input and echo back
	cout << "Do you want to play again? Please input \"Yes\" or \"No\": ";
	cin >> user_input;
	cout << "You inputted: " << user_input << endl;

	// until user gives valid input and action can be taken, run loop
	while (input_is_valid == false) {
		// if user has entered "Yes", this is valid, simply let while loop in run_game continue iterating and it will set up a new round
		if (user_input == "Yes") {

			input_is_valid = true;

			// output to user that they will be playing again
			cout << "Great! New round coming right up!" << endl << endl;
		}
		// if user has entered "No", this is valid, set game_over to true to break loop in run_game and print finals scores and number of ties
		else if (user_input == "No") {
			input_is_valid = true;
			game_over = true;

			cout << "Ok! Game over! Here are the final stats:" << endl << endl;

			cout << "Number of victories for X player: " << x_score << endl;
			cout << "Number of victories for O player: " << y_score << endl;
			cout << "Number of ties: " << num_of_ties << endl;
		}
		// if user did NOT enter "Yes" or "No", this is invalid, and prompt them to input a valid answer, storing this in user_input and echoing back
		else {
			cout << "Please input a valid answer: ";
			cin >> user_input;
			cout << "You inputted: " << user_input << endl;
		}
	}
}