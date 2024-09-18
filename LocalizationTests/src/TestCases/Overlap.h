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
struct BoudingBox {
	int x;
	int y;
	int x2;
	int y2;
};

namespace tesseract {
	class TessBaseAPI;
}

class Overlap : TestCase {
public:
	Overlap();
	~Overlap();
	void test(const std::string& testString) override;
	bool checkOverlap(ButtonLimits lim);
	bool Init(std::string imageUrl);
private:
	std::vector<ButtonLimits> _buttons;
	std::vector<BoudingBox>_boxes;
	tesseract::TessBaseAPI* _ocr = nullptr;
};
#endif