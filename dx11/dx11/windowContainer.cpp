#include "windowContainer.h"
WindowContainer::WindowContainer()
{
	//init the raw input device to our MOUSE
	static bool raw_input_init = false;
	if (raw_input_init == false)
	{
		RAWINPUTDEVICE rid;
		rid.usUsagePage = 0x01;
		rid.usUsage = 0x02;
		rid.dwFlags = 0;
		rid.hwndTarget = NULL;
		if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == false)
		{
			ErrorLogger::Log(GetLastError(), "failed to register raw input device");
			exit(-1);
			//failed
		}
	}
	raw_input_init = true;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
LRESULT WindowContainer::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
		return true;

	switch(uMsg)
	{
	case WM_KEYDOWN:
	{
		unsigned char ch = static_cast<unsigned char>(wParam);
		Keyboard.EnableAutoRepeatKeys();
		if (Keyboard.IsKeyAutoRepeat())
		{
			Keyboard.OnKeyPressed(ch);
		}
		else
		{
			const bool wasPressed = lParam & 0x40000000;
			if (!wasPressed)
			{
				Keyboard.OnKeyPressed(ch);
			}

		}
		return 0;

	}
	case WM_KEYUP:
	{
		unsigned char ch = static_cast<unsigned char>(wParam);
		Keyboard.OnKeyReleased(ch);
		return 0;

	}
	case WM_CHAR:
	{
		unsigned char ch = static_cast<unsigned char>(wParam);
		if (Keyboard.IsCharAutoRepeat())
		{
			Keyboard.OnChar(ch);
		}
		else
		{
			const bool wasPressed = lParam & 0x40000000;
			if (!wasPressed)
			{
				Keyboard.OnChar(ch);
			}
		}
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		Mouse.OnMouseMove(x, y);

		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		Mouse.OnLeftPressed(x, y);

		return 0;
	}
	case WM_LBUTTONUP:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		Mouse.OnLeftReleased(x, y);

		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		Mouse.OnRightPressed(x, y);

		return 0;
	}
	case WM_RBUTTONUP:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		Mouse.OnRightReleased(x, y);

		return 0;
	}
	case WM_MBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		Mouse.OnMiddlePressed(x, y);

		return 0;
	}
	case WM_MBUTTONUP:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		Mouse.OnMiddlePressed(x, y);

		return 0;
	}
	case WM_MOUSEWHEEL:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
		{
			Mouse.OnWheelUp(x, y);
		}
		if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
		{
			Mouse.OnWheelDown(x, y);
		}
		return 0;
	}
	case WM_INPUT:
	{
		UINT dataSize;
		GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));
		if (dataSize > 0)
		{
			RAWINPUT* rawdata = new RAWINPUT;
			if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, rawdata, &dataSize, sizeof(RAWINPUTHEADER))==dataSize)
			{
				if (rawdata->header.dwType == RIM_TYPEMOUSE)
				{
					Mouse.OnMouseMoveRaw(rawdata->data.mouse.lLastX, rawdata->data.mouse.lLastY);
				}
			}
			delete(rawdata);

		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}