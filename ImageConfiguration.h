#include <iostream>
#include <wx/gdicmn.h>
using namespace std;
/**
* klasa przechowuj¹ca informacje o pozycji, rozmiarze i k¹cie obrotu wyœwietlanego obrazka
* @author Marcin Niesciur
*/
class ImageConfiguration {
    public:
        // szerokoœæ obrazka
        int width;
        // wysokoœæ obrazka
        int height;
        // po³o¿enie x œrodka obrazka
        //int xMiddle;
        // po³o¿enie y œrodka obrazka
        //int yMiddle;
        wxPoint imgPlace;
        // k¹t obrotu obrazka
        int angle;
    public:
        ImageConfiguration(int w,int h, wxPoint place, int ang);
        ImageConfiguration();
        ImageConfiguration& operator=(const ImageConfiguration& img);
};
