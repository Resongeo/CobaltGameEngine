#include "Editor/CobaltEditor.h"
using namespace Cobalt;

int main()
{
	ApplicationSpecification appSpecs;
	appSpecs.WindowProps.Width = 1920;
	appSpecs.WindowProps.Height = 1080;
	appSpecs.WindowProps.Title = "Cobalt Editor";
	appSpecs.WindowProps.CaptionColor = Color(23, 23, 23);

	CobaltEditor* editor = new CobaltEditor(appSpecs);
	editor->Run();
	delete editor;

	return 0;
}