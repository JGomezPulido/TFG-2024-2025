#include <iostream>
#include <string>
#include "Tesseract.h"
#include "BadlyImplemented.h"
#include "LocalizationTests.h"
#include "Overlap.h"

int main(int argc, char *argv[]) {

	/*LocalizationTests tests;
	std::vector<std::string> args(argc);
	for (int i = 0; i < argc; i++) {
		args[i] = std::string(argv[i]);
	}
	if (!tests.init(args)) return 1;
	tests.run();*/

	Overlap test = Overlap();
	if (!test.Init("Overlay_Correct2.png")) {
	std::cout << "fallo test" << std::endl;
	}
	if (test.checkOverlap("a"))std::cout << "OVERLAP!!!!" << std::endl;
	else std::cout << "EVERYTHING OK" << std::endl;

	/*Tesseract tess = Tesseract();
	tess.trainModel("spa", "Courier Prime", 1000);*/

	return 0;
}
