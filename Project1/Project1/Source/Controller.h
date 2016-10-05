#ifndef __MVC_CONTROLLER_H__
#define __MVC_CONTROLLER_H__

#include "Model.h"
#include "View.h"

#include "InputHandler.h"

class MVCController
{
public:
	MVCController(MVCModel * MVC_Model, MVCView * MVC_View);
	virtual ~MVCController();

	void RunLoop();

	MVCModel * MVC_Model;
	MVCView * MVC_View;
private:
};

#endif