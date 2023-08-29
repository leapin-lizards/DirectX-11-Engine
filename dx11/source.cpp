#include "renderWIndow.h"
#include "engine.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HRESULT hr = E_INVALIDARG;

	Engine engine;

	if (engine.Initialize(hInstance, "Title", "Mywin", 800,600))
	{
		while (engine.ProcessMessages() == true)
		{
			engine.Update();
			engine.RenderFrame();
			//OutputDebugStringA("YAH\n");
		}
	}

	return 0;
}
