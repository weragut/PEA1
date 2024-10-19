#include "Config.h"
#include <iostream>
#include <fstream>
using namespace std;

bool Config::loadConfig(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku konfiguracyjnego: " << filename << std::endl;
        return false;
    }

    string key;
    while (file >> key) { // odczytywanie kluczy, w kazdej iteracji jest odczytywany nowy klucz
        if (key == "matrix_source") { // sprawdzenie klucza i przypisanie wartosci
            file >> matrix_source;
        } else if (key == "progress_indicator") {
            file >> progress_indicator;
        } else if (key == "repetitions") {
            file >> repetitions;
        } else if (key == "instances") {
            file >> instances;
        } else if (key == "input_file") {
            file >> input_file;
        } else if (key == "matrix_size") {
            file >> matrix_size;
        } else if (key == "matrix_type") {
            file >> matrix_type;
        }else if (key == "alghoritm_type") {
            file >> alghoritm_type;
        }
    }

    file.close();
    return true;
}
