#pragma once
#include "Stream.h"

class bConsole
{
public:
	bConsole() = default;
	virtual void setCursor() = 0;
	~bConsole() = default;
};

class Console : public bConsole
{
public:
	Console() = default;
	virtual void setCursor() override;
	~Console() = default;
};

class ConsolePos
{
public:
	template<class tVal, class ...Args>
	void Position(const tVal& fVal, const tVal& sVal, Args&& ...val)
	{
		outStream _outStream;
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD CursorPosition;
		CursorPosition.X = fVal;
		CursorPosition.Y = sVal;
		SetConsoleCursorPosition(console, CursorPosition);
		_outStream.Print(std::forward<Args>(val)...);
	}
};