#include "Cobalt.h"

class Sandbox : public Cobalt::Application
{
public:
	Sandbox()
	{

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