#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#pragma warning(disable:4018)
#pragma warning(disable:4227)

#define PRESS_DELAY 0.25

#include <iostream>

class MVCView;

//#include "CharBuffer.h"

// Singleton InputHandler

class InputHandler
{
public:
	static InputHandler & getInstance()
	{
		static InputHandler inputHandler;
		return inputHandler;
	}
private:
	InputHandler();
public:
	InputHandler(InputHandler & const) = delete;
	void operator=(InputHandler & const) = delete;

	// Callbacks
	static void Key_Callback(int key, int scancode, int action, int mods);
	static void Mouse_Callback(int button, int action, int mods);

	// Keyboard
	static void PressKey(int key, bool status = true);

	static bool IsKeyPressed(int key);
	static bool IsKeyTriggered(int key);
	static bool IsKeyRepeating(int key);

	static bool isKeyboardEnabled();
	static void setKeyboardEnabled(bool status);

	// Mouse
	static void setMouseX(double newX);
	static void setMouseY(double newY);
	static void setDeltaScroll(double newDs);

	static double getDeltaX();
	static double getDeltaY();

	static double getMouseX();
	static double getMouseY();

	static bool isMouseEnabled();
	static void setMouseEnabled(bool status);

	static void resetMousePosition(MVCView * theView);

	// Generic Functions
	static void MouseUpdate(MVCView * theView, double dt);
	static void KeyboardUpdate(MVCView * theView, double dt);
	static void setClickDelay(double delay);
	static double getClickDelay();
	static void setPressDelay(double delay);
	static double getPressDelay();

	// Buffer
	/*CharBuffer * addNewBuffer();
	CharBuffer * getBuffer(int index);
	void deleteBuffer();
	void setBufferMode(bool status);
	bool getBufferMode();
	void resetBuffer();*/
private:
	static bool m_pressedKeys[348];
	static bool m_triggeredKeys[348];
	static bool m_repeatedKeys[348];

	static double mX, mY;
	static double dX, dY;
	static double last_x, last_y;
	static double dScroll;

	static bool m_bMouseEnabled;
	static bool m_bKeyboardEnabled;
	static double m_dClickDelay;
	static double m_dPressDelay;

	/*bool m_bBufferMode;
	std::vector<CharBuffer*> m_charBufferList;*/
};

#endif