#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <thread>
#include <numeric>  // dla std::accumulate
#include "Config.h"
#include "Matrix.h"
#include "NajblizszychSasiadow.h"
#include "PrzegladZupelny.h"
#include "Losowy.h"
using namespace std;

// Funkcja oblicza i wyświetla zajętą pamięć przez macierz i wektor executionTimes
void calculateAndDisplayMemoryUsage(const Matrix& matrix, const vector<double>& executionTimes) {
    // Obliczanie pamięci zajętej przez macierz
    size_t matrixMemory = matrix.getSize() * sizeof(int*) + matrix.getSize() * matrix.getSize() * sizeof(int);

    // Obliczanie pamięci dla wektora executionTimes
    size_t executionTimesMemory = executionTimes.capacity() * sizeof(double);

    // Wyświetlanie zajętej pamięci
    cout << "Zajeta pamiec: " << (matrixMemory + executionTimesMemory) << " B ("
         << (matrixMemory + executionTimesMemory) / 1024.0 << " KB)" << endl;
}

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

    // Jeśli źródłem jest plik, rozmiar macierzy zostanie wczytany z pliku
    if (config.matrix_source == "file") {
        if (!matrix.loadFromFile(config.input_file)) {
            return 1;
        }
    } else if (config.matrix_source == "manual") {
        matrix.generateManual(config.matrix_size, config.matrix_type);
    }

    // Wyświetlanie rozmiaru macierzy na początku
    cout << "Rozmiar macierzy: " << matrix.getSize() << "x" << matrix.getSize() << endl;


    // Tworzenie plików CSV w trybie dopisywania
    ofstream przegladFile("wyniki/przeglad.csv", ios::app);
    ofstream najblizszychFile("wyniki/najblizszych.csv", ios::app);
    ofstream losowyFile("wyniki/losowy.csv", ios::app);

    if (!przegladFile || !najblizszychFile || !losowyFile) {
        cerr << "Nie mozna otworzyć plikow do zapisu wynikow!" << endl;
        return 1;
    }

    for (int i = 0; i < config.repetitions; i++) {

        // Wyświetlanie wskaźnika postępu, jeśli progress_indicator = 1
        if (config.progress_indicator) {
            int progress = (i + 1) * 100 / config.repetitions;  // Obliczanie procentu ukończenia
            cout << "Postep: " << progress << "% (" << i + 1 << "/" << config.repetitions << ")\r";  // Wskaźnik postępu
            cout.flush();  // Odświeżenie wyświetlania postępu
        }
        // Sztuczne opóźnienie dla celów testowych (np. 100 ms)
        this_thread::sleep_for(chrono::milliseconds(100));

        // Wykonaj algorytm...
        double executionTime = 0.0;
        if (config.alghoritm_type == "przeglad") {
            PrzegladZupelny przeglad(matrix);
            int minCostP = przeglad.findShortestPath();
            executionTime = przeglad.getExecutionTime();
            executionTimes.push_back(executionTime);
        } else if (config.alghoritm_type == "najblizszych") {
            NajblizszychSasiadow tsp_najblizszy(matrix);
            int minCostN = tsp_najblizszy.findShortestPath();
            executionTime = tsp_najblizszy.getExecutionTime();
            executionTimes.push_back(executionTime);
        } else if (config.alghoritm_type == "losowy") {
            Losowy tsp_losowy(matrix, config.repetitions, config.instances);
            int minCostL = tsp_losowy.findShortestPath();
            executionTime = tsp_losowy.getExecutionTime();
            executionTimes.push_back(executionTime);
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


    // Wyświetlanie średniego czasu
    double sumTime = accumulate(executionTimes.begin(), executionTimes.end(), 0.0);
    double avgTime = sumTime / executionTimes.size();
    cout << "Sredni czas wykonania algorytmu: " << avgTime << " ms" << endl;

    // Zamknięcie plików
    przegladFile.close();
    najblizszychFile.close();
    losowyFile.close();

    // Wywołanie funkcji do obliczania i wyświetlania zajętej pamięci
    calculateAndDisplayMemoryUsage(matrix, executionTimes);
    return 0;
}
