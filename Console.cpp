#include "Console.h"
void Console::setCursor()
{
	CONSOLE_CURSOR_INFO lpCursor;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	lpCursor.bVisible = false;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
