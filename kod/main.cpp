#include <iostream>
#include <chrono>
#include "Config.h"
#include "Matrix.h"
#include "NajblizszychSasiadow.h"
#include "PrzegladZupelny.h"
#include "Losowy.h"
using namespace std;

int main() {
    // wczytaj plik konfoguracyjny
    Config config;
    if (!config.loadConfig("C:\\Users\\werag\\Documents\\clionProjekty\\PEA1\\wejscie\\plik_konfiguracyjny.txt")) {
        return 1;
    }

    // deklaracja macierzy
    Matrix matrix;

    double sumTime = 0.0;

    // wyswietlenie macierzy
    // matrix.display();


    for(int i = 0; i < config.repetitions; i++) {

    // wybieranie sposobu generowania macierzy z pliku lub generowanej losowo
    if (config.matrix_source == "manual") {
        matrix.generateManual(config.matrix_size, config.matrix_type);
    } else if (config.matrix_source == "file" && i == 0) {
        if (!matrix.loadFromFile(config.input_file)) {
            return 1;
        }
    }else if (config.matrix_source == "file" && i != 0) {
        return 1;
    }else {
        cout << "matrix_source wczytano jako: [" << config.matrix_source << "]" << endl;
        cerr << "Niepoprawna wartosc dla matrix_source!" << endl;

        return 1;
    }



        if(config.alghoritm_type == "przeglad") {
            // Tworzenie obiektu PrzegladZupelny i znajdowanie najkrótszej ścieżki
            PrzegladZupelny tsp_przeglad(matrix);
            int minCostP = tsp_przeglad.findShortestPath();
            tsp_przeglad.displayBestPath();

            cout << "Minimalny koszt: " << minCostP << endl;
            sumTime += tsp_przeglad.getExecutionTime();  // Dodajemy czas wykonania do sumy

        }else if(config.alghoritm_type == "najblizszych") {
            // Tworzymy obiekt algorytmu najbliższych sąsiadów
            NajblizszychSasiadow tsp_najblizszy(matrix);

            // Znajdujemy najkrótszą ścieżkę
            int minCostN = tsp_najblizszy.findShortestPath();
            if (minCostN != -1) {
                tsp_najblizszy.displayBestPath();  // Wyświetlamy wynik
            }
            sumTime += tsp_najblizszy.getExecutionTime();  // Dodajemy czas wykonania do sumy

        }else if(config.alghoritm_type == "losowy") {
            // Tworzenie obiektu algorytmu losowego
            Losowy tsp_losowy(matrix, config.repetitions, config.instances);

            // Znalezienie najkrótszej ścieżki
            int minCostL = tsp_losowy.findShortestPath();
            if (minCostL != -1) {
                tsp_losowy.displayBestPath();  // Wyświetlamy wynik
            }
            sumTime += tsp_losowy.getExecutionTime();  // Dodajemy czas wykonania do sumy

        }
    }

    double avgTime = sumTime / config.repetitions;  // Obliczamy średnią
    cout << "Sredni czas wykonania algorytmu: " << avgTime << "us" << endl;
    // Wyniki można zapisywać do pliku w kolejnych krokach




    return 0;
}
