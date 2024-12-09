#include "OCR.h"
#include <fstream>
#include <sstream>
#include "Levenshtein.h"
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
