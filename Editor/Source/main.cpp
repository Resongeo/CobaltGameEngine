#include "pch.h"
#include "CobaltEditor/Core/CobaltEditorApplication.h"
using namespace CobaltEditor;

int main()
{
	Cobalt::ApplicationSpecification appSpecs;
	appSpecs.WindowProps.Title = "Cobalt Engine Editor";
	appSpecs.WindowProps.Width = 1600;
	appSpecs.WindowProps.Height = 900;

	Cobalt::Unique<CobaltEditorApplication> application = Cobalt::CreateUnique<CobaltEditorApplication>(appSpecs);
	application->Run();

	return 0;
}