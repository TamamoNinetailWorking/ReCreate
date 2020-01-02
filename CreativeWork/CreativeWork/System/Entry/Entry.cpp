#include <windows.h>
#include <BaseSystem/Frame/BaseSystem.h>
#include <BaseSystem/FramePerSec/FramePerSec.h>
#include <CWindow.h>

#pragma comment(lib,"BaseSystem.lib")
#pragma comment(lib,"CWindow.lib")

//Truely Main Function
void App();

//Entry Init
bool EntryInit()
{
	CWINDOW* newWindow = new CWINDOW();
	
	if (newWindow == nullptr)
		return false;

	GetSystem().SetWindow(newWindow);
	GetSystem().SetAppFunction(App);

	return true;
}

//Primary Init
bool PrimaryInit()
{
	GetFPSManager().Init(
		GetSystem().GetWindow()->GetHWND(),
		"Sampler");

	return true;
}

//Entry Point
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmd)
{

	if(EntryInit())
	{
		//ウィンドウの初期化
		if (SUCCEEDED(GetSystem().GetWindow()->Create_Window(hInstance, cmd)))
		{
			if (PrimaryInit())
			{
				//メインループ
				GetSystem().SystemLoop();
			}
		}
	}

	return (int)GetSystem().GetWindow()->GetMSG().wParam;
}