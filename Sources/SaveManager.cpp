#include <fstream>
#include "SaveManager.h"
using namespace std;

void SaveManager::saveData(const vector<Tick*> settings)
{
	//1->fullscreen, 2->music on, 3-> sound on
	ofstream file("Data.PONG");
	for (Tick* b : settings)
		file << b->getTicked() << '\n';
	file << Stuff::rezProp << '\n';
}

void SaveManager::loadData(vector<Tick*> settings)
{
	bool t;
	ifstream file("Data.PONG");
	for (Tick* b : settings)
	{
		file >> t;
		b->setTicked(t);
	}
	file >> Stuff::rezProp;
}
 