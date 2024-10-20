#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <thread>
#include <numeric>  // dla std::accumulate
#include <windows.h> // do pomiaru zajetej pamieci
#include <psapi.h> // do pomiaru zajetej pamieci
#include "Config.h"
#include "Matrix.h"
#include "NajblizszychSasiadow.h"
#include "PrzegladZupelny.h"
#include "Losowy.h"
using namespace std;
Config config;

// deklaracja macierzy
Matrix matrix;
// Wektor do przechowywania czasów wykonania dla każdej instancji
vector<double> executionTimes;

void printMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memCounter; // struktura do przechowywania danych o zuzyciu pamieci
    GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter)); // ta funkcja pobiera informacje o zuzyciu pamieci dla danego procesu
    // argumenty: process handle, wskaznik na strukture przechowujaca dane o pamieci, rozmiar struktury
    cout << "Pamiec szczytowa (PeakWorkingSetSize): " << memCounter.PeakWorkingSetSize / 1024 << " KB" << endl;
    cout << "Aktualnie zajeta pamiec (WorkingSetSize): " << memCounter.WorkingSetSize / 1024 << " KB" << endl;
}

// funkcja do obliczania zajetej pamieci
void calculateAndDisplayMemoryUsage(const Matrix& matrix, const vector<double>& executionTimes) {
    // Obliczanie pamięci zajętej przez macierz
    size_t matrixMemory = matrix.getSize() * sizeof(int*) + matrix.getSize() * matrix.getSize() * sizeof(int);

    // Obliczanie pamięci dla wektora executionTimes
    size_t executionTimesMemory = executionTimes.capacity() * sizeof(double);

    // Wyświetlanie zajętej pamięci
    cout << "Zajeta pamiec: " << (matrixMemory + executionTimesMemory) << " B ("
         << (matrixMemory + executionTimesMemory) / 1024.0 << " KB)" << endl;
}

void algorithmExecution() {

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
            if (config.matrix_source == "file") {
                cout << "Minimalny koszt = " << minCostP << endl;
            }
        } else if (config.alghoritm_type == "najblizszych") {
            NajblizszychSasiadow tsp_najblizszy(matrix);
            int minCostN = tsp_najblizszy.findShortestPath();
            executionTime = tsp_najblizszy.getExecutionTime();
            executionTimes.push_back(executionTime);
            if (config.matrix_source == "file") {
                cout << "Minimalny koszt = " << minCostN << endl;
            }
        } else if (config.alghoritm_type == "losowy") {
            Losowy tsp_losowy(matrix, config.repetitions, config.instances);
            int minCostL = tsp_losowy.findShortestPath();
            executionTime = tsp_losowy.getExecutionTime();
            executionTimes.push_back(executionTime);
            if (config.matrix_source == "file") {
                cout << "Minimalny koszt = " << minCostL << endl;
            }
        }

    }

    // Tworzenie plików CSV w trybie dopisywania
    ofstream przegladFile("wyniki/przeglad.csv", ios::app);
    ofstream najblizszychFile("wyniki/najblizszych.csv", ios::app);
    ofstream losowyFile("wyniki/losowy.csv", ios::app);

    if (!przegladFile || !najblizszychFile || !losowyFile) {
        cerr << "Nie mozna otworzyć plikow do zapisu wynikow!" << endl;
        //return 1;
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
    // Zamknięcie plików
    przegladFile.close();
    najblizszychFile.close();
    losowyFile.close();

    // Wyświetlanie średniego czasu
    double sumTime = accumulate(executionTimes.begin(), executionTimes.end(), 0.0);
    double avgTime = sumTime / executionTimes.size();
    cout << "Sredni czas wykonania algorytmu: " << avgTime << " ms" << endl;
}

int main() {
    srand(time(0)); // ziarno do funkcji rand

    // wczytaj plik konfiguracyjny
    if (!config.loadConfig("wejscie/plik_konfiguracyjny.txt")) {
        return 1;
    }

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



    algorithmExecution();

    matrix.display();

    //calculateAndDisplayMemoryUsage(matrix, executionTimes);

    // wyswietlenie zajetej pamieci
    printMemoryUsage();

    return 0;
}
