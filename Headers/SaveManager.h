#pragma once
#include<vector>
#include"GameStuff.h"
#include"Tick.h"

class SaveManager
{
public:
	static void loadData(vector<Tick*> settings);
	static void saveData(const vector<Tick*> settings);
};

