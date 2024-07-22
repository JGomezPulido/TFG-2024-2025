#include "LocalizationTests.h"
#include "Tesseract.h"
#include "BadlyImplemented.h"
#include <iostream>
LocalizationTests::LocalizationTests() : state_(State::UNINITIALIZED), initTime_()
{
}
LocalizationTests::~LocalizationTests()
{
}

bool LocalizationTests::init(const std::vector<std::string>& args)
{
	if (parseArguments(args)) {
		
		return true;
	}
	return false;
}

//TODO: ¿Refactorizar el estado a un patrón Strategy/State?
void LocalizationTests::run()
{
	switch (state_) {
		case State::TRAINING:
		{
			Tesseract tess = Tesseract();
			if (tess.trainModel("spa", "courier prime", 1000)) {
				std::cout << "yes\n";
			}
			else std::cout << "no\n";
			//tess.getText("/home/images", "Courier Prime");
			break;
		}
		case State::TESTING:
		{
			PlaceholderVector placeholders = PlaceholderVector();
			placeholders.push_back({ '{','}' });
			BadlyImplemented tests = BadlyImplemented(placeholders);
			initTime_ = std::chrono::system_clock::now();
			tests.test("Hola de buenas");
			printTime();
			tests.test("Hola {name}, que tal estas {laugh}");
			printTime();
			tests.test("Hola {name{player1}}");
			printTime();
			break;
		}
		default:
			break;
	}
}

bool LocalizationTests::parseArguments(const std::vector<std::string>& args)
{
	if (args.size() != 2) return false;
	if (args[1] == "--test") {
		state_ = State::TESTING;
	}
	else if (args[2] == "--train") {
		state_ = State::TRAINING;
	}
	else {
		usage();
	}
	
	return state_ != State::UNINITIALIZED;
}

void LocalizationTests::printTime()
{
	using namespace std::chrono;
	duration<double> dur = duration_cast<nanoseconds>(system_clock::now() - initTime_);

	std::cout << "Test completed in " << dur.count() << " nanoseconds" << std::endl;

	initTime_ = system_clock::now();
}

void LocalizationTests::usage() {
	std::cout << "Usage: LocalizationTests Option\n" << "Options: --train for training the tesseract OCR --test for testing" << std::endl;
}