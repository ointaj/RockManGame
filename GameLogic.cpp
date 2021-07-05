#include "GameLogic.h"
#include "Stream.h"

std::vector<std::vector<char>> GameLogic::setEntity(const ecPrint& eEntity)
{
	if (eEntity == ecPrint::DROP)
	{
		std::vector<std::vector<char>> chTear
		{
			{ '±','±','±'},
			{'±', '±', '±'}
		};
		return chTear;
	}
	else if (eEntity == ecPrint::ENTITY)
	{
		std::vector<std::vector<char>> chPerson
		{
			{'±','±','±','±','±'},
			{'±',' ',' ',' ','±'}
		};
		return chPerson;
	}
	return {};
}

void GameLogic::CreateEntity(const uint16_t& fPos, const uint16_t& sPos, const ecPrint& eEntity)
{
	const auto value = setEntity(eEntity);
	for (uint16_t pos = 0; pos < value.size(); pos++)
	{
		for (uint16_t _pos = 0; _pos < value.at(pos).size(); _pos++)
		{
			this->_consPos.Position(fPos + _pos, sPos + pos, value.at(pos).at(_pos));
		}
	}
}

void GameLogic::EraseEntity(const uint16_t& fPos, const uint16_t& sPos, const ecPrint& eEntity)
{
	const auto value = setEntity(eEntity);
	for (uint16_t pos = 0; pos < value.size(); pos++)
	{
		for (uint16_t _pos = 0; _pos < value.at(pos).size(); _pos++)
		{
			this->_consPos.Position(fPos + _pos, sPos + pos, this->sEmpTy);
		}
	}
}

std::vector<uint16_t> GameLogic::GenPos(const uint16_t& Values)
{
	std::vector<uint16_t> vRandPos;
	vRandPos.reserve(Values);
	srand((uint16_t)time(NULL));
	for (uint16_t pos = 0; pos < Values; ++pos)
	{
		uint16_t uiranVal = rand() % (this->_consScreen.ScreenThickness * 2 - 4) + this->_consScreen.ScreenThickness;
		vRandPos.emplace_back(uiranVal);
	}
	return vRandPos;
}

void GameLogic::AiLogic(void)
{
	constexpr uint16_t setGenValue = 2;
	uint16_t heithtPos = 0;
	uint16_t countEntiy{};
	bool Loop = false;
	uint16_t emidValeu = this->_consScreen.ScreenWidth / 2;
	do
	{
		auto genValues = GenPos(setGenValue);
		do
		{
			if (_kbhit())
			{
				std::optional<uint16_t> Null = std::nullopt;
				this->_consScreen.ClickTest(_kbhit, Loop, Null,ClickAI::AI);
			}
			
			if (heithtPos == this->_consScreen.ScreenHeight / 2) //middle
			{
				this->AiMovment(genValues, emidValeu);
			}

			this->CreateEntity(emidValeu, this->_consScreen.ScreenHeight - 2, ecPrint::ENTITY);

			for (auto& midValue : genValues)
			{
				this->CreateEntity(midValue, heithtPos + countEntiy, ecPrint::DROP);
				this->ColisionControl(std::make_tuple(heithtPos, midValue, emidValeu), Loop);
				countEntiy++;
			}
			
			countEntiy = 0;
			std::this_thread::sleep_for(0.02s);
			
			for (auto& midValue : genValues)
			{
				this->EraseEntity(midValue, heithtPos + countEntiy, ecPrint::DROP);
				countEntiy++;
			}
				
			heithtPos++;
			this->EraseEntity(emidValeu, this->_consScreen.ScreenHeight - 2, ecPrint::ENTITY);
		} while (heithtPos != this->_consScreen.ScreenHeight - 2);
		heithtPos = {};
	} while (!Loop);
	system("cls");
}

void GameLogic::AiMovment(const std::vector<uint16_t>& genpOS, uint16_t& posOfEntity) //maybe two values, not vector
{
	constexpr uint16_t posMove = 8;
	const auto startValeu = posOfEntity;
	uint16_t count{};
	for (auto& test : genpOS)
	{
		count++;
		if ((test >= (posOfEntity - 2)) && (test <= (posOfEntity + 5)))
		{
			if ((posOfEntity > (this->_consScreen.ScreenThickness + 3)) && (posOfEntity < this->_consScreen.ScreenThickness * 3 - (posMove * genpOS.size())))
			{
				posOfEntity += posMove;
				if (count > 1)
				{
					if ((posOfEntity == startValeu) && (posOfEntity > this->_consScreen.ScreenThickness + 3) && (posOfEntity < this->_consScreen.ScreenThickness * 3 - (posMove * genpOS.size() * genpOS.size())))
					{
						posOfEntity += posMove;
					}
					else
					{
						posOfEntity -= (posMove * 2);
					}
				}
			}
			else
			{
				posOfEntity -= posMove;
				if (count > 1)
				{
					if ((posOfEntity == startValeu) && (posOfEntity > this->_consScreen.ScreenThickness + 3) && (posOfEntity < this->_consScreen.ScreenThickness * 3 - (posMove * genpOS.size() * genpOS.size())))

					{
						posOfEntity += (posMove * 2);
					}
					else
					{
						posOfEntity -= posMove;
					}
				}
			}
		}
	}
}
void GameLogic::ColisionControl(const std::tuple<uint16_t, uint16_t, uint16_t>& PosData, bool& Loop)
{
	//tuple -> heihtPos, midValue, EntityMidValue

	if (this->_consScreen.ScreenHeight - 4 == std::get<0>(PosData))
	{
		if ((std::get<1>(PosData) >= std::get<2>(PosData) - 2) && (std::get<1>(PosData) <= std::get<2>(PosData) + 5))
		{
			Loop = true;
		}
	}
}
