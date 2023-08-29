#include "keyboardClass.h"
KeyboardClass::KeyboardClass()
{
	for (int i = 0; i < 256; i++)
	{
		this->KeyStates[i] = false;
	}
}
bool KeyboardClass::KeyIsPressed(unsigned char keycode)
{
	return this->KeyStates[keycode];
}
bool KeyboardClass::KeyBufferIsEmpty()
{
	return this->keybuffer.empty();
}
bool KeyboardClass::CharBufferIsEmpty()
{
	return this->charbuffer.empty();
}
KeyboardEvent KeyboardClass::ReadKey()
{
	if (this->keybuffer.empty())
	{
		return KeyboardEvent();
	}
	else
	{
		KeyboardEvent e = this->keybuffer.front();
		this->keybuffer.pop();
		return e;
	}
}
unsigned char KeyboardClass::ReadChar()
{
	if (this->charbuffer.empty())
	{
		return 0u;
	}
	else
	{
		unsigned char e = this->charbuffer.front();
		this->charbuffer.pop();
		return e;
	}
}
void KeyboardClass::OnKeyPressed(const unsigned char key)
{
	this->KeyStates[key] = true;
	this->keybuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, key));

}
void KeyboardClass::OnKeyReleased(const unsigned char key)
{
	this->KeyStates[key] = false;
	this->keybuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release , key));

}
void KeyboardClass::OnChar(const unsigned char key)
{
	this->charbuffer.push(key);
}

void KeyboardClass::EnableAutoRepeatKeys()
{
	this->autoRepeatKeys = true;
}
void KeyboardClass::EnableAutoRepeatChars()
{
	this->autoRepeatChars = true;
}
void KeyboardClass::DisableAutoRepeatKeys()
{
	this->autoRepeatKeys = false;
}
void KeyboardClass::DisableAutoRepeatChars()
{
	this->autoRepeatChars = false;
}
bool KeyboardClass::IsCharAutoRepeat()
{
	return this->autoRepeatChars;
}
bool KeyboardClass::IsKeyAutoRepeat()
{
	return this->autoRepeatKeys;
}
