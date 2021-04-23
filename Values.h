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
