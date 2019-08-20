#include <iostream>

#define SIZE 9
#define PLAYER 'X'
#define COMP 'O'
#define TIE 't'

/**************************************************************************
 * This is a game of TicTacToe versing the computer.                      *
 * To play, use the keys 1-9 to place in the the spot you would like.     *
 * Use 0 to quit mid game.                                                *
 *                                                                        *
 * move key:                                                              *
 * 1 2 3                                                                  *
 * 4 5 6                                                                  *
 * 7 8 9                                                                  *
 *                                                                        *
 **************************************************************************/

void printBoard(char *board);
int playerMove(const char *board);
int compMove(char *board);
int checkWin(char *board, char who);
char *boardRotate(const char *board);
void newGame(char *board);
int endOfGame(char winner, char *board);



int main(){
    char *board = new char[SIZE];
    std::fill_n(board, SIZE, '-');
    int currentMove;

    newGame(board);

    while(true){
        currentMove = playerMove(board);
        if(currentMove < 0){
            break; // so the player can enter 0 to exit (since player move is -1 and returned, makes < 0 quit)
        }
        board[currentMove] = PLAYER;
        printBoard(board);
        if(checkWin(board, PLAYER) == 1) { //if player won
            if(endOfGame(PLAYER, board) == 0){ //prompt to play again
                return 0; //quit program if they say no
            } else {
                continue; //start again if they say yes (board is reset in endOfGame function).
            }
        } else if (checkWin(board, PLAYER) == 2) { //if there is a tie
            if(endOfGame(TIE, board) == 0){ //prompt tie output,
                return 0; //quit program if they say no
            } else {
                continue; //start again if they say yes (board is reset in the endOfGame function).
            }
        }
        currentMove = compMove(board);
        board[currentMove] = COMP;
        if(checkWin(board, COMP) == 1) { //if comp wins
            printBoard(board); //print the winning board
            if(endOfGame(COMP, board) == 0){
                return 0; //quit if the players doesnt want to play again
            } else {
                continue; //restart if they do.
            }
        } else if (checkWin(board, COMP) == 2) {
            if(endOfGame(TIE, board) == 0){
                return 0;
            } else {
                continue;
            }
        }
        printBoard(board); //print current board state.
    }
    return 0;
}

//states game status, prompts to play again.
int endOfGame(char winner, char *board){
    char ans;

    if(winner == 't'){
        std::cout << "TIE!!!" << std::endl;
    } else {
        std::cout << winner << "'s WIN!!!" << std::endl;
    }

    while (true) {
        std::cout << "Play again? (y/n)" << std::endl;
        std::cin >> ans;
        if (ans == 'y') {
            newGame(board);
            return 1;
        } else if (ans == 'n') {
            return 0;
        } else {
            std::cout << "Please use 'y' or 'n'. Try again." << std::endl;
        }
    }
}

//returns 1 for win, 0 for no win, 2 for tie
int checkWin(char *board, char who){
    for(int i = 0; i < 4; i++) {
        if (board[0] == who && board[4] == who && board[8] == who) { //check for diagonal win
            return 1;
        } else if (board[1] == who && board[4] == who && board[7] == who) { //check for bottom to top win
            return 1;
        } else if (board[0] == who && board[1] == who && board[2] == who) { //check for across the top win
            return 1;
        }
        board = boardRotate(board); //rotate the board so we can check from another angle.
    }
    for(int i = 0; i < SIZE; i++){
        if(board[i] == '-'){ // if there is any blank board spots left, its not a tie, so break and return 0
            break;
        }
        if(i == 8){
            return 2; //if we get all the spots are taken, and no win, then its a tie.
        }
    }
    return 0; //if we get to here, no tie or win.
}

//rotates the current board state.
char *boardRotate(const char *board){
    char *temp = new char[9];
    temp[0] = board[2];
    temp[1] = board[5];
    temp[2] = board[8];
    temp[3] = board[1];
    temp[4] = board[4];
    temp[5] = board[7];
    temp[6] = board[0];
    temp[7] = board[3];
    temp[8] = board[6];

    return temp;
}

// returns computers move
int compMove(char *board){
    std::cout << "Computer's turn: " << std::endl;
    int cornerVals[] = {0, 2, 8, 6};
    int edgeVals[] = {1, 5, 7, 3};

    if (board[0] == '-'){ // if its the first move, take the top left corner.
        return 0;
    } else {
        //all of these statements check if the computer is 1 move from winning. if it is, take that move.
        for (int i = 0; i < 4; i++){
            if (board[0] == COMP && board[1] == COMP && board[2] == '-'){
                return cornerVals[(1 + i) % 4]; // we have to place in the 'pre-rotated' position.
            } else if (board[1] == COMP && board[2] == COMP && board[0] == '-') {
                return cornerVals[(0 + i) % 4];
            } else if (board[1] == COMP && board[4] == COMP && board[7] == '-'){
                return edgeVals[(2 + i) % 4];
            } else if (board[0] == COMP && board[4] == COMP && board[8] == '-'){
                return cornerVals[(2 + i) % 4];
            } else if (board[0] == COMP && board[2] == COMP && board[1] == '-'){
                return edgeVals[(0 + i) % 4];
            }
            board = boardRotate(board); //rotate the board to make it easier to check win conditions.
        }
        for (int i = 0; i < 4; i++){
            //if there is no winning move, look to see if the player is 1 move from winning, and block it.
            if (board[0] == PLAYER && board[1] == PLAYER && board[2] == '-'){
                return cornerVals[(1 + i) % 4];
            } else if (board[1] == PLAYER && board[2] == PLAYER && board[0] == '-') {
                return cornerVals[(0 + i) % 4];
            } else if (board[1] == PLAYER && board[4] == PLAYER && board[7] == '-'){
                return edgeVals[(2 + i) % 4];
            } else if (board[0] == PLAYER && board[4] == PLAYER && board[8] == '-'){
                return cornerVals[(2 + i) % 4];
            } else if (board[0] == PLAYER && board[2] == PLAYER && board[1] == '-'){
                return edgeVals[(0 + i) % 4];
            }
            board = boardRotate(board);
        }
    }
    //if neither of the above conditions are met, then place in an available corner.
    for(int i = 0; i < SIZE; i++){
        if ((i == 2 || i == 6 || i == 8) & board[i] == '-'){
            return i;
        }
    }
    //if nothing is met, place somewhere at random.
    for(int i = 0; i < SIZE; i++){
        if (board[i] == '-'){
            return i;
        }
    }
    return 0; // quit, since something went wrong if we got here (but we wont).
}

//prompts and returns players move.
int playerMove(const char *board){
    int position;

    //keep looping until we get a valid move.
    while(true){
        std::cout << "Which position would you like: ";
        std::cin >> position;

        if (board[position-1] == PLAYER || board[position-1] == COMP){
            std::cout << "That position is already taken. Try again." << std::endl;
        } else if (position >= 0 && position <= 9){
            return (position - 1); // -1 so it fits the array, and the user can used 1-9
        } else {
            std::cout << "Please enter a number between 1-9. Try again." << std::endl;
        }
    }
}

//prints the current board state out.
void printBoard(char *board){
    std::cout << std::endl;
    for(int i = 0; i < SIZE; i++) {
        std::cout << board[i];
        if(i == 2 || i == 5 || i == 8){
            std::cout << std::endl;

        }
        else{
            std::cout << "|";
        }
    }
    std::cout << std::endl;
}

//resets the board array with '-' (blank state).
inline void newGame(char *board){
    std::fill_n(board, SIZE, '-');
    printBoard(board);
}