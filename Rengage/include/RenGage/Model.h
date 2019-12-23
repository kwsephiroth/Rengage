#pragma once
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <glm/vec3.hpp> // glm::vec3
//#include <glm/vec4.hpp> // glm::vec4
//#include <glm/mat4x4.hpp> // glm::mat4
//#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
//#include <SOIL2/soil2.h>
//#include <iostream>
#include <vector>
#include <string>
#include <glm/mat4x4.hpp>
#include <RenGage\Logger.h>

namespace RenGageAPI
{
	namespace Utilities{class ModelLoader;}

	namespace Objects
	{
		class Model
		{
		private:
			std::vector<float> m_positions;
			std::vector<float> m_textureCoords;
			std::vector<float> m_normals;
			std::string m_name;
			bool m_smoothed = false;
			bool m_initialized = false;

		public:
			Model();
			~Model();

			unsigned int GetNumberOfVertices() const { return m_positions.size() / 3; }
			std::string GetName() const { return m_name; }
			bool HasTexture() const { return (!m_textureCoords.empty() ? true : false); }
			bool HasNormals() const { return (!m_normals.empty() ? true : false); }
			bool IsSmoothed() const { return m_smoothed; }
			bool IsInitialized() const { return m_initialized; }
			
			friend class Utilities::ModelLoader;
		};
	}
}

