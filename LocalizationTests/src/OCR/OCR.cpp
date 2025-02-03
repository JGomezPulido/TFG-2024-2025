#include "OCR.h"
#include <fstream>
#include <sstream>
#include "Levenshtein.h"
#include <opencv2/photo.hpp>
#include <opencv2/opencv.hpp>
using namespace std;
std::string OCR::readGT(const std::string& rutaArchivo)
{
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

std::string OCR::findMostSimilarLine(const std::string& target, const std::vector<std::string>& recognizedLines, double threshold)
{
	double maxSimilarity = 0.0;
	std::string bestMatch;

	for (const auto& line : recognizedLines) {
		int distance = Levenshtein::levenshteinDist(target, line);
		double similarity = 1.0 - (double)distance / std::max(target.size(), line.size());
		if (similarity > maxSimilarity && similarity >= threshold) {
			maxSimilarity = similarity;
			bestMatch = line;
		}
	}

	return bestMatch;
}

std::vector<std::string> OCR::splitIntoLines(const std::string& text)
{
	std::vector<std::string> lines;
	std::istringstream stream(text);
	std::string line;
	while (std::getline(stream, line)) {
		lines.push_back(line);
	}
	return lines;
}

bool OCR::preprocessing(std::string iName , imageInfo& imageOutput)
{
	cv::Mat image;
	image = cv::imread(iName, cv::IMREAD_GRAYSCALE);
	if (image.empty()) {
		std::cerr << "Error al leer la imagen" << std::endl;
		return false;
	}
	
	float factor = 1.5;
	cv::resize(image, image, cv::Size(int(image.cols * factor), int(image.rows * factor)), factor, factor, cv::INTER_LINEAR);
	
	cv::threshold(image, image, 127, 255, cv::THRESH_BINARY);
	
	
	
	cv::fastNlMeansDenoising(image, image, 10, 7, 21);
		
	
	cv::medianBlur(image, image, 5);
	cv::GaussianBlur(image, image, cv::Size(5, 5), 0);
		
	cv::Mat kernel = cv::Mat::ones(5, 5, CV_8UC1);  // Kernel de 5x5 de unos
		//Dilatar la imagen
	cv::dilate(image, image, kernel);
		//Erosionar la imagen
	cv::erode(image, image, kernel);   // Configurar los valores de salida
	imageOutput.cols = image.cols;
	imageOutput.rows = image.rows;
	imageOutput.step = image.step;

    // Reservar memoria y copiar los datos
	imageOutput.data = new unsigned char[imageOutput.step * imageOutput.rows];
    memcpy(imageOutput.data, image.data, imageOutput.step * imageOutput.rows);
	return true;
}
