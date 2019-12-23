#include <RenGage\ModelLoader.h>

namespace RenGageAPI
{
	namespace Utilities
	{
		void ModelLoader::SplitLineByDelimeter(const std::string & line, char delimiter, std::queue<std::string>& destination)
		{
			std::string segment;
			int j = 0;
			for (size_t i = 0; i < line.size(); ++i)
			{
				if (line[i] == delimiter)
				{
					//++j;
					//std::cout << "Segment [" << j << "] : " << segment << std::endl;
					destination.push(segment);
					segment.clear();

					++i;

					while (line[i] == delimiter)//Move passed consecutive occurrences of delimiter
						++i;
				}
				if (i < line.size())
					segment += line[i];
			}

			destination.push(segment);
			//std::cout << "Segment [" << j << "] : " << segment << std::endl << std::endl;
		}

		void ModelLoader::SplitFaceLine(const std::string & line, std::queue<std::string>& destination)
		{
			std::string segment;
			int j = 0;
			for (size_t i = 0; i < line.size(); ++i)
			{
				if (line[i] == '/')
				{
					//++j;
					//std::cout << "Segment [" << j << "] : " << segment << std::endl;
					destination.push(segment);
					segment.clear();

					++i;

					while (line[i] == '/')//Move passed consecutive occurrences of delimiter
					{
						destination.push("");//Push an empty string
						++i;
					}
				}
				if (i < line.size())
					segment += line[i];
			}

			destination.push(segment);
			//std::cout << "Segment [" << j << "] : " << segment << std::endl << std::endl;
		}

		Tag ModelLoader::GetTag(const std::string & tagString)
		{
			if (tagString == "o")
				return Tag::ObjectName;
			else if (tagString == "v")
				return Tag::Vertex;
			else if (tagString == "vt")
				return Tag::TextureCoordinate;
			else if (tagString == "vn")
				return Tag::VertexNormal;
			else if (tagString == "f")
				return Tag::Face;
			else if (tagString == "s")
				return Tag::Smoothed;
			else
				return Tag::None;
		}

		void ModelLoader::StoreVertexLocation(std::queue<std::string>& vertexSegments, Vec3& positionDest)
		{
			if (vertexSegments.empty() || vertexSegments.size() < 3)
			{
				std::cout << "ERROR: Failed to store model face: At least three components expected." << std::endl;
				return;
			}

			//try
			//{
			auto x = std::stof(vertexSegments.front());
			vertexSegments.pop();

			auto y = std::stof(vertexSegments.front());
			vertexSegments.pop();

			auto z = std::stof(vertexSegments.front());
			vertexSegments.pop();

			positionDest.emplace_back(x, y, z);

			//TODO: write ostream overload for easy debugging
			//const auto& vertex = destinationModel.m_positions.back();
			//std::cout << "(" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")" << std::endl;
		//}
		//catch (std::exception e)
		//{
		//	std::cout << "ERROR: Failed to store model vertex : " << e.what() << std::endl;
		//	destinationModel.m_initialized = false;
		//}
		}

		void ModelLoader::StoreTextureCoordinate(std::queue<std::string>& textureCoordinateSegments, Vec2& textureCoordDest)
		{
			if (textureCoordinateSegments.empty())
			{
				//destinationModel.m_initialized = false;
				return;
			}

			if (textureCoordinateSegments.size() != 2)
			{
				std::cout << "ERROR: Failed to store model texture coordinate: Exactly two components expected." << std::endl;
				//destinationModel.m_initialized = false;
				return;
			}

			//try
			//{
			auto s = std::stof(textureCoordinateSegments.front());
			textureCoordinateSegments.pop();

			auto t = std::stof(textureCoordinateSegments.front());
			textureCoordinateSegments.pop();

			textureCoordDest.emplace_back(s, t);

			//TODO: write ostream overload for easy debugging
			//const auto& vertex = destinationModel.m_textureCoordinates.back();
			//std::cout << "(" << vertex.s << ", " << vertex.t << ")" << std::endl;
		//}
		//catch (std::exception e)
		//{
		//	std::cout << "ERROR: Failed to store model texture coordinate: " << e.what() << std::endl;
		//	destinationModel.m_initialized = false;
		//}
		}

		void ModelLoader::StoreVertexNormal(std::queue<std::string>& vertexNormalSegments, Vec3& normalDest)
		{
			if (vertexNormalSegments.empty() || vertexNormalSegments.size() < 3)
			{
				std::cout << "ERROR: Failed to store model face: At least three components expected." << std::endl;
				return;
			}

			//try
			//{
			auto x = std::stof(vertexNormalSegments.front());
			vertexNormalSegments.pop();

			auto y = std::stof(vertexNormalSegments.front());
			vertexNormalSegments.pop();

			auto z = std::stof(vertexNormalSegments.front());
			vertexNormalSegments.pop();

			normalDest.emplace_back(x, y, z);

			//TODO: write ostream overload for easy debugging

			//const auto& vertex = destinationModel.m_normals.back();
			//std::cout << "(" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")" << std::endl;
		//}
		//catch (std::exception e)
		//{
		//	std::cout << "ERROR: Failed to store model vertex normal: " << e.what() << std::endl;
		//	destinationModel.m_initialized = false;
		//}
		}

		void ModelLoader::StoreFace(std::queue<std::string>& faceSegments, RenGageAPI::Objects::Model & destinationModel, const Vec3& positions, const Vec2& textureCoords, const Vec3& normals)
		{
			if (faceSegments.empty() || faceSegments.size() < 3)
			{
				std::cout << "ERROR: Failed to store model face: At least three components expected." << std::endl;
				return;
			}

			while (!faceSegments.empty())
			{
				int positionIndex = -1, textureCoorIndex = -1, normalIndex = -1;

				//example 2/7/3 5/8/3 3/9/3
				std::queue<std::string> indexSegments;
				SplitFaceLine(faceSegments.front(), indexSegments);

				auto indicesCount = indexSegments.size();

				if (indicesCount >= 1)
				{
					auto& indexStr = indexSegments.front();

					positionIndex = (indexStr.empty() ? -1 : (std::stoi(indexStr) - 1));
					indexSegments.pop();

					if (indicesCount > 1)
					{
						indexStr = indexSegments.front();
						textureCoorIndex = (indexStr.empty() ? -1 : (std::stoi(indexStr) - 1));
						indexSegments.pop();
					}

					if (indicesCount > 2)
					{
						indexStr = indexSegments.front(); //std::cout << indexStr << " ";
						normalIndex = (indexStr.empty() ? -1 : (std::stoi(indexStr) - 1));
						indexSegments.pop();
					}

					//Now finally add a position, texture coordinate, and normal
					if (positionIndex > -1 && positionIndex < (int)(positions.size()))
					{
						const auto & position = positions[positionIndex];
						destinationModel.m_positions.push_back(position.x);
						destinationModel.m_positions.push_back(position.y);
						destinationModel.m_positions.push_back(position.z);
					}

					if (textureCoorIndex > -1 && textureCoorIndex < (int)(textureCoords.size()))
					{
						const auto & textCoordinate = textureCoords[textureCoorIndex];
						destinationModel.m_textureCoords.push_back(textCoordinate.s);
						destinationModel.m_textureCoords.push_back(textCoordinate.t);
					}

					if (normalIndex > -1 && normalIndex < (int)(normals.size()))
					{
						const auto & normal = normals[normalIndex];
						destinationModel.m_normals.push_back(normal.x);
						destinationModel.m_normals.push_back(normal.y);
						destinationModel.m_normals.push_back(normal.z);
					}
				}

				faceSegments.pop();
			}
		}

		//void ModelLoader::LoadTexture(const char * textureFilePath, RenGageAPI::Objects::Model& destinationModel)
		//{
		//	if (textureFilePath == nullptr)
		//		return;

		//	GLuint textureRef;
		//	textureRef = SOIL_load_OGL_texture(textureFilePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		//	if (textureRef == 0)
		//	{
		//		std::cout << "ERROR: Didnt find texture file '" << textureFilePath << "'" << std::endl;
		//		destinationModel.m_initialized = false;
		//	}
		//	// ----- mipmap/anisotropic section
		//	glBindTexture(GL_TEXTURE_2D, textureRef);
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//	glGenerateMipmap(GL_TEXTURE_2D);
		//	if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
		//		GLfloat anisoset = 0.0f;
		//		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoset);
		//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoset);
		//	}
		//	// ----- end of mipmap/anisotropic section
		//	destinationModel.m_textureID = textureRef;
		//}

		std::unique_ptr<RenGageAPI::Objects::Model> ModelLoader::LoadModelFromOBJFile(const std::string& modelName, const std::string& modelFilePath, const std::string& textureFilePath, const glm::vec3 initalWorldPosition)
		{
			std::cout << "ModelLoader::LoadModelFromOBJFile - Loading model at path '" << modelFilePath << "' ..." << std::endl;

			if (modelName.empty())
			{
				std::cout << "ERROR: Empty model name. Please provide a name for the model you wish to load." << std::endl;
				return nullptr;
			}

			if (modelFilePath.empty())
			{
				std::cout << "ERROR: Empty obj file path. Please provide a valid obj file path." << std::endl;
				return nullptr;
			}

			std::unique_ptr<RenGageAPI::Objects::Model> loadedModelPtr(new RenGageAPI::Objects::Model());//Allocate blank Model on heap first
			auto& loadedModel = *loadedModelPtr;
			loadedModel.m_name = modelName;
			//loadedModel.m_initialWorldPosition = initalWorldPosition;

			std::ifstream modelFileStream(modelFilePath, std::ios::in);
			int numFaces = 0;

			if (!modelFileStream.good())
			{
				std::cout << "ERROR: Failed to open file at path '" << modelFilePath << "'" << std::endl;
				return nullptr;
			}
			else
			{
				//int i = 1;
				std::string line;
				Vec3 tempPositions;
				Vec2 tempTexCoords;
				Vec3 tempNormals;

				while (!modelFileStream.eof())
				{
					std::getline(modelFileStream, line);
					std::queue < std::string > lineSegments;
					SplitLineByDelimeter(line, ' ', lineSegments);

					const std::string lineTagString = lineSegments.front();
					lineSegments.pop();//Remove front element from queue
					auto lineTag = GetTag(lineTagString);

					//std::cout << "Component Count = " << lineSegments.size() << std::endl;

					switch (lineTag)
					{
							/*case Tag::ObjectName:
							{
								if (!lineSegments.empty())
								{
									loadedModel.m_name = lineSegments.front();
									lineSegments.pop();
								}
								//else
								//{
									//TODO: Assign a default object name based on the model file name.
								//}
							}
							break;*/

						case Tag::Vertex:
						{
							try
							{
								if (lineSegments.empty() || lineSegments.size() < 3)
								{
									//TODO: Log error and return nullptr?
									std::cout << "ERROR: Failed to store model face: At least three components expected." << std::endl;
									return nullptr;
								}

								StoreVertexLocation(lineSegments, tempPositions);

								if (tempPositions.empty())
								{
									return nullptr;
								}
							}
							catch (std::exception e)
							{
								std::cout << "ERROR: Failed to store model vertex: " << e.what() << std::endl;
								return nullptr;
							}
						}
						break;

						case Tag::TextureCoordinate:
						{
							try
							{
								if (lineSegments.empty() || lineSegments.size() < 3)
								{
									//TODO: Log error and return nullptr?
									std::cout << "ERROR: Failed to store model face: At least three components expected." << std::endl;
									return nullptr;
								}

								StoreTextureCoordinate(lineSegments, tempTexCoords);
								if (tempTexCoords.empty())
								{
									return nullptr;
								}
							}
							catch (std::exception e)
							{
								std::cout << "ERROR: Failed to store model texture coordinate: " << e.what() << std::endl;
								return nullptr;
							}
						}
						break;

						case Tag::VertexNormal:
						{
							try
							{
								if (lineSegments.empty() || lineSegments.size() < 3)
								{
									//TODO: Log error and return nullptr?
									std::cout << "ERROR: Failed to store model face: At least three components expected." << std::endl;
									return nullptr;
								}

								StoreVertexNormal(lineSegments, tempNormals);
								if (tempNormals.empty())
								{
									return nullptr;
								}
							}
							catch (std::exception e)
							{
								std::cout << "ERROR: Failed to store model vertex normal: " << e.what() << std::endl;
								return nullptr;
							}
						}
						break;

						case Tag::Face:
						{
							try
							{
								++numFaces;
								StoreFace(lineSegments, loadedModel, tempPositions, tempTexCoords, tempNormals);
							}
							catch (std::exception e)
							{
								std::cout << "ERROR: Failed to store model face: " << e.what() << std::endl;
								return nullptr;
							}
						}
						break;

						case Tag::Smoothed:
						{
							if (lineSegments.front() == "on")
								loadedModel.m_smoothed = true;
							else
								loadedModel.m_smoothed = false;

							lineSegments.pop();
						}
						break;

						default:
						{
							//std::cout << "Ignoring the following line:\n" << line << std::endl;
							//std::cout << "lineTag = " << (unsigned short)lineTag << std::endl;
							//std::cout << "lineTagString = \"" << lineTagString << "\"" << std::endl << std::endl;
						}
						break;
					}

					//++i;
				}
			}

			//if (loadedModel.m_name.empty())
			//{
				//TODO: Assign a default object name based on the model file name.
			//}

			//if (!textureFilePath.empty())
			//{
				//Attempt to load texture
				//LoadTexture(textureFilePath.c_str(), loadedModel);
			//}


			//loadedModel.SetupVBOs();
			//loadedModel.InitializeModelMatrix();

			std::cout << "Model Name: " << loadedModel.m_name << std::endl;
			std::cout << "Number of positions: " << loadedModel.m_positions.size() << std::endl;
			std::cout << "Number of texture coordinates: " << loadedModel.m_textureCoords.size() << std::endl;
			std::cout << "Number of normals: " << loadedModel.m_normals.size() << std::endl;
			std::cout << "Number of faces: " << numFaces << std::endl;
			std::cout << "Number of vertices: " << loadedModel.GetNumberOfVertices() << std::endl;
			std::cout << "ModelLoader::LoadModelFromOBJFile - Model loaded complete." << std::endl;
			loadedModel.m_initialized = true;
			return loadedModelPtr;

		}
	}
}