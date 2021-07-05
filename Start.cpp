#include "Start.h"

InitValues SystemStart::Init() const
{
	 return std::make_pair(std::make_pair(100, 25), 
		 std::make_pair(5, "D:/TestPathMyGame/test.txt"));
}

bool SystemStart::MiddleTest(const uint16_t& midPos)
{
	return (_consScreen.ScreenHeight - 6 == midPos);
}

void SystemStart::CrashTest(const uint16_t& midPos, const uint16_t& GeneratedValue, 
	const std::optional<uint16_t>& ouidMidPos, bool& breakValue)
{
		if ((GeneratedValue >= *ouidMidPos) && (GeneratedValue <= *ouidMidPos + 5))
		{
			breakValue = true;
		}
}
void SystemStart::EntityMovment (uint16_t& MiddlePos,
	uint16_t& PositionMove, const ecPrint& entityType,
	std::function<void(uint16_t, uint16_t, ecPrint)> entityMethod,
	const std::optional<uint16_t> ouiMidpos, bool& brekVal,
	const std::optional<std::vector<uint16_t>>& genValues,
	const std::optional<bool>& oCraschTest)
{
	if (ecPrint::DROP == entityType)
	{
		for (auto& _GeneratedEntityPos : *genValues)
		{
			entityMethod(_GeneratedEntityPos, MiddlePos + PositionMove, entityType);
			if (this->MiddleTest(MiddlePos))
			{
				if (oCraschTest)
				{
					this->CrashTest(MiddlePos, _GeneratedEntityPos, ouiMidpos, brekVal);
				}
			}
			PositionMove++;
		}
	}
	else
	{
		entityMethod(PositionMove, MiddlePos, entityType);
	}
	
}

void SystemStart::ValueChange(uint16_t& Value, const Method& MethoType)
{
	if (MethoType == Method::INCREMENT)
	{
		Value++;
	}
	else
	{
		Value = {};
	}
}

void SystemStart::Start(void)
{
	this->Init();
	this->_consScreen.Welcome();
	const auto NameOfPlayer = this->_score.ChooseFileSave();
	_score.PathTest();
	

	do
	{
		system("cls");
		this->_score.SetScorePoints();
		const auto mainStart = _consScreen.MainStart();
		if (mainStart == Start::INSTRUCTIONS)
		{
			this->_consScreen.Borders();
			this->_gameLogic.AiLogic();
		}
		else if (mainStart == Start::START)
		{
			system("cls");
			const auto DifficultyChoose = this->_consScreen.chDifficulty();
			system("cls");
			this->_consScreen.Borders();
			this->_consScreen.DownBorders();
			bool breakVal = false;
			std::optional<uint16_t> ouiMidPos = this->_consScreen.MidPosition();
			uint16_t MiddlePosition{};
			uint16_t PositionMove{};
			do
			{
				this->_score.ScorePrint(*NameOfPlayer);
				const auto GeneratedEntityPos = this->_gameLogic.GenPos(DifficultyChoose.second);
				do
				{
					if (_kbhit())
					{
						this->_consScreen.ClickTest(_kbhit, breakVal, ouiMidPos);
					}
					auto refMidPos = static_cast<uint16_t&&>(_consScreen.ScreenHeight - 2);
					this->EntityMovment(refMidPos,*ouiMidPos, ecPrint::ENTITY,
						[this](const uint16_t& fPos, const uint16_t& sPos, const ecPrint& eEntity) {this->_gameLogic.CreateEntity(fPos, sPos, eEntity); },
						*ouiMidPos, breakVal);

					this->EntityMovment(MiddlePosition, PositionMove, ecPrint::DROP,
						[this](const uint16_t& fPos, const uint16_t& sPos, const ecPrint& eEntity) {this->_gameLogic.CreateEntity(fPos, sPos, eEntity);},
						*ouiMidPos, breakVal, GeneratedEntityPos, true);
					this->ValueChange(PositionMove, Method::SETTOZERO);
					std::this_thread::sleep_for(DifficultyChoose.first);
					this->EntityMovment (MiddlePosition, PositionMove, ecPrint::DROP,
						[this](const uint16_t& fPos, const uint16_t& sPos, const ecPrint& eEntity) {this->_gameLogic.EraseEntity(fPos, sPos, eEntity); },
						*ouiMidPos, breakVal, GeneratedEntityPos);
					this->ValueChange(MiddlePosition, Method::INCREMENT);
					this->EntityMovment(refMidPos, *ouiMidPos, ecPrint::ENTITY,
						[this](const uint16_t& fpos, const uint16_t& spos, const ecPrint& eentity) {this->_gameLogic.EraseEntity(fpos, spos, eentity); },
						*ouiMidPos, breakVal);

				} while (MiddlePosition != _consScreen.ScreenHeight - 2);
				this->ValueChange(MiddlePosition, Method::SETTOZERO);
				this->_score.ScoreCounter(DifficultyChoose.second);
			} while (!breakVal);

			if (NameOfPlayer)
			{
				const auto uiScore = this->_score.fScoreValue();
				const auto scorePoint = this->_score.ScorePoint();
				const auto Diff = this->_consScreen.DiffToString(DifficultyChoose.second);
				const auto saveScore = this->_score.SaveGameData(std::make_tuple(*NameOfPlayer, uiScore - (scorePoint * DifficultyChoose.second), Diff));
				this->_score.ShowScore();
			}
			system("cls");
		}
	} while (true);
}
