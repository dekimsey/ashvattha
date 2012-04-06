#include "SimplexNoise.h"
#include <QApplication>
#include <QImage>
#include <QLabel>
#include <iostream>
#include <cmath>
#include <cstdio>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QImage img(512, 512, QImage::Format_RGB32);
    QLabel lbl;
    
   for (int j = 0; j < 512; j++) {
        for (int i = 0; i < 512; i++) {
            int value = (int)SimplexNoise::octave(16, i, j , .5, .007, 0, 255);
            QRgb color = qRgb(value, value, value);
            img.setPixel(i, j, color);
        }
    }
    
    lbl.setPixmap(QPixmap::fromImage(img));
    lbl.show();
    return app.exec();
}
