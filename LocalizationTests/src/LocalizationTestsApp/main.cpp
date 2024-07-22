#include <iostream>
#include <string>
#include "Tesseract.h"
int main(void) {
	Tesseract tess = Tesseract();
	
	//if (tess.trainModel("spa", "Courier Prime", 1000)) {
	//	std::cout << "YES\n";
	//}else std::cout << "NO\n";
	tess.getText("/home/images", "Courier Prime");
}