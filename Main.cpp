#include "Screen.h"
#include "GameLogic.h"
#include "Score.h"

int32_t main()
{
	ConsoleScreen _consScreen(100, 25);
	GameLogic _gameLogic(_consScreen);
	Console _console;
	Score _score(_consScreen,5, "D:/TestPathMyGame/test.txt");

	_console.setCursor();
	_consScreen.Welcome();
	const auto NameOfPlayer = _score.ChooseFileSave();
	_score.PathTest();
	do
	{
		system("cls");
		_score.SetScorePoints();
		const auto mainStart = _consScreen.MainStart();		
		if (mainStart == Start::INSTRUCTIONS)
		{
			_consScreen.Borders();
			_gameLogic.AiLogic();
		}
		else if (mainStart == Start::START)
		{
			system("cls");
			const auto DifficultyChoose = _consScreen.chDifficulty();
			system("cls");
			_consScreen.Borders();
			_consScreen.DownBorders();
			bool breakVal = false;
			std::optional<uint16_t> ouiMidPos = _consScreen.MidPosition();
			uint16_t MiddlePosition{};
			do
			{
				_score.ScorePrint(*NameOfPlayer);
				const auto GeneratedEntityPos = _gameLogic.GenPos(DifficultyChoose.second);
				do
				{
					if (_kbhit())
					{
						_consScreen.ClickTest(_kbhit, breakVal, ouiMidPos);
					}
					_gameLogic.CreateEntity(*ouiMidPos,_consScreen.ScreenHeight - 2, ecPrint::ENTITY);
					uint16_t PositionMove{};

					for (auto& _GeneratedEntityPos : GeneratedEntityPos)
					{
						_gameLogic.CreateEntity(_GeneratedEntityPos, MiddlePosition + PositionMove, ecPrint::DROP);
						if (_consScreen.ScreenHeight - 6 == MiddlePosition)
						{
							if ((_GeneratedEntityPos >= *ouiMidPos) && (_GeneratedEntityPos <= *ouiMidPos + 5))
							{
								breakVal = true;
								break; 
							}
						}
						PositionMove++;
					}
					PositionMove = {};
					std::this_thread::sleep_for(DifficultyChoose.first);
					for (auto& _GeneratedEntityPos : GeneratedEntityPos)
					{
						_gameLogic.EraseEntity(_GeneratedEntityPos, MiddlePosition + PositionMove, ecPrint::DROP);
						PositionMove++;
					}
					MiddlePosition++;
					_gameLogic.EraseEntity(*ouiMidPos, _consScreen.ScreenHeight - 2, ecPrint::ENTITY);

				} while (MiddlePosition != _consScreen.ScreenHeight - 2);
				MiddlePosition = 0;
				_score.ScoreCounter(DifficultyChoose.second);
			} while (!breakVal);

			if (NameOfPlayer)
			{
				const auto uiScore = _score.fScoreValue();
				const auto scorePoint = _score.ScorePoint();		
				const auto Diff = _consScreen.DiffToString(DifficultyChoose.second);
				const auto saveScore = _score.SaveGameData(std::make_tuple(*NameOfPlayer, uiScore - (scorePoint * DifficultyChoose.second),Diff));
				_score.ShowScore();
			}
			system("cls");
		}
	}
	while (true);
}