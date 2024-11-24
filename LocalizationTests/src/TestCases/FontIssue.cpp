#include "FontIssue.h"
#include <utf8.h>
#include <iostream>
#include <string>

//Error de fuente:
//Restricciones, codificado en utf-8, ambas strings deben tener la misma longitud (en codepoints utf-8)
//El test compara ambas strings caracter a caracter, si encuentra una similaridad <= 90% o un replacement character (carácter no reconocido), falla 
void FontIssue::test(const std::string& testString)
{

	if (utf8::find_invalid(_expected.begin(), _expected.end()) != _expected.end()) {
		std::cout << "Error on Font issue test: expected string not valid utf-8" << std::endl;
		return;
	}

	if (utf8::find_invalid(testString.begin(), testString.end()) != testString.end()) {
		std::cout << "Error on Font issue test: tested string not valid utf-8" << std::endl;
		return;
	}

	if (utf8::distance(_expected.begin(), _expected.end()) != utf8::distance(testString.begin(), testString.end())) {
		std::cout << "Error on Font issue test: tested string not same length as expected" << std::endl;
		return;
	}

	//Replacement character: \ufffd
	//Null character \0 (.notdef)
	bool replacement = false;
	int same = 0;

	auto testIterator = testString.begin();
	for (auto it =_expected.begin(); it != _expected.end(); ) {
		auto expected = utf8::next(it, _expected.end());
		auto test = utf8::next(testIterator, testString.end());
		if (expected == test) {
			same++;
		}
		if (test == u'\ufffd') {
			replacement = true;
		}
	}

	
	float pass = (float)same / _expected.size();
	
	if(replacement || pass <= .80) 
		std::cout << "FONT TEST NOT PASSED: " << (replacement?"REPLACEMENT CHARACTER FOUND ":"") << pass*100.0 << "% similarity" << std::endl;
	else
		std::cout << "FONT TEST PASSED " << pass * 100.0 << "% similarity\n";
}
