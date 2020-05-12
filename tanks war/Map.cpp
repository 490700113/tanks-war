#include "Map.h"
#include <iostream>
#include <fstream>


Map::Map()
{
	chooseMap();
}

void Map::ChangeLevel(int level)
{
	chooseMap(level);
}