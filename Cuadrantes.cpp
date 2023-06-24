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
	if ((topLeft.x + botRight.x) / 2 > node->pos.x) {
		// Indicates topLeftTree
		if ((topLeft.y + botRight.y) / 2 > node->pos.y) {
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
		if ((topLeft.y + botRight.y) / 2 > node->pos.y) {
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

	if ((topLeft.x + botRight.x) / 2 > p.x) {
		// Indicates topLeftTree
		if ((topLeft.y + botRight.y) / 2 > p.y) {
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
		if ((topLeft.y + botRight.y) / 2 > p.y) {
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

int Cuadrantes::totalPoints() {
    if (n != nullptr) {
        // Si el nodo actual contiene un punto, se cuenta como 1
        return 1;
    } else {
        // Si el nodo actual no contiene un punto, se suma la cantidad de puntos en los nodos hijos recursivamente
        int totalCount = 0;
        if (topLeftTree != nullptr)
            totalCount += topLeftTree->totalPoints();
        if (topRightTree != nullptr)
            totalCount += topRightTree->totalPoints();
        if (botLeftTree != nullptr)
            totalCount += botLeftTree->totalPoints();
        if (botRightTree != nullptr)
            totalCount += botRightTree->totalPoints();

        return totalCount;
    }
}

int Cuadrantes::totalNodes() {
    int count = 1;  // Contador para el nodo actual

    // Sumar la cantidad de nodos en los nodos hijos recursivamente
    if (topLeftTree != nullptr)
        count += topLeftTree->totalNodes();
    if (topRightTree != nullptr)
        count += topRightTree->totalNodes();
    if (botLeftTree != nullptr)
        count += botLeftTree->totalNodes();
    if (botRightTree != nullptr)
        count += botRightTree->totalNodes();

    return count;
}

//https://github.com/jrd730/QuadTree/blob/master/QuadTree.cpp
//linea 207
int Cuadrantes::countRegion(Point p, int d){
	int cont = 0;

	if(n != NULL){
		if((n->pos.x >= abs(p.x - d)) && (n->pos.x <= p.x + d) && (n->pos.y >= abs(p.y - d)) && (n->pos.y <= p.y + d)){
			return 1;
		}
	}
	
	if(topLeftTree != NULL){
		cont += topLeftTree->countRegion(p,d);
	}
	if(topRightTree != NULL){
		cont += topRightTree->countRegion(p,d);
	}
	if(botLeftTree != NULL){
		cont += botLeftTree->countRegion(p,d);
	}
	if(botRightTree != NULL){
		cont += botRightTree->countRegion(p,d);
	}
	return cont;
}

int Cuadrantes::AggregateRegion(Point p, int d){
	int cont = 0;

	if (n != nullptr) {
    	if ((abs(n->pos.x - p.x) <= d) && (abs(n->pos.y - p.y) <= d)) {
        	return n->data;
    	}
	}
	
	if(topLeftTree != NULL){
		cont += topLeftTree->AggregateRegion(p,d);
	}
	if(topRightTree != NULL){
		cont += topRightTree->AggregateRegion(p,d);
	}
	if(botLeftTree != NULL){
		cont += botLeftTree->AggregateRegion(p,d);
	}
	if(botRightTree != NULL){
		cont += botRightTree->AggregateRegion(p,d);
	}
	return cont;
}

void Cuadrantes::_printQuadTree(Cuadrantes* t, int indent)
{
  for(int i=0; i < indent; i++)
    cout << "--";

  if(t != NULL && t->n != NULL)
    cout << " " << t->n->data << endl;
  else if(t == NULL)
    cout << " NULL" << endl;
  else {
    cout << " X " << endl;
  
    _printQuadTree(t->topLeftTree, indent+1);
    _printQuadTree(t->topRightTree, indent+1);
    _printQuadTree(t->botLeftTree, indent+1);
    _printQuadTree(t->botRightTree, indent+1);
  }
}




//}
//vector <Point> Cuadrantes::list(){

//}

