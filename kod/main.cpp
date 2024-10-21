// Weronika Gut 273003
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <thread>
#include <numeric>  // dla accumulate
#include <windows.h> // do pomiaru zajetej pamieci
#include <psapi.h> // do pomiaru zajetej pamieci
#include "Config.h"
#include "Matrix.h"
#include "NajblizszychSasiadow.h"
#include "PrzegladZupelny.h"
#include "Losowy.h"
using namespace std;

// obiekt config do przechowywania ustawien z pliku konfiguracyjnego
Config config;
// deklaracja macierzy
Matrix matrix;
// wektor do przechowywania czasów
vector<double> executionTimes;

void printMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memCounter; // struktura do przechowywania danych o zuzyciu pamieci
    GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter)); // ta funkcja pobiera informacje o zuzyciu pamieci dla danego procesu
    // argumenty: process handle, wskaznik na strukture przechowujaca dane o pamieci, rozmiar struktury
    cout << "Aktualnie zajeta pamiec: " << memCounter.WorkingSetSize / 1024 << " KB" << endl;
}

// wykonywanie algorytmu i zapis czasow do plikow
void algorithmExecution() {

    for (int i = 0; i < config.repetitions; i++) {

        // wskaznik postepu
        if (config.progress_indicator) {
            int progress = (i + 1) * 100 / config.repetitions;  // obliczenie procentu ukonczenia
            cout << "Postep: " << progress << "% (" << i + 1 << "/" << config.repetitions << ")\r";
            cout.flush();  // odswiezenie

        }

        // opoznienie, zeby zdazyl wyswietlic sie postep
        this_thread::sleep_for(chrono::milliseconds(300));

        double executionTime = 0.0;
        int minCost = -1;

        if (config.alghoritm_type == "przeglad") {
            PrzegladZupelny przeglad(matrix);
            minCost = przeglad.findShortestPath();
            executionTime = przeglad.getExecutionTime();
            executionTimes.push_back(executionTime);

        } else if (config.alghoritm_type == "najblizszych") {
            NajblizszychSasiadow tsp_najblizszy(matrix);
            minCost = tsp_najblizszy.findShortestPath();
            executionTime = tsp_najblizszy.getExecutionTime();
            executionTimes.push_back(executionTime);

        } else if (config.alghoritm_type == "losowy") {
            Losowy tsp_losowy(matrix, config.instances);
            minCost = tsp_losowy.findShortestPath();
            executionTime = tsp_losowy.getExecutionTime();
            executionTimes.push_back(executionTime);

        }

        // wyswietla koszt jesli jest to zaznaczone w pliku konfiguracyjnym
        if (config.display_cost && minCost != -1) {
            cout << "Minimalny koszt = " << minCost << endl;
        }

    }

    // otworzenie plikow w trybie dopisywania
    ofstream przegladFile("wyniki/przeglad.csv", ios::app);
    ofstream najblizszychFile("wyniki/najblizszych.csv", ios::app);
    ofstream losowyFile("wyniki/losowy.csv", ios::app);


    // zapisanie wynikow
    if (config.alghoritm_type == "przeglad") {
        przegladFile << matrix.getSize() << endl; // zapisujemy rozmiar
        for (double time : executionTimes) {
            przegladFile << time << " ";  // zapisujemy czasy oddzielone spacja
        }
        przegladFile << endl;

    } else if (config.alghoritm_type == "najblizszych") {
        najblizszychFile << matrix.getSize() << endl;
        for (double time : executionTimes) {
            najblizszychFile << time << " ";
        }
        najblizszychFile << endl;

    } else if (config.alghoritm_type == "losowy") {
        losowyFile << matrix.getSize() << endl;
        for (double time : executionTimes) {
            losowyFile << time << " ";
        }
        losowyFile << endl;
    }

    // zamkniecie plikow
    przegladFile.close();
    najblizszychFile.close();
    losowyFile.close();

    //sredni czas
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

    // tworzenie macierzy z pliku lub generowanie jej manualnie
    if (config.matrix_source == "file") {
        if (!matrix.loadFromFile(config.input_file)) {
            return 1;
        }
    } else if (config.matrix_source == "manual") {
        matrix.generateManual(config.matrix_size, config.matrix_type);
    }

    // wyswietlenie rozmiaru macierzy
    cout << "Rozmiar macierzy: " << matrix.getSize() << "x" << matrix.getSize() << endl;

    // wywolanie wykonania algorytmu
    algorithmExecution();

    // wyswietlenie zajetej pamieci
    printMemoryUsage();

    return 0;
}
