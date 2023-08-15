#include "cbpch.h"

#include "Cobalt/Scene/ECS/LuaEntity.h"
#include "Cobalt/Scene/ECS/Components.h"
#include "Cobalt/Logger/Log.h"
#include "Cobalt/Input/Input.h"

#include <cmath>

namespace Cobalt
{
	void LuaEntity::OpenLibraries()
	{
		m_LuaState->open_libraries(sol::lib::base);
		m_LuaState->open_libraries(sol::lib::math);
		m_LuaState->open_libraries(sol::lib::string);
	}

	void LuaEntity::SetupKeyCodesTable()
	{
		m_LuaState->create_named_table("KeyCode",
			"SPACE", 32,
			"APOSTROPHE", 39,
			"COMMA", 44,
			"MINUS", 45,
			"PERIOD", 46,
			"SLASH", 47,
			"A0", 48,
			"A1", 49,
			"A2", 50,
			"A3", 51,
			"A4", 52,
			"A5", 53,
			"A6", 54,
			"A7", 55,
			"A8", 56,
			"A9", 57,
			"SEMICOLON", 59,
			"EQUAL", 61,
			"A", 65,
			"B", 66,
			"C", 67,
			"D", 68,
			"E", 69,
			"F", 70,
			"G", 71,
			"H", 72,
			"I", 73,
			"J", 74,
			"K", 75,
			"L", 76,
			"M", 77,
			"N", 78,
			"O", 79,
			"P", 80,
			"Q", 81,
			"R", 82,
			"S", 83,
			"T", 84,
			"U", 85,
			"V", 86,
			"W", 87,
			"X", 88,
			"Y", 89,
			"Z", 90,
			"LEFT_BRACKET", 91,
			"BACKSLASH", 92,
			"RIGHT_BRACKET", 93,
			"GRAVE_ACCENT", 96,
			"ESCAPE", 256,
			"ENTER", 257,
			"TAB", 258,
			"BACKSPACE", 259,
			"INSERT", 260,
			"DELETE", 261,
			"RIGHT", 262,
			"LEFT", 263,
			"DOWN", 264,
			"UP", 265,
			"PAGE_UP", 266,
			"PAGE_DOWN", 267,
			"HOME", 268,
			"END", 269,
			"CAPS_LOCK", 280,
			"SCROLL_LOCK", 281,
			"NUM_LOCK", 282,
			"PRINT_SCREEN", 283,
			"PAUSE" , 284,
			"F1", 290,
			"F2", 291,
			"F3", 292,
			"F4", 293,
			"F5", 294,
			"F6", 295,
			"F7", 296,
			"F8", 297,
			"F9", 298,
			"F10", 299,
			"F11", 300,
			"F12", 301,
			/*"N0", 320,
			"N1", 321,
			"N2", 322,
			"N3", 323,
			"N4", 324,
			"N5", 325,
			"N6", 326,
			"N7", 327,
			"N8", 328,
			"N9", 329,
			"NDECIMAL", 330,
			"NDIVIDE", 331,
			"NMULTIPLY", 332,
			"NSUBTRACT", 333,
			"NADD", 334,
			"NENTER", 335,
			"NEQUAL", 336,*/
			"LEFT_SHIFT", 340,
			"LEFT_CONTROL", 341,
			"LEFT_ALT", 342,
			"LEFT_SUPER", 343,
			"RIGHT_SHIFT", 344,
			"RIGHT_CONTROL", 345,
			"RIGHT_ALT", 346,
			"RIGHT_SUPER", 347,
			"MENU", 348,
			"LAST", 348
		);
	}

	void LuaEntity::SetupTransformTable()
	{
		auto transformTable = m_LuaState->create_named_table("Transform");
		transformTable.set_function("GetPositionX", &LuaEntity::GetPositionX, this);
		transformTable.set_function("GetPositionY", &LuaEntity::GetPositionY, this);
		transformTable.set_function("GetPositionZ", &LuaEntity::GetPositionZ, this);

		transformTable.set_function("SetPosition", &LuaEntity::SetPosition, this);
		transformTable.set_function("SetPositionX", &LuaEntity::SetPositionX, this);
		transformTable.set_function("SetPositionY", &LuaEntity::SetPositionY, this);
		transformTable.set_function("SetPositionZ", &LuaEntity::SetPositionZ, this);

		transformTable.set_function("RotateX", &LuaEntity::RotateX, this);
		transformTable.set_function("RotateY", &LuaEntity::RotateY, this);
		transformTable.set_function("RotateZ", &LuaEntity::RotateZ, this);

		transformTable.set_function("Translate", &LuaEntity::Translate, this);
		transformTable.set_function("TranslateX", &LuaEntity::TranslateX, this);
		transformTable.set_function("TranslateY", &LuaEntity::TranslateY, this);
		transformTable.set_function("TranslateZ", &LuaEntity::TranslateZ, this);
	}

	void LuaEntity::SetupDebugTable()
	{
		auto debugTable = m_LuaState->create_named_table("Debug");
		debugTable.set_function("Log", &LuaEntity::Log, this);
		debugTable.set_function("Info", &LuaEntity::Info, this);
		debugTable.set_function("Warn", &LuaEntity::Warn, this);
		debugTable.set_function("Error", &LuaEntity::Error, this);
	}

	void LuaEntity::SetupInputTable()
	{
		auto inputTable = m_LuaState->create_named_table("Input");
		inputTable.set_function("IsMouseButtonClicked", &LuaEntity::IsMouseButtonClicked, this);
		inputTable.set_function("IsKeyDown", &LuaEntity::IsKeyDown, this);
	}

	void LuaEntity::SetupSpriteRendererTable()
	{
		auto spriteTable = m_LuaState->create_named_table("SpriteRenderer");
		spriteTable.set_function("SetColor", &LuaEntity::SetColor, this);
		spriteTable.set_function("SetColorHSV", &LuaEntity::SetColorHSV, this);
	}

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
		m_Sprite->Tint = Vec4(r / 255.0, g / 255.0, b / 255.0, a / 255.0);
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

		m_Sprite->Tint = Vec4(r, g, b, 1.0);
	}

	void LuaEntity::Log(const char* message)   { COBALT_TRACE(message); }
	void LuaEntity::Info(const char* message)  { COBALT_INFO(message); }
	void LuaEntity::Warn(const char* message)  { COBALT_WARN(message); }
	void LuaEntity::Error(const char* message) { COBALT_ERROR(message); }

	bool LuaEntity::IsMouseButtonClicked(int button) { return Input::GetMouseButtonClicked(button); }

	bool LuaEntity::IsKeyDown(int key) { return Input::GetKeyDown(key); }
}