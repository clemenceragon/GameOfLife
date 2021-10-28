#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

using grid = typename std::vector <std::vector<bool>>;

// Iterations of the game
const int ITERATIONS = 20;

// Grid Initialisation
std::vector<std::vector<bool>> game = {};

// Declaration functions
void printGrid(std::vector<std::vector<bool>>);
void determineGrid(std::vector<std::vector<bool>>&);
int nbNeighboor(grid, int, int);


int main() {
;
	std::string line = {};
	std::ifstream file("grid.txt");

	// Reading the file and filling the grid
	if (file.is_open())
	{
		  while (std::getline(file, line)) {
	    
				std::vector <bool> vectorInit = { };
				vectorInit.reserve(line.size());

				for (auto a : line) {
					vectorInit.push_back(a == '1');
				}
				game.push_back(vectorInit);
			
		  }
	  file.close();
	}
	else {
		std::cout << "Error : File can't be open !" << std::endl;
		return 0;
	}

	// Print the original grid
	printGrid(game);

	for (int i = 0; i < ITERATIONS; i++) {
		determineGrid(game);
		printGrid(game);
		Sleep(1000);
		// sleep(1): // For Unix
		//std::system("clear");
	}


}

// Function for printing the grid
void printGrid(grid game_) {

	for (unsigned int i = 0; i < game_.size(); i++) {

		for (unsigned int j = 0; j < game_[i].size(); j++) {

			if (game_[i][j])
				std::cout << "0";
			else std::cout << ".";
		}

		std::cout << std::endl;
	}
}

// Function that count the number of alive neighboor
int nbNeighboor(grid game_, int x, int y) {
	int nbAlive = 0;

	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if (game_[i][j])
				nbAlive++;
		}
	}
	if (game_[x][y]) return nbAlive--;
	return nbAlive;
}

// Function that determine the next grid
void determineGrid(std::vector< std::vector<bool>>& gameOne) {
	grid gameTwo = gameOne;

	for (unsigned int i = 1; i < gameTwo.size()-1; i++) {

		for (unsigned int j = 1; j < gameTwo[i].size()-1; j++) {

			int nbNeigh = nbNeighboor(gameTwo, i, j);
			if ((gameTwo[i][j] && (nbNeigh == 2 || nbNeigh == 3))
				|| (!gameTwo[i][j] && nbNeigh == 3)) {

				gameOne[i][j] = true;
			}
			else gameOne[i][j] = false;
		}
	}
}
