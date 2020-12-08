#include "MainGame.h"



int main(int argc, char **argv)
{

	HWND consoleWindow = GetConsoleWindow();

	SetWindowPos(consoleWindow, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);


	MainGame mainGame;
	mainGame.run();

	std::cin;
	return 0;
}
