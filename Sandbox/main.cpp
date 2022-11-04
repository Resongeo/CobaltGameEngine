#include "Cobalt.h"

class ExampleLayer : public Cobalt::Layer
{
public:
	ExampleLayer() : Layer("ExampleLayer") {}
	
	void OnUpdate() override
	{
		LOG_INFO("Layer: {0} update", m_DebugName);
	}
};

class Sandbox : public Cobalt::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

int main()
{
	Sandbox* sandbox = new Sandbox();
	sandbox->Run();
	delete sandbox;

	return 0;
}