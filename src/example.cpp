#include "SimplexNoise.h"
#include <QApplication>
#include <QImage>
#include <QLabel>
#include <iostream>
#include <cmath>
#include <cstdio>

static const int width = 512;
static const int height = 512;
static const int nOctaves = 16;
static const float  persistence = .5;
static const float frequency = .007;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QImage img(width, height, QImage::Format_RGB32);
    QLabel lbl;
    
   for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int value = (int)SimplexNoise::octave(nOctaves, i, j , persistence, frequency, 0, 255);
            QRgb color = qRgb(value, value, value);
            img.setPixel(i, j, color);
        }
    }
    
    lbl.setPixmap(QPixmap::fromImage(img));
    lbl.show();
    return app.exec();
}
