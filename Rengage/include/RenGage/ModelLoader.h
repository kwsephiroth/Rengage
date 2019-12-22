#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <memory>
#include <SOIL2/soil2.h>
#include <glm/vec2.hpp> 
#include <glm/vec3.hpp>
#include <RenGage/Model.h>

namespace RenGageAPI
{
	namespace Utilities
	{
		//using namespace RenGageAPI::Objects;

		enum class Tag
		{
			None,
			ObjectName,
			Vertex,
			TextureCoordinate,
			VertexNormal,
			Face,
			Smoothed
		};

		enum class ErrorCode
		{
			Fail = -1,
			Success = 1
		};

		class ModelLoader
		{
		private:
			using Vec2 = std::vector <glm::vec2>;
			using Vec3 = std::vector<glm::vec3>;

			static void SplitLineByDelimeter(const std::string&, char, std::queue < std::string>&);
			static void SplitFaceLine(const std::string&, std::queue < std::string>&);
			static Tag GetTag(const std::string&);
			static void StoreVertexLocation(std::queue<std::string>&, Vec3&);
			static void StoreTextureCoordinate(std::queue<std::string>&, Vec2&);
			static void StoreVertexNormal(std::queue<std::string>&, Vec3&);
			static void StoreFace(std::queue<std::string>&, RenGageAPI::Objects::Model&, const Vec3&, const Vec2&, const Vec3&);
			static void LoadTexture(const char *, RenGageAPI::Objects::Model&);

			ModelLoader(void);
		public:
			static std::unique_ptr<RenGageAPI::Objects::Model> LoadModelFromOBJFile(const std::string& modelName, const std::string& modelFilePath, const std::string& textureFilePath, const glm::vec3 initalWorldPosition = { 0,0,0 });
		};
	}
}