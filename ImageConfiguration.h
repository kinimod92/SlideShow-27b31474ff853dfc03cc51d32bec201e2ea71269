#include <iostream>
#include <wx/gdicmn.h>
using namespace std;
/**
* klasa przechowuj�ca informacje o pozycji, rozmiarze i k�cie obrotu wy�wietlanego obrazka
* @author Marcin Niesciur
*/
class ImageConfiguration {
    public:
        // szeroko�� obrazka
        int width;
        // wysoko�� obrazka
        int height;
        // po�o�enie x �rodka obrazka
        //int xMiddle;
        // po�o�enie y �rodka obrazka
        //int yMiddle;
        wxPoint imgPlace;
        // k�t obrotu obrazka
        int angle;
    public:
        ImageConfiguration(int w,int h, wxPoint place, int ang);
        ImageConfiguration();
        ImageConfiguration& operator=(const ImageConfiguration& img);
};
