#include <wx/image.h>
#include <wx/colour.h>
#include <iostream>
#include "ImageConfiguration.h"
using namespace std;
/**
* klasa wy�wietlanego obrazka
* @author Marcin Niesciur
*/
class SlideImage : public wxImage {
    private:
           // zmienna okre�laj�ca obecno�� ramki wok� obrazka
           bool isPolaroidFrame;
           // kolor ramki
           wxColour polaroidFrameColor;
           // zmienna okre�laj�ca obecno�� opisu wy�wietlanego na ramce
           bool isDescription;
           // opis 
           string description;
           // wska�nik okre�laj�cy konfiguracje wy�wietlanego obrazka
           ImageConfiguration *imgConf;
    public:
        SlideImage(int width, int height);
};
