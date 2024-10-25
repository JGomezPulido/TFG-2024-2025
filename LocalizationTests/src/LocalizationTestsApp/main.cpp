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
	std::string volumen = "/home/localizationtests/volumen/overlap/";
	Overlap testCorrect = Overlap();
	if (!testCorrect.Init(volumen + "C.png")) {
	std::cout << "fallo test" << std::endl;
	}
	testCorrect.getButtons();
	if (testCorrect.checkOverlap())std::cout << "OVERLAP!!!!" << std::endl;
	else std::cout << "EVERYTHING OK" << std::endl;
	

	Overlap testFail = Overlap();
	if (!testFail.Init(volumen+"F.png")) {
		std::cout << "fallo test" << std::endl;
	}
	testFail.getButtons();
	if (testFail.checkOverlap())std::cout << "OVERLAP!!!!" << std::endl;
	else std::cout << "EVERYTHING OK" << std::endl;

	Overlap testMultiFail = Overlap();
	if (!testMultiFail.Init(volumen + "Multi_Fail.png")) {
		std::cout << "fallo test" << std::endl;
	}
	testMultiFail.getButtons();
	if (testMultiFail.checkOverlap())std::cout << "OVERLAP!!!!" << std::endl;
	else std::cout << "EVERYTHING OK" << std::endl;

	Overlap testMultiCorrect = Overlap();
	if (!testMultiCorrect.Init(volumen + "Multi_Correct.png")) {
		std::cout << "fallo test" << std::endl;
	}
	testMultiCorrect.getButtons();
	if (testMultiCorrect.checkOverlap())std::cout << "OVERLAP!!!!" << std::endl;
	else std::cout << "EVERYTHING OK" << std::endl;


	

	//FontIssue font("Àvila es una ciudad");
	//font.test("Eavila es una ciudad");

	/*Tesseract tess = Tesseract();
	tess.trainModel("spa", "Arial", 1000);*/

	return 0;
}
