#include <cmath>
#include <iostream>
#include <vector>
#include "Cuadrantes.h"

using namespace std;

int main(){
    Cuadrantes plane2D(Point(0, 0), Point(8, 8));
    Node p1(Point(0, 0), 5);
    Node p2(Point(0, 1), 4);
    Node p3(Point(1, 0), 2);
    Node p4(Point(1, 1), 2);
    Node p5(Point(2, 1), 1);
    Node p6(Point(5, 1), 3);
    Node p7(Point(6, 2), 10);
    Node p8(Point(7, 7), 8);
    plane2D.insert(&p1);
    plane2D.insert(&p2);
    plane2D.insert(&p3);
    plane2D.insert(&p4);
    plane2D.insert(&p5);
    plane2D.insert(&p6);
    plane2D.insert(&p7);
    plane2D.insert(&p8);
    cout<<plane2D.topLeftTree->topLeftTree->topLeftTree->topLeft.x<<","<<plane2D.topLeftTree->topLeftTree->topLeftTree->topLeft.y<<" "<<
    plane2D.topLeftTree->topLeftTree->topLeftTree->botRight.x<<","<<plane2D.topLeftTree->topLeftTree->topLeftTree->botRight.y<<endl;
    cout<<plane2D.topLeftTree->topLeftTree->topRightTree->n->pos.x<<endl;
    cout<<plane2D.topLeftTree->topLeftTree->topRightTree->n->pos.y<<endl;
    //plane2D._printQuadTree(&plane2D,0);
    cout << "Cantidad de puntos" << plane2D.countRegion(Point(2,2),2)<<endl;
    int totalPoints = plane2D.totalPoints();
    cout << "Total Points: " << totalPoints << endl;
    int totalNodes = plane2D.totalNodes();
    cout << "Total Nodes: " << totalNodes << endl;

    return 0;
}