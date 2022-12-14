#include "GameObject.h"

#include "System.h"

#include "SDL2/SDL.h"

GameObject::~GameObject()
{
	/*if (renderer)
	{
		delete renderer;
		renderer = nullptr;
	}
	if (collider)
	{
		delete collider;
		collider = nullptr;
	}
	if (player)
	{
		delete player;
		player = nullptr;
	}
	if (colorChanger)
	{
		delete colorChanger;
		colorChanger = nullptr;
	}*/
}

void GameObject::CreateTransform(GameObject& rObj, Vector3 vPos, Vector3 vRot, Vector3 vScale)
{
	World* world = gpr460::engine->world;
	if (world->activeTransforms + 1 >= gpr460::MAX_GAMEOBJECTS)
	{
		gpr460::engine->system->ErrorMessage(gpr460::ERROR_COMPONENT_OVERFLOW);
		gpr460::engine->system->LogToErrorFile(gpr460::ERROR_COMPONENT_OVERFLOW);
	}

	world->GetComponents().transformComponents[world->activeTransforms] = Transform(vPos, vRot, vScale);
	rObj.SetTransform(&world->GetComponents().transformComponents[world->activeTransforms]);
	world->activeTransforms++;
}

void GameObject::CreateRectangleRenderer(GameObject& rObj, int vWidth, int vheight, Vector3 vColor)
{
	World* world = gpr460::engine->world;
	if (world->activeRectRenderers + 1 >= gpr460::MAX_GAMEOBJECTS)
	{
		gpr460::engine->system->ErrorMessage(gpr460::ERROR_COMPONENT_OVERFLOW);
		gpr460::engine->system->LogToErrorFile(gpr460::ERROR_COMPONENT_OVERFLOW);
	}

	world->GetComponents().rectRendererComponents[world->activeRectRenderers] = RectangleRenderer(vWidth, vheight, vColor, &(world->GetGameObjects()[world->activeGameObjects]));
	rObj.SetRectRenderer(&(world->GetComponents().rectRendererComponents[world->activeRectRenderers]));
	world->activeRectRenderers++;
}

void GameObject::CreateRectangleCollider(GameObject& rObj, int vWidth, int vHeight)
{
	World* world = gpr460::engine->world;
	if (world->activeRectColliders + 1 >= gpr460::MAX_GAMEOBJECTS)
	{
		gpr460::engine->system->ErrorMessage(gpr460::ERROR_COMPONENT_OVERFLOW);
		gpr460::engine->system->LogToErrorFile(gpr460::ERROR_COMPONENT_OVERFLOW);
	}

	world->GetComponents().rectColliderComponents[world->activeRectColliders] = RectangleCollider(vWidth, vHeight, &(world->GetGameObjects()[world->activeGameObjects]));
	rObj.SetCollider(&(world->GetComponents().rectColliderComponents[world->activeRectColliders]));
	world->activeRectColliders++;
}

void GameObject::CreatePlayerController(GameObject& rObj, float vSpeed)
{
	World* world = gpr460::engine->world;
	if (world->activePlayerControllers + 1 >= gpr460::MAX_GAMEOBJECTS)
	{
		gpr460::engine->system->ErrorMessage(gpr460::ERROR_COMPONENT_OVERFLOW);
		gpr460::engine->system->LogToErrorFile(gpr460::ERROR_COMPONENT_OVERFLOW);
	}

	world->GetComponents().playerControllerComponents[world->activePlayerControllers] = (PlayerController(vSpeed, &(world->GetGameObjects()[world->activeGameObjects])));
	rObj.SetPlayer(&(world->GetComponents().playerControllerComponents[world->activePlayerControllers]));
	world->activePlayerControllers++;
}

void GameObject::CreateCollisionColorChange(GameObject& rObj, Vector3 vColor)
{
	World* world = gpr460::engine->world;
	if (world->activeColorChange + 1 >= gpr460::MAX_GAMEOBJECTS)
	{
		gpr460::engine->system->ErrorMessage(gpr460::ERROR_COMPONENT_OVERFLOW);
		gpr460::engine->system->LogToErrorFile(gpr460::ERROR_COMPONENT_OVERFLOW);
	}

	world->GetComponents().colorChangeComponents[world->activeColorChange] = CollisionColorChanger(vColor, &(world->GetGameObjects()[world->activeGameObjects]));
	rObj.SetColorChanger(&(world->GetComponents().colorChangeComponents[world->activeColorChange]));
	world->activeColorChange++;
}

void GameObject::CreateMeshRenderer(GameObject& rObj, std::string modelFilePath, std::string textureFilePath)
{
	World* world = gpr460::engine->world;
	EngineVulkan& vulkan = gpr460::engine->vulkanEngine;

	if (world->activeMeshRenderers + 1 >= gpr460::MAX_GAMEOBJECTS)
	{
		gpr460::engine->system->ErrorMessage(gpr460::ERROR_COMPONENT_OVERFLOW);
		gpr460::engine->system->LogToErrorFile(gpr460::ERROR_COMPONENT_OVERFLOW);
	}

	//Create new MeshRenderer, pass new GameObject made by world
	world->GetComponents().meshRendererComponents[world->activeMeshRenderers] = MeshRenderer(&(world->GetGameObjects()[world->activeGameObjects]));
	//MeshRenderer* meshRend = &world->GetComponents().meshRendererComponents[world->activeMeshRenderers];
	
	world->GetComponents().meshRendererComponents[world->activeMeshRenderers].vulkanObj = vulkan.AddVulkanObject();;
	world->GetComponents().meshRendererComponents[world->activeMeshRenderers].vulkanObj->CreateObject(modelFilePath, textureFilePath);
	rObj.SetMeshRenderer(&world->GetComponents().meshRendererComponents[world->activeMeshRenderers]);
	//vulkan.objects.push_back((world->GetComponents().meshRendererComponents[world->activeMeshRenderers]).vulkanObj);

	world->activeMeshRenderers++;
}

void GameObject::CreateCamera(GameObject& rObj, float vZoomSpeed, float vMoveSpeed, float vRotateSpeed, Vector3 lookAt, Vector3 eye, bool vAttachToTransform)
{
	World* world = gpr460::engine->world;
	if (world->activeCameras + 1 >= gpr460::MAX_GAMEOBJECTS)
	{
		gpr460::engine->system->ErrorMessage(gpr460::ERROR_COMPONENT_OVERFLOW);
		gpr460::engine->system->LogToErrorFile(gpr460::ERROR_COMPONENT_OVERFLOW);
	}

	world->GetComponents().cameraComponents[world->activeCameras] = Camera(vZoomSpeed, vMoveSpeed, vRotateSpeed, lookAt, eye, vAttachToTransform, &(world->GetGameObjects()[world->activeGameObjects]));
	rObj.SetCamera(&(world->GetComponents().cameraComponents[world->activeCameras]));
	world->activeCameras++;
}

/*RectangleRenderer* GameObject::CreateRenderer(int vWidth, int vHeight, Vector3 vColor)
{
	if (!renderer)
	{
		renderer = DBG_NEW RectangleRenderer(vWidth, vHeight, vColor);
		return renderer;
	}
	else
	{
		gpr460::engine.system->ErrorMessage(gpr460::ERROR_COMPONENT_EXISTS);
		gpr460::engine.system->LogToErrorFile(gpr460::ERROR_COMPONENT_EXISTS);
		return renderer;
	}
}


RectangleCollider* GameObject::CreateCollider(int vWidth, int vHeight, GameObject* vGameObject)
{
	if (!collider)
	{
		collider = DBG_NEW RectangleCollider(vWidth, vHeight, vGameObject);
		return collider;
	}
	else
	{
		gpr460::engine.system->ErrorMessage(gpr460::ERROR_COMPONENT_EXISTS);
		gpr460::engine.system->LogToErrorFile(gpr460::ERROR_COMPONENT_EXISTS);
		return collider;
	}
}

PlayerController* GameObject::CreatePlayerController(GameObject* vGameObject)
{
	if (!player)
	{
		player = DBG_NEW PlayerController(vGameObject);
		return player;
	}
	else
	{
		gpr460::engine.system->ErrorMessage(gpr460::ERROR_COMPONENT_EXISTS);
		gpr460::engine.system->LogToErrorFile(gpr460::ERROR_COMPONENT_EXISTS);
		return player;
	}
}

CollisionColorChanger* GameObject::CreateCollisionColorChanger(Vector3 vColor, GameObject* vGameObject)
{
	if (!colorChanger)
	{
		colorChanger = DBG_NEW CollisionColorChanger(vColor, vGameObject);
		return colorChanger;
	}
	else
	{
		gpr460::engine.system->ErrorMessage(gpr460::ERROR_COMPONENT_EXISTS);
		gpr460::engine.system->LogToErrorFile(gpr460::ERROR_COMPONENT_EXISTS);
		return colorChanger;
	}
}*/

/*void GameObject::Update(std::vector<GameObject>& gameObjects)
{
	if (player)
		player->Update();
	if (colorChanger)
		colorChanger->Update(gameObjects);
}

void GameObject::Render(SDL_Renderer*& prRenderer)
{

	if (renderer && prRenderer)
	{
		SDL_Rect rect = {
		transform->position.x - (renderer->width / 2),
		transform->position.y - (renderer->height / 2),
		renderer->width,
		renderer->height
		};
		
		SDL_SetRenderDrawColor(prRenderer, renderer->color.x, renderer->color.y, renderer->color.z, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(prRenderer, &rect);
	}
}*/