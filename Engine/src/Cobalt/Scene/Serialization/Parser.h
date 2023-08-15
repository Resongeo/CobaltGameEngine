#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Core/Math.h"
#include "Cobalt/Scene/ECS/Entity.h"

namespace Cobalt
{
	namespace CBS
	{
		class Parser
		{
		public:
			static void CreateEntity(std::ifstream& file, const Ref<Scene>& scene);

			inline static std::string GetString(const std::string& input)
			{
				return input.substr(input.find(':') + 1);
			}

		private:
			template<int size>
			static glm::vec<size, float> GetVec(const std::string& input)
			{
				glm::vec<size, float> result{};

				std::stringstream ss(input);
				std::string temp;

				for (int i = 0; i < size; i++)
				{
					std::getline(ss, temp, ',');
					result[i] = std::stof(temp);
				}

				return result;
			}

			inline static uint64_t GetUUID(const std::string& input)
			{
				std::string idStr = input.substr(input.find(":") + 1);
				char* end;
				return strtoull(idStr.c_str(), &end, 10);
			}

			inline static std::string ExtractNumbers(const std::string& input)
			{
				std::string result = input;

				result = result.substr(input.find(":") + 2);
				result = result.substr(0, result.size() - 1);

				return result;
			}
		};
	}
}