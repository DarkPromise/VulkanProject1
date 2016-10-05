#include "Controller.h"

MVCController::MVCController(MVCModel * MVC_Model, MVCView * MVC_View)
: MVC_Model(MVC_Model)
, MVC_View(MVC_View)
{
	std::cout << "Controller Created" << std::endl;
}

MVCController::~MVCController()
{

}

void MVCController::RunLoop()
{
	bool Loop = true;

	InputHandler::getInstance(); // Create Input Handler Singleton

	if (this->MVC_View->CreateVulkanWindow("Vulkan Window", 800, 600, 32))
	{
		std::cout << "Vulkan Window Created\n" << std::endl;
	}
	else
	{
		std::cout << "Failed to create Window" << std::endl;
	}

	do
	{

		if (glfwWindowShouldClose(this->MVC_View->getWindow()) || InputHandler::IsKeyPressed(GLFW_KEY_ESCAPE))
		{
			glfwDestroyWindow(this->MVC_View->getWindow());
			Loop = false;
		}
		else
		{
			if (InputHandler::IsKeyPressed(GLFW_KEY_1))
			{

			}
			glfwPollEvents();
			this->MVC_View->drawFrame();
		}

	} while (Loop);

}