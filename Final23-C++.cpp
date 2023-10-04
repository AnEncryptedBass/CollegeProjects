/******************************************************************************************************************
    Eric Bass - C++ Programing - FINAL - MAIN

    Building on your tic-tac-toe game you are to create a working connect 4 game.
    You should design it to be an exact digital representation of the popular game
    which has the same number of rows and columns.  You should design an interface
    that is logical and easy to understand.  It should clearly describe how the user
    should interact with it.

    [X] The code will be graded for spacing and commenting.  This will be 20% of the grade.

    [X] The efficiency of your code will be graded.  It will represent 10% of the grade.

    [X] The overall appearance and board layout will be 10% of the grade.

    [X] The ability to play again once the game determines a winner will be worth 20%.

    [X] The ability to select color or character will be 10% of the grade.

    [X] The functionality of the code will be the remaining 20% of the grade.

    [] The final 10% will be a video of you explaining your code. You need to show your
    code on screen during the explanation to get full credit.

    [X] A bonus of 5 points is available if your are able to use colors for the game pieces.
    This does not require use of the same character,

    [] an additional 5 points will be given if you can determine the winner based on color,
    or other means, rather thancharacter.

    While online research is acceptable, you should develop your own code to achieve
    this program.  Copying and pasting could result in a 0.


******************************************************************************************************************/
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

/*********** USER INTERFACE FUNCTIONS ***********/

// User Interface - Choose Game Piece
char chooseGamePiece(const string& prompt) {
    string input;

    // Prompt for user input
    cout << prompt;
    getline(cin, input);

    // Check if valid piece
    while (input.length() != 1 || !isalpha(input[0])) {
        // Error message
        cout << "Invalid input. Choose a letter from A to Z: ";
        getline(cin, input);
    }

    // Convert to uppercase
    input[0] = toupper(input[0]);

    // Return GamePiece
    return input[0];
}


// User Interface - Choose Game Piece Color
string chooseColor(string excludedColor = "") {

    int color;
    string input;

    // Display Possible Colors
    cout << "1. Red" << endl;
    cout << "2. Green" << endl;
    cout << "3. Yellow" << endl;
    cout << "4. Blue" << endl;
    cout << "5. Magenta" << endl;
    cout << "6. Cyan" << endl;

    // Prompt User to pick color
    cout << "\nChoose a color for your game piece (1-6): ";
    cin >> input;

    // Error Message - Not valid color num (1-6)
    while (input.length() != 1 || !isdigit(input[0]) || stoi(input) < 1 || stoi(input) > 6) {
        cout << "Invalid input. Choose a color for your game piece (1-6): ";
        cin >> input;
    }

    color = stoi(input);

    // Color Choice
    string colorCode;
    switch (color) {
        // Red
    case 1: colorCode = "\033[31m"; break;
        // Green
    case 2: colorCode = "\033[32m"; break;
        // Yellow
    case 3: colorCode = "\033[33m"; break;
        // Blue
    case 4: colorCode = "\033[34m"; break;
        // Magenta
    case 5: colorCode = "\033[35m"; break;
        // Cyan
    case 6: colorCode = "\033[36m"; break;
    }

    // Check if the chosen color is the same as the excluded color
    if (colorCode == excludedColor) {
        return chooseColor(excludedColor);
    }
    else {
        return colorCode;
    }
}

// User Interface - Choose Board Placement
int userInput() {

    int column;
    string input;

    // Prompt User to Assign Game Piece to Board
    cout << "Enter a column (0-6): ";
    getline(cin, input);

    // Limits Input from 0 to 6
    while (input.length() != 1 || input[0] < '0' || input[0] > '6') {
        // Error Message
        cout << "Invalid input. Enter a column (0-6): ";
        getline(cin, input);
    }

    // Converts Char to Number
    column = input[0] - '0';
    return column;
}

// User Interface - Loop Game
bool playAgain() {

    string input;

    // Prompt User to Input answer to Start a new game
    cout << "Do you want to play again? (Y/N): ";
    getline(cin, input);

    // Limits Input to Y and N, Allows lowercase
    while (input.length() != 1 || (toupper(input[0]) != 'Y' && toupper(input[0]) != 'N')) {
        // Error Message
        cout << "Invalid input. Do you want to play again? (Y/N): ";
        getline(cin, input);
    }

    return toupper(input[0]) == 'Y';
}

/*********** GAME LOGIC FUNCTIONS ***********/

// Game Logic - Check For Winner
bool winCF(char gameBoardCF[6][7], char gamePiece) {

    // Main Function of each - Check for 4 in a row
    // Checks Horizontal
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            if (gameBoardCF[i][j] == gamePiece &&
                gameBoardCF[i][j + 1] == gamePiece &&
                gameBoardCF[i][j + 2] == gamePiece &&
                gameBoardCF[i][j + 3] == gamePiece) {
                return true;
            }
        }
    }

    // Checks Vertical
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            if (gameBoardCF[i][j] == gamePiece &&
                gameBoardCF[i + 1][j] == gamePiece &&
                gameBoardCF[i + 2][j] == gamePiece &&
                gameBoardCF[i + 3][j] == gamePiece) {
                return true;
            }
        }
    }

    // Checks Diagonal - Top Left to Bottom Right
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            if (gameBoardCF[i][j] == gamePiece &&
                gameBoardCF[i + 1][j + 1] == gamePiece &&
                gameBoardCF[i + 2][j + 2] == gamePiece &&
                gameBoardCF[i + 3][j + 3] == gamePiece) {
                return true;
            }
        }
    }

    // Checks Diagonal - Bottom Left to Top Right
    for (int i = 3; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            if (gameBoardCF[i][j] == gamePiece &&
                gameBoardCF[i - 1][j + 1] == gamePiece &&
                gameBoardCF[i - 2][j + 2] == gamePiece &&
                gameBoardCF[i - 3][j + 3] == gamePiece) {
                return true;
            }
        }
    }

    return false;
}

// Game Logic - Check For Full Board
bool isBoardFull(char gameBoardCF[6][7]) {

    // Checks each row 
    for (int i = 0; i < 6; ++i) {
        // Checks each column
        for (int j = 0; j < 7; ++j) {
            // If Blank - Return False 
            if (gameBoardCF[i][j] == ' ') {
                return false;
            }
        }
    }
    // If Full - Return True, Ends Game
    return true;
}

// Game Logic - Allows Placement
bool placement(char gameBoardCF[6][7], int column, char gamePiece) {

    // Places Game Piece to lowest possible blank spot
    for (int row = 5; row >= 0; --row) {
        if (gameBoardCF[row][column] == ' ') {
            gameBoardCF[row][column] = gamePiece;
            return true;
        }
    }
    // If Column is Full - Return False, Keeps from allowing placement of Game Piece
    return false;
}

/*********** DISPLAY FUNCTIONS ***********/

// Display - Game Board
void displayCF(char gameBoardCF[6][7], char gamePiece, const string& player1Color, const string& player2Color, char player1Piece, char player2Piece) {


    // Displays Colored Game Piece 
    auto displayColoredPiece = [&player1Color, &player2Color, &player1Piece, &player2Piece](char piece) {

        // Player 1
        if (piece == player1Piece) {
            cout << player1Color << piece << "\033[0m";
        }
        // Player 2
        else if (piece == player2Piece) {
            cout << player2Color << piece << "\033[0m";
        }
        // Empty Space
        else {
            cout << piece;
        }
    };

    // Game Board Display
    cout << "\033[96m\n\t\t  Connect 4\033[0m" << endl;
    cout << "\n\t\033[34m-----------------------------\033[0m" << endl;
    // Creates Array
    for (int i = 0; i < 6; i++) {
        cout << "\t\033[34m|\033[0m ";
        for (int j = 0; j < 7; j++) {
            // Displays Game Piece Color
            displayColoredPiece(gameBoardCF[i][j]);
            if (j < 6) {
                // Divider for Game Board Layout
                cout << " \033[34m|\033[0m ";
            }
        }
        cout << " \033[34m|\033[0m";
        cout << endl;
    }
    cout << "\t\033[34m-----------------------------\033[0m";

    // Display Aid - helps User visually see numerical columns
    cout << "\n\033[1;30m\t| " "0" " | " "1" " | " "2" " | " "3" " | " "4" " | " "5" " | " "6" " | \033[0m";

    // Displays Current Player
    cout << "\n\nCurrent player: ";
    // Player 1
    if (gamePiece == player1Piece) {
        cout << player1Color << gamePiece << "\033[0m";
    }
    // Player 2
    else {
        cout << player2Color << gamePiece << "\033[0m";
    }
    cout << endl;
}

/*********** MAIN ***********/

int main() {

    bool continuePlaying;

    do {
        // Calls Game Board - Applies Blank Spaces to Board
        char gameBoardCF[6][7];
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 7; ++j) {
                gameBoardCF[i][j] = ' ';
            }
        }

        int player = 1;
        bool gameOver = false;
        char gamePiece;
        string player1Color, player2Color;

        // Title Art
        cout << "\033[96m   _____                            _     _  _   \n";
        cout << "  / ____|                          | |   | || |  \n";
        cout << " | |     ___  _ __  _ __   ___  ___| |_  | || |_ \n";
        cout << " | |    / _ \\| '_ \\| '_ \\ / _ \\/ __| __| |__   _|\n";
        cout << " | |___| (_) | | | | | | |  __/ (__| |_     | |  \n";
        cout << " \\______\\___/|_| |_|_| |_|\\___|\\___|\\__|    |_|  \n\033[0m";

        // Player 1 - Get Game Peice and Color 
        char player1Piece = chooseGamePiece("\nPlayer 1, choose your game piece (any letter from A to Z): ");
        player1Color = chooseColor();
        cin.ignore();

        // Player 2 - Get Game Peice and Color, Check to make sure Game Piece is not deplicate or Player 1
        char player2Piece;
        do {
            player2Piece = chooseGamePiece("Player 2, choose your game piece (any letter from A to Z, but not the same as Player 1): ");
        } while (player2Piece == player1Piece);

        player2Color = chooseColor(player1Color);
        cin.ignore();

        // Current Player Display
        while (!gameOver) {
            if (player == 1) {
                gamePiece = player1Piece;
            }
            else {
                gamePiece = player2Piece;
            }

            // Calls Main Display
            displayCF(gameBoardCF, gamePiece, player1Color, player2Color, player1Piece, player2Piece);
            // User Input
            int column = userInput();
            // Calls Placement - Checks for full Column
            if (!placement(gameBoardCF, column, gamePiece)) {
                // Error Message 
                cout << "Column is full. Try again." << endl;
                continue;
            }

            // Calls Win - Checks for Winner 
            if (winCF(gameBoardCF, gamePiece)) {
                displayCF(gameBoardCF, gamePiece, player1Color, player2Color, player1Piece, player2Piece);
                // Displays Winner 
                cout << "Player " << player << " wins!" << endl;
                // Ends Game
                gameOver = true;
            }
            // Calls Full Board - Checks for Full Board
            else if (isBoardFull(gameBoardCF)) {
                displayCF(gameBoardCF, gamePiece, player1Color, player2Color, player1Piece, player2Piece);
                // Displays Tie
                cout << "Tie - No one wins" << endl;
                // Ends Game
                gameOver = true;
            }
            else {
                // Swaps between Player 1 and Player 2
                player = 3 - player;
            }
        }

        // Calls play again - Allows for a new game 
        continuePlaying = playAgain();
    } while (continuePlaying);

    return 0;
}
