#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Core/Types/DataStructures.h"

namespace Cobalt
{
	enum class ShaderDataType
	{
		None = 0, Bool, Int, Int2, Int3, Int4, Float, Float2, Float3, Float4, Mat3, Mat4
	};

	static u32 ShaderDataTypeSize(ShaderDataType type)
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
		const char* Name = "";
		ShaderDataType Type = ShaderDataType::None;
		u32 Offset = 0;
		u32 Size = 0;

		BufferElement() {}
		BufferElement(ShaderDataType type, const char* name)
			: Name(name), Type(type), Offset(0), Size(ShaderDataTypeSize(type)) {}

		u32 GetElementCount() const
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
		BufferLayout(const InitializerList<BufferElement>& elements) : m_Elements(elements)
		{
			u32 offset = 0;

			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

		const Vector<BufferElement>& GetElements() const { return m_Elements; }
		const u32 GetStride() const { return m_Stride; }

		Vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		Vector<BufferElement>::iterator end() { return m_Elements.end(); }
		Vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		Vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		Vector<BufferElement> m_Elements{};
		u32 m_Stride{};
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		virtual void CopyData(const void* data, u32 size) = 0;

		static Ref<VertexBuffer> Create(u32 size);
		static Ref<VertexBuffer> Create(float* vertices, u32 size);
	};
}