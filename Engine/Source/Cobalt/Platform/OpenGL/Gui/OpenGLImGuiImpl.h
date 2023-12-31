#pragma once

#include "Cobalt/Gui/ImGuiImpl.h"

namespace Cobalt
{
	class OpenGLImGuiImpl : public ImGuiImpl
	{
	public:
		OpenGLImGuiImpl();

		virtual void NewFrame() override;
		virtual void Render() override;
		virtual void ShutDown() override;
	};
}