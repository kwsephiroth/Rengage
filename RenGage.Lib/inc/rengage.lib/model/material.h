#pragma once
#include <string>
#include <glm\glm.hpp>
#include <iostream>
#include <iomanip>

namespace rengage::model
{
	struct SpecularComponent
	{
		glm::vec3 color;
		double exponent;
	};

	struct MaterialProperties
	{
		glm::vec3 ambient_color;
		glm::vec3 diffuse_color;
		SpecularComponent specular_component;
	};

	class Material
	{
	public:
		Material(std::string name, MaterialProperties properties) : m_name(name), m_properties(properties) {}
		Material(std::string name) : m_name(name), m_properties(MaterialProperties()) {}
		~Material() = default;

		const glm::vec3& GetAmbientColor() const { return m_properties.ambient_color; }
		const glm::vec3& GetDiffuseColor() const { return m_properties.diffuse_color; }
		const glm::vec3& GetSpecularColor() const { return m_properties.specular_component.color; }
		const double GetSpecularExponent() const { return m_properties.specular_component.exponent; }

		//friend class MaterialLoader;
		friend std::ostream& operator << (std::ostream& os, const Material& mtl);
	private:
		std::string m_name;
		MaterialProperties m_properties;
	};

	static inline std::ostream& operator << (std::ostream& os, const Material& mtl)
	{
		os << "Material Name: " << mtl.m_name << std::endl;
		os << "Ambient Color: " << std::setprecision(6) << std::fixed << mtl.m_properties.ambient_color.x << " " << mtl.m_properties.ambient_color.y << " " << mtl.m_properties.ambient_color.z << std::endl;
		os << "Diffuse Color: " << mtl.m_properties.diffuse_color.x << " " << mtl.m_properties.diffuse_color.y << " " << mtl.m_properties.diffuse_color.z << std::endl;
		os << "Specular Color: " << mtl.m_properties.specular_component.color.x << " " << mtl.m_properties.specular_component.color.y << " " << mtl.m_properties.specular_component.color.z << std::endl;
		os << "Specular Exponent: " << mtl.m_properties.specular_component.exponent << std::endl;

		return os;
	}
}
