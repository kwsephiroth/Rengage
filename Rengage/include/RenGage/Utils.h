#pragma once
#include <glm\glm.hpp>
#include <iostream>

namespace RenGageAPI
{
	namespace Utilities
	{
		static void PrintMat4(const glm::mat4& m)
		{
			for (size_t j = 0; j < 4; ++j)
			{
				std::cout << m[0][j] << " " << m[1][j] << " " << m[2][j] << " " << m[3][j] << std::endl;
			}
		}
	}
}