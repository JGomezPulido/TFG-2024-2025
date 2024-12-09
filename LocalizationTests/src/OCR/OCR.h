#pragma once
#ifndef OCR_H
#define OCR_H
#include <iostream>
#include <cstdlib>
#include <vector>
class OCR
{
public:


private:
	std::string readGT(const std::string& rutaArchivo);
	std::string findMostSimilarLine(const std::string& target, const std::vector<std::string>& recognizedLines, double threshold);
	std::vector<std::string> splitIntoLines(const std::string& text);
	std::string _volumen = "/home/localizationtests/volumen/";
};


#endif