#include "Overlap.h"

#include <fstream>
#include <iostream>
#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
using namespace cv;
using namespace std;
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

bool Overlap::checkOverlap()
{
	for (int j = 0; j < _buttons.size(); j++) {
		int btnX = _buttons[j].x;
		int btnY = _buttons[j].y;
		int btnW = _buttons[j].w;
		int btnH = _buttons[j].h;
		// Limites del boton
		int btnRight = btnX + btnW;
		int btnBottom = btnY + btnH;

		// Verificar si el bounding box se sale de los límites del botón
		for (int i = 0; i < _boxes.size(); i++) {
			if (_boxes[i].x < btnX || _boxes[i].x2 > btnRight || _boxes[i].y < btnY || _boxes[i].y2 > btnBottom) {
				return true;  // El bounding box se sale de los límites
			}
		}
	}
	return false;  // El bounding box está dentro de los límites
}

bool Overlap::Init(std::string imageUrl)
{
	_imageUrl = imageUrl;
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
	tesseract::PageIteratorLevel level = tesseract::RIL_TEXTLINE;
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

bool Overlap::getButtons()
{
	Mat imagen = imread(_imageUrl);

	if (imagen.empty()) {
		cout << "No se pudo cargar la imagen." << endl;
		return -1;
	}

	cv::Mat gray;
	cv::cvtColor(imagen, gray, cv::COLOR_BGR2GRAY);

	// Aplicar un umbral para binarizar la imagen
	cv::Mat thresh;
	cv::threshold(gray, thresh, 200, 255, cv::THRESH_BINARY_INV); // Ajusta el valor 200 según sea necesario

	// Encontrar contornos
	std::vector<std::vector<cv::Point>> contornos;
	cv::findContours(thresh, contornos, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	// Dibujar los contornos que podrían ser botones
	for (size_t i = 0; i < contornos.size(); i++) {
		vector<Point> aprox;
		approxPolyDP(contornos[i], aprox, arcLength(contornos[i], true) * 0.02, true);

		if (aprox.size() == 4) { // Consideramos que un botón podría ser rectangular
			Rect rect = boundingRect(aprox);
			rectangle(imagen, rect, Scalar(0, 255, 0), 2);  // Dibujar el rectángulo alrededor del botón
			cout << "Coordenadas del boton: " << rect.x << ", " << rect.y
				<< ", ancho: " << rect.width << ", alto: " << rect.height << endl;
			_buttons.push_back({ rect.x,rect.y,rect.width,rect.height });
		}
	}
	
}
