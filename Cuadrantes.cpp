#include <cmath>
#include <iostream>
#include <vector>
#include "Cuadrantes.h"

using namespace std;

void Cuadrantes::insert(Node* node){
	if (node == NULL)
		return;

	//Si el punto que se quiere insertar no está dentro de los limites, termina el método
	if (!inBoundary(node->pos))
		return;

	//En revisa si estamos en un cuadrante que ya no se puede subdividir más, si es el caso, entra al if
	if (abs(topLeft.x - botRight.x) <= 1 && abs(topLeft.y - botRight.y) <= 1) {
		if (n == NULL)
			n = node;
		return;
	}
	//En estos if, chequea por que hijo se debe ir, y llama de nuevo a la función pero en el cuadrante correspondiente.
	if ((topLeft.x + botRight.x) / 2 >= node->pos.x) {
		// Indicates topLeftTree
		if ((topLeft.y + botRight.y) / 2 >= node->pos.y) {
			if (topLeftTree == NULL)
				topLeftTree = new Cuadrantes(Point(topLeft.x, topLeft.y),Point((topLeft.x + botRight.x) / 2,(topLeft.y + botRight.y) / 2));
			topLeftTree->insert(node);
		}

		// Indicates botLeftTree
		else {
			if (botLeftTree == NULL)
				botLeftTree = new Cuadrantes(Point(topLeft.x,(topLeft.y + botRight.y) / 2),Point((topLeft.x + botRight.x) / 2,botRight.y));
			botLeftTree->insert(node);
		}
	}
	else {
		// Indicates topRightTree
		if ((topLeft.y + botRight.y) / 2 >= node->pos.y) {
			if (topRightTree == NULL)
				topRightTree = new Cuadrantes(Point((topLeft.x + botRight.x) / 2,topLeft.y),Point(botRight.x,(topLeft.y + botRight.y) / 2));
			topRightTree->insert(node);
		}

		// Indicates botRightTree
		else {
			if (botRightTree == NULL)
				botRightTree = new Cuadrantes(Point((topLeft.x + botRight.x) / 2,(topLeft.y + botRight.y) / 2),Point(botRight.x, botRight.y));
			botRightTree->insert(node);
		}
	}
}

Node* Cuadrantes::search(Point p){
	// Current quad cannot contain it
	if (!inBoundary(p))
		return NULL;

	// We are at a quad of unit length
	// We cannot subdivide this quad further
	if (n != NULL)
		return n;

	if ((topLeft.x + botRight.x) / 2 >= p.x) {
		// Indicates topLeftTree
		if ((topLeft.y + botRight.y) / 2 >= p.y) {
			if (topLeftTree == NULL)
				return NULL;
			return topLeftTree->search(p);
		}

		// Indicates botLeftTree
		else {
			if (botLeftTree == NULL)
				return NULL;
			return botLeftTree->search(p);
		}
	}
	else {
		// Indicates topRightTree
		if ((topLeft.y + botRight.y) / 2 >= p.y) {
			if (topRightTree == NULL)
				return NULL;
			return topRightTree->search(p);
		}

		// Indicates botRightTree
		else {
			if (botRightTree == NULL)
				return NULL;
			return botRightTree->search(p);
		}
	}
}
bool Cuadrantes::inBoundary(Point p){
	return (p.x >= topLeft.x && p.x <= botRight.x
			&& p.y >= topLeft.y && p.y <= botRight.y);
}

Cuadrantes::Cuadrantes(){
	topLeft = Point(0, 0);
	botRight = Point(0, 0);
	n = NULL;
	topLeftTree = NULL;
	topRightTree = NULL;
	botLeftTree = NULL;
	botRightTree = NULL;
}

Cuadrantes::Cuadrantes(Point topL, Point botR){
	n = NULL;
	topLeftTree = NULL;
	topRightTree = NULL;
	botLeftTree = NULL;
	botRightTree = NULL;
	topLeft = topL;
	botRight = botR;
}

int Cuadrantes::totalPoints(){

}

int Cuadrantes::totalNodes(){

}

int Cuadrantes::countRegion(Point p, int d){
    if(!inBoundary(p)){
        return 0;
	}
    
    // Si la distancia entre los límites del cuadrante es menor o igual a d,
    // todos los puntos en ese cuadrante están dentro de la región
    if(abs(topLeft.x - botRight.x) <= d && abs(topLeft.y - botRight.y) <= d){
        // Si hay un nodo en este cuadrante, devuelve 1
        if(n != NULL){
            return 1;
		}else{
            return 0;
		}
	}
    int count = 0;
    // Recorre los cuadrantes hijo y llama a la función de forma recursiva
    if(topLeftTree != NULL){
        count += topLeftTree->countRegion(p, d);
	}
    if(topRightTree != NULL){
        count += topRightTree->countRegion(p, d);
	}
    if(botLeftTree != NULL){
        count += botLeftTree->countRegion(p, d);
	}
    if(botRightTree != NULL){
        count += botRightTree->countRegion(p, d);
	}
    return count;
}

int Cuadrantes::AggregateRegion(Point p, int d){

}
vector <Point> Cuadrantes::list(){

}