#pragma once

#include "Cobalt/Logger/Log.h"

namespace Cobalt
{
	struct TransformComponent;
	struct SpriteRendererComponent;

	class LuaEntity
	{
	public:
		LuaEntity() = default;

		float GetPositionX();
		float GetPositionY();
		float GetPositionZ();

		void SetPosition(float x, float y, float z);
		void SetPositionX(float value);
		void SetPositionY(float value);
		void SetPositionZ(float value);

		void Translate(float x, float y, float z);
		void TranslateX(float value);
		void TranslateY(float value);
		void TranslateZ(float value);

		void RotateX(float value);
		void RotateY(float value);
		void RotateZ(float value);

		void SetColor(float r, float g, float b, float a);
		void SetColorHSV(float H, float S, float V);

		void Log(const char* message);
		void Info(const char* message);
		void Warn(const char* message);
		void Error(const char* message);
		
		bool IsMouseButtonClicked(int button);

		bool IsKeyDown(int key);

		void SetTransformComponent(TransformComponent* transform) { m_Transform = transform; }
		void SetSpriteRendererComponent(SpriteRendererComponent* sprite) { m_Sprite = sprite; }

	private:
		const char* Name = "Entity name here";
		TransformComponent* m_Transform = nullptr;
		SpriteRendererComponent* m_Sprite = nullptr;
	};
}