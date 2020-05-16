#include <Windows.h>
#include "AllSettings.h"
#include "Windows.h"

int main()
{
	Windows* playthegame = new Windows;
	playthegame->Loadgame();
	delete playthegame;
}