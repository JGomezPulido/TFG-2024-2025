#pragma once
#ifndef OVERLAP_H
#define OVERLAP_H

#include "TestCase.h"
#include <vector>
struct ButtonLimits
{
	int x;
	int y;
	int w;
	int h;
};

namespace tesseract {
	class TessBaseAPI;
}

class Overlap : TestCase {
public:
	Overlap();
	~Overlap();
	void test(const std::string& testString) override;
	bool checkOverlap(std::vector<ButtonLimits> boxes);
	bool Init();
private:
	std::vector<ButtonLimits> _buttons;
	tesseract::TessBaseAPI* _ocr = nullptr;
};
#endif