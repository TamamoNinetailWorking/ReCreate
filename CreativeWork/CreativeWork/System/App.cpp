//main application
#include <BaseSystem/FramePerSec/FramePerSec.h>

void PrimaryMain();

void TestMain();

void App()
{

	GetFPSManager().ReadyTime();
	if (GetFPSManager().CheckTime())
	{
		GetFPSManager().UpdateTime();
		GetFPSManager().DrawWindowBezel();

		//PrimaryMain();
		TestMain();
	}
	GetFPSManager().ReadyTime();
	GetFPSManager().Measurement_FPS();

	return;
}