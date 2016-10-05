#include "InputHandler.h"
#include "View.h"
//#include "CharBuffer.h"

bool InputHandler::m_pressedKeys[348];
bool InputHandler::m_triggeredKeys[348];
bool InputHandler::m_repeatedKeys[348];

double InputHandler::mX = 0.0;
double InputHandler::mY = 0.0;
double InputHandler::dX = 0.0;
double InputHandler::dY = 0.0;
double InputHandler::last_x = 0.0;
double InputHandler::last_y = 0.0;
double InputHandler::dScroll = 0.0;

bool InputHandler::m_bMouseEnabled = true;
bool InputHandler::m_bKeyboardEnabled = true;
double InputHandler::m_dClickDelay = 0.0;
double InputHandler::m_dPressDelay = 0.0;

InputHandler::InputHandler()
{
	std::cout << "InputHandler Created" << std::endl;

	for (int i = 0; i < GLFW_KEY_LAST; i++)
	{
		m_pressedKeys[i] = false;
		m_triggeredKeys[i] = false;
		m_repeatedKeys[i] = false;
	}
}

void InputHandler::Key_Callback(int key, int scancode, int action, int mods)
{
	if (m_bKeyboardEnabled)
	{
		if (action == GLFW_PRESS)
		{
			{
				PressKey(key);
			}
		}
		else if (action == GLFW_RELEASE)
		{
			{
				PressKey(key, false);
			}
		}
		else if (action == GLFW_REPEAT)
		{
			{
				PressKey(key);
			}
		}
	}
}

void InputHandler::Mouse_Callback(int button, int action, int mods)
{
	if (m_bMouseEnabled)
	{
		if (action == GLFW_PRESS)
		{
			PressKey(button);
		}
		else if (action == GLFW_RELEASE)
		{
			PressKey(button, false);
		}
		else if (action == GLFW_REPEAT)
		{
			PressKey(button);
		}
	}
}

void InputHandler::PressKey(int key, bool status)
{
	if (status)
	{
		// Check if key is pressed
		if (m_pressedKeys[key] == false)
		{
			// Set to true
			m_pressedKeys[key] = true;
			if (m_triggeredKeys[key] == false)
			{
				m_triggeredKeys[key] = true;
#if _DEBUG
				std::cout << key << " has been triggered" << std::endl;
#endif
			}
			else
			{
				m_triggeredKeys[key] = false;
#if _DEBUG
				std::cout << key << " has been un-triggered" << std::endl;
#endif
			}
		}
		else
		{
			// Key is still being pressed
			m_repeatedKeys[key] = true;
#if _DEBUG
			std::cout << key << " is being pressed repeatedly" << std::endl;
#endif
		}
	}
	else
	{
		// Key is not pressed anymore
		m_pressedKeys[key] = false;
		m_repeatedKeys[key] = false;
#if _DEBUG
		std::cout << "Setting " << key << " to false" << std::endl;
#endif
	}
}

void InputHandler::KeyboardUpdate(MVCView * theView, double dt)
{
	m_dPressDelay += dt;
}

void InputHandler::MouseUpdate(MVCView * theView, double dt)
{
	if (m_dClickDelay > 0.0)
	{
		m_dClickDelay -= dt;
	}

	glfwGetCursorPos(theView->getWindow(), &mX, &mY);

	float screenXmid = (float)theView->getWindowWidth() * 0.5f;
	float screenYmid = (float)theView->getWindowHeight() * 0.5f;


	dX = (screenXmid - mX);
	dY = (screenYmid - (ceil)(mY));

	dX *= 0.15;
	dY *= 0.15;

	if (m_bMouseEnabled == false)
	{
		glfwSetInputMode(theView->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPos(theView->getWindow(), screenXmid, screenYmid);
	}
	else
	{
		glfwSetInputMode(theView->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

bool InputHandler::IsKeyPressed(int key)
{
	return m_pressedKeys[key];
}

bool InputHandler::IsKeyTriggered(int key)
{
	return m_triggeredKeys[key];
}

bool InputHandler::IsKeyRepeating(int key) 
{
	return m_repeatedKeys[key];
}

bool InputHandler::isKeyboardEnabled()
{
	return m_bKeyboardEnabled;
}

void InputHandler::setKeyboardEnabled(bool status)
{
	m_bKeyboardEnabled = status;
}

void InputHandler::setMouseX(double newX)
{
	mX = newX;
}

void InputHandler::setMouseY(double newY)
{
	mY = newY;
}

void InputHandler::setDeltaScroll(double newDs)
{
	dScroll = newDs;
}

void InputHandler::setClickDelay(double delay)
{
	m_dClickDelay = delay;
}

void InputHandler::setPressDelay(double delay)
{
	m_dPressDelay = delay;
}

double InputHandler::getDeltaX()
{
	return dX;
}

double InputHandler::getDeltaY()
{
	return dY;
}

bool InputHandler::isMouseEnabled()
{
	return m_bMouseEnabled;
}

void InputHandler::setMouseEnabled(bool status)
{
	m_bMouseEnabled = status;
}

double InputHandler::getMouseX()
{
	return mX;
}

double InputHandler::getMouseY()
{
	return mY;
}

double InputHandler::getClickDelay()
{
	return m_dClickDelay;
}

double InputHandler::getPressDelay()
{
	return m_dPressDelay;
}

void InputHandler::resetMousePosition(MVCView * theView)
{
	glfwSetCursorPos(theView->getWindow(),theView->getWindowWidth() * 0.5, theView->getWindowHeight() * 0.5);
}