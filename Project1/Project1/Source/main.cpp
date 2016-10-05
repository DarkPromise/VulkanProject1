#include "Model.h"
#include "View.h"
#include "Controller.h"

void main()
{
	MVCModel * MVC_Model = new MVCModel();
	MVCView * MVC_View = new MVCView(MVC_Model);
	MVCController * MVC_Controller = new MVCController(MVC_Model, MVC_View);

	MVC_Controller->RunLoop();

	if (MVC_Controller)
	{
		delete MVC_Controller;
		MVC_Controller = nullptr;
	}

	if (MVC_View)
	{
		delete MVC_View;
		MVC_View = nullptr;
	}

	if (MVC_Model)
	{
		delete MVC_Model;
		MVC_Model = nullptr;
	}
}