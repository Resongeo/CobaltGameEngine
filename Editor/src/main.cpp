#include "CobaltEditor/Core/CobaltEditorApplication.h"
using namespace CobaltEditor;

int main()
{
	Cobalt::ApplicationSpecification appSpecs;
	appSpecs.WindowProps.Title = "Cobalt Engine Editor";
	appSpecs.WindowProps.Width = 1600;
	appSpecs.WindowProps.Height = 900;

	CobaltEditorApplication* application = new CobaltEditorApplication(appSpecs);
	application->Run();
	delete application;

	return 0;
}