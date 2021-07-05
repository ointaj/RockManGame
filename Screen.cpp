#include "Screen.h"

void ConsoleScreen::ClickTest(const std::function<int __cdecl()>& Func, bool& Loop, std::optional<uint16_t>& Vall , const std::optional<ClickAI>& AiClick)
{
	if (Func)
	{
		char choose = _getch();
		auto test = this->ScreenThickness * 3;
		
		if(!AiClick)
		{
			if (choose == this->_nEnterScreenVal.asciiEnd)
			{
				Loop = true;
			}
			if (choose == this->_nEnterScreenVal.lowRight || this->_nEnterScreenVal.uppRight == choose)
			{
				if (Vall < test - 8)
				{
					*Vall += 4;
				}
			}
			else if (choose == this->_nEnterScreenVal.lowLeft || this->_nEnterScreenVal.uppLeft == choose)
			{
				if (Vall > this->ScreenThickness + 4)
				{
					*Vall -= 4;
				}
			}
		}
		if (AiClick || !AiClick)
		{
			if (choose == this->_nEnterScreenVal.asciiEnd)
			{
				Loop = true;
			}
		}
	}
}
std::string ConsoleScreen::CreateEmptyString(const std::size_t& ValueSite)
{
	std::string emptyString;
	uint8_t startPos{};
	for (uint16_t pos = startPos; pos < ValueSite; pos++)
	{
		emptyString.append(_sEnterScreenVal.Empty);
	}
	return emptyString;
}

void ConsoleScreen::PrintMenuValues(const uint16_t& midPos, const uint16_t& rowPos, const std::vector<std::string>& Values, const std::optional<bool>& Blink = std::nullopt)
{

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

	ReturnThreadSleepVal _returnThreadSleepVal;
	system("cls");

	this->PrintMenuValues(this->_nEnterScreenVal.midPosDiff, this->_nEnterScreenVal.rowPosDiff, _sEnterScreenVal.sValsDiff);
	this->PrintMenuValues(this->_nEnterScreenVal.midPosDiff, this->_nEnterScreenVal.rowPosDiffChoose, _sEnterScreenVal.sValsDiffChoose);

	do
	{
		const char value = _getch();
		if (value == this->_nEnterScreenVal.fChoose)
		{
			return _returnThreadSleepVal.EASY;
		}
		else if (value == this->_nEnterScreenVal.sChoose)
		{
			return _returnThreadSleepVal.MEDIUM;
		}
		else if (value == this->_nEnterScreenVal.tChoose)
		{
			return _returnThreadSleepVal.HARD;
		}
		else if (value == this->_nEnterScreenVal.asciiEnd)
		{
			exit(NULL);
		}
	} 
	while (this->_nEnterScreenVal.infinitLoop);
}

void ConsoleScreen::Welcome(void)
{
	const std::vector<std::string> WelcomeSign =
	{
		  "#     # ##### #     ##### ###### ##   ## #####",
		  "#     # #     #     #     #    # # # # # #",
		  "#  #  # ####  #     #     #    # #  #  # ####",
		  "# # # # #     #     #     #    # #     # #  ",
		  "##   ## ##### ##### ##### ###### #     # #####"
	};
	const std::string CreatorName = "Created by: @github.com/ointaj";
	const std::string Press = "Press any key to continue...";

	this->PrintMenuValues(this->_nEnterScreenVal.midPosDiff, this->_nEnterScreenVal.rowPosDiff, WelcomeSign);
	_consPos.Position(static_cast<uint16_t>(this->_nEnterScreenVal.midPosDiff + WelcomeSign.at(0).length() / 4), static_cast<uint16_t>(this->_nEnterScreenVal.rowPosDiff + WelcomeSign.size() + 1),CreatorName);
	_consPos.Position(static_cast<uint16_t>(this->_nEnterScreenVal.midPosDiff + WelcomeSign.at(0).length() / 4), static_cast<uint16_t>(this->_nEnterScreenVal.rowPosDiff + WelcomeSign.size() + 4), Press);
	while (!_kbhit())
	{
	}
	system("cls");
	return;
}

Start ConsoleScreen::MainStart(void)
{
	constexpr bool bBlink = true;
	do
	{
		this->PrintMenuValues(this->_nEnterScreenVal.midPosDiff, this->_nEnterScreenVal.rowPosDiff, _sEnterScreenVal.sValsStart);
		if (_kbhit())
		{
			const auto value = _getch();
			if (value == this->_nEnterScreenVal.fChoose)
			{
				return Start::START;
			}
			else if (value == this->_nEnterScreenVal.sChoose)
			{
				return Start::INSTRUCTIONS;
			}
			else if (value == this->_nEnterScreenVal.asciiEnd)
			{
				exit(NULL);
			}
		}
		this->PrintMenuValues(this->_nEnterScreenVal.midPosDiff, this->_nEnterScreenVal.rowPosDiffChoose, _sEnterScreenVal.sValsStartChoose);
	}
	while (this->_nEnterScreenVal.infinitLoop);
}

void ConsoleScreen::Borders(void)
{

	for (uint16_t posHei = 0; posHei < this->ScreenHeight; ++posHei)
	{
		uint16_t startValue = 0;
		for (auto& Borders : this->_sEnterScreenVal.sBorders)
		{
			for (uint16_t __posHei = startValue; __posHei < ScreenThickness + startValue; ++__posHei)
			{
				this->_consPos.Position(__posHei, posHei, Borders);
			}
			startValue += ScreenThickness;
		}
	}
	this->BordersInfo();
}

void ConsoleScreen::BordersInfo(void)
{
	constexpr std::tuple<uint16_t,uint16_t,uint16_t,uint16_t> DivisionVar = std::make_tuple(3,4,10,2);
	uint16_t StartPosColumns = this->ScreenThickness / std::get<2>(DivisionVar);
	uint16_t sStartPosCol = StartPosColumns + std::get<3>(DivisionVar);
	const auto LenghOfBorders = static_cast<uint16_t>(_sEnterScreenVal.sValsHow.at(0).length() + std::get<1>(DivisionVar));
	const auto RowCount = static_cast<uint16_t>(_sEnterScreenVal.sValsInfoBorders.size() + _sEnterScreenVal.sValsHow.size() + std::get<0>(DivisionVar));
	
	for (uint16_t posR = StartPosColumns; posR < RowCount; ++posR)
	{
		for (uint16_t posC = StartPosColumns; posC < LenghOfBorders; ++posC)
		{
			this->_consPos.Position(posC,posR,_sEnterScreenVal.Empty);
		}
	}
	for (auto& Info : _sEnterScreenVal.sValsInfoBorders) //call the function
	{
		this->_consPos.Position(sStartPosCol, StartPosColumns, Info);
		StartPosColumns++;
	}
	sStartPosCol--;
	for (auto& How : _sEnterScreenVal.sValsHow)
	{
		this->_consPos.Position(sStartPosCol, StartPosColumns, How);
		StartPosColumns++;
	}
}

void ConsoleScreen::DownBorders(void)
{
	for (uint16_t fpos = 0; fpos < this->ScreenWidth; ++fpos)
	{
		this->_consPos.Position(fpos,static_cast<uint16_t>(this->ScreenHeight + 3), static_cast<std::string>("*"));
	}
	for (uint16_t pos = this->ScreenHeight + 4; pos < (this->ScreenHeight + 4) + this->ScreenHeight / 5; ++pos)
	{ 
		uint16_t startVal{};
		for (auto& values : _sEnterScreenVal.sBorders)
		{
			for (uint16_t sPos = startVal; sPos < this->ScreenThickness + startVal; ++sPos)
			{
				this->_consPos.Position(sPos,pos,values);
			}
			startVal += this->ScreenThickness;
		}
	}
	for (uint16_t tpos = 0; tpos < this->ScreenWidth; ++tpos)
	{
		this->_consPos.Position(tpos, static_cast<uint16_t>(this->ScreenHeight + this->ScreenHeight/5), "*");
	}
}

std::string ConsoleScreen::DiffToString(const uint16_t& DiffValue) const
{
	return _sEnterScreenVal.sValsDiffChoose.at(DiffValue - 2).substr(2, _sEnterScreenVal.sValsDiffChoose.at(DiffValue - 2).length() - 2);
}

void ConsoleScreen::PrintScoreBorders(const uint16_t& CollumnHeight, const uint16_t& LenghhValue, const std::optional<eScoreOptional>& oScorePrint = std::nullopt )
{
	
	if (oScorePrint || oScorePrint != std::nullopt)
	{
		this->PrintMenuValues(static_cast<uint16_t>(LenghhValue / 2 - _sEnterScreenVal.sValsButtonShowScore.at(0).length() / 2), this->_nEnterScreenVal.rowPosDiff - static_cast<uint16_t>(_sEnterScreenVal.sScoreList.size() + 2), _sEnterScreenVal.sValsHighestScore);
	}
	for (uint16_t pos = this->_nEnterScreenVal.midPosDiff - 3; pos < LenghhValue + 12; ++pos)
	{
		this->_consPos.Position(pos,static_cast<uint16_t>(this->_nEnterScreenVal.rowPosDiff - 2), static_cast<std::string>("-"));
	}
	for (uint16_t pos = this->_nEnterScreenVal.rowPosDiff - 1; pos < (this->_nEnterScreenVal.rowPosDiff - 1) + CollumnHeight + 7; ++pos)
	{
		this->_consPos.Position(static_cast<uint16_t>(this->_nEnterScreenVal.midPosDiff - 4),pos,"|");
		for (uint16_t spos = this->_nEnterScreenVal.midPosDiff - 3; spos < LenghhValue - 24; ++spos)
		{
			this->_consPos.Position(spos, pos, " ");
		}
		this->_consPos.Position(static_cast<uint16_t>(LenghhValue + 12), pos, "|");
	}
	for (uint16_t pos = this->_nEnterScreenVal.midPosDiff - 3; pos < LenghhValue + 12; ++pos)
	{
		this->_consPos.Position(pos, static_cast<uint16_t>((this->_nEnterScreenVal.rowPosDiff - 1) + (CollumnHeight + 7)), static_cast<std::string>("-"));
	}
	if (oScorePrint || oScorePrint != std::nullopt)
	{
		this->PrintMenuValues(static_cast<uint16_t>(LenghhValue / 2 - _sEnterScreenVal.sValsButtonShowScore.at(0).length() / 2), CollumnHeight + this->_nEnterScreenVal.midPosDiff + 2, _sEnterScreenVal.sValsButtonShowScore);
	}
}

uint16_t ConsoleScreen::MidPosition(void) const
{
	return static_cast<uint16_t>(this->ScreenWidth / 2);
}

void ConsoleScreen::ScoreDataPrinter(const std::vector<std::string>& DataOfFile, const uint16_t& RowPos)
{
	uint16_t ColumnPos = this->_nEnterScreenVal.midPosDiff;
	uint16_t PosOfVec{};

	for (auto& Value : _sEnterScreenVal.sDataOfPlayers)
	{
		_consPos.Position(ColumnPos, RowPos, Value,DataOfFile.at(PosOfVec));
		ColumnPos += static_cast<uint16_t>((Value.length() + DataOfFile.at(PosOfVec).length()) + 3);
		PosOfVec++;
	}
}

uint16_t ConsoleScreen::LengtgOfsVec(const std::vector<std::string>& sVec) const
{
	uint16_t Length{};
	for (auto& Value : sVec)
	{
		Length += static_cast<uint16_t>(Value.length());
	}
	Length += static_cast<uint16_t>(sVec.size() * 3);
	return Length;
}