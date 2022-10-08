#include "RectangleCollider.h"

#include "GameObject.h"
#include "System.h"

bool RectangleCollider::CheckCollision(RectangleCollider* other)
{
	if (!other)
	{
		gpr460::engine.system->ErrorMessage(gpr460::ERROR_MISSING_RECTCOLLIDER_REFERENCE);
		gpr460::engine.system->LogToErrorFile(gpr460::ERROR_MISSING_RECTCOLLIDER_REFERENCE);
		return false;
	}

	if (!other->GetGameObject() || !gameObject)
	{
		gpr460::engine.system->ErrorMessage(gpr460::ERROR_MISSING_GAMEOBJECT_REFERENCE);
		gpr460::engine.system->LogToErrorFile(gpr460::ERROR_MISSING_GAMEOBJECT_REFERENCE);
		return false;
	}

	Transform otherTransform = other->GetGameObject()->GetTransform();

	if (otherTransform.position.x - gameObject->GetTransform().position.x < other->width + width &&
		otherTransform.position.y - gameObject->GetTransform().position.y < other->height + height)
	{
		return true;
	}

	return false;
}

bool RectangleCollider::ResolveCollision(RectangleCollider* other)
{
	if (!other)
	{
		gpr460::engine.system->ErrorMessage(gpr460::ERROR_MISSING_RECTCOLLIDER_REFERENCE);
		gpr460::engine.system->LogToErrorFile(gpr460::ERROR_MISSING_RECTCOLLIDER_REFERENCE);
		return false;
	}

	if (!other->GetGameObject() || !gameObject)
	{
		gpr460::engine.system->ErrorMessage(gpr460::ERROR_MISSING_GAMEOBJECT_REFERENCE);
		gpr460::engine.system->LogToErrorFile(gpr460::ERROR_MISSING_GAMEOBJECT_REFERENCE);
		return false;
	}

	Transform otherTransform = other->GetGameObject()->GetTransform();

	if (otherTransform.position.x - gameObject->GetTransform().position.x < other->width + width)
	{
		return true;
	}

	if (otherTransform.position.y - gameObject->GetTransform().position.y < other->height + height)
	{

	}

	return false;
}