#include <wx/image.h>
#include <wx/colour.h>
#include <iostream>
#include "ImageConfiguration.h"
using namespace std;
/**
* klasa wyœwietlanego obrazka
* @author Marcin Niesciur
*/
class SlideImage : public wxImage {
    private:
           // zmienna okreœlaj¹ca obecnoœæ ramki wokó³ obrazka
           bool isPolaroidFrame;
           // kolor ramki
           wxColour polaroidFrameColor;
           // zmienna okreœlaj¹ca obecnoœæ opisu wyœwietlanego na ramce
           bool isDescription;
           // opis 
           string description;
           // wska¿nik okreœlaj¹cy konfiguracje wyœwietlanego obrazka
           ImageConfiguration *imgConf;
    public:
        SlideImage(int width, int height);
};
