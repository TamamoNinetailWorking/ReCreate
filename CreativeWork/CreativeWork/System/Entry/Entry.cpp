#include <windows.h>
#include <iostream>

#include <Object/ObjectManager/ObjectManager.h>
#include <BaseSystem/Frame/BaseSystem.h>
#include <BaseSystem/FramePerSec/FramePerSec.h>
#include <CWindow.h>
#include <DirectX11/SystemWrapper/SystemWrapper.h>
#include <DirectX11/PrimaryDevice/DirectX11.h>
#include <Shader/ShaderCast/ShaderCast.h>
#include <Shader/ShaderManager/ShaderManager.h>

#pragma comment(lib,"BaseClass.lib")
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

	/* ShaderManager Init */
	ShaderCast().Init(
		PrimaryDevice().GetDevice(),
		PrimaryDevice().GetImmediateContext());
	ShaderManager().Init(
		PrimaryDevice().GetDevice(),
		PrimaryDevice().GetImmediateContext());

	/* ObjectManager Init */
	ObjectManager().Init();

	return true;
}

//Primary Exit
void PrimaryExit()
{
	ObjectManager().Exit();

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