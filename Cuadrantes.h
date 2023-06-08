#include <iostream>

struct Point {
	int x;
	int y;
    Point(int _x, int _y)
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
};
