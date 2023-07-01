#include "cbpch.h"
#include "Cobalt/Scene/ECS/LuaEntity.h"
#include "Cobalt/Scene/ECS/Components.h"
#include "Cobalt/Logger/Log.h"
#include "Cobalt/Input/Input.h"

#include <cmath>

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

	void LuaEntity::SetColor(float r, float g, float b, float a)
	{
		if (m_Sprite == nullptr) return;
		m_Sprite->Color = Vec4(r / 255.0, g / 255.0, b / 255.0, a / 255.0);
	}

	void LuaEntity::SetColorHSV(float H, float S, float V)
	{
		double r = 0, g = 0, b = 0;

		if (S == 0)
		{
			r = V;
			g = V;
			b = V;
		}
		else
		{
			int i;
			double f, p, q, t;

			if (H == 360)
				H = 0;
			else
				H = H / 60;

			i = (int)trunc(H);
			f = H - i;

			p = V * (1.0 - S);
			q = V * (1.0 - (S * f));
			t = V * (1.0 - (S * (1.0 - f)));

			switch (i)
			{
			case 0:
				r = V;
				g = t;
				b = p;
				break;

			case 1:
				r = q;
				g = V;
				b = p;
				break;

			case 2:
				r = p;
				g = V;
				b = t;
				break;

			case 3:
				r = p;
				g = q;
				b = V;
				break;

			case 4:
				r = t;
				g = p;
				b = V;
				break;

			default:
				r = V;
				g = p;
				b = q;
				break;
			}
		}

		m_Sprite->Color = Vec4(r, g, b, 1.0);
	}

	void LuaEntity::Log(const char* message)   { LOG_ENGINE_TRACE(message); }
	void LuaEntity::Info(const char* message)  { LOG_ENGINE_INFO(message); }
	void LuaEntity::Warn(const char* message)  { LOG_ENGINE_WARN(message); }
	void LuaEntity::Error(const char* message) { LOG_ENGINE_ERROR(message); }

	bool LuaEntity::IsMouseButtonClicked(int button) { return Input::GetMouseButtonClicked(button); }

	bool LuaEntity::IsKeyDown(int key) { return Input::GetKeyDown(key); }
}