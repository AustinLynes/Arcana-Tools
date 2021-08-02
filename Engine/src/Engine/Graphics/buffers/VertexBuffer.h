#pragma once
#include <iostream>
#include <glad/glad.h>

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iomanip>
#include <ostream>

namespace ArcanaTools {


	struct Vertex {
		glm::vec3 position;
	};

	struct Vertex2D {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 UV;
		float texID;
		float tileFactor;
		int entityID;

		friend std::ostream& operator<<(std::ostream& _os, Vertex2D& _v) {
			_os << std::setw(4)
				<< std::setfill(' ')
				<< std::fixed
				<< std::setprecision(1)
				<< "Position: "  << _v.Position.x << ", " << _v.Position.y << ", " << _v.Position.z << ", " << "\t"
				<< "Color: "		 << _v.Color.r << ", " << _v.Color.g << ", " << _v.Color.b << ", " << _v.Color.a << "\t"
				<< "UV: "			 << _v.UV.x << ", " << _v.UV.y << "\t"
				<< "tile factor: " << _v.tileFactor << "\t"
				<< "entity id: "	 << _v.entityID;
			
			
			return _os;
		}
	};

	struct Vertex3D {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec3 Color;
		glm::vec2 UV;

		friend std::ostream& operator<<(std::ostream& _in, Vertex3D& _v) {
			_in << std::setw(4)
				<< std::setfill(' ')
				<< std::fixed
				<< std::setprecision(1)
				<< _v.Position.x << ", " << _v.Position.y << ", " << _v.Position.z << ", "
				<< _v.Color.r << ", " << _v.Color.g << ", " << _v.Color.b << ", "
				<< _v.Normal.x << ", " << _v.Normal.y << ", " << _v.Normal.z << ", "
				<< _v.UV.x << ", " << _v.UV.y << std::endl;
			return _in;
		}
	};



	/*struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec3 Color;
		glm::vec2 UV;


		friend std::ostream& operator<<(std::ostream& _in, Vertex _v) {
			_in << std::setw(4)
				<< std::setfill(' ')
				<< std::fixed
				<< std::setprecision(1)
				<< _v.Position.x << ", " << _v.Position.y << ", " << _v.Position.z << ", "
				<< _v.Color.r << ", " << _v.Color.g << ", " << _v.Color.b << ", "
				<< _v.Normal.x << ", " << _v.Normal.y << ", " << _v.Normal.z << ", "
				<< _v.UV.x << ", " << _v.UV.y << std::endl;
			return _in;
		}
	};*/

	enum class ShaderDataType {
		None, 
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
		case ArcanaTools::ShaderDataType::Float:
			return 4;
		case ArcanaTools::ShaderDataType::Float2:
			return 4*2;
		case ArcanaTools::ShaderDataType::Float3:
			return 4 * 3;

		case ArcanaTools::ShaderDataType::Float4:
			return 4 * 4;

		case ArcanaTools::ShaderDataType::Mat3:
			return 4 * 3 * 3;

		case ArcanaTools::ShaderDataType::Mat4:
			return 4 * 4 * 4;

		case ArcanaTools::ShaderDataType::Int:
			return 4;

		case ArcanaTools::ShaderDataType::Int2:
			return 4 * 2;
		case ArcanaTools::ShaderDataType::Int3:
			return 4 * 3;
		case ArcanaTools::ShaderDataType::Int4:
			return 4 * 4;
		case ArcanaTools::ShaderDataType::Bool:
			return 1;
		}
		std::cout << "Error... Unknown Shader Data Type" << std::endl;

		return 0;
	}

	struct BufferElement {
		std::string name;
		ShaderDataType type;
		uint32_t size;
		size_t offset;
		bool normalized;

		BufferElement() = default;
		BufferElement(ShaderDataType _type, const std::string& _name, bool _normalized = false) : name(_name), type(_type), offset(0), normalized(_normalized), size(ShaderDataTypeSize(type)) {}
		
		uint32_t GetComponentCount() const {
			switch (type)
			{
			case ArcanaTools::ShaderDataType::Float: return 1;
			case ArcanaTools::ShaderDataType::Float2: return 2;
			case ArcanaTools::ShaderDataType::Float3:return 3;
			case ArcanaTools::ShaderDataType::Float4:return 4;
			case ArcanaTools::ShaderDataType::Mat3: return 3;
			case ArcanaTools::ShaderDataType::Mat4:return 4;
			case ArcanaTools::ShaderDataType::Int:return 1;
			case ArcanaTools::ShaderDataType::Int2:return 2;
			case ArcanaTools::ShaderDataType::Int3:return 3;
			case ArcanaTools::ShaderDataType::Int4:return 4;
			case ArcanaTools::ShaderDataType::Bool:return 1;
			}
			std::cout << "Error.. Unknow ShaderDataType!" << std::endl;
			return 0;
		}
	};

	class BufferLayout {
	public: 
		BufferLayout() {}
		BufferLayout(std::initializer_list<BufferElement> elements) : m_elements(elements) { CalculateOffsetAndStride(); }
		
		uint32_t GetStride() const { return m_stride; }

		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

	private:
		void CalculateOffsetAndStride() {
			size_t offset = 0;
			m_stride = 0;
			for (auto& el : m_elements) {
				el.offset = offset;
				offset += el.size;
				m_stride += el.size;
			}
		}
	private:
		std::vector<BufferElement> m_elements;
		uint32_t m_stride = 0;
	};

	class VertexBuffer
	{
	public:
		VertexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetData(const void* data, uint32_t size) = 0;
		
		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
	
		virtual void Delete() = 0;


		static VertexBuffer* Create(uint32_t size);

		static VertexBuffer* Create(Vertex* vertices, uint32_t size);
		static VertexBuffer* Create(Vertex2D* vertices, uint32_t size);
		static VertexBuffer* Create(Vertex3D* vertices, uint32_t size);

	};

}
