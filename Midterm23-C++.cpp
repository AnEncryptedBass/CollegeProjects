/******************************************************************************************************************
    Eric Bass - C++ Programing - MIDTERM TASK 3

    Task 3 - Edit your game to prompt the user for a game file. The file should be a txt file named plays.txt.
             If the user selects a game file, read from the file and determine the winner. The format of the file
             should be three lines of X and O with single spaces in between.  There should only be one clear winner
             from each game file.  Output the winner the same as in task 1. An example gamefile is shown below.

                X O X

                O X O

                O O X


******************************************************************************************************************/
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <windows.h>

using namespace std;

// Board for TicTacToe
void displayGame(char gameBoard[3][3]) {

    cout << "\t-------------" << endl;
    cout << "\t| " << gameBoard[0][0] << " | " << gameBoard[0][1] << " | " << gameBoard[0][2] << " |\n";
    cout << "\t| " << gameBoard[1][0] << " | " << gameBoard[1][1] << " | " << gameBoard[1][2] << " |\n";
    cout << "\t| " << gameBoard[2][0] << " | " << gameBoard[2][1] << " | " << gameBoard[2][2] << " |\n";
    cout << "\t-------------";
}

// Checks for Win using true or false
bool win(char gameBoard[3][3], char gamePiece) {

    // Checks Horizontal for 3 in row
    for (int i = 0; i < 3; i++) {
        if (gameBoard[i][0] == gamePiece &&
            gameBoard[i][1] == gamePiece &&
            gameBoard[i][2] == gamePiece) {
            return true;
        }
    }
    // Checks Verticly for 3 in row
    for (int i = 0; i < 3; i++) {
        if (gameBoard[0][i] == gamePiece &&
            gameBoard[1][i] == gamePiece &&
            gameBoard[2][i] == gamePiece) {
            return true;
        }
    }
    // Checks Diagonal for 3 in row
    for (int i = 0; i < 3; i++) {
        if (gameBoard[0][0] == gamePiece &&
            gameBoard[1][1] == gamePiece &&
            gameBoard[2][2] == gamePiece) {
            return true;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (gameBoard[0][2] == gamePiece &&
            gameBoard[1][1] == gamePiece &&
            gameBoard[2][0] == gamePiece) {
            return true;
        }
    }

    return false;
}

// Allows the user to choose from an existing game (.txt) or start reg game
void menu() {
    cout << "\n******** Tic-Tac-Toe Menu ********" << endl;
    cout << "1. Start a new game" << endl;
    cout << "Continues to Tic-Tac-Toe" << endl;


    cout << "\n2. Choose existing game" << endl;
    cout << "Opens File Exploror - Must have a file named 'plays.txt' else it will not show." << endl;

    cout << "\n3. Quit" << endl;
    cout << "Stops program" << endl;

    int choice;
    while (true) {
        cout << "\nEnter Choice 1, 2, or 3 to continue: ";
        cin >> choice;

        // start reg
        if (choice == 1) {
            break;
        }

        // Opens file explorer, had to look this one up
        else if (choice == 2) {

            OPENFILENAME ofn = { 0 };
            TCHAR szFile[MAX_PATH] = { 0 };
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = NULL;
            ofn.lpstrFile = szFile;
            ofn.lpstrFile[0] = '\0';
            ofn.nMaxFile = sizeof(szFile);
            // Filters to show .txt files
            ofn.lpstrFilter = TEXT("Text Files (plays.txt)\0*plays.txt\0");
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
            // Applies .txt if user doesnt add it
            ofn.lpstrDefExt = TEXT("txt");
            // Explorer Text at top of window 
            ofn.lpstrTitle = TEXT("Tic-Tac-Toe - Please select your 'plays.txt' game file to continue.");

            if (GetOpenFileName(&ofn) == TRUE) {
                ifstream infile(ofn.lpstrFile);

                // Read game board from file
                char gameBoard[3][3];
                char c;
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        infile >> c;
                        gameBoard[i][j] = c;
                    }
                }

                displayGame(gameBoard);

                // Check for winner
                if (win(gameBoard, 'X')) {
                    cout << "\tX wins." << endl;
                }
                else if (win(gameBoard, 'O')) {
                    cout << "\tO wins." << endl;
                }
                else {
                    cout << "\tTie" << endl;
                }
            }
            else {
                cout << "Unable to open file." << endl;
            }

            // Keep looping after file read or error message
            continue;
        }
        else if (choice == 3) {
            cout << "\nThanks for Playing!" << endl;
            // Return 0 leaves error - must use exit
            exit(0);
        }
        else {
            cout << "ERROR - Only select '1', '2', or '3'" << endl;
        }
    }
}
int main() {

    char fileName[100] = "plays.txt";
    wchar_t wideFileName[100];
    int size = MultiByteToWideChar(CP_UTF8, 0, fileName, -1, NULL, 0);
    if (size > 0) {
        wchar_t* wideFileName = new wchar_t[size];
        if (MultiByteToWideChar(CP_UTF8, 0, fileName, -1, wideFileName, size) > 0) {
        }
        // Free up memory
        delete[] wideFileName;
    }

        // Start
        menu();

        int choice;
        char gamePiece;

        // Game Title
        cout << "\n******** Tic-Tac-Toe ********" << endl;

        // Assigns Numbers to the table                - Game Board Layout / Table
        char gameBoard[3][3] = { {'1', '2', '3'},      // [0][0]  [0][1]  [0][2]
                                 {'4', '5', '6'},      // [1][0]  [1][1]  [1][2]
                                 {'7', '8', '9'} };    // [2][0]  [2][1]  [2][2]    

        // Allows player to choose gamePiece, only allows X and O, and allows lowercase
        while (true) {
            cout << "Select Game Piece - [ X ] or [ O ]: ";
            cin >> gamePiece;
            gamePiece = toupper(gamePiece);
            if (gamePiece == 'X' || gamePiece == 'O') {
                break;
            }
            else {
                cout << "ERROR - Enter 'X' or 'O', Selection is *not* case sensitive." << endl;
            }
        }

        // player 1 always starts first
        char player1 = gamePiece;
        char player2 = (gamePiece == 'X') ? 'O' : 'X';

        cout << endl;
        cout << "Player 1 Selected: " << player1 << endl;


        // Calls Game Board   
        displayGame(gameBoard);

        // Swaps turns [X] [O] - loops 1 - 9 (max moves), "i % 2 == 0" is player swap
        for (int i = 0; i < 9; i++) {

            // Displays correct player 1 selection 
            if (i % 2 == 0) {
                gamePiece = player1;
                cout << endl;
                cout << "Player 1: [ " << gamePiece << " ] " << "- Enter Board Number: ";
            }
            else {
                gamePiece = player2;
                cout << endl;
                cout << "Player 2: [ " << gamePiece << " ] " << "- Enter Board Number: ";
            }

            cin >> choice;

            // gameBoard Selection
            if (choice == 1) {
                gameBoard[0][0] = gamePiece;
            }
            else if (choice == 2) {
                gameBoard[0][1] = gamePiece;
            }
            else if (choice == 3) {
                gameBoard[0][2] = gamePiece;
            }
            else if (choice == 4) {
                gameBoard[1][0] = gamePiece;
            }
            else if (choice == 5) {
                gameBoard[1][1] = gamePiece;
            }
            else if (choice == 6) {
                gameBoard[1][2] = gamePiece;
            }
            else if (choice == 7) {
                gameBoard[2][0] = gamePiece;
            }
            else if (choice == 8) {
                gameBoard[2][1] = gamePiece;
            }
            else if (choice == 9) {
                gameBoard[2][2] = gamePiece;
            }

            // Updates Game Board
            displayGame(gameBoard);

            // Calls 'bool win' to check for win
            if (win(gameBoard, gamePiece)) {
                if (i % 2 == 0) {
                    cout << endl;
                    cout << "Player 1: [ " << player1 << " ]" << " wins." << endl;
                    break;
                }
                else {
                    cout << endl;
                    cout << "Player 2: [ " << player2 << " ]" << " wins." << endl;
                    break;
                }
            }
            else if (i == 9) {
                cout << endl;
                cout << "No one wins";
                break;
            }
        }

        // loops menu
        char playAgain;
        while (true) {
            cout << "\nShall we play again? Y/N: ";
            cin >> playAgain;
            
            // This loops you back
            if (playAgain == 'Y' || playAgain == 'y') {
                main();
                break;
            }
            else if (playAgain == 'N' || playAgain == 'n') {
                return 0;
            }
            else {
                cout << "Error - Please enter 'Y' or 'N'." << endl;
            }
        }
        return 0;
    }