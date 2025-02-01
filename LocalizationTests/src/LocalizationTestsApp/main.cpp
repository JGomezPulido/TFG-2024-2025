#include <iostream>
#include <string>
#include "Tesseract.h"
#include "BadlyImplemented.h"
#include "LocalizationTests.h"
#include "Overlap.h"
#include "FontIssue.h"

#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <opencv2/photo.hpp>
#include <regex>

#include "Levenshtein.h"

#include "DictionaryManager.h"
#include "OrthographicError.h"
#include <spdlog/spdlog.h>

int main(int argc, char *argv[]) {

	/*FontIssue f = FontIssue("¿Hola qué tal?");
	f.test("\ufffdHola qu\ufffd tal?");*/
	spdlog::info("Welcome to spdlog!");
	
	DictionaryManager dictMan;
	if (dictMan.setup())
		std::cout << "Dictionaries found" << std::endl;

	OrtographicError o = OrtographicError(dictMan.getDict(DictionaryManager::Language::Spanish));
	o.test("Hoala soy yo");

	std::string volumen = "/home/localizationtests/volumen/";
	
	tesseract::TessBaseAPI* _ocr = new tesseract::TessBaseAPI();
	if (_ocr->Init("/home/trainingFont/trainedModel", "eng")) {
		std::cout << "fallo Init tess" << std::endl;
		return false;
	}
	_ocr->End();
	return 0;
}
