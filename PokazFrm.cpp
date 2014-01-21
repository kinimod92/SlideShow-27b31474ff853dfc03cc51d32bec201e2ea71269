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
wxDEFINE_EVENT(myEVT_THREAD_UPDATE, wxThreadEvent);
////Event Table Start
BEGIN_EVENT_TABLE(PokazFrm,wxFrame)
	////Manual Code Start
	EVT_THREAD(myEVT_THREAD_UPDATE, PokazFrm::OnThreadUpdate)
	////Manual Code End
	EVT_CLOSE(PokazFrm::OnClose)
	EVT_PAINT(PokazFrm::PokazFrmPaint)
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

	BGPanel = new wxPanel(this, ID_WXPANEL1, wxPoint(0, 0), wxSize(1024, 768));
	WxBoxSizer1->Add(BGPanel, 1, wxALIGN_CENTER | wxEXPAND | wxALL, 0);

	SetTitle(_("PokazSlajdow"));
	SetIcon(wxNullIcon);
	
	Layout();
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	Center();
	
	////GUI Items Creation End
    
	ReadCfg();
	setBackground();
	loadImages();
	
	BGPanel->SetFocus();
	BGPanel->Bind(wxEVT_KEY_UP, &PokazFrm::Exit, this);
	//BGPanel->Bind(wxEVT_LEFT_UP, &PokazFrm::FullScreen, this); //EVT_DLEFT_CLICK
	this->Show();
	this->ShowFullScreen(TRUE);
	
    //BGPanel->GetSize(&w, &h);
    //client->SetDeviceOrigin(w/2,h/2);
    drawImages();
}

void PokazFrm::OnClose(wxCloseEvent& event) {
    /*if (GetThread() &&      
        GetThread()->IsRunning())
        GetThread()->Wait();*/
	Destroy();
}

void PokazFrm::FullScreen(wxMouseEvent& event) {
	this->ShowFullScreen(!this->IsFullScreen());
	//drawBackground();
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
    //img.Rotate(3, wxPoint(0,0));
    }
    
}

void PokazFrm::PokazFrmPaint(wxPaintEvent& event) {
    //drawBackground();
    //drawImages();
}

void PokazFrm::Exit(wxKeyEvent& event) {
    if (event.GetKeyCode() == 27)
	   Destroy();
	if (event.GetKeyCode() == WXK_F11)
	  this->ShowFullScreen(!this->IsFullScreen());
}

void PokazFrm::ReadCfg() {
    std::fstream file;
    string desc,rgb,params;
    int RGB[3];
    file.open( "config.txt", std::ios::in | std::ios::out );
    if(file.good() == true ) {
        getline(file, desc);
        getline(file, BGName);
        getline(file, desc);
        getline(file, desc);
        getline(file, rgb);
        if(rgb!=""){
            isPolaroidFrame=true;
            stringstream stream(rgb);
            for(int i=0;i<3;i++) {
                stream >> RGB[i];
                if(!stream)
                    break;
            }
            polaroidColor.Set(RGB[0],RGB[1],RGB[2]);
        }
        else
            isPolaroidFrame=false;
        getline(file,desc);
        file>>animType; //getline(file,animType);
        getline(file,desc);
        getline(file,desc);
        file>>showInterval; //getline(file,showInterval);
        getline(file,desc);
        getline(file,desc);
        while(getline(file,params))
            ReadParams(params);
        file.close();
    } 
    else 
        wxMessageBox("Nie mozna odczytac pliku konfiguracyjnego");
    //wxMessageBox(wxString::Format(wxT("%i"),showInterval));
}

void PokazFrm::ReadParams(string params) {
    int config[5];
    stringstream stream(params);
    for(int i=0;i<5;i++) {
        stream >> config[i];
        if(!stream)
            break;
    }
    configurations.push_back(ImageConfiguration(config[0],config[1],wxPoint(config[2],config[3]),config[4]));
    //wxMessageBox(wxString::Format(wxT("%i"),config[4]));
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

void PokazFrm::drawBackground() {
    if (!background.Ok()) 
        return;
    //dc->Clear();
    /*
    stringstream ss;
    ss << w;
    string str = ss.str();
    test(str,true);
     ss << h;
    str = ss.str();
    test(str);
    */ 
    wxClientDC c(BGPanel);
    wxBufferedDC b(&c);
    int w,h;
    BGPanel->GetSize(&w, &h);
  // client->DrawBitmap( wxBitmap(background.Scale(w,h)), -(w)/2,-(h)/2, true );
    b.DrawBitmap( wxBitmap(background.Scale(w,h)), 0,0, true );
    //c.Blit(0, 0, w, h, &b, 0, 0);
}

void PokazFrm::drawImages() {
    // we want to start a long task, but we don't want our GUI to block
    // while it's executed, so we use a thread to do it.
    if (CreateThread(wxTHREAD_JOINABLE) != wxTHREAD_NO_ERROR) {
        wxLogError("Could not create the worker thread!");
        return;
    }
    // go!
    if (GetThread()->Run() != wxTHREAD_NO_ERROR) {
        wxLogError("Could not run the worker thread!");
        return;
    }
}
//rysowanie
wxThread::ExitCode PokazFrm::Entry() {
    while (!GetThread()->TestDestroy()) {
            int x = 50;
            wxClientDC client(BGPanel);
            wxBufferedDC buffered(&client);
            int w,h;
            BGPanel->GetSize(&w, &h);
            wxBitmap bitmap(background.Scale(w,h));
            int random, size;
            ImageConfiguration randConfiguration;
            for (std::vector<SlideImage>::iterator it = images.begin(); it != images.end(); ++it,  x += 350) {
                    if(animType == 1) {
                        it->Rescale(300, 300);
                        it->SetMaskColour(0,0,255);  
                        double r = 0;
                        for(int i = 50; i <= 400; i += 4) {
                            buffered.DrawBitmap( bitmap, 0,0, true );
                            //wxImage im = it->Rotate( i, wxPoint(150,150) );
                            buffered.DrawBitmap( wxBitmap( (*it).Rotate(r, wxPoint(it->GetWidth()/2,it->GetHeight()/2)) ),100 +x, 50+i, true );
                            client.Blit(0, 0, w, h, &buffered, 0, 0, wxCOPY );
                            //wxMilliSleep(1000);
                            r += 0.1;
                        }
                        bitmap = wxBitmap( buffered.GetAsBitmap().ConvertToImage().Scale(w,h) );
                    }
                    else if(animType == 2) {               
                         size = configurations.size(); 
                         random =  rand() % size;
                         randConfiguration  = configurations[random];
                         wxImage temp = it->Scale( randConfiguration.width, randConfiguration.height );
                         it->SetMaskColour(0,0,255);  
                         for(int i = 0; i <= randConfiguration.imgPlace.y; i += 4) {
                            buffered.DrawBitmap( bitmap, 0,0, true );
                            buffered.DrawBitmap( wxBitmap( (temp) ), randConfiguration.imgPlace.x, i, true );
                            client.Blit(0, 0, w, h, &buffered, 0, 0, wxCOPY );
                            wxMilliSleep(4);
                         }
                         bitmap = wxBitmap( buffered.GetAsBitmap().ConvertToImage().Scale(w,h) );
                    }    
            }
      
        wxQueueEvent(this, new wxThreadEvent(myEVT_THREAD_UPDATE));
    }
    return (wxThread::ExitCode)0;
}

void PokazFrm::OnThreadUpdate(wxThreadEvent& evt) {
    // ...do something... e.g. m_pGauge->Pulse();
    // read some parts of m_data just for fun:
}
