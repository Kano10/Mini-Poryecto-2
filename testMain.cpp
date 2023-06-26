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

void ajustarCoordenadas(float& latitud, float& longitud){
    latitud = latitud + 90;
    longitud = longitud + 180;
}

int main() {
    const int numIterations = 20;
    double totalTime = 0.0;
    double averageTime = 0.0;
    
    ofstream archivo("resultados3MInsert.txt");

    for (int iteration = 0; iteration < numIterations; iteration++) {
        // Reiniciar el QuadTree para cada iteración
        Cuadrantes* quadTree = new Cuadrantes(Point(0.0,0.0), Point(360.0,180.0));
        
        // Leer el dataset desde un archivo
        ifstream inputFile("worldcitiespop_fixed.txt");
        
        string line;
        int lineCount = 0;
        const int maxLines = 3000000;
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

            ajustarCoordenadas(latitude,longitude);
            
            // Redondear las coordenadas a 3 decimales
            latitude = round(latitude * 100000) / 100000.0f;
            longitude = round(longitude * 100000) / 100000.0f;
            
            // Crear un nuevo nodo y medir el tiempo de ejecución de la inserción en el QuadTree
            Point point(latitude, longitude);
            Node* newNode = new Node(point, population);
            
            // Medir el tiempo de ejecución del método insert
            double duracion = 0.0;
            auto start = high_resolution_clock::now();
            
            quadTree->insert(newNode);
            
            auto end = high_resolution_clock::now();
            
            // Calcular el tiempo transcurrido en milisegundos
            duration<double> diff = end - start;
            duracion = diff.count();
            totalTime += duracion;
            
            lineCount++;
        }
        
        inputFile.close();

        archivo<< fixed << setprecision(8) << totalTime << '\n';
        
        averageTime += totalTime;
        totalTime = 0.0;
        delete quadTree;
    }
    
    // Calcular el tiempo promedio
    averageTime = averageTime/numIterations;
    archivo << fixed << setprecision(8) << averageTime <<'\n';

//COUNT Y AGGERGATE REGION

    Cuadrantes* quadTree = new Cuadrantes(Point(0,0), Point(360,180));
    
    // Leer el dataset desde un archivo
    ifstream inputFile("worldcitiespop_fixed.txt");
        
    string line;
    int lineCount = 0;
    const int maxLines = 3000000;
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

        ajustarCoordenadas(latitude,longitude);
            
        // Redondear las coordenadas a 3 decimales
        latitude = round(latitude * 100000) / 100000.0f;
        longitude = round(longitude * 100000) / 100000.0f;
            
        // Crear un nuevo nodo y medir el tiempo de ejecución de la inserción en el QuadTree
        Point point(latitude, longitude);
        Node* newNode = new Node(point, population);
            
        quadTree->insert(newNode);
        lineCount++;
    }

    // REGION 2X2


    double averageTime2 = 0.0;
    double duracion2 = 0.0;
    
    ofstream archivo2("resultados3MCount2x2.txt");
    for (int i = 0; i < numIterations; ++i)
        {
             
        auto start2 = high_resolution_clock::now(); 

        int a = quadTree->countRegion(Point(90,180), 2);

        auto end2 = high_resolution_clock::now();
        duration<double> diff2 = end2 - start2;
        duracion2 = diff2.count();
        archivo2 << fixed << setprecision(8) << duracion2 << '\n';
        averageTime2+= duracion2;
        duracion2 = 0.0;
    }
    averageTime2 = averageTime2/numIterations;
    archivo2 << fixed << setprecision(8) << averageTime2 << '\n';

    averageTime2 = 0.0;
    duracion2 = 0.0;
    
    ofstream archivo3("resultados3MAggregate2x2.txt");
    for (int i = 0; i < numIterations; ++i)
        {
             
        auto start2 = high_resolution_clock::now(); 

        int a = quadTree->countRegion(Point(90,180), 2);

        auto end2 = high_resolution_clock::now();
        duration<double> diff2 = end2 - start2;
        duracion2 = diff2.count();
        archivo3 << fixed << setprecision(8) << duracion2 << '\n';
        averageTime2+= duracion2;
        duracion2 = 0.0;
    }
    averageTime2 = averageTime2/numIterations;
    archivo3 << fixed << setprecision(8) << averageTime2 << '\n';


    //REGION 30X30

    averageTime2 = 0.0;
    duracion2 = 0.0;
    
    ofstream archivo4("resultados3MCount30x30.txt");
    for (int i = 0; i < numIterations; ++i)
        {
             
        auto start2 = high_resolution_clock::now(); 

        int a = quadTree->countRegion(Point(90,180), 15);

        auto end2 = high_resolution_clock::now();
        duration<double> diff2 = end2 - start2;
        duracion2 = diff2.count();
        archivo4 << fixed << setprecision(8) << duracion2 << '\n';
        averageTime2+= duracion2;
        duracion2 = 0.0;
    }
    averageTime2 = averageTime2/numIterations;
    archivo4 << fixed << setprecision(8) << averageTime2 << '\n';

    averageTime2 = 0.0;
    duracion2 = 0.0;
    
    ofstream archivo5("resultados3MAggregate30x30.txt");
    for (int i = 0; i < numIterations; ++i)
        {
             
        auto start2 = high_resolution_clock::now(); 

        int a = quadTree->countRegion(Point(90,180), 15);

        auto end2 = high_resolution_clock::now();
        duration<double> diff2 = end2 - start2;
        duracion2 = diff2.count();
        archivo5 << fixed << setprecision(8) << duracion2 << '\n';
        averageTime2+= duracion2;
        duracion2 = 0.0;
    }
    averageTime2 = averageTime2/numIterations;
    archivo5 << fixed << setprecision(8) << averageTime2 << '\n';

    //REGION 100X100

    averageTime2 = 0.0;
    duracion2 = 0.0;
    
    ofstream archivo6("resultados3MCount100x100.txt");
    for (int i = 0; i < numIterations; ++i)
        {
             
        auto start2 = high_resolution_clock::now(); 

        int a = quadTree->countRegion(Point(90,180), 50);

        auto end2 = high_resolution_clock::now();
        duration<double> diff2 = end2 - start2;
        duracion2 = diff2.count();
        archivo6 << fixed << setprecision(8) << duracion2 << '\n';
        averageTime2+= duracion2;
        duracion2 = 0.0;
    }
    averageTime2 = averageTime2/numIterations;
    archivo6 << fixed << setprecision(8) << averageTime2 << '\n';

    averageTime2 = 0.0;
    duracion2 = 0.0;
    
    ofstream archivo7("resultados3MAggregate100x100.txt");
    for (int i = 0; i < numIterations; ++i)
        {
             
        auto start2 = high_resolution_clock::now(); 

        int a = quadTree->countRegion(Point(90,180), 50);

        auto end2 = high_resolution_clock::now();
        duration<double> diff2 = end2 - start2;
        duracion2 = diff2.count();
        archivo7 << fixed << setprecision(8) << duracion2 << '\n';
        averageTime2+= duracion2;
        duracion2 = 0.0;
    }
    averageTime2 = averageTime2/numIterations;
    archivo7 << fixed << setprecision(8) << averageTime2 << '\n';

    //REGION 200x180

    averageTime2 = 0.0;
    duracion2 = 0.0;
    
    ofstream archivo8("resultados3MCount200x180.txt");
    for (int i = 0; i < numIterations; ++i)
        {
             
        auto start2 = high_resolution_clock::now(); 

        int a = quadTree->countRegion(Point(90,180), 100);

        auto end2 = high_resolution_clock::now();
        duration<double> diff2 = end2 - start2;
        duracion2 = diff2.count();
        archivo8 << fixed << setprecision(8) << duracion2 << '\n';
        averageTime2+= duracion2;
        duracion2 = 0.0;
    }
    averageTime2 = averageTime2/numIterations;
    archivo8 << fixed << setprecision(8) << averageTime2 << '\n';

    averageTime2 = 0.0;
    duracion2 = 0.0;
    
    ofstream archivo9("resultados3MAggregate200x180.txt");
    for (int i = 0; i < numIterations; ++i)
        {
             
        auto start2 = high_resolution_clock::now(); 

        int a = quadTree->countRegion(Point(90,180), 100);

        auto end2 = high_resolution_clock::now();
        duration<double> diff2 = end2 - start2;
        duracion2 = diff2.count();
        archivo9 << fixed << setprecision(8) << duracion2 << '\n';
        averageTime2+= duracion2;
        duracion2 = 0.0;
    }
    averageTime2 = averageTime2/numIterations;
    archivo9 << fixed << setprecision(8) << averageTime2 << '\n';

    //REGION COMPLETA

    averageTime2 = 0.0;
    duracion2 = 0.0;
    
    ofstream archivo10("resultados3MCountCompleta.txt");
    for (int i = 0; i < numIterations; ++i)
        {
             
        auto start2 = high_resolution_clock::now(); 

        int a = quadTree->countRegion(Point(90,180), 100);

        auto end2 = high_resolution_clock::now();
        duration<double> diff2 = end2 - start2;
        duracion2 = diff2.count();
        archivo10 << fixed << setprecision(8) << duracion2 << '\n';
        averageTime2+= duracion2;
        duracion2 = 0.0;
    }
    averageTime2 = averageTime2/numIterations;
    archivo10 << fixed << setprecision(8) << averageTime2 << '\n';

    averageTime2 = 0.0;
    duracion2 = 0.0;
    
    ofstream archivo11("resultados3MAggregateCompleta.txt");
    for (int i = 0; i < numIterations; ++i)
        {
             
        auto start2 = high_resolution_clock::now(); 

        int a = quadTree->countRegion(Point(90,180), 100);

        auto end2 = high_resolution_clock::now();
        duration<double> diff2 = end2 - start2;
        duracion2 = diff2.count();
        archivo11 << fixed << setprecision(8) << duracion2 << '\n';
        averageTime2+= duracion2;
        duracion2 = 0.0;
    }
    averageTime2 = averageTime2/numIterations;
    archivo11 << fixed << setprecision(8) << averageTime2 << '\n';


    int b = quadTree->totalPoints();
    cout<<b<<endl;
    return 0;
}
