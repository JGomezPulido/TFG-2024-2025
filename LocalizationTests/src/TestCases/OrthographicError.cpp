#include "OrthographicError.h"

#include <vector>
#include <sstream>
#include <iostream>
void OrtographicError::test(const std::string& testString)
{
	std::stringstream ss(testString);

	std::string word;
	std::vector<std::string> words;
	while (ss >> word) {
		words.push_back(word);

	}

	int success;
	for (auto w : words) {
		success += dict.spell(w) ? 1 : 0;
	}

	std::cout << "Ortographic chech success rate: " << (float)success / words.size() * 100. << " %" << std::endl;
}
