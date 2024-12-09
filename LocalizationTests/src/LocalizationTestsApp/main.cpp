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


int main(int argc, char *argv[]) {

	FontIssue f = FontIssue("¿Hola qué tal?");
	f.test("\ufffdHola qu\ufffd tal?");

	DictionaryManager dictMan;
	if (dictMan.setup())
		std::cout << "Dictionaries found" << std::endl;

	
	

	return 0;
}
