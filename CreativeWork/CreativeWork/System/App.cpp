//main application
#include <BaseSystem/FramePerSec/FramePerSec.h>

void PrimaryMain();

void App()
{

	GetFPSManager().ReadyTime();
	if (GetFPSManager().CheckTime())
	{
		GetFPSManager().UpdateTime();
		GetFPSManager().DrawWindowBezel();

		PrimaryMain();
	}
	GetFPSManager().ReadyTime();
	GetFPSManager().Measurement_FPS();

	return;
}