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
	if (!test.Init()) {
	std::cout << "fallo Init" << std::endl;
	}



	return 0;
}
