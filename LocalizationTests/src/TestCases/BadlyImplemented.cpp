#include "BadlyImplemented.h"

#include <fstream>
#include <iostream>
BadlyImplemented::BadlyImplemented(const PlaceholderVector& placeholder) : _placeholders(placeholder) {};

void BadlyImplemented::test(const std::string& testString) {
	bool passed = true;
	std::vector<int> placeholderPos = std::vector<int>();
	std::vector<bool> counting = std::vector<bool>(_placeholders.size());

	for (int i = 0; i < testString.length(); i++) {
		for (int ph = 0; ph < _placeholders.size(); ph++) {
			std::pair<char, char> placeholder = _placeholders[ph];
			if (testString[i] == placeholder.first) {
				if(!counting[ph]) placeholderPos.push_back(i);
				counting[ph] = true;
			}
			else if (testString[i] == placeholder.second) {
				if (counting[ph]) placeholderPos.push_back(i);
				counting[ph] = false;			
			}
		}
	}

	passed = placeholderPos.empty();

	if (passed) {
		std::cout << "PLACEHOLDER TEST OK FOR STRING: " << testString << "\n";
	}
	else {
		std::cout << "PLACEHOLDER TEST FAILED FOR STRING: " << testString << "See results in testResults.txt \n";
		std::ofstream file("testResults.txt", std::ios::app);
		if (!file) {
			std::cerr << "Error opening testResults.txt\n";
		}
		file << "Placeholder positions for: " << testString << ":";
		for (int pos : placeholderPos) {
			file << pos << " ";
		}
		file << "\n\n";
	}
}