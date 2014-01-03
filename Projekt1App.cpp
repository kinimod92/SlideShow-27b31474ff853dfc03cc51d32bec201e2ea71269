//---------------------------------------------------------------------------
//
// Name:        Projekt1App.cpp
// Author:      Dominik
// Created:     2013-12-23 16:02:01
// Description: 
//
//---------------------------------------------------------------------------

#include "Projekt1App.h"
#include "PokazFrm.h"

IMPLEMENT_APP(PokazFrmApp)

bool PokazFrmApp::OnInit()
{
    PokazFrm* frame = new PokazFrm(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int PokazFrmApp::OnExit()
{
	return 0;
}

/*int PokazFrmApp::FilterEvent(wxEvent& event)
{
if ( event.GetEventType()==wxEVT_KEY_DOWN 
     && ((wxKeyEvent&)event).GetKeyCode()==WXK_F1 )
   { Destroy(); return true; }

return -1;
}*/
