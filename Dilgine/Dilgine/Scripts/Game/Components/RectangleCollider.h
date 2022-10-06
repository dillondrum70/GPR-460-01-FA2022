#ifndef RECTANGLE_COLLIDER_H
#define RECTANGLE_COLLIDER_H

class GameObject;

class RectangleCollider
{
private:
	GameObject* gameObject;

public:
	int width, height;

	RectangleCollider() { width = 1; height = 1; gameObject = nullptr; }
	RectangleCollider(int vWidth, int vHeight, GameObject* vGameObject) { width = vWidth; height = vHeight; gameObject = vGameObject; }

	GameObject* GetGameObject() { return gameObject; }

	bool CheckCollision(RectangleCollider* other);
};

#endif
