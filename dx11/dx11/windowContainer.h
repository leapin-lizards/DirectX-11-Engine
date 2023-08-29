#pragma once
#include "renderWIndow.h"
#include "Keyboard/keyboardClass.h"
#include "Mouse/mouseClass.h"
#include "Graphics/graphics.h"
class WindowContainer {
public:
	WindowContainer();
	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM LParam);
protected:
	RenderWindow render_window;
	KeyboardClass Keyboard;
	MouseClass Mouse;
	Graphics gfx;
private:

};