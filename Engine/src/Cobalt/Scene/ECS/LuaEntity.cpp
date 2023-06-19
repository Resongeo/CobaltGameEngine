#include "cbpch.h"
#include "Cobalt/Scene/ECS/LuaEntity.h"
#include "Cobalt/Scene/ECS/Components.h"
#include "Cobalt/Logger/Log.h"
#include "Cobalt/Input/Input.h"

namespace Cobalt
{
	float LuaEntity::GetPositionX() { return m_Transform->Position.x; }
	float LuaEntity::GetPositionY() { return m_Transform->Position.y; }
	float LuaEntity::GetPositionZ() { return m_Transform->Position.z; }

	void LuaEntity::SetPosition(float x, float y, float z) { m_Transform->Position = Vec3(x, y, z); }
	void LuaEntity::SetPositionX(float value) { m_Transform->Position.x = value; }
	void LuaEntity::SetPositionY(float value) { m_Transform->Position.y = value; }
	void LuaEntity::SetPositionZ(float value) { m_Transform->Position.z = value; }
	
	void LuaEntity::Translate(float x, float y, float z) { m_Transform->Position += Vec3(x, y, z); }
	void LuaEntity::TranslateX(float value) { m_Transform->Position.x += value; }
	void LuaEntity::TranslateY(float value) { m_Transform->Position.y += value; }
	void LuaEntity::TranslateZ(float value) { m_Transform->Position.z += value; }

	void LuaEntity::RotateX(float value) { m_Transform->Rotation.x += value; }
	void LuaEntity::RotateY(float value) { m_Transform->Rotation.y += value; }
	void LuaEntity::RotateZ(float value) { m_Transform->Rotation.z += value; }

	void LuaEntity::Log(const char* message)   { LOG_ENGINE_TRACE(message); }
	void LuaEntity::Info(const char* message)  { LOG_ENGINE_INFO(message); }
	void LuaEntity::Warn(const char* message)  { LOG_ENGINE_WARN(message); }
	void LuaEntity::Error(const char* message) { LOG_ENGINE_ERROR(message); }

	bool LuaEntity::IsMouseButtonClicked(int button) { return Input::GetMouseButtonClicked(button); }

	bool LuaEntity::IsKeyDown(int key) { return Input::GetKeyDown(key); }
}