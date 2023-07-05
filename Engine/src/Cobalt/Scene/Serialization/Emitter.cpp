#include "cbpch.h"

#include "Cobalt/Scene/Serialization/Emitter.h"
#include "Cobalt/Logger/Log.h"

namespace Cobalt
{
	namespace CBS
	{
		Emitter::Emitter(const std::string& filepath) : m_Filepath(filepath) { }

		void CBS::Emitter::Write() const
		{
			std::filesystem::path path(m_Filepath);
			std::filesystem::create_directories(path.parent_path());

			std::ofstream file(path.c_str());

			if (file.is_open())
				file << m_Ss.str();
			else
				COBALT_TRACE("Failed to open file: {}", m_Filepath.c_str());
		}
	}
}
