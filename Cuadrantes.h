#include <iostream>
#include <vector>

using namespace std;

struct Point {
	float x;
	float y;
    Point(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
    Point()
    {
        x = 0;
        y = 0;
    }
};

struct Node {
    Point pos;
    int data;
    Node(Point _pos, int _data)
    {
        pos = _pos;
        data = _data;
    }
    Node() { data = 0; }
};

class Cuadrantes {
public:
	// Hold details of the boundary of this node
	Point topLeft;
	Point botRight;

	// Contains details of node
	Node* n;

	// Children of this tree
	Cuadrantes* topLeftTree;
	Cuadrantes* topRightTree;
	Cuadrantes* botLeftTree;
	Cuadrantes* botRightTree;


    Cuadrantes();
    Cuadrantes(Point topL, Point botR);
	void insert(Node* node);
	Node* search(Point p);//busca nodo
	bool inBoundary(Point p);//busca punto
    int totalPoints();//retorna la cantidad de puntos que hay
    int totalNodes();//retorna la cantidad de nodos que hay
    int countRegion(Point p, int d);//retora la cantidad de puntos de una región, p el el centro y d como la distancia
    int AggregateRegion(Point p, int d);//lo mismo que antes pero retorna la cantidad de población de la zona
    vector <Point> list();//retorna un contenedor con los puntos del QuadTree, nosotros vemos que contenedor se devuelve, y tambien
    //debemos ver si se recorre inOrder, postOrder o preOrder
    void _printQuadTree(Cuadrantes* t, int indent);

};
