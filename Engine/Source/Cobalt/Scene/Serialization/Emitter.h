#pragma once

#include "Cobalt/Core/Types.h"

namespace Cobalt
{
	namespace CBS
	{
		class Emitter
		{
		public:
			Emitter(const String& filepath);

			template<typename T>
			inline Emitter& operator<<(const T& data)
			{
				m_Ss << String(m_IdentationLevel * 2, ' ') << data;
				return *this;
			}

			inline void Add(const char* key, const String& value)
			{
				m_Ss << String(m_IdentationLevel * 2, ' ');
				m_Ss << key << ":";
				m_Ss << value << "\n";
			}

			inline void Add(const char* key, u64 value)
			{
				m_Ss << String(m_IdentationLevel * 2, ' ');
				m_Ss << key << ":";
				m_Ss << value << "\n";
			}

			inline void Add(const char* key, const Vec2& value)
			{
				m_Ss << String(m_IdentationLevel * 2, ' ');
				m_Ss << key << ":";
				m_Ss << "[" << value.x << "," << value.y << "]\n";
			}

			inline void Add(const char* key, const Vec3& value)
			{
				m_Ss << String(m_IdentationLevel * 2, ' ');
				m_Ss << key << ":";
				m_Ss << "[" << value.x << "," << value.y << "," << value.z << "]\n";
			}

			inline void Add(const char* key, const Vec4& value)
			{
				m_Ss << String(m_IdentationLevel * 2, ' ');
				m_Ss << key << ":";
				m_Ss << "[" << value.r << "," << value.g << "," << value.b << "," << value.a << "]\n";
			}

			inline void BeginMap()
			{
				m_IdentationLevel++;
			}
			inline void EndMap()
			{
				m_IdentationLevel--;
				if (m_IdentationLevel < 0) m_IdentationLevel = 0;
			}

			void Write() const;

		private:
			String m_Filepath;
			std::stringstream m_Ss;

			int m_IdentationLevel = 0;
		};
	}
}