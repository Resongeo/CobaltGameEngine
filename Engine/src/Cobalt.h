#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Core/Core.h"
#include "Core/Math.h"
#include "Core/Application.h"

#include "Cameras/SceneCamera.h"

#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

#include "Input/Input.h"
#include "Input/KeyCodes.h"
#include "Input/MouseButtonCodes.h"

#include "Layers/Layer.h"

#include "Logger/Log.h"

#include "Renderer/GraphicsContext.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Renderer/Shader.h"

#include "Platform/Window.h"

#include "imgui.h"