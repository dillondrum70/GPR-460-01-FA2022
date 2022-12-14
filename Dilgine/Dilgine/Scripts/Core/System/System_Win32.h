#ifndef SYSTEM_WIN32_H
#define SYSTEM_WIN32_H

#ifdef _WIN32
// THIS IS WINDOWS-ONLY
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <crtdbg.h>

#include "System_Common.h"

namespace gpr460
{

	//filenames
	const gpr460::string FILENAME_ERROR = L"GameErrors.txt";
	const gpr460::string FILENAME_LEVEL0 = L"level0.dat";

	//error constants
	const gpr460::string ERROR_PRESSED_K = L"Error: User pressed 'k'";

	const gpr460::string ERROR_CREATE_SDL_RENDERER_FAILED = L"Error: Creation of SDL_Renderer failed";
	const gpr460::string ERROR_MISSING_ENGINE_RENDERER = L"Error: Could not get SDL_Renderer* renderer on engine";

	//Vulkan Errors
	const gpr460::string ERROR_CREATE_VULKAN_INSTANCE_FAILED = L"Error: Creation of Vulkan Instance failed";
	const gpr460::string ERROR_CREATE_DEBUG_MESSENGER_FAILED = L"Error: Creation of Vulkan Debug Messenger failed";
	const gpr460::string ERROR_VALIDATION_LAYER_DNE = L"Error: One or more validation layers were not found";
	const gpr460::string ERROR_NO_GPU_VULKAN_SUPPORT = L"Error: Failed to find GPUs with Vulkan support";
	const gpr460::string ERROR_NO_CAPABLE_GPU = L"Error: Failed to find capable GPU";
	const gpr460::string ERROR_QUEUE_FAMILY_INCOMPLETE = L"Error: Queue families incomplete";
	const gpr460::string ERROR_EXTENSIONS_UNSUPPORTED = L"Error: One or more extensions are not supported";
	const gpr460::string ERROR_SWAP_CHAIN_INADEQUATE = L"Error: Swap chain is inadequate";
	const gpr460::string ERROR_CREATE_LOGICAL_DEVICE_FAILED = L"Error: Creation of Vulkan logical device failed";
	const gpr460::string ERROR_CREATE_SURFACE_FAILED = L"Error: Creation of Vulkan surface failed";
	const gpr460::string ERROR_CREATE_SWAPCHAIN_FAILED = L"Error: Creation of Vulkan swapchain failed";
	const gpr460::string ERROR_CREATE_IMAGE_VIEW_FAILED = L"Error: Creation of Vulkan image view failed";
	const gpr460::string ERROR_OPEN_FILE_VULKAN_FAILED = L"Error: Failed to open a file for Vulkan";
	const gpr460::string ERROR_CREATE_SHADER_MODULE_FAILED = L"Error: Failed to create shader module";
	const gpr460::string ERROR_CREATE_PIPELINE_LAYOUT_FAILED = L"Error: Failed to create pipeline layout";
	const gpr460::string ERROR_CREATE_RENDER_PASS_FAILED = L"Error: Failed to create render pass";
	const gpr460::string ERROR_CREATE_PIPELINE_FAILED = L"Error: Failed to create graphics pipeline";
	const gpr460::string ERROR_CREATE_FRAMEBUFFER_FAILED = L"Error: Failed to create frame buffer";
	const gpr460::string ERROR_ALLOCATE_COMMAND_BUFFER_FAILED = L"Error: Failed to allocate command buffers";
	const gpr460::string ERROR_BEGIN_COMMAND_BUFFER_FAILED = L"Error: Failed to begin command buffer";
	const gpr460::string ERROR_RECORD_COMMAND_BUFFER_FAILED = L"Error: Failed to record command buffer";
	const gpr460::string ERROR_CREATE_SEMAPHORES_AND_FENCES_FAILED = L"Error: Failed to create semaphores and fences";
	const gpr460::string ERROR_SUBMIT_DRAW_FAILED = L"Error: Failed to submit draw command buffer";
	const gpr460::string ERROR_ACQUIRE_SWAPCHAIN_IMAGE_FAILED = L"Error: Failed to acuire swapchain image";
	const gpr460::string ERROR_PRESENT_SWAPCHAIN_IMAGE_FAILED = L"Error: Failed to present swapchain image";
	const gpr460::string ERROR_CREATE_BUFFER_FAILED = L"Error: Failed to create buffer";
	const gpr460::string ERROR_FIND_MEMORY_TYPE_FAILED = L"Error: Failed to find memory type";
	const gpr460::string ERROR_ALLOCATE_BUFFER_FAILED = L"Error: Failed to allocate buffer memory";
	const gpr460::string ERROR_CREATE_DESCRIPTOR_SET_LAYOUT_FAILED = L"Error: Failed to create descriptor set layout";
	const gpr460::string ERROR_CREATE_DESCRIPTOR_POOL_FAILED = L"Error: Failed to create descriptor pool";
	const gpr460::string ERROR_ALLOCATE_DESCRIPTOR_SETS_FAILED = L"Error: Failed to allocate descriptor sets";
	const gpr460::string ERROR_LOAD_TEXTURE_IMAGE_FAILED = L"Error: Failed to load texture image";
	const gpr460::string ERROR_CREATE_TEXTURE_IMAGE_FAILED = L"Error: Failed to create texture image";
	const gpr460::string ERROR_ALLOCATE_TEXTURE_IMAGE_FAILED = L"Error: Failed to allocate texture image memory";
	const gpr460::string ERROR_UNSUPPORTED_LAYOUT_TRANSITION_FAILED = L"Error: Unsupported layout transition";
	const gpr460::string ERROR_CREATE_TEXTURE_IMAGE_VIEW_FAILED = L"Error: Failed to create texture image view";
	const gpr460::string ERROR_CREATE_TEXTURE_SAMPLER_FAILED = L"Error: Failed to create texture sampler";
	const gpr460::string ERROR_FIND_SUPPORTED_FORMAT_FAILED = L"Error: Failed to find supported format";
	const gpr460::string ERROR_LOADING_MODEL_FAILED = L"Error: Failed to load model";

	const gpr460::string ERROR_MISSING_GAMEOBJECT_REFERENCE = L"Error: Missing Reference to GameObject";
	const gpr460::string ERROR_MISSING_TRANSFORM_REFERENCE = L"Error: Missing Reference to Transform Component";
	const gpr460::string ERROR_MISSING_RECTCOLLIDER_REFERENCE = L"Error: Missing Reference to RectangularCollider Component";
	const gpr460::string ERROR_MISSING_RECTRENDERER_REFERENCE = L"Error: Missing Reference to RectangularRenderer Component";

	const gpr460::string ERROR_COMPONENT_EXISTS = L"Error: Component to be created already exists";

	const gpr460::string ERROR_GAMEOBJECT_OVERFLOW = L"Error: Too many game objects";
	const gpr460::string ERROR_COMPONENT_OVERFLOW = L"Error: Too many components";
	const gpr460::string ERROR_VULKAN_OBJECT_OVERFLOW = L"Error: Too many vulkan objects";


	const gpr460::string ERROR_LEVEL_OPEN_FAIL = L"Level data file failed to open";

	class System_Win32 : public System
	{
		~System_Win32() override {}

		void Init() override;

		void TrackMemory() override;
		void LogMemory() override;

		void Shutdown() override;

		void ErrorMessage(const gpr460::string& message) override;

		void LogToErrorFile(const gpr460::string& message) override;

		_CrtMemState memState;

		HANDLE errorFile;
	};

}
#endif

#endif