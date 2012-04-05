#include "SimplexNoise.hpp"
#include <QApplication>
#include <QImage>
#include <QLabel>
#include <iostream>
#include <cmath>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QImage img(512, 512, QImage::Format_RGB32);
    QLabel lbl;
    
    for (int i = 0; i < 512; i++) {
        for (int j = 0; j < 512; j++) {
            int value = (int)(SimplexNoise::getInstance().noise(i, j) *127) + 128;
            QRgb color = qRgb(value, value, value);
            img.setPixel(i, j, color);
            if (value < 128)
                std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    lbl.setPixmap(QPixmap::fromImage(img));
    lbl.show();
    return app.exec();
}
