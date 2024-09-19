#include <iostream>
#include <string>
#include "Tesseract.h"
#include "BadlyImplemented.h"
#include "LocalizationTests.h"
#include "Overlap.h"
#include "FontIssue.h"

int main(int argc, char *argv[]) {

	/*LocalizationTests tests;
	std::vector<std::string> args(argc);
	for (int i = 0; i < argc; i++) {
		args[i] = std::string(argv[i]);
	}
	if (!tests.init(args)) return 1;
	tests.run();*/

	Overlap testCorrect = Overlap();
	if (!testCorrect.Init("Overlay_Correct2.png")) {
	std::cout << "fallo test" << std::endl;
	}
	if (testCorrect.checkOverlap({65,67,337,144}))std::cout << "OVERLAP!!!!" << std::endl;
	else std::cout << "EVERYTHING OK" << std::endl;

	Overlap testFail = Overlap();
	if (!testFail.Init("Overlay_Fail.png")) {
		std::cout << "fallo test" << std::endl;
	}
	if (testFail.checkOverlap({ 65,67,337,144 }))std::cout << "OVERLAP!!!!" << std::endl;
	else std::cout << "EVERYTHING OK" << std::endl;

	FontIssue font("Àvila es una ciudad");
	font.test("Eavila es una ciudad");
	/*Tesseract tess = Tesseract();
	tess.trainModel("spa", "Courier Prime", 1000);*/

	return 0;
}
