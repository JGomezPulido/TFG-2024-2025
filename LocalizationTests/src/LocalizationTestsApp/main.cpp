#include <iostream>
#include <string>
#include "Tesseract.h"
#include "BadlyImplemented.h"
#include "LocalizationTests.h"
#include "Overlap.h"
#include "FontIssue.h"

#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <fstream>
#include <opencv2/photo.hpp>


// Función para corrección de gamma
cv::Mat corregirGamma(const cv::Mat& imagen, double gamma) {
	cv::Mat imagenCorregida;
	cv::Mat tabla(1, 256, CV_8U);
	uchar* p = tabla.ptr();
	for (int i = 0; i < 256; ++i)
		p[i] = cv::saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);

	cv::LUT(imagen, tabla, imagenCorregida);
	return imagenCorregida;
}

int main(int argc, char *argv[]) {

	std::string volumen = "/home/localizationtests/volumen/";
	
	tesseract::TessBaseAPI* _ocr = new tesseract::TessBaseAPI();
	if (_ocr->Init("/home/trainingFont/trainedModel", "eng")) {
		std::cout << "fallo Init tess" << std::endl;
		return false;
	}
	std::vector<std::pair<std::string, int>> carpetas;
	carpetas.push_back({ "fondo_complejo", 5 });
	carpetas.push_back({ "fondo_simple", 5 });
	carpetas.push_back({ "texto_en_bocadillo", 8 });
	carpetas.push_back({ "pixelart", 9 });
	carpetas.push_back({ "texto_en_bocadillo_2", 5 });

	std::string command = "sudo mkdir -p /home/result";
	std::system(command.c_str());
	command = "sudo chmod 777 /home/result";
	std::system(command.c_str());

	command = "sudo mkdir -p /home/imageresult/";
	std::system(command.c_str());
	command = "sudo chmod 777 /home/imageresult/";
	std::system(command.c_str());

	for (int j = 0;j < carpetas.size();j++) {
		std::string folder = carpetas[j].first;

		std::string command = "sudo mkdir -p /home/result/" + folder;
		std::system(command.c_str());
		command = "sudo chmod 777 /home/result/" + folder;
		std::system(command.c_str());

		command = "sudo mkdir -p /home/imageresult/" + folder;
		std::system(command.c_str());
		command = "sudo chmod 777 /home/imageresult/" + folder;
		std::system(command.c_str());

		for (int i = 1;i <= carpetas[j].second;i++) {
			std::string iName = volumen + folder + "/" + std::to_string(i) + ".png";

			cv::Mat image = cv::imread(iName, cv::IMREAD_GRAYSCALE);

			if (image.empty()) {
				std::cerr << "Error al leer la imagen" << std::endl;
				return -1;
			}
			// Aplicar un suavizado para reducir el ruido
			cv::Mat blurred;
			cv::GaussianBlur(image, image, cv::Size(5, 5), 0);

			// Aplicar Canny para detectar bordes
			cv::Mat edges;
			cv::Canny(image, image, 100, 200);

			// Opcional: Dilatar los bordes para hacer más visibles las áreas de texto
			cv::dilate(image, image, cv::Mat(), cv::Point(-1, -1), 2);

			cv::morphologyEx(image, image, cv::MORPH_CLOSE, cv::Mat(), cv::Point(-1, -1), 2);

			// Invertir la imagen para que el texto sea oscuro sobre fondo blanco
			cv::Mat inverted;
			cv::bitwise_not(image, image);

		

			//cv::fastNlMeansDenoising(image, image, 10, 7, 21);

			//cv::Mat kernel = cv::Mat::ones(5, 5, CV_8UC1);  // Kernel de 5x5 de unos
			//// Dilatar la imagen
			//cv::dilate(image, image, kernel);
			//// Erosionar la imagen
			//cv::erode(image, image, kernel);

			// Aplicar filtro Gaussiano
			/*cv::medianBlur(image, image, 5);
			cv::GaussianBlur(image, image, cv::Size(5, 5), 0);*/
			
			/*float factor = 1.5;
			cv::resize(image, image, cv::Size(int(image.cols * factor), int(image.rows * factor)), factor, factor, cv::INTER_LINEAR);*/

			//cv::threshold(image, image, 127, 255, cv::THRESH_BINARY);
			//cv::adaptiveThreshold(image, image, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 11, 2);

			//// Aumentar contraste
			//double alfa = 1.2; // Contraste
			//int beta = 20;     // Brillo
			//image.convertTo(image, -1, alfa, beta);

			//// Equalización del histograma
			//cv::equalizeHist(image, image);

			// // Corrección gamma
			//cv::Mat gammaCorregida = corregirGamma(image, 1.5);

			//// Filtrar ruido y aplicar enfoque
			//cv::Mat kernel = (cv::Mat_<float>(3, 3) << -1, -1, -1, -1, 9, -1, -1, -1, -1);
			//cv::filter2D(image, image, -1, kernel);

			_ocr->SetImage(image.data, image.cols, image.rows, 1, image.step);
			char* outText = _ocr->GetUTF8Text();


			// Guardar el texto en un archivo en la carpeta result
			std::string savepath = "/home/result/" + folder;
			std::string imagesavepath = "/home/imageresult/" + folder;

			if (!cv::imwrite(imagesavepath + "/" + std::to_string(i) + ".png", image)) {
				std::cerr << "Error al guardar la imagen " << std::endl;
				return -1;
			}
			std::ofstream outFile(savepath + "/" + std::to_string(i) + ".txt");
			if (outFile.is_open()) {
				outFile << outText;
				outFile.close();
				std::cout << "Texto guardado" << std::endl;
			}
			else {
				std::cerr << "No se pudo abrir el archivo para escribir" << std::endl;
			}

			// Liberar recursos
			delete[] outText;
		}
	}
	
	
	_ocr->End();

	return 0;
}
