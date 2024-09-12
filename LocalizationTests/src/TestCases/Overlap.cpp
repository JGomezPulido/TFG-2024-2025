#include "Overlap.h"

#include <fstream>
#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

Overlap::Overlap()
{
	
}

Overlap::~Overlap()
{
	_ocr->End();
	std::cout << "BYE" << std::endl;
}

void Overlap::test(const std::string& testString)
{

}

bool Overlap::checkOverlap(std::vector<ButtonLimits> boxes)
{
	for (ButtonLimits box : boxes) {
		if (box.x < _buttons[0].x ||
			box.x + box.w > _buttons[0].x + _buttons[0].w ||
			box.y < _buttons[0].y ||
			box.y + box.h > _buttons[0].y + _buttons[0].h) 
		{
			return true;
		}
	}
	return false;
}

bool Overlap::Init()
{
	_ocr = new tesseract::TessBaseAPI();
	if (_ocr->Init("/home/trainingFont/trainedModel", "CourierPrime")) {
		std::cout << "fallo Init tess" << std::endl;
		return false;
	}
	Pix* image = pixRead("5.png");
	if (!image) {
		std::cout << "fallo img" << std::endl;
		return false;
	}
	_ocr->SetImage(image);
	_ocr->Recognize(0);
	tesseract::ResultIterator* ri = _ocr->GetIterator();
	tesseract::PageIteratorLevel level = tesseract::RIL_WORD;
	if (ri != nullptr) {
		do {
			const char* word = ri->GetUTF8Text(level);
			float conf = ri->Confidence(level);
			int x1, y1, x2, y2;
			ri->BoundingBox(level, &x1, &y1, &x2, &y2);
			std::cout << "Word: '" << word << "' at (" << x1 << ", " << y1 << ") -> ("
				<< x2 << ", " << y2 << "), Confidence: " << conf << "\n";
			delete[] word;
		} while (ri->Next(level));
	}
	pixDestroy(&image);
	return true;
}
