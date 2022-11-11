#pragma once

#include "Core/Core.h"

namespace Cobalt
{
	enum class ShaderDataType
	{
		None = 0, Bool, Int, Int2, Int3, Int4, Float, Float2, Float3, Float4, Mat3, Mat4
	};

	static unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Bool:	 return 1;
			case ShaderDataType::Int:	 return 4;
			case ShaderDataType::Int2:	 return 4 * 2;
			case ShaderDataType::Int3:	 return 4 * 3;
			case ShaderDataType::Int4:	 return 4 * 4;
			case ShaderDataType::Float:	 return 4;
			case ShaderDataType::Float2: return 4 * 2;
			case ShaderDataType::Float3: return 4 * 3;
			case ShaderDataType::Float4: return 4 * 4;
			case ShaderDataType::Mat3:	 return 4 * 3 * 3;
			case ShaderDataType::Mat4:	 return 4 * 4 * 4;
		}

		return -1;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		unsigned int Offset;
		unsigned int Size;

		BufferElement() {}
		BufferElement(ShaderDataType type, const std::string& name)
			: Name(name), Type(type), Offset(0), Size(ShaderDataTypeSize(type)) {}

		unsigned int GetElementCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Int:	 return 1;
				case ShaderDataType::Int2:	 return 2;
				case ShaderDataType::Int3:	 return 3;
				case ShaderDataType::Int4:	 return 4;
				case ShaderDataType::Float:	 return 1;
				case ShaderDataType::Float2: return 2;
				case ShaderDataType::Float3: return 3;
				case ShaderDataType::Float4: return 4;
				case ShaderDataType::Mat3:   return 3 * 3;
				case ShaderDataType::Mat4:   return 4 * 4;
			}

			return -1;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements)
		{
			unsigned int offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline unsigned int GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		std::vector<BufferElement> m_Elements;
		unsigned int m_Stride;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static Ref<VertexBuffer> Create(float* vertices, unsigned int size);
	};
}