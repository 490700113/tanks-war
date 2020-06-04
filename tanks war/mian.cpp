#include <Windows.h>
#include "AllSettings.h"
#include "CWindows.h"

int main()
{
	CWindows* playthegame = new CWindows;
	playthegame->Loadgame();
	delete playthegame;
}

//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	CWindows* playthegame = new CWindows;
//	playthegame->Loadgame();
//	delete playthegame;
//	return 0;
//}
