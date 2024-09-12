#include "Tesseract.h"
#include <fstream> 
#include <string>
#include <algorithm>
#include <vector>
#include <dirent.h>
#include <cstring>

bool Tesseract::getText(std::string imgPath ,std::string model)
{
    //Eliminar espacios
    model.erase(std::remove_if(model.begin(), model.end(), ::isspace), model.end());

    std::vector<std::string> pngFiles;
    DIR* dir;
    struct dirent* ent;

    // Abre el directorio
    if ((dir = opendir(imgPath.c_str())) != nullptr) {
        // Itera sobre las entradas del directorio
        while ((ent = readdir(dir)) != nullptr) {
            // Obtiene el nombre del archivo
            std::string filename = ent->d_name;
            // Verifica si la entrada es un archivo regular y tiene la extensión .png
            if (ent->d_type == DT_REG && filename.size() > 4 && filename.substr(filename.size() - 4) == ".png") {
                pngFiles.push_back(filename);
            }
        }
        // Cierra el directorio
        closedir(dir);
    }
    else {
        // Muestra un mensaje de error si el directorio no se puede abrir
        std::cerr << "No se pudo abrir el directorio: " << imgPath << std::endl;
    }
    //const char* output_file = "output.log";
    for (int i = 0; i < pngFiles.size(); i++) {
        std::string command = "sudo tesseract " + imgPath + "/" + pngFiles[i] + " " + imgPath + "/" + pngFiles[i] + " --tessdata-dir " + tessdatadir + " -l " + model;
        //std::string command = "sudo tesseract " + imgPath + "/" + pngFiles[i] + " stdout --tessdata-dir " + tessdatadir + " -l " + model +" > " + std::string(output_file);
        system(command.c_str());
        //std::ifstream output_stream(output_file);
        //std::string output_message((std::istreambuf_iterator<char>(output_stream)), std::istreambuf_iterator<char>());
        //output_stream.close();
        //std::cout << output_message << std::endl;
    }
    //std::remove(output_file);
    return false;
}
bool Tesseract::trainModel(std::string lan, std::string font, int iteration, bool clear)
{
    if (train(lan, font, iteration, clear)) {
        font.erase(std::remove_if(font.begin(), font.end(), ::isspace), font.end());
        std::string command = "sudo cp /home/tesseract_repos/tesstrain/data/" + font + "_data/" + font + "-" + lan + "-output/" + font + ".traineddata " + tessdatadir + "/" + font + ".traineddata ";
        std::cout << command << std::endl;
        system(command.c_str());
        return true;
    }
}
bool Tesseract::train(std::string lan, std::string font, int iteration ,bool clear)
{
    if (!generateGT(lan, font)) {
        std::cerr << "Error during GT\n";
        return false;
    }
    //Archivo log para la salida
    const char* output_file = "output.log";
    const char* error_file = "error.log";

    //Cadenas donde si aparecen entonces es un error
    std::string errorIndicators[] = {
        "There is no ground-truth",
        "Failed loading language",
        "Tesseract couldn't load any languages!"
    };
    //Eliminar espacios
    font.erase(std::remove_if(font.begin(), font.end(), ::isspace), font.end());

    std::string command = "sudo " + trainTess + " -l " + lan + " -f \"" + font + "\"" +" -it "+ std::to_string(iteration);
    if (clear)command = command + " -cl";
    //command = command + " > > (tee " + std::string(output_file) + ") 2> > (tee " + std::string(error_file) +" 2>&)";

    //command = command + " > " + std::string(output_file) + " 2> " + std::string(error_file);
    std::cout << command << std::endl;
    int res = system(command.c_str());

    // Leer la salida estándar
    std::ifstream output_stream(output_file);
    std::string output_message((std::istreambuf_iterator<char>(output_stream)), std::istreambuf_iterator<char>());
    output_stream.close();

    // Leer la salida de error
    std::ifstream error_stream(error_file);
    std::string error_message((std::istreambuf_iterator<char>(error_stream)), std::istreambuf_iterator<char>());
    error_stream.close();

    //Se elimina el log temporal y se escribe la salida
    std::remove(output_file);
    std::remove(error_file);
    /*std::cout << output_message << std::endl;
    std::cout << error_message << std::endl;*/

    //Error de fuente
    for (const auto& indicator : errorIndicators) {
        if (output_message.find(indicator) != std::string::npos || error_message.find(indicator) != std::string::npos) {
            return false;
        }
    }
    if (WIFEXITED(res) && WEXITSTATUS(res) == 0) {
        return true;
    }
    else {
        return false;
    }
}
bool Tesseract::generateGT(std::string lan, std::string font)
{
    //Archivo log para la salida
    const char* output_file = "output.log";
    const char* error_file = "error.log";
    
    //Cadenas donde si aparecen entonces es un error
    std::string errorIndicators[] = {
        "Please correct --font arg.",
    };

    //Comando del groundTruth con sudo , los argumentos lan y font , y se recoge la salida estandar de error
    std::string command = "sudo " + groundTruth + " -l " + lan + " -f \" " + font + "\"" + " > " + std::string(output_file) + " 2> " + std::string(error_file);
	int res = system(command.c_str());

    // Leer la salida estándar
    std::ifstream output_stream(output_file);
    std::string output_message((std::istreambuf_iterator<char>(output_stream)), std::istreambuf_iterator<char>());
    output_stream.close();

    // Leer la salida de error
    std::ifstream error_stream(error_file);
    std::string error_message((std::istreambuf_iterator<char>(error_stream)), std::istreambuf_iterator<char>());
    error_stream.close();

    //Se elimina el log temporal y se escribe la salida
    std::remove(output_file);
    std::remove(error_file);
    std::cout << output_message << std::endl;
    std::cout << error_message << std::endl;

    //Error de fuente
    for (const auto& indicator : errorIndicators) {
        if (output_message.find(indicator) != std::string::npos || error_message.find(indicator) != std::string::npos) {
            std::cerr << "Font error" << std::endl;
            return false;
        }
    }
    //Error del sistema o lenguaje no soportado por tesseract
    if (WIFEXITED(res) && WEXITSTATUS(res) == 0) {
        return true;
    }
    else {
        return false;
    }
   
}


