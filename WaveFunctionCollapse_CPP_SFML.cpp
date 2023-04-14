#include  <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>
#include <stdlib.h>     // used for: srand, rand 
#include <time.h>       // used for: time 

class Arrray {
public:
	bool bgrid[40][40][6];
	short int grid[40][40]; // each cell with have a value from 1 to 4
	// this version of the example is only for 1920x1080 screens...
	// so the biggest value that can fit on the screen is 1080/64 = 16,875
	// almost 17... But i put [40][40] for the future =))

	// max 33 pe ecran
	//bool grid[33][33][5]; // sau int grid[33][33];

	int Size2dVector;
	Arrray(int _Size2dVector) {
		Size2dVector = _Size2dVector;

	// My boolean vector of vectors (of vectors =))) ) has random values everytime
	// probably because of the allocation in RAM 
	// I couldn't think for other ways to fill the "variable" with 1...
	// So i'm stuck with 3 nested fors
		for (int i = 1; i <= Size2dVector; i++)
			for (int j = 1; j <= Size2dVector; j++)
				for (int k = 1; k <= 6; k++)
					bgrid[i][j][k] = 1;

		randomisation();
	}

	void filling(int y, int x) {
		for (int i = 1; i <= 4; i++)
			bgrid[y][x][i] = 0;
	}

	void constraints(int y, int x, int tile) {

		// I'm ashamed of the switch case =))), but this was the best method i could think of at that point
		switch (tile) {
		case 1:
			filling(y - 1, x);
			bgrid[y - 1][x][2] = 1;
			bgrid[y - 1][x][4] = 1;

			filling(y + 1, x);
			bgrid[y + 1][x][2] = 1;
			bgrid[y + 1][x][4] = 1;

			filling(y, x - 1);
			bgrid[y][x - 1][2] = 1;
			bgrid[y][x - 1][4] = 1;

			filling(y, x + 1);
			bgrid[y][x + 1][2] = 1;
			bgrid[y][x + 1][4] = 1;
			break;
		case 2:
			filling(y - 1, x);
			bgrid[y - 1][x][1] = 1;
			bgrid[y - 1][x][3] = 1;

			filling(y + 1, x);
			bgrid[y + 1][x][1] = 1;
			bgrid[y + 1][x][3] = 1;

			filling(y, x - 1);
			bgrid[y][x - 1][1] = 1;
			bgrid[y][x - 1][3] = 1;

			filling(y, x + 1);
			bgrid[y][x + 1][1] = 1;
			bgrid[y][x + 1][3] = 1;
			break;
		case 3:
			filling(y - 1, x);
			bgrid[y - 1][x][2] = 1;
			bgrid[y - 1][x][4] = 1;

			filling(y + 1, x);
			bgrid[y + 1][x][2] = 1;
			bgrid[y + 1][x][4] = 1;

			filling(y, x - 1);
			bgrid[y][x - 1][2] = 1;
			bgrid[y][x - 1][4] = 1;

			filling(y, x + 1);
			bgrid[y][x + 1][2] = 1;
			bgrid[y][x + 1][4] = 1;
			break;
		case 4:
			filling(y - 1, x);
			bgrid[y - 1][x][3] = 1;
			bgrid[y - 1][x][1] = 1;

			filling(y + 1, x);
			bgrid[y + 1][x][3] = 1;
			bgrid[y + 1][x][1] = 1;

			filling(y, x - 1);
			bgrid[y][x - 1][3] = 1;
			bgrid[y][x - 1][1] = 1;

			filling(y, x + 1);
			bgrid[y][x + 1][3] = 1;
			bgrid[y][x + 1][1] = 1;
			break;

		}

	}
	void randomisation() {
		short int randomtile;
		for (int i = 1; i <= Size2dVector; i++) {
			for (int j = 1; j <= Size2dVector; j++) {
				while (true) {
					randomtile = rand() % 4 + 1; // random from 1 to 4
					if (bgrid[i][j][randomtile] == 1) { // if the tile is available in the bgrid
						grid[i][j] = randomtile; // attributing the value to the 2D vector
						constraints(i, j, randomtile); // applying the constraints to the bgrid
						break;
					}
				}
			}
		}
	}
};



int main()
{
	srand(time(NULL));
	int howbig;
	std::cout << "Enter a number between 1 - 17 \n";
	std::cin >> howbig;
	howbig = std::min(howbig, 17);
	Arrray myArrray(howbig);

	std::cout << "1 - forest (brown) \n";
	std::cout << "2 - grass (green) \n";
	std::cout << "3 - water (blue) \n";
	std::cout << "4 - desert (yellow)\n\n";

	std::cout << "1 - can only stay near 2 and 4 \n";
	std::cout << "2 - can only stay near 1 and 3 \n";
	std::cout << "3 - can only stay near 2 and 4 \n";
	std::cout << "4 - can only stay near 1 and 3 \n\n";

	for (int i = 1; i <= howbig; i++) {
		for (int j = 1; j <= howbig; j++)
			std::cout << myArrray.grid[i][j] << ' ';
		std::cout << '\n';
	}

	int w = 64;
	int windowDimensions = howbig * w;
	sf::RenderWindow window(sf::VideoMode(windowDimensions, windowDimensions), "WaveFunctionCollapse");
	sf::Event event;

	sf::Texture t;
	t.loadFromFile("images/TerrainRawImag.jpg");
	sf::Sprite s(t);

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				window.close();
			}
		}
		window.clear(sf::Color::Black);

		for (int i = 1; i <= myArrray.Size2dVector; i++) {
			for (int j = 1; j <= myArrray.Size2dVector; j++) {
				s.setTextureRect(sf::IntRect((myArrray.grid[i][j]-1) * w, 0, w, w));
				s.setPosition((i - 1) * w, (j - 1) * w);
				window.draw(s);
			}
		}
		window.display();


	}

	return 0;
}