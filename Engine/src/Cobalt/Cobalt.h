#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Cobalt/Core/Core.h"
#include "Cobalt/Core/Math.h"
#include "Cobalt/Core/Time.h"
#include "Cobalt/Core/Color.h"
#include "Cobalt/Core/Random.h"
#include "Cobalt/Core/Application.h"

#include "Cobalt/Cameras/Camera.h"
#include "Cobalt/Cameras/EditorCamera.h"

#include "Cobalt/Events/Event.h"
#include "Cobalt/Events/KeyEvent.h"
#include "Cobalt/Events/MouseEvent.h"
#include "Cobalt/Events/ApplicationEvent.h"

#include "Cobalt/Input/Input.h"
#include "Cobalt/Input/KeyCodes.h"
#include "Cobalt/Input/MouseButtonCodes.h"

#include "Cobalt/Layers/Layer.h"

#include "Cobalt/Logger/Log.h"

#include "Cobalt/Platform/Window.h"
#include "Cobalt/Platform/FileSystem.h"

#include "Cobalt/Graphics/GraphicsContext.h"
#include "Cobalt/Graphics/VertexArray.h"
#include "Cobalt/Graphics/IndexBuffer.h"
#include "Cobalt/Graphics/Framebuffer.h"
#include "Cobalt/Graphics/Texture2D.h"
#include "Cobalt/Graphics/Shader.h"

#include "Cobalt/Rendering/RenderCommand.h"
#include "Cobalt/Rendering/Renderer.h"

#include "Cobalt/Scene/ECS/Components.h"
#include "Cobalt/Scene/ECS/Entity.h"
#include "Cobalt/Scene/Serialization/SceneSerializer.h"
#include "Cobalt/Scene/Scene.h"

#include <imgui.h>
#include <ImGuizmo.h>
