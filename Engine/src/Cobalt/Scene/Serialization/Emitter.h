#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Core/Math.h"

namespace Cobalt
{
	namespace CBS
	{
		class Emitter
		{
		public:
			Emitter(const std::string& filepath);

			template<typename T>
			inline Emitter& operator<<(const T& data)
			{
				m_Ss << std::string(m_IdentationLevel * 2, ' ') << data;
				return *this;
			}

			inline void Add(const char* key, const std::string& value)
			{
				m_Ss << std::string(m_IdentationLevel * 2, ' ');
				m_Ss << key << ":";
				m_Ss << value << "\n";
			}

			inline void Add(const char* key, const glm::vec2& value)
			{
				m_Ss << std::string(m_IdentationLevel * 2, ' ');
				m_Ss << key << ":";
				m_Ss << "[" << value.x << "," << value.y << "]\n";
			}

			inline void Add(const char* key, const glm::vec3& value)
			{
				m_Ss << std::string(m_IdentationLevel * 2, ' ');
				m_Ss << key << ":";
				m_Ss << "[" << value.x << "," << value.y << "," << value.z << "]\n";
			}

			inline void Add(const char* key, const glm::vec4& value)
			{
				m_Ss << std::string(m_IdentationLevel * 2, ' ');
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
			std::string m_Filepath;
			std::stringstream m_Ss;

			int m_IdentationLevel = 0;
		};
	}
}