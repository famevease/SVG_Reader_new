#pragma once 

#include "Image.h"
#include <iostream>
#include <string>

using namespace std;

class RealImage : public Image {
private:
	string fileName;

	void loadImageFromDisk(string fileName) {
		cout << "[RealImage] Loading image from disk: " << fileName << " ...\n";
	}
public:
	RealImage(string fileName) : fileName(fileName) {
		loadImageFromDisk(fileName);
	}

	void display() override {
		cout << "[RealImage] Displaying image: " << fileName << "\n";
	}
};