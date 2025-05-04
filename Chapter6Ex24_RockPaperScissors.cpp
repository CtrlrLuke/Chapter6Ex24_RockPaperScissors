/*
File Name: Chapter6Ex24_RockPaperScissors
Developer/Programmer: Luke Pritchard
Date: 05/04/2025
Requirements:
- Show menu: view scores, play game, delete scores, exit
- After each session, save player name + best score
- Validate input
- Use modular structure
- Store score data in Scores.txt
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <limits>

using namespace std;

// Function Prototypes
void DisplayMenu();
int GetMenuChoice();
void PlayGame();
void ViewScores();
void DeleteScores();
string GetPlayerName();
string GetUserChoice();
string GetComputerChoice();
string DetermineWinner(const string&, const string&);
bool AskToPlayAgain();
void SaveScore(const string&, int);

/*
   main
   Displays menu and processes menu choices.
*/
int main()
{
    srand(static_cast<unsigned>(time(0)));

    bool running = true;
    while (running)
    {
        DisplayMenu();
        int choice = GetMenuChoice();

        switch (choice)
        {
        case 1:
            ViewScores();
            break;
        case 2:
            PlayGame();
            break;
        case 3:
            DeleteScores();
            break;
        case 4:
            running = false;
            cout << "Goodbye!" << endl;
            break;
        }
    }

    return 0;
}

/*
   DisplayMenu
   Shows the main menu
*/
void DisplayMenu()
{
    cout << "\n=== Rock, Paper, Scissors Menu ===\n";
    cout << "1. View Previous Scores\n";
    cout << "2. Play New Game\n";
    cout << "3. Delete All Scores\n";
    cout << "4. Exit\n";
}

/*
   GetMenuChoice
   Validates and returns a menu option (1–4)
*/
int GetMenuChoice()
{
    string input;
    int choice;

    while (true)
    {
        cout << "Enter your choice (1-4): ";
        getline(cin, input);

        if (input.length() == 1 && input[0] >= '1' && input[0] <= '4')
        {
            choice = input[0] - '0';
            return choice;
        }

        cout << "ERROR: Enter a number between 1 and 4.\n";
    }
}

/*
   ViewScores
   Reads and displays scores from file
*/
void ViewScores()
{
    ifstream file("Scores.txt");
    string line;

    cout << "\n--- Previous Scores ---\n";

    if (!file)
    {
        cout << "(No scores found)\n";
        return;
    }

    bool empty = true;
    while (getline(file, line))
    {
        cout << line << endl;
        empty = false;
    }

    if (empty)
        cout << "(No scores found)\n";

    file.close();
}

/*
   DeleteScores
   Removes the Scores.txt file
*/
void DeleteScores()
{
    if (remove("Scores.txt") == 0)
        cout << "All scores deleted successfully.\n";
    else
        cout << "No scores to delete.\n";
}

/*
   PlayGame
   Plays one full session and saves the best score
*/
void PlayGame()
{
    string name = GetPlayerName();
    int wins = 0;

    do
    {
        string user = GetUserChoice();
        string cpu = GetComputerChoice();

        cout << "Computer chose: " << cpu << endl;
        string result = DetermineWinner(user, cpu);
        cout << result << endl;

        if (result == "You win!")
            wins++;

    } while (AskToPlayAgain());

    cout << "\nSession ended. Wins: " << wins << endl;
    SaveScore(name, wins);
}

/*
   SaveScore
   Appends name and score to Scores.txt
*/
void SaveScore(const string& name, int wins)
{
    ofstream file("Scores.txt", ios::app);
    if (file)
    {
        file << name << " - " << wins << " wins" << endl;
        file.close();
    }
    else
    {
        cout << "ERROR: Could not write to Scores.txt\n";
    }
}

/*
   GetPlayerName
   Gets and validates player name
*/
string GetPlayerName()
{
    string name;
    cout << "Enter your name: ";
    getline(cin, name);

    while (name.empty())
    {
        cout << "ERROR: Name cannot be blank. Try again: ";
        getline(cin, name);
    }

    return name;
}

/*
   GetUserChoice
   Gets rock/paper/scissors with validation
*/
string GetUserChoice()
{
    string input;
    while (true)
    {
        cout << "\nEnter rock, paper, or scissors: ";
        getline(cin, input);

        for (char& c : input) c = tolower(c);

        if (input == "rock" || input == "paper" || input == "scissors")
            return input;

        cout << "ERROR: Invalid choice.\n";
    }
}

/*
   GetComputerChoice
   Randomly returns rock, paper, or scissors
*/
string GetComputerChoice()
{
    int roll = rand() % 3 + 1;
    return (roll == 1) ? "rock" : (roll == 2) ? "paper" : "scissors";
}

/*
   DetermineWinner
   Returns outcome as string
*/
string DetermineWinner(const string& user, const string& cpu)
{
    if (user == cpu)
        return "It's a tie!";

    if ((user == "rock" && cpu == "scissors") ||
        (user == "scissors" && cpu == "paper") ||
        (user == "paper" && cpu == "rock"))
        return "You win!";

    return "Computer wins!";
}

/*
   AskToPlayAgain
   Prompts user with Y/N
*/
bool AskToPlayAgain()
{
    string input;
    while (true)
    {
        cout << "Play again? (Y/N): ";
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
