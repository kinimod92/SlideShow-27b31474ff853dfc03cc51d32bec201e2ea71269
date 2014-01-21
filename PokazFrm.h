///-----------------------------------------------------------------
///
/// @file      PokazFrm.h
/// @author    Dominik
/// Created:   2013-12-23 16:02:01
/// @section   DESCRIPTION
///            PokazFrm class declaration
///
///------------------------------------------------------------------

#ifndef __POKAZFRM_H__
#define __POKAZFRM_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/panel.h>
#include <wx/sizer.h>
////Header Include End

////Dialog Style Start
#undef PokazFrm_STYLE
#define PokazFrm_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

#include "libgfl.h"
#include "libgfle.h"
#include "SlideImage.h"
#include <wx/image.h>
#include <wx/dcbuffer.h>
#include <wx/filefn.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h> 
#include <sstream>
#include <wx/utils.h>
#include <wx/graphics.h>
#include <wx/thread.h>
//#include "DrawThread.h"
/*#if wxUSE_GRAPHICS_CONTEXT == 0
  #error wxGraphicsContext not available
#endif*/


//#include "BackgroundPanel.h"
using namespace std;
wxDECLARE_EVENT(myEVT_THREAD_UPDATE, wxThreadEvent);
class PokazFrm : public wxFrame, public wxThreadHelper {
    private:
        // zmienne s³u¿¹ce do rysowania
       // wxClientDC client;
      //  wxBufferedDC dc;
        // nazwa obrazka bêd¹cego t³em
        std::string BGName;
        // obrazek bêd¹cy t³em
        wxImage background;
        // zmienna okreœlaj¹ca obecnoœæ ramki wokó³ obrazka
        bool isPolaroidFrame;
        // kolor ramki
        wxColour polaroidColor;
        // typ animacji
        int animType;
        // czas pomiedzy kolejnymi zdjeciami
        int showInterval;
        // bitmapa biblioteki gfl
        GFL_BITMAP *bitmapGfl;
        int w, h;
        // zmienne biblioteki gfl slu¿¹ce do wczytania obrazów
        GFL_LOAD_PARAMS load_option;
        GFL_FILE_INFORMATION file_info;
        GFL_ERROR error;
        // vector przechowuj¹cy konfiguracje wyœwietlanych obrazków
        vector<ImageConfiguration> configurations;
        // vector przechowuj¹cy wyswietlane obrazki
        vector<SlideImage> images;
        void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
		// wczytanie obrazu przy pomocy biblioteki gfl
		bool gflLoadImage(string fileName);
        // funkcja ustawia t³o
		void setBackground();
        // funkcja konwertuje bitmape z biblioteki gfl do zmiennej wxImage
        void gflToWx(GFL_BITMAP *bitmapGfl, wxImage &img);
        // rysowanie t³a
		void drawBackground();
		//odczytuje dane z pliku konfiguracyjnego
		void ReadCfg();
		void ReadParams(string params);
		// funkcja slu¿¹ca do testow, zapisuje str do pliku, jeœli drugi arg jest true to czysci plik, domyœlnie dopisuje na koniec pliku
		void test(string str, bool clearFile = false ) const;
		// funkcja wczytuje do programu obrazy z katologu Output/MingW
		void loadImages();
		// funkcja rysuje obrazki
        void drawImages();
        //poki co do niczego nie sluzy, ale moze sie przyda
        void OnThreadUpdate(wxThreadEvent& evt);
        
		DECLARE_EVENT_TABLE();

	public:
		PokazFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("PokazSlajdow"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = PokazFrm_STYLE);
		virtual ~PokazFrm();
		//po podwojnym kliknieciu lewego przycisku myszy przelacza miedzy trybem pelnoekranowym
		void FullScreen(wxMouseEvent& event);
		void PokazFrmPaint(wxPaintEvent& event);
		//po wcisnieciu ESC wywoluje sie i zamyka program
		void Exit(wxKeyEvent& event);

	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxPanel *BGPanel;
		wxBoxSizer *WxBoxSizer1;
		////GUI Control Declaration End

	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXPANEL1 = 1004,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};

	protected:
        virtual wxThread::ExitCode Entry();



};


#endif
