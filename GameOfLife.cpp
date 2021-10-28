#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Field dimensions
const int WIDTH = 15;
const int HEIGHT = 10;

// Iterations of the game
const int ITERATIONS = 20;

// Grid Initialisation
std::vector< std::vector<bool> > grid = {};

void printGrid(std::vector< std::vector<bool>>);
void determineGrid(std::vector< std::vector<bool>> &);
bool isBorder(int, int);
int nbNeighboor(std::vector< std::vector<bool>>, int, int);


int main() {

        std::string line = {};
	std::ifstream file("grid.txt");

	// Reading the file and filling the grid
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			std::vector <bool> vectorInit = { };
			vectorInit.reserve(line.size());

			for (auto a : line) {
				vectorInit.push_back(a == '1');
			}
			grid.push_back(vectorInit);
		}
		file.close();
	}
	else {
		std::cout << "Error : File can't be open !" << std::endl;
		return 0;
	}

	file.close();
	printGrid(grid);

	for (int i = 0; i < ITERATIONS; i++) {
		determineGrid(grid);
		printGrid(grid);
		sleep(10);
		std::cout << std::endl;
	}


}

void printGrid(std::vector< std::vector<bool>> grid) {

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {

			if (grid[i][j])
				std::cout << "0";
			else std::cout << ".";
		}

		std::cout << std::endl;
	}
}

// CHECK IF THE POSITION IS A BORDER
bool isBorder(int x, int y) {
	return (x == 0 || x == HEIGHT - 1 || y == 0 || y == WIDTH - 1);
}

// CHECK THE NUMBER OF ALIVE NEIGHBOOR
int nbNeighboor(std::vector< std::vector<bool>> grid, int x, int y) {
	int nbAlive = 0;

	for (int i = x-1; i <= x+1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if (grid[i][j])
				nbAlive++;
		}
	}

	return nbAlive;
}

// DETEMINE THE NEXT GRID
void determineGrid(std::vector< std::vector<bool>> &gridOne) {
	std::vector< std::vector<bool>> gridTwo = gridOne;

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			
			// Check if it's a border
			if (!isBorder(i, j)) {

				int nbNeigh = nbNeighboor(gridTwo, i, j);

				if (    (gridTwo[i][j] && (nbNeigh == 3 || nbNeigh == 4))
					|| (!gridTwo[i][j] &&  nbNeigh == 3))
					gridOne[i][j] = true;

				else gridOne[i][j] = false;
			}
			else gridOne[i][j] = false;

		}
	}
}
