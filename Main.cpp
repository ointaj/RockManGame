#include "Screen.h"
#include "GameLogic.h"
#include "Score.h"
//test

int32_t main()
{
	ConsoleScreen _consScreen(100, 25);
	GameLogic _gameLogic(_consScreen);
	Console _console;
	Score _score(_consScreen,5, "D:/TestPathMyGame/test.txt");

	uint16_t midPos = 0;
	
	_console.setCursor();
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
			const auto choose = _consScreen.chDifficulty();
			bool breakVal = false;
			system("cls");
			_consScreen.Borders();
			_consScreen.DownBorders();
			std::optional<uint16_t> vall = _consScreen.MidPosition();
			do
			{
				_score.ScorePrint(*NameOfPlayer);
				const auto pos = _gameLogic.GenPos(choose.second);
				do
				{
					if (_kbhit())
					{
						_consScreen.ClickTest(_kbhit, breakVal, vall);
					}
					 /*one function later*/
					_gameLogic.CreateEntity(*vall,_consScreen.ScreenHeight - 2, ecPrint::ENTITY);
					uint16_t posPlus{};
					for (auto& test : pos)
					{
						_gameLogic.CreateEntity(test, midPos + posPlus, ecPrint::DROP);
						if (_consScreen.ScreenHeight - 6 == midPos)
						{
							if ((test >= *vall) && (test <= *vall + 5))	
							{
								breakVal = true;
								break; //test this
							}
						}
						posPlus++;
					}
					posPlus = {};
					std::this_thread::sleep_for(choose.first);
					for (auto& test : pos)
					{
						_gameLogic.EraseEntity(test, midPos + posPlus, ecPrint::DROP);
						posPlus++;
					}
					midPos++;
					_gameLogic.EraseEntity(*vall, _consScreen.ScreenHeight-2, ecPrint::ENTITY);

				} while (midPos != _consScreen.ScreenHeight - 2);
				midPos = 0;
				_score.ScoreCounter(choose.second);
			} while (!breakVal);

			if (NameOfPlayer)
			{
				const auto uiScore = _score.fScoreValue();
				const auto scorePoint = _score.ScorePoint();		
				const auto Diff = _consScreen.DiffToString(choose.second);
				const auto saveScore = _score.SaveGameData(std::make_tuple(*NameOfPlayer, uiScore - (scorePoint * choose.second),Diff)); //add dii-ffculty and time i guess
				{
					_score.ShowScore();
				}
			}
			
			system("cls");
		}
	}
	while (true);
}