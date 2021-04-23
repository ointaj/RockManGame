#pragma once
#include "Screen.h"
#include <forward_list>

enum class ecPrint : int8_t
{
	DROP,
	ENTITY
};

class bGameLogic
{
public:
	bGameLogic() = default;
	virtual std::vector<std::vector<char>> setEntity(const ecPrint& eEntity) = 0;
	virtual void CreateEntity(const uint16_t& fPos, const uint16_t& sPos, const ecPrint& eEntity) = 0;
	virtual void EraseEntity(const uint16_t& fPos, const uint16_t& sPos, const ecPrint& eEntity) = 0;
	virtual std::vector<uint16_t> GenPos(const uint16_t& Values) = 0;
	virtual void ColisionControl(const std::tuple<uint16_t, uint16_t, uint16_t>& PosData, bool& Loop) = 0;
	virtual void AiLogic(void) = 0;
	virtual void AiMovment(const std::vector<uint16_t>& genpOS, uint16_t& posOfEntity) = 0;
	~bGameLogic() = default;
};

class GameLogic : public bGameLogic
{
	friend class ConsoleScreen;
	using str = std::string;
private:

	uint16_t scWidth{};
	uint16_t scThickness{};
	uint16_t scHeight{};
	str sEmpTy = " ";
public:
	GameLogic() = default;
	GameLogic(const ConsoleScreen& cons) 
		: scWidth(cons.ScreenWidth), scHeight(cons.ScreenHeight),scThickness(cons.ScreenThickness) {}
	virtual std::vector<std::vector<char>> setEntity(const ecPrint& eEntity) override;
	virtual void CreateEntity(const uint16_t& fPos, const uint16_t& sPos, const ecPrint& eEntity) override;
	virtual void EraseEntity(const uint16_t& fPos, const uint16_t& sPos, const ecPrint& eEntity) override;
	virtual std::vector<uint16_t> GenPos(const uint16_t& Values) override;
	virtual void ColisionControl(const std::tuple<uint16_t, uint16_t, uint16_t>& PosData, bool& Loop) override;
	virtual void AiLogic(void) override;
	virtual void AiMovment(const std::vector<uint16_t>& genpOS, uint16_t& posOfEntity) override;
	~GameLogic() = default;
};

