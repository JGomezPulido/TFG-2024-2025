#pragma once
#ifndef LOCALIZATIONTESTS_H
#define LOCALIZATIONTESTS_H

#include <chrono>
#include <vector>
#include <string>

class LocalizationTests {
public:
	LocalizationTests();
	~LocalizationTests();
	bool init(const std::vector<std::string>& args);
	void run();
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
};
#endif