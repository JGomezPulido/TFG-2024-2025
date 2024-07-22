#include <iostream>
#include <string>
#include "Tesseract.h"
#include "TestsAssert.h"
#include "BadlyImplemented.h"
int main(void) {
	PlaceholderVector placeholders = PlaceholderVector();
	placeholders.push_back({ '{','}' });
	BadlyImplemented tests = BadlyImplemented(placeholders);
	tests.test("Hola de buenas");
	tests.test("Hola {name}, que tal est�s {laugh}");
	tests.test("Hola {name{player1}}");
	return 0;

	//Tesseract tess = Tesseract();
	//
	////if (tess.trainModel("spa", "Courier Prime", 1000)) {
	////	std::cout << "YES\n";
	////}else std::cout << "NO\n";
	//tess.getText("/home/images", "Courier Prime");
}