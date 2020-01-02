#include <windows.h>
#include <iostream>

#include <BaseSystem/Frame/BaseSystem.h>
#include <BaseSystem/FramePerSec/FramePerSec.h>
#include <CWindow.h>
#include <DirectX11/PrimaryDevice/DirectX11.h>


#pragma comment(lib,"BaseSystem.lib")
#pragma comment(lib,"CWindow.lib")
#pragma comment(lib,"DirectX11.lib")

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
	bool sts;


	/* FPSManager Init */
	GetFPSManager().Init(
		GetSystem().GetWindow()->GetHWND(),
		"Sampler"
	);


	/* DirectX11 Primary Device Init */
	sts = PrimaryDevice().Init(
		GetSystem().GetWindow()->GetHWND(),
		false,
		GetSystem().GetWindow()->GetWindowWidth(),
		GetSystem().GetWindow()->GetWindowHeight()
	);

	if (!sts)
	{
		return false;
	}

	std::cout << " Primary Device is Create Success !!" << std::endl;

	return true;
}

//Primary Exit
void PrimaryExit()
{
	PrimaryDevice().Exit();

	GetFPSManager().Exit();
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

	PrimaryExit();

	return (int)GetSystem().GetWindow()->GetMSG().wParam;
}