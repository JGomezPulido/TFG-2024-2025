#include <iostream>
#include <string>
#include "Tesseract.h"
#include "BadlyImplemented.h"
#include "LocalizationTests.h"
#include "Overlap.h"
#include "FontIssue.h"
#include "DictionaryManager.h"
#include "OrthographicError.h"

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>



using json = nlohmann::json;

int main(int argc, char *argv[]) {

	/*FontIssue f = FontIssue("¿Hola qué tal?");
	f.test("\ufffdHola qu\ufffd tal?");*/


	spdlog::info("Welcome to spdlog!");
	
	//Para testear paso de argumentos
	std::vector<std::vector<std::string>> testCases = {
		{"program", "--test"},
		{"program", "--test", "-c", "/home/localizationtests/volumen/config.json"},
		{"program", "--train", "-f", "Arial", "-l", "eng"},
		{"program", "--train", "-f", "Arial", "-l", "eng", "-i", "50"},
		{"program", "--train", "-f", "Arial", "-l", "eng", "-i", "100", "--clear"},
		{"program", "--train", "-f", "Arial", "-l", "eng", "--clear"},
		{"program", "--train", "-f", "Arial", "-l", "eng", "-i", "abc"} // Caso con error
	};

	LocalizationTests* test = new LocalizationTests();
	test->init(testCases[0]);
	test->run();
	test->release();
	delete test;

	DictionaryManager dictMan;
	if (dictMan.setup())
		std::cout << "Dictionaries found" << std::endl;

	OrtographicError o = OrtographicError(dictMan.getDict(DictionaryManager::Language::Spanish));
	o.test("Hoala soy yo");

	std::string volumen = "/home/localizationtests/volumen/";
	OCR* ocr = new Tesseract();
	ocr->init("/home/trainingFont/trainedModel", "eng");
	//ocr->getDirImgText("/home/images", "/home/result");
	ocr->release();
	delete ocr;
	return 0;
}
