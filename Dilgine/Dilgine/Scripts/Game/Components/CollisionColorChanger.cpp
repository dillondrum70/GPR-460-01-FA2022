#include "CollisionColorChanger.h"
#include "GameObject.h"
#include "System.h"

#include "SDL2/SDL.h"

#include <iostream>

void CollisionColorChanger::Update()
{
	std::vector<GameObject>& gameObjects = gpr460::engine.world->GetGameObjects();
	Components& components = gpr460::engine.world->GetComponents();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		for (int j = i; j < gameObjects.size(); j++)
		{
			if (gameObjects[i].GetCollider() && gameObjects[j].GetCollider() &&
				gameObjects[i].GetRenderer() && gameObjects[j].GetRenderer() &&
				gameObjects[i].GetColorChanger() && gameObjects[j].GetColorChanger())
			{
				if (gameObjects[i].GetCollider()->CheckCollision(*gameObjects[j].GetCollider()))
				{
					gameObjects[i].GetRenderer()->color = gameObjects[i].GetColorChanger()->color;
					gameObjects[j].GetRenderer()->color = gameObjects[j].GetColorChanger()->color;
					break;
				}
				else
				{
					gameObjects[i].GetRenderer()->color = gameObjects[i].GetRenderer()->baseColor;
					gameObjects[j].GetRenderer()->color = gameObjects[j].GetRenderer()->baseColor;
				}
			}
		}
	}
}