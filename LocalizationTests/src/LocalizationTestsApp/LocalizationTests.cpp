#include "LocalizationTests.h"
#include "Tesseract.h"
#include "BadlyImplemented.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
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

//TODO: �Refactorizar el estado a un patr�n Strategy/State?
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
			break;
		}
		case State::TESTING:
		{
			//PlaceholderVector placeholders = PlaceholderVector();
			//placeholders.push_back({ '{','}' });
			//BadlyImplemented tests = BadlyImplemented(placeholders);
			//initTime_ = std::chrono::system_clock::now();
			//tests.test("Hola de buenas");
			//printTime();
			//tests.test("Hola {name}, que tal estas {laugh}");
			//printTime();
			//tests.test("Hola {name{player1}}");
			//printTime();
			break;
		}
		default:
			break;
	}
}

void LocalizationTests::release()
{
}

bool LocalizationTests::parseArguments(const std::vector<std::string>& args)
{
	//if (args.size() < 2) return false;

	//if (args[1] == "--test") {
	//	state_ = State::TESTING;
	//	if (args.size() >= 4 && args[2] == "-c") { //Si se proporciona un archivo de config
	//		_configFile = args[3];
	//	}
	//	getConfig();
	//}
	//else if (args[1] == "--train") {
	//	if (args.size() < 6 || args[2] != "-f" || args[4] != "-l") {
	//		std::cerr << "Uso incorrecto: --train -f <font> -l <language>\n";
	//		return false;
	//	}
	//	state_ = State::TRAINING;
	//	_trainInfo.font = args[3];
	//	_trainInfo.lan = args[5];
	//	// Buscar par�metros opcionales (-i iter, --clear)
	//	for (int i = 6; i < args.size(); ++i) {
	//		if (args[i] == "-i" && i + 1 < args.size()) {
	//			try {
	//				_trainInfo.iter = std::stoi(args[i + 1]);  // Convertir a entero
	//				i++;  // Saltar el siguiente argumento
	//			}
	//			catch (...) {
	//				std::cerr << "Error: Iteraciones debe ser un n�mero entero.\n";
	//				return false;
	//			}
	//		}
	//		else if (args[i] == "--clear") {
	//			_trainInfo.clear = true;
	//		}
	//		else {
	//			std::cerr << "Argumento desconocido: " << args[i] << "\n";
	//			return false;
	//		}
	//	}
	//}
	//else {
	//	usage();
	//	return false;
	//}

	return state_ != State::UNINITIALIZED;
}


void LocalizationTests::usage() {
	std::cout << "Usage: LocalizationTests Option\n" << "Options: --train for training the tesseract OCR --test for testing\n"
		<< "  --test [-c <configfile>]\n"
		<< "  --train -f <font> -l <language> [-i <iteraciones>] [--clear]\n";
}


