#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <numeric>  // dla std::accumulate
#include "Config.h"
#include "Matrix.h"
#include "NajblizszychSasiadow.h"
#include "PrzegladZupelny.h"
#include "Losowy.h"
using namespace std;

int main() {
    srand(time(0));

    // wczytaj plik konfiguracyjny
    Config config;
    if (!config.loadConfig("wejscie/plik_konfiguracyjny.txt")) {
        return 1;
    }

    // deklaracja macierzy
    Matrix matrix;

    // Wektor do przechowywania czasów wykonania dla każdej instancji
    vector<double> executionTimes;

    // Jeśli źródłem jest plik, rozmiar macierzy zostanie wczytany z pliku, nie z pliku konfiguracyjnego
    if (config.matrix_source == "file") {
        if (!matrix.loadFromFile(config.input_file)) {
            return 1;
        }
    } else if (config.matrix_source == "manual") {
        matrix.generateManual(config.matrix_size, config.matrix_type);  // Dla manualnych danych
    }

    // Tworzenie plików CSV w trybie dopisywania
    ofstream przegladFile("wyniki/przeglad.csv", ios::app);
    ofstream najblizszychFile("wyniki/najblizszych.csv", ios::app);
    ofstream losowyFile("wyniki/losowy.csv", ios::app);

    // Sprawdzenie, czy pliki CSV zostały poprawnie otwarte
    if (!przegladFile || !najblizszychFile || !losowyFile) {
        cerr << "Nie można otworzyć plików do zapisu wyników!" << endl;
        return 1;
    }

    for (int i = 0; i < config.repetitions; i++) {
        // Wybór algorytmu
        double executionTime = 0.0;
        if (config.alghoritm_type == "przeglad") {
            PrzegladZupelny przeglad(matrix);
            int minCostP = przeglad.findShortestPath();
            executionTime = przeglad.getExecutionTime();
            executionTimes.push_back(executionTime);  // Dodanie czasu do wektora

        } else if (config.alghoritm_type == "najblizszych") {
            NajblizszychSasiadow tsp_najblizszy(matrix);
            int minCostN = tsp_najblizszy.findShortestPath();
            executionTime = tsp_najblizszy.getExecutionTime();
            executionTimes.push_back(executionTime);  // Dodanie czasu do wektora

        } else if (config.alghoritm_type == "losowy") {
            Losowy tsp_losowy(matrix, config.repetitions, config.instances);
            int minCostL = tsp_losowy.findShortestPath();
            executionTime = tsp_losowy.getExecutionTime();
            executionTimes.push_back(executionTime);  // Dodanie czasu do wektora
        }
    }

    // Zapisanie wyników do odpowiednich plików na podstawie algorytmu
    if (config.alghoritm_type == "przeglad") {
        przegladFile << matrix.getSize() << endl;  // Używamy rozmiaru macierzy wczytanego z pliku
        for (double time : executionTimes) {
            przegladFile << time << " ";  // Zapisujemy czasy oddzielone spacją
        }
        przegladFile << endl;  // Nowa linia po zapisaniu czasów

    } else if (config.alghoritm_type == "najblizszych") {
        najblizszychFile << matrix.getSize() << endl;  // Używamy rozmiaru macierzy wczytanego z pliku
        for (double time : executionTimes) {
            najblizszychFile << time << " ";  // Zapisujemy czasy oddzielone spacją
        }
        najblizszychFile << endl;  // Nowa linia po zapisaniu czasów

    } else if (config.alghoritm_type == "losowy") {
        losowyFile << matrix.getSize() << endl;  // Używamy rozmiaru macierzy wczytanego z pliku
        for (double time : executionTimes) {
            losowyFile << time << " ";  // Zapisujemy czasy oddzielone spacją
        }
        losowyFile << endl;  // Nowa linia po zapisaniu czasów
    }

    // Obliczanie średniej z czasów wykonania
    double sumTime = accumulate(executionTimes.begin(), executionTimes.end(), 0.0);
    double avgTime = sumTime / executionTimes.size();  // Obliczamy średnią

    // Wyświetlanie średniego czasu w terminalu
    cout << "Sredni czas wykonania algorytmu: " << avgTime << " us" << endl;

    // Zamknięcie plików
    przegladFile.close();
    najblizszychFile.close();
    losowyFile.close();

    return 0;
}
