#include <iostream>
#include <string>
#include "TestsAssert.h"
#include "BadlyImplemented.h"
int main(void) {
	PlaceholderVector placeholders = PlaceholderVector();
	placeholders.push_back({ '{','}'});
	BadlyImplemented tests = BadlyImplemented(placeholders);
	tests.test("Hola de buenas");
	tests.test("Hola {name}, que tal estás {laugh}");
	tests.test("Hola {name{player1}}");
	return 0;
}