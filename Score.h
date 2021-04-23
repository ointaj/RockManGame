#pragma once
#include "Stream.h"
#include "Screen.h"

enum class SaveScore : bool
{
	FAIL,
	SAVED
};

enum class Player : bool
{
	INFILE
};
class bScore
{
public:
	bScore() = default;
	virtual void ScoreCounter(const uint16_t& DiffValue) = 0;
	virtual void ScorePrint(const std::optional<std::string>& Name) = 0;
	virtual void SetScorePoints() = 0;
	virtual uint32_t fScoreValue() const = 0;
	virtual uint16_t ScorePoint() const = 0;
	virtual std::optional<std::string> ChooseFileSave() = 0;
	
	virtual SaveScore SaveGameData(const std::tuple<std::string,uint32_t,std::string>& ScoreData) = 0;
	virtual std::optional<Player> ControlPlayerName(const std::pair<std::string, std::string>& Name) = 0;
	virtual void ShowScore() = 0;
	virtual char* CurrentTime() = 0;
	virtual void SaveChangesInFile(const std::string& newData) = 0;
	virtual void HighestScore(const uint16_t& ScoreValeu) = 0;
 
	virtual void PathTest() = 0;
	~bScore() = default;
};

class Score : public bScore
{
	friend class ConsoleScreen;
private:
	uint16_t ScoreValue{};
	uint32_t uiScore{};

	std::string tesPath;
	std::ifstream readFile;
	std::ofstream writeInFile;
	std::string DataOfFile;

	uint16_t sHeight{};
	uint16_t sThicknes{};

public:
	Score() = default;
	Score(const ConsoleScreen& conVal,const uint16_t& scoreValue, const std::string& Path)
	{
		this->sHeight = conVal.ScreenHeight;
		this->sThicknes = conVal.ScreenThickness;
		this->ScoreValue = scoreValue;
		this->tesPath = Path;
	}
	virtual void ScoreCounter(const uint16_t& DiffValue) override;
	virtual void ScorePrint(const std::optional<std::string>& Name) override;
	virtual void SetScorePoints() override;
	virtual uint32_t fScoreValue() const override;
	virtual uint16_t ScorePoint() const override;
	virtual std::optional<std::string> ChooseFileSave() override;
	virtual SaveScore SaveGameData(const std::tuple<std::string, uint32_t, std::string>& ScoreData) override;
	virtual std::optional<Player> ControlPlayerName(const std::pair<std::string,std::string>& Name) override;
	virtual void HighestScore(const uint16_t& ScoreValeu) override;
	virtual void ShowScore() override;
	virtual char* CurrentTime() override;
	virtual void SaveChangesInFile(const std::string& newData) override;
	virtual void PathTest() override;
	~Score() = default;

};