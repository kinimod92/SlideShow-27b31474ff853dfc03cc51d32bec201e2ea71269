//---------------------------------------------------------------------------
//
// Name:        Projekt1App.h
// Author:      Dominik
// Created:     2013-12-23 16:02:01
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __POKAZFRMApp_h__
#define __POKAZFRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class PokazFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
		//int FilterEvent(wxEvent& event);
};

#endif
