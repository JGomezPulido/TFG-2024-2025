#pragma once
#ifndef LOCALIZATIONTESTS_H
#define LOCALIZATIONTESTS_H

#include <chrono>
#include <vector>
#include <string>
struct ConfigInfo {
	std::string imgPath;
	std::string gtPath;
	std::string model;
	std::string modelPath;
	std::string outputPath;
	std::string ocr;
	std::vector<char> placeholders;
};
struct TrainInfo {
	std::string font;
	std::string lan;
	int iter;
	bool clear;
};
class LocalizationTests {
public:
	LocalizationTests();
	~LocalizationTests();
	bool init(const std::vector<std::string>& args);
	void run();
	void release();
private:
	enum class State {
		TESTING,
		TRAINING,
		UNINITIALIZED
	};
	State state_;
	std::chrono::system_clock::time_point initTime_;
	bool parseArguments(const std::vector<std::string>& args);
	void printTime();
	void usage();
	bool getConfig();
	TrainInfo _trainInfo;
	std::string _configFile;
	ConfigInfo _configinfo;
};
#endif