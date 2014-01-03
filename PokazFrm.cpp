///-----------------------------------------------------------------
///
/// @file      PokazFrm.cpp
/// @author    Dominik
/// Created:   2013-12-23 16:02:01
/// @section   DESCRIPTION
///            PokazFrm class implementation
///
///------------------------------------------------------------------

#include "PokazFrm.h"


//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// PokazFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(PokazFrm,wxFrame)
	////Manual Code Start
	//EVT_CHAR(PokazFrm::Exit)
	////Manual Code End
	
	EVT_CLOSE(PokazFrm::OnClose)
	EVT_PAINT(PokazFrm::PokazFrmPaint)
	
	EVT_UPDATE_UI(ID_WXPANEL1,PokazFrm::BGPanelUpdateUI)
END_EVENT_TABLE()
////Event Table End

PokazFrm::PokazFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style) {
    gflLibraryInit();
    wxInitAllImageHandlers();
	CreateGUIControls();
		
}

PokazFrm::~PokazFrm(){
}

void PokazFrm::CreateGUIControls() {
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(WxBoxSizer1);
	this->SetAutoLayout(true);

	BGPanel = new wxPanel(this, ID_WXPANEL1, wxPoint(0, 0), wxSize(441, 311));
	WxBoxSizer1->Add(BGPanel, 1, wxALIGN_CENTER | wxEXPAND | wxALL, 0);

	SetTitle(_("PokazSlajdow"));
	SetIcon(wxNullIcon);
	
	Layout();
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	Center();
	
	////GUI Items Creation End
	this->client = new wxClientDC(BGPanel);
    this->dc = new wxBufferedDC();
    
    
	ReadCfg();
	setBackground();
	//drawBackground();
	loadImages();
	
	BGPanel->SetFocus();
	BGPanel->Bind(wxEVT_KEY_UP, &PokazFrm::Exit, this);
	BGPanel->Bind(wxEVT_LEFT_UP, &PokazFrm::FullScreen, this); //EVT_DLEFT_CLICK
	this->Show();
	this->ShowFullScreen(TRUE);
}

void PokazFrm::OnClose(wxCloseEvent& event) {
	Destroy();
}

void PokazFrm::FullScreen(wxMouseEvent& event) {
	this->ShowFullScreen(!this->IsFullScreen());
	//client = new wxClientDC(BGPanel);
    //dc = new wxBufferedDC(client);
    //dc = wxGraphicsContext::Create( bdc );
	drawBackground();
}

bool PokazFrm::gflLoadImage(string fileName) {
    gflGetDefaultLoadParams(&load_option);
    this->load_option.Flags |= GFL_LOAD_METADATA;
    this->error = gflLoadBitmap(fileName.c_str(), &bitmapGfl, &load_option, &file_info);
    if (error) {
        wxMessageBox("Nie mozna wczytac pliku");
        return false;
    } else 
        return true;
}

void PokazFrm::setBackground() {  
    if( true == gflLoadImage(this->BGName) )
        gflToWx(bitmapGfl, background);
}

void PokazFrm::gflToWx(GFL_BITMAP *bitmap, wxImage &img) {
    img.Create(bitmap->Width, bitmap->Height);
    GFL_COLOR c;
    for (int i = 0; i < bitmap->Width; i++) {
        for (int j = 0; j < bitmap->Height; j++) {
            gflGetColorAt(bitmap, i, j, &c);
            img.SetRGB(i, j, c.Red, c.Green, c.Blue);
        }
    }
}

void PokazFrm::drawBackground() {
    if (!background.Ok()) 
        return;
    //dc->Init(client, BGPanel->GetSize());
    int w, h;
    
    dc->Clear();
    BGPanel->GetSize(&w, &h);
    client->DrawBitmap( wxBitmap(background.Scale(w,h)), 0, 0, true );
    dc->Blit(0, 0, w, h, client, -(w)/2,-(h)/2);
}

void PokazFrm::PokazFrmPaint(wxPaintEvent& event) {
	drawBackground();
	drawImages();
}

void PokazFrm::Exit(wxKeyEvent& event) {
    if (event.GetKeyCode() == 27)
	   Destroy();
}

void PokazFrm::ReadCfg() {
    std::fstream file;
    file.open( "config.txt", std::ios::in | std::ios::out );
    if(file.good() == true ) {
        getline(file, BGName);
        file.close();
    } else wxMessageBox("Nie mozna odczytac pliku konfiguracyjnego");
}

void PokazFrm::BGPanelUpdateUI(wxUpdateUIEvent& event) {
    //drawBackground();
}

void PokazFrm::test(string str, bool clearFile ) const {
    std::fstream file;
    if (clearFile == true)
        file.open( "test.txt", ios::in | ios::out | ios::trunc);
    else
        file.open( "test.txt", ios::in | ios::out | ios::ate);
    if(file.good() == true ) {
        file << str << endl ;
        file.close();
    }
    else
        wxMessageBox("Nie ma pliku test.txt");
}

void PokazFrm::loadImages() {
    wxString fileName = wxFindFirstFile("*.*");
    //test("",true);
    string temp;
    while ( !fileName.empty() ) {
        temp = fileName.ToStdString();
        if (  temp.find(".dll") == std::string::npos & temp.find(".exe") == std::string::npos & temp.find(".txt") == std::string::npos & temp.find(this->BGName) == std::string::npos ) { 
            gflLoadImage(temp);
            SlideImage img(bitmapGfl->Width, bitmapGfl->Height);
            gflToWx(bitmapGfl, img);
            this->images.push_back(img);
            //test( temp );
        }  
        fileName = wxFindNextFile();
    }    
}

void PokazFrm::drawImages() {
    int x = 50;
    int w, h;
    BGPanel->GetSize(&w, &h);
    for (std::vector<SlideImage>::iterator it = images.begin(); it != images.end(); ++it,  x += 250) {
        for(int i = 0;  i <= 600 ; i += 2) {
            dc->Clear();
            client->DrawBitmap( wxBitmap(background.Scale(w,h)), 0, 0, true );
            client->DrawRectangle(30+i, 230, 340,380);
            client->DrawBitmap( wxBitmap( (*it).Scale(300,300)), 50+i, 250, true );
            dc->Blit(0, 0, w, h, client, 0, 0, wxCOPY );
            //Sleep(5);
            
            wxMilliSleep(5);
        }
    }
}
