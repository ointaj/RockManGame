#pragma once

#include "Stream.h"
#include "Values.h"
#include "Console.h"
#include <functional>
	
using namespace std::chrono_literals;
using ThreadSleepValue = std::pair<std::chrono::duration<double>,uint16_t>;

enum class Start : bool
{
	START,
	INSTRUCTIONS
};

enum class ClickAI : int8_t
{
	AI
};

enum class eScoreOptional : int8_t
{
	PRINT
};
class bConsoleScreen 
{
public:
	bConsoleScreen() = default;
	virtual void Welcome(void) = 0;
	virtual Start MainStart(void) = 0;
	virtual ThreadSleepValue chDifficulty(void) = 0;
	virtual void Borders(void) = 0;
	virtual void BordersInfo(void) = 0;
	virtual void DownBorders(void) = 0;
	virtual void ClickTest(const std::function<int __cdecl()>& Func, bool& Loop, std::optional<uint16_t>& Vall, const std::optional<ClickAI>& AiClick) = 0;
	virtual std::string CreateEmptyString(const std::size_t& ValueSite) = 0;
	virtual void PrintMenuValues(const uint16_t& midPos, const uint16_t& rowPos, const std::vector<std::string>& Values, const std::optional<bool>& Blink) = 0;
	virtual void PrintScoreBorders(const uint16_t& CollumnHeight, const uint16_t& LengthValue, const std::optional<eScoreOptional>& oSorePrint) = 0;
	virtual std::string DiffToString(const uint16_t& DiffValue) = 0;
	virtual uint16_t MidPosition() const = 0;
	virtual void ScoreDataPrinter(const std::vector<std::string>& DataFromFile, const uint16_t& RowPos) = 0;
	virtual uint16_t LengtgOfsVec(const std::vector<std::string>& sVec) const = 0;
	~bConsoleScreen() = default;
};

class ConsoleScreen : public bConsoleScreen
{
protected:

public:
	uint16_t ScreenWidth{};
	uint16_t ScreenHeight{};
	uint16_t ScreenThickness{};
	
	ConsoleScreen() = default;
	
	ConsoleScreen(const uint16_t& sWidth, const uint16_t& sHeight)
		: ScreenHeight(sHeight), ScreenWidth(sWidth),ScreenThickness(sWidth/(uint16_t)4) {}
	
	ConsoleScreen(const uint16_t& scThick)
		: ScreenThickness(scThick){}

	virtual void Welcome(void) override;
	virtual Start MainStart(void) override;
	virtual ThreadSleepValue chDifficulty(void) override;
	virtual void Borders(void) override;
	virtual void BordersInfo(void) override;
	virtual void ClickTest(const std::function<int __cdecl()>& Func, bool& Loop, std::optional<uint16_t>& Vall, const std::optional<ClickAI>& AiClick = std::nullopt) override;
	virtual void DownBorders(void) override;
	virtual std::string CreateEmptyString(const std::size_t& ValueSite) override;
	virtual void PrintMenuValues(const uint16_t& midPos,const uint16_t& rowPos, const std::vector<std::string>& Values, const std::optional<bool>& Blink) override;
	virtual void PrintScoreBorders(const uint16_t& CollumnHeight, const uint16_t& LengthValue, const std::optional<eScoreOptional>& oSorePrint) override;
	virtual std::string DiffToString(const uint16_t& DiffValue) override;
	virtual uint16_t MidPosition() const override;
	virtual void ScoreDataPrinter(const std::vector<std::string>& DataFromFile, const uint16_t& RowPos) override;
	virtual uint16_t LengtgOfsVec(const std::vector<std::string>& sVec) const override;

	~ConsoleScreen() = default;
};

class sEnterScrenVal
{
	using str = std::string;
	using svec = std::vector<std::string>;
public:
	const str Empty = " ";
	const svec sValsDiff = { "--------------","| DIIFICULTY |","--------------" };
	const svec sValsSaveChoose = { "1. SAVE" , "2. DONT SAVE" };
	const svec sValsDiffChoose = {"1. EASY", "2. MEDDIUM", "3. HARD", "Esc(button)  End"};
	const svec sValsStart = { "*********************","| ATTENTION, ROCKS !|","*********************" };
	const svec sValsWelcome = { "*********************","|     WELCOME!!!    |","*********************" };
	const svec sValsHighestScore = { "*********************","|  HIGHEST SCORE!!! |","*********************" };
	const svec sValsSave = { "*********************","|DO YOU WANT TO SAVE|"," |YOUR ACHIVED SCORE|","*********************" };
	const svec sValsStartChoose = {"1. START GAME","2. INTRODUCTION","Esc(button) ENDGAME"};
	const svec sBorders = { "*"," "," ","*" };
	const svec sDataOfPlayers = {"NAME: ","SCORE: ", "DIFFICULTY: ","DATE: "};
	const svec sScoreList = { "*********************","|    SCORE LIST!    |","*********************" };
	const str sEnterName = "Enter the name: ";

	const svec sValsInfoBorders = {"--------------","|  MOVEMANT  |","--------------" };

	const svec sValsButtonShowScore = {"-----------------------","|1 - BEST PLAYER SCORE|", "|2 - ERASE SCORE LIST |","-----------------------"};
	const svec sValsHow = {"A - Move to left ","D - Move to right"};
};

class ReturnThreadSleepVal
{
public:
	static constexpr ThreadSleepValue EASY = std::make_pair(0.15s, 2);
	static constexpr ThreadSleepValue MEDIUM = std::make_pair(0.1s,3);
	static constexpr ThreadSleepValue HARD = std::make_pair(0.05s,4);
};
