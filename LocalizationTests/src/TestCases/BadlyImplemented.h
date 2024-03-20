#pragma once
#ifndef BADLY_IMPLEMENTED_H
#define BADLY_IMPLEMENTED_H

#include "TestCase.h"
#include <vector>

typedef std::vector <std::pair<char, char>> PlaceholderVector;
class BadlyImplemented : TestCase {
public:
	BadlyImplemented(const PlaceholderVector& placeholderMarkers);
	~BadlyImplemented() {};
	void test(const std::string& testString) override;
private:
	PlaceholderVector _placeholders;

};
#endif