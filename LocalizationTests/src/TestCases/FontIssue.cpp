#include "FontIssue.h"
#include "iostream"
void FontIssue::test(const std::string& testString)
{
	if (_expected.size() != testString.size()) { 
		std::cout << "Font test failed: expected and tested strings dont have the same length\n";
		return;
	}

	int same = 0;
	for (int i = 0; i < _expected.size(); i++) {
		if (_expected[i] == testString[i]) {
			same++;
		}
	}

	float pass = (float)same / _expected.size();
	std::cout << "FONT TEST RETURNED " << pass * 100.0 << "% similarity\n";
	std::cout << "FONT TEST FAILED";
}
