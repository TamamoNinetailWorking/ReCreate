#include <windows.h>
#include <iostream>

#include <BaseSystem/Frame/BaseSystem.h>
#include <BaseSystem/FramePerSec/FramePerSec.h>
#include <CWindow.h>
#include <DirectX11/SystemWrapper/SystemWrapper.h>

#include <d3d11.h>


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

	/* System Wrapper Init */
	sts = GraphicsSystem().Init(
		GetSystem().GetWindow()->GetHWND(),
		GetSystem().GetWindow()->GetWindowWidth(),
		GetSystem().GetWindow()->GetWindowHeight(),
		false);
	if (!sts)
	{
		return false;
	}

	std::cout << "Create Successfull GraphicsSystem!!" << std::endl;

	return true;
}

//Primary Exit
void PrimaryExit()
{
	GraphicsSystem().Exit();

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