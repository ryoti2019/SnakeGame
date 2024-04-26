#include <DxLib.h>
#include "main.h"
#include "class/Scene/SceneMng.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{	
	SceneMng sceneMng;

	sceneMng.Run();

	return 0;
}