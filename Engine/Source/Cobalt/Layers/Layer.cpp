#include "cbpch.h"

#include "Cobalt/Layers/Layer.h"

namespace Cobalt
{
	Layer::Layer(const std::string& name) : m_DebugName(name) {}
	Layer::~Layer() {}
}