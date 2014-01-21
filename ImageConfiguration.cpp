#include "ImageConfiguration.h"

ImageConfiguration::ImageConfiguration() { }

ImageConfiguration::ImageConfiguration(int w,int h, wxPoint place, int ang) {
    width=w;
    height=h;
    imgPlace=place;
    angle=ang;
}

ImageConfiguration& ImageConfiguration::operator=(const ImageConfiguration& img) {
    this->width = img.width;
    this->height = img.height;
    this->imgPlace = img.imgPlace;
    this->angle = img.angle;
}
