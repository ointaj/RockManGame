#include "Screen.h"


void ConsoleScreen::ClickTest(const std::function<int __cdecl()>& Func, bool& Loop, std::optional<uint16_t>& Vall , const std::optional<ClickAI>& AiClick)
{
	EnterScreenVal _eScreenVal;
	if (Func)
	{
		char choose = _getch();
		auto test = this->ScreenThickness * 3;
		
		if(!AiClick)
		{
			if (choose == _eScreenVal.asciiEnd)
			{
				Loop = true;
			}
			if (choose == _eScreenVal.lowRight || _eScreenVal.uppRight == choose)
			{
				if (Vall < test - 8)
				{
					*Vall += 4;
				}
			}
			else if (choose == _eScreenVal.lowLeft || _eScreenVal.uppLeft == choose)
			{
				if (Vall > this->ScreenThickness + 4)
				{
					*Vall -= 4;
				}
			}
		}
		if (AiClick || !AiClick)
		{
			if (choose == _eScreenVal.asciiEnd)
			{
				Loop = true;
			}
		}
	}
}
std::string ConsoleScreen::CreateEmptyString(const std::size_t& ValueSite)
{
	sEnterScrenVal _sEnterScreenval;
	std::string emptyString;
	uint8_t startPos{};
	for (uint16_t pos = startPos; pos < ValueSite; pos++)
	{
		emptyString.append(_sEnterScreenval.Empty);
	}
	return emptyString;
}

void ConsoleScreen::PrintMenuValues(const uint32_t& midPos, const uint32_t& rowPos, const std::vector<std::string>& Values, const std::optional<bool>& Blink = std::nullopt)
{

	ConsolePos _consPos;
	auto _rowPos = rowPos;
	for (auto& Vals : Values)
	{
		_consPos.Position(midPos, _rowPos, Vals);
		_rowPos++;
	}
	_rowPos = rowPos;
	if (Blink)
	{
		std::this_thread::sleep_for(1s);
		auto sEmptyReplace = CreateEmptyString(Values.at(0).size());
		for (auto& Vals : Values)
		{
			_consPos.Position(midPos, _rowPos, sEmptyReplace);
			_rowPos++;
		}
	}
}
ThreadSleepValue ConsoleScreen::chDifficulty(void)
{
	sEnterScrenVal _sEnterScreenval;
	EnterScreenVal _nEnterScreenval;
	ReturnThreadSleepVal _returnThreadSleepVal;
	
	system("cls");

	this->PrintMenuValues(_nEnterScreenval.midPosDiff, _nEnterScreenval.rowPosDiff, _sEnterScreenval.sValsDiff);
	this->PrintMenuValues(_nEnterScreenval.midPosDiff, _nEnterScreenval.rowPosDiffChoose, _sEnterScreenval.sValsDiffChoose);

	do
	{
		const char value = _getch();
		if (value == _nEnterScreenval.fChoose)
		{
			return _returnThreadSleepVal.EASY;
		}
		else if (value == _nEnterScreenval.sChoose)
		{
			return _returnThreadSleepVal.MEDIUM;
		}
		else if (value == _nEnterScreenval.tChoose)
		{
			return _returnThreadSleepVal.HARD;
		}
		else if (value == _nEnterScreenval.asciiEnd)
		{
			exit(NULL);
		}
	} 
	while (_nEnterScreenval.infinitLoop);
}

Start ConsoleScreen::MainStart(void)
{
	sEnterScrenVal _sEnterScreenval;
	EnterScreenVal _nEnterScreenval;

	constexpr bool bBlink = true;

	do
	{
		this->PrintMenuValues(_nEnterScreenval.midPosDiff, _nEnterScreenval.rowPosDiff, _sEnterScreenval.sValsStart);
		if (_kbhit())
		{
			const auto value = _getch();
			if (value == _nEnterScreenval.fChoose)
			{
				return Start::START;
			}
			else if (value == _nEnterScreenval.sChoose)
			{
				return Start::INSTRUCTIONS;
			}
			else if (value == _nEnterScreenval.asciiEnd)
			{
				exit(NULL);
			}
		}
		this->PrintMenuValues(_nEnterScreenval.midPosDiff, _nEnterScreenval.rowPosDiffChoose, _sEnterScreenval.sValsStartChoose);
	}
	while (_nEnterScreenval.infinitLoop);
}

void ConsoleScreen::Borders(void)
{
	ConsolePos _conole;
	sEnterScrenVal _enterVal;

	for (uint16_t posHei = 0; posHei < this->ScreenHeight; ++posHei)
	{
		uint16_t startValue = 0;
		for (auto& fun : _enterVal.sBorders)
		{
			for (uint16_t __posHei = startValue; __posHei < ScreenThickness + startValue; ++__posHei)
			{
				_conole.Position(__posHei, posHei, fun);
			}
			startValue += ScreenThickness;
		}
	}
}

void ConsoleScreen::DownBorders(void)
{
	ConsolePos _console;
	sEnterScrenVal _enterVal;
	for (uint16_t fpos = 0; fpos < this->ScreenWidth; ++fpos)
	{
		_console.Position(fpos,static_cast<uint16_t>(this->ScreenHeight + 3), static_cast<std::string>("*"));
	}
	for (uint16_t pos = this->ScreenHeight + 4; pos < (this->ScreenHeight + 4) + this->ScreenHeight / 5; ++pos)
	{ 
		uint16_t startVal{};
		for (auto& values : _enterVal.sBorders)
		{
			for (uint16_t sPos = startVal; sPos < this->ScreenThickness + startVal; ++sPos)
			{
				_console.Position(sPos,pos,values);
			}
			startVal += this->ScreenThickness;
		}
	}
	for (uint16_t tpos = 0; tpos < this->ScreenWidth; ++tpos)
	{
		_console.Position(tpos, static_cast<uint16_t>(this->ScreenHeight + this->ScreenHeight/5), "*");
	}
}

std::string ConsoleScreen::DiffToString(const uint16_t& DiffValue)
{
	sEnterScrenVal _sEnterValue;
	return _sEnterValue.sValsDiffChoose.at(DiffValue - 2).substr(2, _sEnterValue.sValsDiffChoose.at(DiffValue - 2).length() - 2);
}

void ConsoleScreen::PrintScoreBorders(const uint16_t& CollumnHeight, const uint16_t& LenghhValue)
{
	ConsolePos _console;
	EnterScreenVal _enterScreenVals;

	for (uint16_t pos = _enterScreenVals.midPosDiff - 3; pos < LenghhValue + 12; ++pos)
	{
		_console.Position(pos,static_cast<uint16_t>(_enterScreenVals.rowPosDiff - 2), static_cast<std::string>("-"));
	}
	for (uint16_t pos = _enterScreenVals.rowPosDiff - 1; pos < (_enterScreenVals.rowPosDiff - 1) + CollumnHeight + 4; ++pos)
	{
		_console.Position(static_cast<uint16_t>(_enterScreenVals.midPosDiff - 4),pos,"|");
		for (uint16_t spos = _enterScreenVals.midPosDiff - 3; spos < LenghhValue - 24; ++spos)
		{
			_console.Position(spos, pos, " ");
		}
		_console.Position(static_cast<uint16_t>(LenghhValue + 12), pos, "|");
	}
	for (uint16_t pos = _enterScreenVals.midPosDiff - 3; pos < LenghhValue + 12; ++pos)
	{
		_console.Position(pos, static_cast<uint16_t>((_enterScreenVals.rowPosDiff - 1) + (CollumnHeight + 4)), static_cast<std::string>("-"));
	}
}

uint16_t ConsoleScreen::MidPosition() const
{
	return static_cast<uint16_t>(this->ScreenWidth / 2);
}


void ConsoleScreen::ScoreDataPrinter(const std::vector<std::string>& DataOfFile, const uint16_t& RowPos)
{
	sEnterScrenVal _sEnterScrenVal;
	EnterScreenVal _nEnterScreenval;
	ConsolePos _consPos;

	uint16_t ColumnPos = _nEnterScreenval.midPosDiff;
	uint16_t PosOfVec{};

	for (auto& Value : _sEnterScrenVal.sDataOfPlayers)
	{
		_consPos.Position(ColumnPos, RowPos, Value,DataOfFile.at(PosOfVec));
		ColumnPos += static_cast<uint16_t>((Value.length() + DataOfFile.at(PosOfVec).length()) + 3);
		PosOfVec++;
	}
}

uint16_t ConsoleScreen::LenghOfPrinterVec() const
{
	sEnterScrenVal _sEnterScrenVal;
	uint16_t Length{};
	for (auto& Value : _sEnterScrenVal.sDataOfPlayers)
	{
		Length += static_cast<uint16_t>(Value.length());
	}
	Length += static_cast<uint16_t>(_sEnterScrenVal.sDataOfPlayers.size() * 3);
	return Length;
}