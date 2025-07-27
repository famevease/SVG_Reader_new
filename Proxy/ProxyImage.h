// ProxyImage.h
#pragma once
#include "Image.h"
#include "RealImage.h"
#include <iostream>
#include <string>

using namespace std;

class ProxyImage : public Image {
private:
    string filename;
    RealImage* realImage;

public:
    ProxyImage(const string& filename)
        : filename(filename), realImage(nullptr) {}

    ~ProxyImage() {
        delete realImage;
    }

    void display() override {
        if (!realImage) {
            char choice;
            cout << "[ProxyImage] Do you want to load '" << filename << "'? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                realImage = new RealImage(filename);  // Lazy initialize
            } else {
                cout << "[ProxyImage] Skipped loading image.\n";
                return;
            }
        }
        realImage->display();
    }
};
