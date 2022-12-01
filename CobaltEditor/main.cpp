#include "Editor/CobaltEditor.h"

int main()
{
	ApplicationSpecification appSpecs;
	appSpecs.WindowProperties.Width = 1920;
	appSpecs.WindowProperties.Height = 1080;
	appSpecs.WindowProperties.Title = "Cobalt Editor";

	CobaltEditor* editor = new CobaltEditor(appSpecs);
	editor->Run();
	delete editor;

	return 0;
}