#ifndef __MVC_VIEW_H__
#define __MVC_VIEW_H__

#include <stdio.h>
#include <stdlib.h>

#define WIN32_LEAN_AND_MEAN // Winsock2 (Networking)

#include <Windows.h>


#define GLFW_INCLUDE_VULKAN
#include <glfw3.h>

// GLM
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <vec4.hpp>
#include <mat4x4.hpp>

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <functional>

// MVC
#include "Model.h"

// Vulkan Deleter Wrapper
#include "VDeleter.h"

// Core
#include "InputHandler.h"
#include "FileReader.h"

// Required Device Extensions
const std::vector<const char *> deviceExtensions = 
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME // Swap Chain Extension
};

class MVCView
{
public:

	struct QueueFamilyIndices
	{
		int graphicsFamily = -1; // Support Graphics
		int presentFamily = -1; // Support Presentation

		bool isComplete()
		{
			return graphicsFamily >= 0 && presentFamily >= 0;
		}
	};

	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	enum PIPELINE_MODE
	{
		PIPELINE_STANDARD,
		PIPELINE_BLEND,
		PIPELINE_WIREFRAME,
	};

public:
	MVCView(MVCModel * model);
	virtual ~MVCView();

	BOOL CreateVulkanWindow(const char * title, int width, int height, int bits);
	BOOL InitVulkan();

	void selectPhysicalDevice(); // Function that selects the Graphic Card(s) to use
	bool isPhysicalDeviceSuitable(VkPhysicalDevice); // Function to check if the Graphic Card(s) are able to do what we want them to do
	int ratePhysicalDeviceSuitability(VkPhysicalDevice); // Rate the graphic card 
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice); // Function to check if the GPU supports graphics commands
	void createLogicalDevice();
	void createSurface();
	void createSwapChain();
	void createSwapChainImageViews();
	void createRenderPass();
	void createGraphicsPipelines();
	void createFrameBuffers();
	void createCommandPool();
	void createCommandBuffers();
	void createSemaphores();
	void createShaderModule(const std::vector<char> &, VDeleter<VkShaderModule> &);
	bool checkDeviceExtensionSupport(VkPhysicalDevice);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &);

public:
	void drawFrame();

	GLFWwindow * getWindow() { return m_window; }
	
	int getWindowWidth();
	int getWindowHeight();

private:
	GLFWwindow * m_window;
	VkViewport m_viewport;

	int m_iWindowWidth;
	int m_iWindowHeight;

	VDeleter<VkInstance> m_instance{ vkDestroyInstance };

	VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
	VDeleter<VkDevice> m_device{ vkDestroyDevice };

	VDeleter<VkSurfaceKHR> m_surface{ m_instance, vkDestroySurfaceKHR };

	VkQueue graphicsQueue;
	VkQueue presentQueue;

	VDeleter<VkSwapchainKHR> m_swapChain{ m_device, vkDestroySwapchainKHR };
	std::vector <VkImage> m_swapChainImages;
	VkFormat m_swapChainImageFormat;
	VkExtent2D m_swapChainExtent;

	std::vector<VDeleter<VkImageView>> m_swapChainImageViews;

	VDeleter<VkPipelineLayout> m_pipelineLayout{ m_device, vkDestroyPipelineLayout };
	VDeleter<VkRenderPass> m_renderPass{ m_device, vkDestroyRenderPass };
	VDeleter<VkPipeline> m_graphicsPipeline{ m_device, vkDestroyPipeline };

	std::vector<VDeleter<VkFramebuffer>> m_swapChainFramebuffers;
	VDeleter<VkCommandPool> m_commandPool{ m_device, vkDestroyCommandPool };
	std::vector<VkCommandBuffer> m_commandBuffers;

	VDeleter<VkSemaphore> m_imageAvailableSemaphore{ m_device, vkDestroySemaphore };
	VDeleter<VkSemaphore> m_renderFinishedSemaphore{ m_device, vkDestroySemaphore };

	MVCModel * MVC_Model;
};

#endif