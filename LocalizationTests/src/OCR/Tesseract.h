#pragma once
#ifndef TESSERACT_H
#define TESSERACT_H
#include "OCR.h"
class Tesseract
{
public:
	bool getText(std::string imgPath, std::string model);
	bool trainModel(std::string lan, std::string font, int iteration,bool clear=false);
private:
	const std::string trainFolder = "/home/trainingFont";
	const std::string groundTruth = "python3 " + trainFolder + "/ground_truth_exec.py";
	const std::string trainTess = "python3 " + trainFolder + "/trainTess_exec.py";
	const std::string tessdatadir = trainFolder + "/trainedModel";
	bool generateGT(std::string lan, std::string font);
	bool train(std::string lan, std::string font, int iteration, bool clear = false);
};

#endif