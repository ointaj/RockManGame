#pragma once

#include "Screen.h"
#include "GameLogic.h"
#include "Score.h"

using InitValues = std::pair<std::pair<uint16_t, uint16_t>, std::pair<uint16_t, std::string>>;

enum class Method
{
	SETTOZERO,
	INCREMENT
};

class SystemStart
{
private:
	ConsoleScreen _consScreen;
	ConsolePos _consPos;
	EnterScreenVal _nEnterScreenVal;
	sEnterScrenVal _sEnterScreenval;
	Console _console;
	Score _score;
	GameLogic _gameLogic;

public:

	SystemStart()
				: _consScreen(this->Init().first.first, this->Init().first.second, _consPos, _nEnterScreenVal, _sEnterScreenval),
				  _gameLogic(_consScreen, _consPos),
				  _score(_consScreen, this->Init().second.first, this->Init().second.second, _consPos, _nEnterScreenVal, _sEnterScreenval)
		{}

	InitValues Init() const;
	void Start(void);
	void EntityMovment(uint16_t& MiddlePos,
		uint16_t& PositionMove, const ecPrint& entityType,
		std::function<void(uint16_t, uint16_t, ecPrint)> entityMethod,
		const std::optional<uint16_t> ouiMidpos, bool& brekVal,
		const std::optional<std::vector<uint16_t>>& genValues = std::nullopt,
		const std::optional<bool>& oCraschTest = std::nullopt);
	void CrashTest(const uint16_t& midPos, const uint16_t& GeneratedValue, 
		const std::optional<uint16_t>& ouidMidPos, bool& breakValue);
	void ValueChange(uint16_t& Value, const Method& MethoType);
	bool MiddleTest(const uint16_t& midPos);
	
	~SystemStart() = default;
};
