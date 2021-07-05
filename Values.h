#pragma once
#include "Stream.h"

class EnterScreenVal
{
	using ch = char;
	using ui = uint16_t;
	using vec = std::vector<uint16_t>;
public:
	static constexpr bool infinitLoop = true;

	static constexpr ch fChoose = '1';
	static constexpr ch sChoose = '2';
	static constexpr ch tChoose = '3';
	static constexpr ch lowLeft = 'a';
	static constexpr ch uppLeft = 'A';
	static constexpr ch lowRight = 'd';
	static constexpr ch uppRight = 'D';
	static constexpr ui asciiEnd = 27;

	static constexpr ui midPosDiff = 10;
	static constexpr ui rowPosDiff = 10;
	static constexpr ui rowPosDiffChoose = 15;
};

class sEnterScrenVal
{
	using str = std::string;
	using svec = std::vector<std::string>;
public:
	const str Empty = " ";
	const svec sValsDiff = { "--------------","| DIIFICULTY |","--------------" };
	const svec sValsSaveChoose = { "1. SAVE" , "2. DONT SAVE" };
	const svec sValsDiffChoose = { "1. EASY", "2. MEDDIUM", "3. HARD", "Esc(button)  End" };
	const svec sValsStart = { "*********************","| ATTENTION, ROCKS !|","*********************" };
	const svec sValsWelcome = { "*********************","|     WELCOME!!!    |","*********************" };
	const svec sValsHighestScore = { "*********************","|  HIGHEST SCORE!!! |","*********************" };
	const svec sValsSave = { "*********************","|DO YOU WANT TO SAVE|"," |YOUR ACHIVED SCORE|","*********************" };
	const svec sValsStartChoose = { "1. START GAME","2. INTRODUCTION","Esc(button) ENDGAME" };
	const svec sBorders = { "*"," "," ","*" };
	const svec sDataOfPlayers = { "NAME: ","SCORE: ", "DIFFICULTY: ","DATE: " };
	const svec sScoreList = { "*********************","|    SCORE LIST!    |","*********************" };
	const str sEnterName = "Enter the name: ";

	const svec sValsInfoBorders = { "--------------","|  MOVEMANT  |","--------------" };

	const svec sValsButtonShowScore = { "-----------------------","|1 - BEST PLAYER SCORE|", "|2 - ERASE SCORE LIST |","-----------------------" };
	const svec sValsHow = { "A - Move to left ","D - Move to right" };
};
