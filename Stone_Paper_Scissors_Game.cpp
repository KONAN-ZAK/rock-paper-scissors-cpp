#include<iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Enum for player/computer choices
enum enChoice { stone = 1, paper = 2, scissors = 3 };

// Enum for winner of a round
enum enWinner { player = 1, computer = 2, draw = 3 };

// Structure to store one round data
struct stRound {
	short round = 0;
	enChoice playerChoice;
	enChoice computerChoice;
	enWinner roundWinner;
};

// Structure to store final game results
struct stGame {
	short rounds = 0;
	short playerWonTimes = 0;
	short ComputerWonTimes = 0;
	short DrawTimes = 0;
	string gameWinner = "";
};

//_________________________________________

// Creates tab spacing for formatting output
string Tab(short number) {
	string tab = "";
	for (int i = 1; i <= number; i++)
	{
		tab += "\t";
	}
	return tab;
}

// Prints final game statistics
void print_GameOverResults(stGame gameResults) {
	cout << Tab(4) << "Game Rounds:        " << gameResults.rounds << endl;
	cout << Tab(4) << "Player won Times:   " << gameResults.playerWonTimes << endl;
	cout << Tab(4) << "Computer won Times: " << gameResults.ComputerWonTimes << endl;
	cout << Tab(4) << "Draw Times:         " << gameResults.DrawTimes << endl;
	cout << Tab(4) << "Final Winner:       " << gameResults.gameWinner << endl;
	cout << Tab(3) << "__________________________________________________________________________________________\n\n\n";
}

// Displays game over header
void final_ResultCard() {
	cout << "\n\n\n" << Tab(3) << "__________________________________________________________________________________________\n\n";
	cout << Tab(7) << "+ + +  G A M E   O V E R  + + + \n\n";
	cout << Tab(3) << "__________________________________________________________________________________________\n\n";
	cout << Tab(3) << "_________________________________________ Game Results ___________________________________\n\n\n";
}

// Changes console color and plays sound depending on winner
void play_ScreenActions(enWinner winner) {
	switch (winner)
	{
	case enWinner::player:
		system("color 2F"); // Green
		break;
	case enWinner::computer:
		system("color 4F"); // Red
		cout << "\a";        // Beep sound
		break;
	case enWinner::draw:
		system("color 6F"); // Yellow
		break;
	}
}

// Determines final game winner based on win counts
string findFinalWinnerName(short playerWonTimes, short computerWonTimes) {
	if (playerWonTimes == computerWonTimes)
	{
		play_ScreenActions(enWinner::draw);
		return "Draw";
	}
	else if (computerWonTimes > playerWonTimes) {
		play_ScreenActions(enWinner::computer);
		return "Computer";
	}
	else
	{
		play_ScreenActions(enWinner::player);
		return "Player";
	}
}

// Fills final game result structure
stGame fillFinalResults(short GameRounds, short playerWonTimes, short computerWonTimes, short draw) {
	stGame gameResults;

	gameResults.ComputerWonTimes = computerWonTimes;
	gameResults.playerWonTimes = playerWonTimes;
	gameResults.DrawTimes = draw;
	gameResults.rounds = GameRounds;
	gameResults.gameWinner = findFinalWinnerName(playerWonTimes, computerWonTimes);

	return gameResults;
}

// Converts winner enum to readable string
string convertEnums_WinnerToName(enWinner winner) {
	switch (winner) {
	case enWinner::player:
		return "[User]";
	case enWinner::computer:
		return "[Computer]";
	case enWinner::draw:
		return "[Draw]";
	default:
		return "Not Found!";
	}
}

// Converts choice enum to readable string
string convertEnums_choiceToName(enChoice choice) {
	switch (choice) {
	case enChoice::stone:
		return "Rock";
	case enChoice::paper:
		return "Paper";
	case enChoice::scissors:
		return "Scissors";
	default:
		return "Not Found!";
	}
}

// Prints details of each round
void printRoundResult(stRound roundInfo) {
	cout << "\n________________ Round [" << roundInfo.round << "] ________________\n\n";
	cout << "Player Choice   : " << convertEnums_choiceToName(roundInfo.playerChoice) << endl;
	cout << "Computer Choice : " << convertEnums_choiceToName(roundInfo.computerChoice) << endl;
	cout << "Round Winner    : " << convertEnums_WinnerToName(roundInfo.roundWinner) << endl;
	cout << "\n___________________________________________\n\n";
}

// Updates win counters based on round result
void calculate_WinningTimes(enWinner roundWinner, unsigned short& playerWonTimes, unsigned short& computerWonTimes, unsigned short& draw) {
	if (roundWinner == enWinner::player)
	{
		play_ScreenActions(enWinner::player);
		playerWonTimes++;
	}
	else if (roundWinner == enWinner::computer)
	{
		play_ScreenActions(enWinner::computer);
		computerWonTimes++;
	}
	else
	{
		play_ScreenActions(enWinner::draw);
		draw++;
	}
}

// Determines winner of a round
enWinner findRoundWinner(stRound roundInfo) {
	if (roundInfo.computerChoice == roundInfo.playerChoice)
		return enWinner::draw;

	switch (roundInfo.playerChoice)
	{
	case enChoice::stone:
		return (roundInfo.computerChoice == enChoice::scissors) ? enWinner::player : enWinner::computer;

	case enChoice::paper:
		return (roundInfo.computerChoice == enChoice::stone) ? enWinner::player : enWinner::computer;

	case enChoice::scissors:
		return (roundInfo.computerChoice == enChoice::paper) ? enWinner::player : enWinner::computer;

	default:
		return enWinner::draw;
	}
}

// Generates random number in range
short get_RandomNumber(short from, short to) {
	return rand() % (to - from + 1) + from;
}

// Generates computer choice randomly
enChoice computerChoice() {
	return enChoice(get_RandomNumber(1, 3));
}

// Gets valid user input
enChoice userChoice() {
	unsigned short userChoice;
	do
	{
		cout << "Your Choice : [1]Stone  [2]Paper  [3]Scissors ? ";
		cin >> userChoice;
	} while (userChoice > 3 || userChoice < 1);

	return enChoice(userChoice);
}

// Runs all rounds and returns final results
stGame startRounds(short GameRounds) {
	stRound roundInfo;
	unsigned short playerWonTimes = 0, computerWonTimes = 0, draw = 0;

	for (short round = 1; round <= GameRounds; round++)
	{
		cout << "\nRound [" << round << "] Began:\n";

		roundInfo.round = round;
		roundInfo.computerChoice = computerChoice();
		roundInfo.playerChoice = userChoice();
		roundInfo.roundWinner = findRoundWinner(roundInfo);

		printRoundResult(roundInfo);

		// Update counters
		calculate_WinningTimes(roundInfo.roundWinner, playerWonTimes, computerWonTimes, draw);
	}

	return fillFinalResults(GameRounds, playerWonTimes, computerWonTimes, draw);
}

//_________________________________________

// Ask user to play again
bool playAgain() {
	char choice;

	do {
		cout << Tab(3) << "Do you want to play again? (Y , N): ";
		cin >> choice;

		if (choice == 'Y' || choice == 'y')
			return true;
	} while (choice != 'N' && choice != 'n');

	return false;
}

// Ask user for number of rounds
short howManyRounds() {
	short rounds;
	do
	{
		cout << "How many Rounds Do you want to play from 1 to 10 ?";
		cin >> rounds;
	} while (rounds < 1 || rounds > 10);

	return rounds;
}

// Clears screen and resets console color
void resetScreen() {
	system("cls");
	system("color 0F");
}

// Main game loop
void startGame() {
	stGame game;
	short totalRounds = 0;

	do
	{
		resetScreen();

		totalRounds = howManyRounds();
		game = startRounds(totalRounds);

		final_ResultCard();
		print_GameOverResults(game);
	} while (playAgain());
}

//_________________________________________

int main() {
	srand((unsigned)time(NULL)); // Seed random generator

	startGame();

	return 0;
}