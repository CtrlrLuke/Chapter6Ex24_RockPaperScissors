/*
File Name: Chapter6Ex24_RockPaperScissors.cpp
Developer/Programmer: Luke Pritchard
Date: 05/04/2025
Requirements:
- Computer randomly chooses rock, paper, or scissors
- User inputs choice (validated)
- Compare choices and determine winner
- Repeatable structure using modular functions
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function Prototypes
string GetUserChoice();
string GetComputerChoice();
string DetermineWinner(const string& user, const string& computer);
char AskToPlayAgain();

/*
   main
   Repeats the game loop until the user chooses not to play again.
*/
int main()
{
    srand(static_cast<unsigned>(time(0))); // Seed RNG
    char playAgain;

    do {
        string userChoice = GetUserChoice();
        string computerChoice = GetComputerChoice();

        cout << "Computer chose: " << computerChoice << endl;

        string result = DetermineWinner(userChoice, computerChoice);
        cout << result << endl;

        playAgain = AskToPlayAgain();

    } while (playAgain == 'Y');

    cout << "Thanks for playing!\n";
    return 0;
}

/*
   GetUserChoice
   Prompts the user to enter rock, paper, or scissors. Validates input.
*/
string GetUserChoice()
{
    string input;
    while (true)
    {
        cout << "Enter your choice (rock, paper, or scissors): ";
        getline(cin, input);

        // Convert to lowercase manually if needed
        for (char& c : input)
            c = tolower(c);

        if (input == "rock" || input == "paper" || input == "scissors")
            return input;

        cout << "ERROR: Invalid choice. Please type rock, paper, or scissors.\n";
    }
}

/*
   GetComputerChoice
   Returns a random choice from rock, paper, or scissors.
*/
string GetComputerChoice()
{
    int roll = rand() % 3 + 1;
    if (roll == 1) return "rock";
    else if (roll == 2) return "paper";
    else return "scissors";
}

/*
   DetermineWinner
   Compares user and computer choice to determine outcome.
*/
string DetermineWinner(const string& user, const string& computer)
{
    if (user == computer)
        return "It's a tie! Play again.";

    if ((user == "rock" && computer == "scissors") ||
        (user == "scissors" && computer == "paper") ||
        (user == "paper" && computer == "rock"))
        return "You win!";

    return "Computer wins!";
}

/*
   AskToPlayAgain
   Prompts the user to play again (Y/N). Validates input.
*/
char AskToPlayAgain()
{
    string input;
    while (true)
    {
        cout << "Would you like to play again? (Y/N): ";
        getline(cin, input);

        if (input.length() == 1)
        {
            char c = toupper(input[0]);
            if (c == 'Y' || c == 'N')
                return c;
        }

        cout << "ERROR: Enter Y or N.\n";
    }
}
