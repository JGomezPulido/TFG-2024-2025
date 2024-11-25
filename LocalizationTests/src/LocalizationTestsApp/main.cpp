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
#include <regex>

#include "Levenshtein.h"
std::string readGT(const std::string& rutaArchivo) {
	std::ifstream archivo(rutaArchivo, std::ios::in | std::ios::binary);
	if (!archivo) {
		throw std::runtime_error("No se pudo abrir el archivo: " + rutaArchivo);
	}

	// Mover el puntero al final para determinar el tamaño
	archivo.seekg(0, std::ios::end);
	std::streamsize tamano = archivo.tellg();
	archivo.seekg(0, std::ios::beg);

	// Reservar espacio y leer todo el contenido
	std::string contenido(tamano, '\0');
	archivo.read(&contenido[0], tamano);
	archivo.close();

	return contenido;
}
// Función para limpiar la salida de Tesseract
std::string cleanTesseractOutput(const std::string& tesseractOutput,
	const std::string& expectedOutput,
	double similarityThreshold) {
	std::vector<std::string> tesseractWords;
	std::vector<std::string> expectedWords;
	std::string cleanedOutput;

	// Dividir la salida en palabras
	std::istringstream tessStream(tesseractOutput);
	std::string word;
	while (tessStream >> word) {
		tesseractWords.push_back(word);
	}

	std::istringstream expStream(expectedOutput);
	while (expStream >> word) {
		expectedWords.push_back(word);
	}

	// Comparar cada palabra de la salida de Tesseract con la mejor coincidencia esperada
	for (const auto& tessWord : tesseractWords) {
		double bestSimilarity = 0.0;
		for (const auto& expWord : expectedWords) {
			int distance = Levenshtein::levenshteinDist(tessWord, expWord);
			double similarity = 1.0 - (double)distance / std::max(expWord.size(), tessWord.size());
			bestSimilarity = std::max(bestSimilarity, similarity);
		}
		// Verificar si la palabra cumple con el umbral de similitud
		if (bestSimilarity >= similarityThreshold) {
			cleanedOutput += tessWord + " ";
		}
	}

	// Eliminar el último espacio extra
	if (!cleanedOutput.empty()) {
		cleanedOutput.pop_back();
	}

	return cleanedOutput;
}
int main(int argc, char *argv[]) {

	std::string volumen = "/home/localizationtests/volumen/";
	
	tesseract::TessBaseAPI* _ocr = new tesseract::TessBaseAPI();
	if (_ocr->Init("/home/trainingFont/trainedModel", "eng")) {
		std::cout << "fallo Init tess" << std::endl;
		return false;
	}
	_ocr->SetVariable("tessedit_char_whitelist", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789' ");
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
			std::string gtName = volumen + folder + "/" + std::to_string(i) + "-gt.txt";
			// Guardar el texto en un archivo en la carpeta result
			std::string savepath = "/home/result/" + folder;
			std::string imagesavepath = "/home/imageresult/" + folder;
			cv::Mat image = cv::imread(iName, cv::IMREAD_GRAYSCALE);

			if (image.empty()) {
				std::cerr << "Error al leer la imagen" << std::endl;
				return -1;
			}

			float factor = 1.5;
			cv::resize(image, image, cv::Size(int(image.cols * factor), int(image.rows * factor)), factor, factor, cv::INTER_LINEAR);

			cv::threshold(image, image, 127, 255, cv::THRESH_BINARY);

			//if (!cv::imwrite(imagesavepath + "/" + std::to_string(i) + "0.png", image)) {
			//	std::cerr << "Error al guardar la imagen " << std::endl;
			//	return -1;
			//}

			cv::fastNlMeansDenoising(image, image, 10, 7, 21);
			//if (!cv::imwrite(imagesavepath + "/" + std::to_string(i) + "1.png", image)) {
			//	std::cerr << "Error al guardar la imagen " << std::endl;
			//	return -1;
			//}

			cv::medianBlur(image, image, 5);
			cv::GaussianBlur(image, image, cv::Size(5, 5), 0);
			//if (!cv::imwrite(imagesavepath + "/" + std::to_string(i) + "2.png", image)) {
			//	std::cerr << "Error al guardar la imagen " << std::endl;
			//	return -1;
			//}

			cv::Mat kernel = cv::Mat::ones(5, 5, CV_8UC1);  // Kernel de 5x5 de unos
			// Dilatar la imagen
			cv::dilate(image, image, kernel);
			// Erosionar la imagen
			cv::erode(image, image, kernel);

	/*		if (!cv::imwrite(imagesavepath + "/" + std::to_string(i) + "3.png", image)) {
				std::cerr << "Error al guardar la imagen " << std::endl;
				return -1;
			}*/

			/*cv::adaptiveThreshold(image, image, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 11, 2);
			if (!cv::imwrite(imagesavepath + "/" + std::to_string(i) + "4.png", image)) {
				std::cerr << "Error al guardar la imagen " << std::endl;
				return -1;
			}*/

			//// Equalización del histograma
			//cv::equalizeHist(image, image);
			//if (!cv::imwrite(imagesavepath + "/" + std::to_string(i) + "5.png", image)) {
			//	std::cerr << "Error al guardar la imagen " << std::endl;
			//	return -1;
			//}

			

			// Aplicar filtro Gaussiano
			
			
			

			
			
			//// Aumentar contraste
			//double alfa = 1.2; // Contraste
			//int beta = 20;     // Brillo
			//image.convertTo(image, -1, alfa, beta);

			// // Corrección gamma
			//cv::Mat gammaCorregida = corregirGamma(image, 1.5);

			// aplicar filtro de nitidez
			cv::Mat kernel2 = (cv::Mat_<float>(3, 3) << -1, -1, -1, -1, 9, -1, -1, -1, -1);
			cv::filter2D(image, image, -1, kernel2);

			_ocr->SetImage(image.data, image.cols, image.rows, 1, image.step);
			char* outText = _ocr->GetUTF8Text();

			//std::string extractedText(outText);
			////-------------------------
			//std::regex pattern("([A-Za-z0-9' ]+)");
			//std::smatch match;
			//std::string cleanText;
			//std::string::const_iterator searchStart(extractedText.cbegin());

			//while (std::regex_search(searchStart, extractedText.cend(), match, pattern)) {
			//	cleanText += match[0].str() + "\n";
			//	searchStart = match.suffix().first;
			//}
			////-------------------------------
			

			/*if (!cv::imwrite(imagesavepath + "/" + std::to_string(i) + ".png", image)) {
				std::cerr << "Error al guardar la imagen " << std::endl;
				return -1;
			}*/
			std::string expected = readGT(gtName);
			std::string cleanOutPut = cleanTesseractOutput(outText, expected, 0.7);
			std::ofstream outFile(savepath + "/" + std::to_string(i) + ".txt");
			if (outFile.is_open()) {
				outFile << cleanOutPut;
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
