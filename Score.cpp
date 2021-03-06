#include "Score.h"

SaveScore Score::SaveGameData(const std::tuple<std::string, uint32_t, std::string>& ScoreData)
{
	const auto Val = this->ControlPlayerName(std::make_pair(std::get<0>(ScoreData), std::get<2>(ScoreData)));
	const auto sCurrentTime = this->CurrentTime();
	if (!Val)
	{
		this->writeInFile.open(this->testPath, std::fstream::app);

		if (this->writeInFile.is_open())
		{
			this->writeInFile << std::get<0>(ScoreData) << "/" << std::to_string(std::get<1>(ScoreData)) << "-> " << std::get<2>(ScoreData) << "-> " << sCurrentTime << std::endl;
			this->writeInFile.close();
			return SaveScore::SAVED;
		}
		else
		{
			this->writeInFile.close();
			return SaveScore::FAIL;
		}
	}
	if (Val)
	{
		std::string newData{};
		this->readFile.open(this->testPath);
		while (getline(this->readFile, this->DataOfFile))
		{
			if(!this->DataOfFile.empty())
			{
				if (readFile.is_open())
				{
					bool testt = false;
					const auto Delimer = this->DataOfFile.find("/");
					const auto SecondDelimmeter = this->DataOfFile.find("->");
					const auto TimeDelimter = this->DataOfFile.find("->", SecondDelimmeter + 1);
					const auto NameInFile = this->DataOfFile.substr(0, Delimer);
					const auto ScoreValue = this->DataOfFile.substr(Delimer + 1, SecondDelimmeter - Delimer - 1);
					const auto Difficulty = this->DataOfFile.substr(SecondDelimmeter + 3, TimeDelimter - SecondDelimmeter - 3);
					
					if (NameInFile == std::get<0>(ScoreData))
					{
						if ((static_cast<uint32_t>(std::stoi(ScoreValue)) <= std::get<1>(ScoreData)) && (Difficulty == std::get<2>(ScoreData)))
						{
							testt = true;
							auto ReplacedData = this->DataOfFile.replace(Delimer + 1, SecondDelimmeter - Delimer - 1, std::to_string(std::get<1>(ScoreData)));
							ReplacedData.replace(TimeDelimter + 4, ReplacedData.length() - TimeDelimter - 4, sCurrentTime);
							newData.append(ReplacedData).append("\n");
						}
					}
					if (testt == false)
					{
						newData.append(this->DataOfFile).append("\n");
					}
				}
				else
				{
					this->readFile.close();
					return SaveScore::FAIL;
				}
			}
		}

		this->SaveChangesInFile(newData);
		this->readFile.close();
		return SaveScore::SAVED;
	}
	return SaveScore::FAIL;
}

void Score::ShowScore()
{
	std::set<uint32_t, std::greater<uint32_t>> sortValue;
	std::vector<uint16_t> lenghString;
	
	uint16_t RowCount{};
	
	this->readFile.open(this->testPath);
	while (getline(this->readFile, this->DataOfFile))
	{
		if (!this->DataOfFile.empty())
		{
			lenghString.emplace_back(static_cast<uint16_t>(this->DataOfFile.length()));
			const auto findDel = this->DataOfFile.find("/");
			const auto SecDelimter = this->DataOfFile.find("->", findDel + 1);
			if (findDel != std::string::npos)
			{
				const auto ValScore = static_cast<uint32_t>(std::stoi(this->DataOfFile.substr(findDel + 1, SecDelimter - findDel - 1)));
				sortValue.insert(ValScore);
			}
			RowCount++;
		}
	}
	this->readFile.close();
	system("cls");
	auto RowPos = _nEnterScreenVal.rowPosDiff;
	const auto LenghOfVec = _consScreen.LengtgOfsVec(_sEnterScreenVal.sDataOfPlayers);
	_consScreen.PrintScoreBorders(RowCount, (*std::max_element(lenghString.begin(), lenghString.end()) + LenghOfVec), eScoreOptional::PRINT);

	do
	{
		for (auto& sortVals : sortValue)
		{
			this->readFile.open(this->testPath);

			while (getline(this->readFile, this->DataOfFile))
			{
				const auto posOfDelimeter = this->DataOfFile.find("/");
				const auto SecDelimter = this->DataOfFile.find("->");
				const auto ScoreSub = this->DataOfFile.substr(posOfDelimeter + 1, SecDelimter - posOfDelimeter - 1);
				if (std::to_string(sortVals) == ScoreSub)
				{
					std::vector<std::string> SubstrOfData;
					constexpr std::size_t ReserveValue = 4;
					SubstrOfData.reserve(ReserveValue);
					const auto TimeDelimeter = this->DataOfFile.rfind("->");
					const auto NameSub = this->DataOfFile.substr(0,posOfDelimeter);
					const auto DiffSub = this->DataOfFile.substr(SecDelimter + 3,TimeDelimeter - SecDelimter - 3);
					const auto DateSub = this->DataOfFile.substr(TimeDelimeter + 3, this->DataOfFile.length() - TimeDelimeter - 3 );
					SubstrOfData.insert(SubstrOfData.end(), { NameSub ,ScoreSub ,DiffSub ,DateSub });
					_consScreen.ScoreDataPrinter(SubstrOfData, RowPos);
					RowPos++;
				}
			}
			this->readFile.close();
			if (_kbhit())
			{
				const char InputValue = _getch();
				if (InputValue == _nEnterScreenVal.fChoose)
				{
					this->HighestScore(*std::max_element(sortValue.begin(), sortValue.end()));
					return;
				}

				if (InputValue == _nEnterScreenVal.sChoose)
				{
					this->EraseScoreList();
					return;
				}

				if (InputValue == _nEnterScreenVal.asciiEnd)
				{
					this->readFile.close();
					return;
				}
			}
		}
		RowPos = _nEnterScreenVal.rowPosDiff;
	} while (true);
}

std::optional<std::string> Score::ChooseFileSave()
{
	system("cls");
	
	bInputStrem <std::string> _inpStream;
	
	_consScreen.PrintMenuValues(_nEnterScreenVal.midPosDiff - 3, _nEnterScreenVal.rowPosDiff - 3, _sEnterScreenVal.sValsWelcome, std::nullopt);
	_consScreen.PrintMenuValues(_nEnterScreenVal.midPosDiff, _nEnterScreenVal.rowPosDiff, _sEnterScreenVal.sValsSaveChoose,std::nullopt);
	do
	{
		const char value = _getch();
		if (value == _nEnterScreenVal.fChoose)
		{
			break;
		}
		else if (value == _nEnterScreenVal.sChoose)
		{
			return std::nullopt;
		}
		else if (value == _nEnterScreenVal.asciiEnd)
		{
			exit(NULL);
		}
	} 
	while (true);
	system("cls");
	_consPos.Position(_nEnterScreenVal.midPosDiff, _nEnterScreenVal.rowPosDiff,_sEnterScreenVal.sEnterName);
	const auto nameTest = _inpStream.sInput();
	return nameTest;
}

std::optional<Player> Score::ControlPlayerName(const std::pair<std::string, std::string>& NameDiff)
{
	this->readFile.open(this->testPath);
	while (getline(this->readFile, this->DataOfFile))
	{
		if (this->readFile.is_open())
		{
			if (!this->DataOfFile.empty())
			{
				const auto Delimeter = this->DataOfFile.find("/");
				const auto diffDelimeter = this->DataOfFile.find("->");
				const auto rdiffDelimeter = this->DataOfFile.rfind("->");
				const auto Difficulty = this->DataOfFile.substr(diffDelimeter + 3, rdiffDelimeter - diffDelimeter - 3);
				const auto Name = this->DataOfFile.substr(0, Delimeter);
				if ((NameDiff.first) == Name)
				{
					if ((NameDiff.second) == Difficulty)
					{
						this->readFile.close();
						return Player::INFILE;
					}
				}
			}
		}
	}
	this->readFile.close();
	return std::nullopt;
}

void Score::ScoreCounter(const uint16_t& DiffValue)
{
	for (uint16_t pos = 0; pos < DiffValue; ++pos)
	{
		this->uiScore += this->ScoreValue;
	}
}

void Score::ScorePrint(const std::optional<std::string>& Name)
{
	
	std::string sName = "Game without PlayerName ";
	if (Name != std::nullopt)
	{
		sName = *Name;
	}
	_consPos.Position(static_cast<uint16_t>(this->_consScreen.ScreenThickness * 2 - 15), static_cast<uint16_t>(this->_consScreen.ScreenHeight + (this->_consScreen.ScreenHeight / 5 / 2), static_cast<std::string>("Name of player: "), sName,static_cast<std::string>(" SCORE: "), this->uiScore));
}

void Score::SetScorePoints()
{
	this->uiScore = 0;
}
uint32_t Score::fScoreValue() const
{
	return this->uiScore;
}

uint16_t Score::ScorePoint() const
{
	return this->ScoreValue;
}

void Score::SaveChangesInFile(const std::string& newData)
{
	this->writeInFile.open(this->testPath);
	this->writeInFile << newData;
	this->writeInFile.close();
}

char* Score::CurrentTime()
{
	time_t tCurrentTime = time(NULL);
	char* chTime = ctime(&tCurrentTime);
	return chTime;
}

void Score::PathTest()
{
	this->readFile.open(this->testPath);
	if (this->readFile.is_open())
	{
		this->readFile.close();
		return;
	}
	else
	{
		//add comment for screen
		exit(NULL);
	}
	this->readFile.close();
}

void Score::EraseScoreList(void)
{
	this->writeInFile.open(this->testPath);
	this->writeInFile.close();
}

void Score::HighestScore(const uint16_t& ScoreValue)
{
	
	system("cls");

	std::string HighestScoreVal;
	this->readFile.open(this->testPath);
	while (getline(this->readFile, this->DataOfFile))
	{
		const auto fDel = this->DataOfFile.find("/");
		const auto sDel = this->DataOfFile.find("->");
		const auto Score = this->DataOfFile.substr(fDel + 1, sDel - fDel - 1);
		if (Score == std::to_string(ScoreValue))
		{
			HighestScoreVal = this->DataOfFile;
			break;
		}
	}
	this->readFile.close();

	_consScreen.PrintMenuValues(static_cast<uint16_t>(HighestScoreVal.length() / 2), _nEnterScreenVal.rowPosDiff - 5, _sEnterScreenVal.sValsHighestScore,std::nullopt);
	_consScreen.PrintScoreBorders(1,static_cast<uint16_t>(HighestScoreVal.length()),std::nullopt);
	_consPos.Position(_nEnterScreenVal.midPosDiff, _nEnterScreenVal.rowPosDiff, HighestScoreVal);
	do
	{
		if (_kbhit())
		{
			const auto Input = _getch();
			if (Input == 27)
			{
				return;
			}
		}
	}
	while (true);
}
