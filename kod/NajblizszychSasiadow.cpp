
#include "NajblizszychSasiadow.h"
#include <iostream>
#include <limits>
#include <chrono>
using namespace std;

// konstruktor inicjalizujacy referencje do obiektu macierzy kosztow
// pobiera rozmiar i ustawia minimalny koszt na maksymalna liczbe
NajblizszychSasiadow::NajblizszychSasiadow(const Matrix& m) : matrix(m), size(m.getSize()), minCost(numeric_limits<int>::max()) {}

// metoda obliczenia najkrotszej sciezki
int NajblizszychSasiadow::findShortestPath() {
    bestPath.clear(); // wyczyszczenie poprzednich danych
    vector<int> visited(size, 0);  // wektor odwiedzonych wierzcholkow (0 - nieodwiedzone, 1 - odwiedzone)
    // poczatkowo wszystkie wierzcholki nieodwiedzone

    // poczatek pomiaru czasu
    auto start = chrono::high_resolution_clock::now();

    int currentVertex = rand() % size; // losowy wierzcholek startowy
    visited[currentVertex] = 1; // pierwszy wierzcholek oznaczony jako odwiedzony
    bestPath.push_back(currentVertex); // zapisuje do sciezki pierwszy wierzcholek
    minCost = 0;


    // wybieramy najblizszy nieodwiedzony wierzcholek
    for (int i = 1; i < size; ++i) {
        int nearestVertex = -1; // indeks najblizszego nieodwiedzonego wierzcholka
        int nearestCost = numeric_limits<int>::max(); // poczatkowo ustawiamy odleglosc na najwieksza mozliwa liczba

        //szukamy najblizszyego nieodwiedzonego wierzcholka
        for (int j = 0; j < size; ++j) {
            if (!visited[j]) { // jesli wierzcholek nieodwiedzony
                int cost = matrix.getCost(currentVertex, j);
                if (cost != -1 && cost < nearestCost) { // jesli ma majmniejszy koszt
                    nearestVertex = j;
                    nearestCost = cost;
                }
            }
        }

        // odwiedzenie najblizszego wierzcholka
        if (nearestVertex != -1) {
            visited[nearestVertex] = 1; // wierzcholek odwiedzony
            bestPath.push_back(nearestVertex); // wierzcholek dodajemy do sciezki
            minCost += nearestCost; // dodaj koszt wieszcholka do calkowitego kosztu
            currentVertex = nearestVertex; // przechodzimy do kolejnego wierzcholka
        } else {
            cerr << "Blad: Nie znaleziono polaczenia." << endl;
            return -1;
        }
    }

    //powrot do pierwszego miasta
    int returnCost = matrix.getCost(currentVertex, bestPath[0]); // koszt z ostatniego do pierwszego wierzcholka
    if (returnCost != -1) {
        minCost += returnCost;
        bestPath.push_back(bestPath[0]); // dodaj pierwsze miasto na koniec listy
    } else {
        cerr << "Blad: Brak polaczenia powrotnego do miasta startowego." << endl;
        return -1;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    //cout << "Czas wykonania wybranego fragmentu: " << duration.count() << " ms" << endl;

    // zapisz czas wykonania
    executionTime = duration.count();

    return minCost;
}

// zwraca czas wykonania algorytmu
double NajblizszychSasiadow::getExecutionTime() const {
    return executionTime;
}

// wyswietlenie najkrotszej sciezki (funkcja pomocnicza)
void NajblizszychSasiadow::displayBestPath() const {
    cout << "Najkrotsza sciezka (algorytm najblizszych sasiadow): ";
    for (int city : bestPath) {
        cout << city << " ";
    }
    cout << endl;
    cout << "Koszt: " << minCost << endl;
}
