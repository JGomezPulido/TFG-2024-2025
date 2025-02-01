//#include "TesseractApi.h"
//
//void TesseractApi::test()
//{
//	Inicio tesseract (se necesita modelo e idioma)
//	tesseract::TessBaseAPI* _ocr = new tesseract::TessBaseAPI();
//	if (_ocr->Init("/home/trainingFont/trainedModel", "eng")) {
//		std::cout << "fallo Init tess" << std::endl;
//		return false;
//	}
//
//	Carpetas de imagetesting
//	std::vector<std::pair<std::string, int>> carpetas;
//	carpetas.push_back({ "fondo_complejo", 5 });
//	carpetas.push_back({ "fondo_simple", 5 });
//	carpetas.push_back({ "texto_en_bocadillo", 8 });
//	carpetas.push_back({ "pixelart", 9 });
//	carpetas.push_back({ "texto_en_bocadillo_2", 5 });
//
//	Creación de carpetas de resultados
//	std::string command = "sudo mkdir -p /home/result";
//	std::system(command.c_str());
//	command = "sudo chmod 777 /home/result";
//	std::system(command.c_str());
//
//	command = "sudo mkdir -p /home/imageresult/";
//	std::system(command.c_str());
//	command = "sudo chmod 777 /home/imageresult/";
//	std::system(command.c_str());
//
//	for (int j = 0;j < carpetas.size();j++) {
//		std::string folder = carpetas[j].first;
//		Permisos de escritura de las carpetas
//		std::string command = "sudo mkdir -p /home/result/" + folder;
//		std::system(command.c_str());
//		command = "sudo chmod 777 /home/result/" + folder;
//		std::system(command.c_str());
//
//		command = "sudo mkdir -p /home/imageresult/" + folder;
//		std::system(command.c_str());
//		command = "sudo chmod 777 /home/imageresult/" + folder;
//		std::system(command.c_str());
//
//		for (int i = 1;i <= carpetas[j].second;i++) {
//			Nombre de imagen y gt
//			std::string iName = volumen + folder + "/" + std::to_string(i) + ".png";
//			std::string gtName = volumen + folder + "/" + std::to_string(i) + "-gt.txt";
//			 Guardar el texto en un archivo en la carpeta result
//			std::string savepath = "/home/result/" + folder;
//			std::string imagesavepath = "/home/imageresult/" + folder;
//
//			Preprocesamientos
//			cv::Mat image = cv::imread(iName, cv::IMREAD_GRAYSCALE);
//
//			if (image.empty()) {
//				std::cerr << "Error al leer la imagen" << std::endl;
//				return -1;
//			}
//
//			float factor = 1.5;
//			cv::resize(image, image, cv::Size(int(image.cols * factor), int(image.rows * factor)), factor, factor, cv::INTER_LINEAR);
//
//			cv::threshold(image, image, 127, 255, cv::THRESH_BINARY);
//
//
//
//			cv::fastNlMeansDenoising(image, image, 10, 7, 21);
//	
//
//			cv::medianBlur(image, image, 5);
//			cv::GaussianBlur(image, image, cv::Size(5, 5), 0);
//	
//
//			cv::Mat kernel = cv::Mat::ones(5, 5, CV_8UC1);  // Kernel de 5x5 de unos
//			 Dilatar la imagen
//			cv::dilate(image, image, kernel);
//			 Erosionar la imagen
//			cv::erode(image, image, kernel);
//
//	
//			_ocr->SetImage(image.data, image.cols, image.rows, 1, image.step);
//			char* outText = _ocr->GetUTF8Text();
//
//			std::string expected = readGT(gtName);
//			std::vector<std::string> expectedLines = splitIntoLines(expected);
//			std::vector<std::string> outputLines =  splitIntoLines(outText);
//			std::string cleanOutPut;
//			for (const auto& expectedLine : expectedLines) {
//				std::string bestMatch = findMostSimilarLine(expectedLine, outputLines, 0.8);
//				if (!bestMatch.empty()) {
//					cleanOutPut += bestMatch + "\n";
//				}
//			}
//			std::ofstream outFile(savepath + "/" + std::to_string(i) + ".txt");
//			if (outFile.is_open()) {
//				outFile << cleanOutPut;
//				outFile.close();
//				std::cout << "Texto guardado" << std::endl;
//			}
//			else {
//				std::cerr << "No se pudo abrir el archivo para escribir" << std::endl;
//			}
//
//			 Liberar recursos
//			delete[] outText;
//		}
//	}
//	
//	
//	_ocr->End();
//}
