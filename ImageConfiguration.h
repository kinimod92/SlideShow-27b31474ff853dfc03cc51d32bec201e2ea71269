#include <iostream>
using namespace std;
/**
* klasa przechowuj�ca informacje o pozycji, rozmiarze i k�cie obrotu wy�wietlanego obrazka
* @author Marcin Niesciur
*/
class ImageConfiguration {
    private:
        // szeroko�� obrazka
        int width;
        // wysoko�� obrazka
        int height;
        // po�o�enie x �rodka obrazka
        int xMiddle;
        // po�o�enie y �rodka obrazka
        int yMiddle;
        // k�t obrotu obrazka
        int angle;    
};
