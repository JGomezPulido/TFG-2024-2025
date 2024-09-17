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
}

void Overlap::test(const std::string& testString)
{

}

bool Overlap::checkOverlap(std::string imageUrl)
{
	int btnX=65;
	int btnY=67;
	int btnW=337;
	int btnH=144;
	// Limites del boton
	int btnRight = btnX + btnW;
	int btnBottom = btnY + btnH;

	// Verificar si el bounding box se sale de los límites del botón
	for (int i = 0;i < _boxes.size();i++) {
		if (_boxes[i].x < btnX || _boxes[i].x2 > btnRight || _boxes[i].y < btnY || _boxes[i].y2 > btnBottom) {
			return true;  // El bounding box se sale de los límites
		}
	}
	return false;  // El bounding box está dentro de los límites
}

//bool Overlap::checkOverlap(std::vector<ButtonLimits> boxes)
//{
//	for (ButtonLimits box : boxes) {
//		if (box.x < _buttons[0].x ||
//			box.x + box.w > _buttons[0].x + _buttons[0].w ||
//			box.y < _buttons[0].y ||
//			box.y + box.h > _buttons[0].y + _buttons[0].h) 
//		{
//			return true;
//		}
//	}
//	return false;
//}

bool Overlap::Init(std::string imageUrl)
{
	//Esto tiene que ir en tesseract
	_ocr = new tesseract::TessBaseAPI();
	if (_ocr->Init("/home/trainingFont/trainedModel", "CourierPrime")) {
		std::cout << "fallo Init tess" << std::endl;
		return false;
	}
	//----------------------------------------------------------------------
	Pix* image = pixRead(imageUrl.c_str());
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
			_boxes.push_back({ x1,y1,x2,y2 });
			delete[] word;
		} while (ri->Next(level));
	}
	pixDestroy(&image);
	return true;
}
