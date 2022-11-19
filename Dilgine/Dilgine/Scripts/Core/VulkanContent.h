#ifndef VULKAN_CONTENT_H
#define VULKAN_CONTENT_H

#include <vector>
#include <optional>

#include "vulkan/vulkan.h"

struct SDL_Window;

struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	//QueueFamilyIndices is complete if graphics family has a value (not null)
	bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
};

class EngineVulkan
{
public:
	//Vulkan Instance
	VkInstance vInstance;

	//Initialize Vulkan
	void InitVulkan(SDL_Window* window);

	//Destroy relevant items
	void Cleanup();

private:

	//Physical graphics card Vulkan will use
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	//Logical device interface
	VkDevice logicalDevice;

	//Use vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue); to get device queue
	//Graphics queue, accepts command buffer to run on GPU
	VkQueue graphicsQueue;
	//Presentation queue
	VkQueue presentQueue;

	//Represents SDL window, Vulkan is platform agnostic and this allows it to interface with an abstract surface that can render images
	VkSurfaceKHR surface;

	//Validation layers to enable
	const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

	//Device extensions to query GPU for support before choosing and later enable
	const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

	//Only use validation layers if not debugging, can just define this macro to turn them off
#ifndef NDEBUG
	const bool enableValidationLayers = false;
#else
	cosnt bool enableValidationLayers = true;
#endif

	void CreateInstance(SDL_Window* window);			//Instance everything is done with
	void InitValidationLayers(VkInstanceCreateInfo* cInfo);	//Debugging symbols
	void ChoosePhysicalDevice();	//Choose which GPU to use, must support everything we need
	void CreateLogicalDevice();		//Create logical interface
	void CreateSurface(SDL_Window* window);

	//Check if validation layers are supported
	bool CheckValidationSupport();

	
	bool CheckDevice(VkPhysicalDevice device); //Check properties and supporting features of the passed GPU
	bool CheckDeviceExtensionSupport(VkPhysicalDevice device);//Check for extension support on a device

	//Find queue families supported by device
	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
};

#endif