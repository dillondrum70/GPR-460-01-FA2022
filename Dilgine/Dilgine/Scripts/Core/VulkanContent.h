#ifndef VULKAN_CONTENT_H
#define VULKAN_CONTENT_H

#define DEBUGGING

#include <vector>
#include <optional>
#include <fstream>
#include <array>

#include "vulkan/vulkan.h"
#include "SDL2/SDL.h"
#include "glm/glm.hpp"

const int MAX_FRAMES_IN_FLIGHT = 2;

struct SDL_Window;

struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	//QueueFamilyIndices is complete if graphics family has a value (not null)
	bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
};

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;			//Minimum and maximum capabilities of swap chain
	std::vector<VkSurfaceFormatKHR> formats;		//Surface formats
	std::vector<VkPresentModeKHR> presentModes;		//Available presentation modes
};

struct Vertex
{
	glm::vec2 position;
	glm::vec3 color;

	//Defines how to pass Vertex data format
	static VkVertexInputBindingDescription GetBindingDescription()
	{
		//Define rate to load data from memory, bytes  betweend data entries
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;	//Move to next data entry after each vertex

		return bindingDescription;
	}

	//How to handle vertex input
	static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions()
	{
		//Two  descriptions tell us how to extract vertex attribute from vertex data in binding description, one for position, one for color
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
		attributeDescriptions[0].binding = 0;							//Which binding the per-vertex data comes from
		attributeDescriptions[0].location = 0;							//location directive of input in vertex shader
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;		//Type of data, R32G32 is same as vec2, 2 x 32 bit values
		attributeDescriptions[0].offset = offsetof(Vertex, position);	//Number of bytes since start of per-vertex data to read from

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, position);

		return attributeDescriptions;
	}
};

//Vertex data, position-color pairs
const std::vector<Vertex> vertices = {
		{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
		{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
};

class EngineVulkan
{
public:
	
	VkInstance vInstance;		//Vulkan Instance
	VkDevice logicalDevice;		//Logical device interface

	//Use vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue); to get device queue
	VkQueue graphicsQueue;								//Graphics queue, accepts command buffer to run on GPU
	VkQueue presentQueue;								//Presentation queue

	VkSwapchainKHR swapChain;				//Swapchain object

	std::vector<VkCommandBuffer> commandBuffers;	//Commands to change anything are submitted to this buffer

	//Used to synchronize GPU processes, i.e. can't run render until we have image
	std::vector <VkSemaphore> imageAvailableSemaphores;
	std::vector <VkSemaphore> renderFinishedSemaphores;
	std::vector <VkFence> inFlightFences;		//Pauses CPU until GPU finishes specified process

	VkBuffer vertexBuffer;	//Stores list of vertices that define triangles
	
	bool framebufferResized = false;

	uint32_t currentFrame = 0;

	//Initialize Vulkan
	void InitVulkan(SDL_Window* window);

	//Destroy relevant items
	void Cleanup();

	//Sumbit command to command buffer
	void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	//Recreate swapchain in the case that it is invalidated, i.e. resized
	void RecreateSwapChain(SDL_Window* window);

	//Callback for when framebuffer is resized, data will be an SDL_Window* and sdlEvent will be WINDOW_EVENT type with WINDOWEVENT_RESIZED event
	static int FramebufferResizeCallback(void* data, SDL_Event* sdlEvent);

private:

	VkDebugUtilsMessengerEXT debugMessenger;

	
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;	//Physical graphics card Vulkan will use

	VkSurfaceKHR surface;	//Represents SDL window, Vulkan is platform agnostic and this allows it to interface with an abstract surface that can render images
	
	
	std::vector<VkImage> swapChainImages;	//Images in swap chain that are referenced during rendering
	VkFormat swapChainImageFormat;			//store swap chain image info
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;

	VkRenderPass renderPass;			//The actual render pass object
	VkPipelineLayout pipelineLayout;	//Defines how uniforms are passed to shaders
	VkPipeline graphicsPipeline;		//Graphics pipeline object

	std::vector<VkFramebuffer> swapChainFramebuffers;	//Frames are submitted to this buffer, how and when they are drawn is defined elsewhere

	VkCommandPool commandPool;	//Manage memory used to store command buffers

	//Validation layers to enable
	const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

	//Device extensions to query GPU for support before choosing and later enable
	const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

	//Only use validation layers if not debugging, can just define this macro to turn them off
#ifndef DEBUGGING
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

	void CreateInstance(SDL_Window* window);				//Instance everything is done with
	void CreateDebugMessenger();							//Create messenger for printing validation layer errors
	void CreateSurface(SDL_Window* window);					//Platform agnostic representation of actual window that is drawn to
	void InitValidationLayers(VkInstanceCreateInfo* cInfo);	//Debugging symbols
	void ChoosePhysicalDevice();							//Choose which GPU to use, must support everything we need
	void CreateLogicalDevice();								//Create logical interface
	void CreateSwapChain(SDL_Window* window);				//Determine and create parameters for drawing
	void CreateImageViews();								//The view of an image, specifies how and what part of image to access
	void CreateRenderPass();								//Handles information regarding rendering
	void CreateGraphicsPipeline();							//Handles rendering steps like vertex, geometry, and fragment shaders
	void CreateFramebuffers();								//Render pass attachments are used here, references VkImageView objects
	void CreateCommandPool();								//Manage command buffer memory and allocate command buffers from here
	void CreateVertexBuffer();								//Buffer of vertices that define triangles
	void CreateCommandBuffers();							//All operations that are to be done are stored here
	void CreateSyncObjects();								//Create Semaphores and Fences
	
	//Check if validation layers are supported
	bool CheckValidationSupport();

	//Callback function for debug messaging
	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

	//Create debug messensger object
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

	//Populate debug create info struct
	void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	//Destroy debug messenger
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
	
	bool CheckDevice(VkPhysicalDevice device); //Check properties and supporting features of the passed GPU
	bool CheckDeviceExtensionSupport(VkPhysicalDevice device);//Check for extension support on a device

	//Find queue families supported by device
	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

	//Populate SwapChainSupportDetails
	SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

	//Determine surface format
	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

	//Determine best present mode
	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

	//Choosing resolution of swap chain images
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, SDL_Window* window);

	//Read bytes from a file and return a byte array
	static std::vector<char> ReadFile(const std::string& filename);

	//Creates a shader module from given code
	VkShaderModule CreateShaderModule(const std::vector<char>& code);

	//Cleanup last swapchain before recreation
	void CleanupSwapChain();

	//GPUs offer different types of memory to allocate from
	uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};

#endif