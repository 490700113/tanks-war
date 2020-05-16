#include <iostream>
#include <fstream>
#include "Map.h"
#include "Picture.h"

Map::Map()
{
	chooseMap();
}

void Map::ChangeLevel(int level)
{
	chooseMap(level);
}