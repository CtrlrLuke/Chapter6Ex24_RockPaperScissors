/*
File Name: Chapter6Ex24_RockPaperScissors.cpp
Developer/Programmer: Luke Pritchard
Date: 05/04/2025
Requirements:
- User plays rock/paper/scissors against the computer
- Ask for player's name once
- Count how many rounds the player wins
- Use a sentinel loop ("do again?") to repeat the game
- All input validated; modular design with 3+ functions
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
bool AskToPlayAgain();
string GetPlayerName();

/*
   main
   Gets player name, tracks win count, and loops using sentinel ("Play again?")
*/
int main()
{
    srand(static_cast<unsigned>(time(0))); // Seed RNG
    string playerName = GetPlayerName();
    int playerWins = 0;

    bool play = true;

    while (play)
    {
        string userChoice = GetUserChoice();
        string computerChoice = GetComputerChoice();

        cout << "Computer chose: " << computerChoice << endl;

        string result = DetermineWinner(userChoice, computerChoice);
        cout << result << endl;

        if (result == "You win!")
            playerWins++;

        play = AskToPlayAgain();
    }

    cout << "\nThanks for playing, " << playerName << "!\n";
    cout << "Total wins: " << playerWins << endl;

    return 0;
}

/*
   GetPlayerName
   Prompts for and returns the player's name
*/
string GetPlayerName()
{
    string name;
    cout << "Enter your name: ";
    getline(cin, name);
    while (name.empty())
    {
        cout << "ERROR: Name cannot be blank. Enter your name: ";
        getline(cin, name);
    }
    return name;
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
        cout << "\nEnter your choice (rock, paper, or scissors): ";
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
   Prompts user with sentinel-style loop control.
*/
bool AskToPlayAgain()
{
    string input;
    while (true)
    {
        cout << "\nDo you want to play again? (Y/N): ";
        getline(cin, input);

        if (input.length() == 1)
        {
            char c = toupper(input[0]);
            if (c == 'Y') return true;
            if (c == 'N') return false;
        }

        cout << "ERROR: Enter Y or N.\n";
    }
}