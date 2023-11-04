#include <iostream>
#include <time.h>
#include <SDL.h>
#include "World.h"
#undef main
using namespace std;
World world;
int main(int* argc, char* argv[]) {
	srand(time(NULL));
	world.init();

	while (world.m_run) {
		world.update();
		world.draw();
	}

	world.exit();

	return 0;
}	