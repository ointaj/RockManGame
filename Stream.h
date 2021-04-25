#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <thread>
#include <utility>
#include <string>
#include <chrono>
#include <optional>
#include <memory>
#include <conio.h>
#include <fstream>
#include <set>
#include <algorithm>

class outStream
{
public:
	template<class... Arg>
	void Print(Arg&&... arv)
	{
		((std::cout << std::forward<Arg>(arv)), ...);
	}
};

template<class ReturnType>
class bInputStrem
{
public:
	ReturnType sInput()
	{
		ReturnType Input;
		std::cin >> Input;
		return Input;
	}
};
