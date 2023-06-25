#include <cmath>
#include <iostream>
#include <vector>
#include "Cuadrantes.h"
#include <fstream>
#include <sstream>
#include <chrono> // Para medir el tiempo de ejecución
#include <iomanip> // Para imprimir los tiempos con decimales

using namespace std;
using namespace std::chrono;

int main() {
    const int numIterations = 20;
    double totalTime = 0.0;
    
    for (int iteration = 0; iteration < numIterations; iteration++) {
        // Reiniciar el QuadTree para cada iteración
        Cuadrantes quadTree;
        
        // Leer el dataset desde un archivo
        ifstream inputFile("worldcitiespop_fixed.txt");
        if (!inputFile) {
            cout << "Error al abrir el archivo." << endl;
            return 1;
        }
        
        string line;
        int lineCount = 0;
        const int maxLines = 100;
        while (getline(inputFile, line) && lineCount < maxLines) {
            // Separar los valores de cada línea por punto y coma
            istringstream iss(line);
            string country, city, accentCity, region, populationStr, latitudeStr, longitudeStr, geopointStr;
            getline(iss, country, ';');
            getline(iss, city, ';');
            getline(iss, accentCity, ';');
            getline(iss, region, ';');
            getline(iss, populationStr, ';');
            getline(iss, latitudeStr, ';');
            getline(iss, longitudeStr, ';');
            getline(iss, geopointStr, ';');
            
            // Convertir las cadenas a los tipos de datos apropiados
            int population = stoi(populationStr);
            float latitude = stof(latitudeStr);
            float longitude = stof(longitudeStr);
            
            // Redondear las coordenadas a 3 decimales
            latitude = round(latitude * 1000) / 1000.0f;
            longitude = round(longitude * 1000) / 1000.0f;
            
            // Crear un nuevo nodo y medir el tiempo de ejecución de la inserción en el QuadTree
            Point point(latitude, longitude);
            Node* newNode = new Node(point, population);
            
            // Medir el tiempo de ejecución del método insert
            double duracion = 0.0;
            auto start = high_resolution_clock::now();
            
            quadTree.insert(newNode);
            
            auto end = high_resolution_clock::now();
            
            // Calcular el tiempo transcurrido en milisegundos
            duration<double> diff = end - start;
            duracion = diff.count();
            totalTime += duracion;
            
            lineCount++;
        }
        
        inputFile.close();
        
        // Realizar otras operaciones con el QuadTree si es necesario
        
        cout << "Tiempo de ejecución de la iteración " << iteration + 1 << ": " << fixed << setprecision(20) << totalTime << " ms" << endl;
        
        // Reiniciar el tiempo para la siguiente iteración
        totalTime = 0.0;
    }
    
    // Calcular el tiempo promedio
    double averageTime = totalTime / numIterations;
    cout << "Tiempo promedio de ejecución: " << fixed << setprecision(8) << averageTime << " ms" << endl;
    
    return 0;
}
