#include "engine.h"

bool Engine::Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height)
{
	//Keyboard.EnableAutoRepeatChars();
	timer.Start();
	if (!this->render_window.Initialize(this, hInstance, window_title, window_class, width, height))
	{
		return false;
	}
	if (!this->gfx.Initialize(render_window.GetHWND(), width, height))
	{
		return false;
	}
	return true; 


}
bool Engine::ProcessMessages()
{
	return this->render_window.ProcessMessages();
}

void Engine::Update()
{
	float dt = timer.GetMilisecondsElapsed();
	timer.Restart();
	if (this->gfx.blockInputForImGui)
	{
		return;
	}

	while (!Keyboard.KeyBufferIsEmpty())
	{
		KeyboardEvent kbe = Keyboard.ReadKey();
		unsigned char ch = kbe.GetKeyCode();
		std::string outMsg = "";
		if (kbe.IsPress())
		{
			outMsg += "PressKey:: ";
		}
		if (kbe.IsRelease())
		{
			outMsg += "ReleaseKey ";

		}
		outMsg += ch;
		outMsg += "\n";
		OutputDebugStringA(outMsg.c_str());
	}
	while (!Keyboard.CharBufferIsEmpty())
	{
		
		unsigned char ch = Keyboard.ReadChar();
		std::string outMsg = "Char:: ";
		outMsg += ch;
		outMsg += "\n";
		OutputDebugStringA(outMsg.c_str());
	}
	const float mouseSensetivity = 0.01f;
	while (!Mouse.EventBufferIsEmpty())
	{
		MouseEvent me = Mouse.ReadEvent();

		if (me.GetType() == MouseEvent::EventType::RAW_MOVE&&Mouse.IsLeftDown())
		{
			this->gfx.camera.AdjustRotation((float)me.GetPosY()*mouseSensetivity,(float)me.GetPosX()* mouseSensetivity,0.0f);

			OutputDebugStringA(std::to_string(this->gfx.camera.GetRotationFloat3().x).c_str());

			OutputDebugStringA("   ");
			OutputDebugStringA(std::to_string(this->gfx.camera.GetRotationFloat3().y).c_str());

			OutputDebugStringA("   ");
			OutputDebugStringA(std::to_string(this->gfx.camera.GetRotationFloat3().z).c_str());
			OutputDebugStringA("\n");
		}
		
	}
	const float cameraSpeed = 0.002f;
	const float rotationSpeed = 0.002f;

	this->gfx.gameObject.AdjustRotation(0.0f,rotationSpeed*dt,0.0f);


	if (Keyboard.KeyIsPressed('W'))
	{
		this->gfx.camera.AdjustPosition(this->gfx.camera.GetForwardVector() * cameraSpeed*dt);
	}
	if (Keyboard.KeyIsPressed('S'))
	{
		this->gfx.camera.AdjustPosition(this->gfx.camera.GetBackwardVector() * cameraSpeed * dt);
	}
	if (Keyboard.KeyIsPressed('A'))
	{
		this->gfx.camera.AdjustPosition(this->gfx.camera.GetLeftVector() * cameraSpeed * dt);
	}
	if (Keyboard.KeyIsPressed('D'))
	{
		this->gfx.camera.AdjustPosition(this->gfx.camera.GetRightVector() * cameraSpeed * dt);
	}
}

void Engine::RenderFrame()
{
	gfx.RenderFrame();
}
