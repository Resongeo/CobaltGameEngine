#pragma once

#include "Cobalt/Core/Types.h"
#include "Cobalt/Scene/ECS/Entity.h"

namespace Cobalt
{
	namespace CBS
	{
		class Parser
		{
		public:
			static void CreateEntity(std::ifstream& file, const Shared<Scene>& scene);

			inline static String GetString(const String& input)
			{
				return input.substr(input.find(':') + 1);
			}

		private:
			template<int size>
			static Vec<size, float> GetVec(const String& input)
			{
				Vec<size, float> result{};

				std::stringstream ss(input);
				String temp;

				for (int i = 0; i < size; i++)
				{
					std::getline(ss, temp, ',');
					result[i] = std::stof(temp);
				}

				return result;
			}

			inline static u64 GetUUID(const String& input)
			{
				String idStr = input.substr(input.find(":") + 1);
				char* end;
				return strtoull(idStr.c_str(), &end, 10);
			}

			inline static String ExtractNumbers(const String& input)
			{
				String result = input;

				result = result.substr(input.find(":") + 2);
				result = result.substr(0, result.size() - 1);

				return result;
			}
		};
	}
}