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

bool Overlap::checkOverlap(ButtonLimits lim)
{
	int btnX = lim.x;
	int btnY=lim.y;
	int btnW=lim.w;
	int btnH=lim.h;
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
	int result = _ocr->Recognize(0);
	if (result != 0) {
		std::cout << "Recognition failed with error code: " << result << std::endl;
		return false;
	}
	tesseract::ResultIterator* ri = _ocr->GetIterator();
	tesseract::PageIteratorLevel level = tesseract::RIL_WORD;
	if (ri != nullptr) {
		const char* word = ri->GetUTF8Text(level);
		while (word != nullptr) {
			float conf = ri->Confidence(level);
			int x1, y1, x2, y2;
			ri->BoundingBox(level, &x1, &y1, &x2, &y2);
			std::cout << "Word: '" << word << "' at (" << x1 << ", " << y1 << ") -> ("
				<< x2 << ", " << y2 << "), Confidence: " << conf << "\n";
			_boxes.push_back({ x1, y1, x2, y2 });
			delete[] word;

			// Avanza al siguiente nivel de iteración
			if (!ri->Next(level)) {
				break;
			}
			word = ri->GetUTF8Text(level);
		}
	}
	pixDestroy(&image);
	return true;
}
