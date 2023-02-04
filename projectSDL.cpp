#include <iostream>
#include <SDL.h>
#include <time.h>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

class differentNodesList
{
private:
    struct Node
    {
        string name;
        int x, y;
        int index;
        Node* next;
    };
    Node* Head;

public:
    differentNodesList()
    {
        Head = NULL;
    }
    void addNode(string n, int i, double X, double Y)
    {


        Node* curr = new Node, * temp = Head;
        curr->x = X;
        curr->y = Y;
        curr->name = n;
        curr->index = i;
        curr->next = NULL;
        if (Head == NULL)
        {
            Head = curr;
        }
        else
        {
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = curr;
        }
    }
    int getX(int n)
    {
        Node* temp = Head;
        while (temp->index != n)
        {
            temp = temp->next;
        }
        int x = temp->x;
        return x;
    }
    int getY(int n)
    {
        Node* temp = Head;
        while (temp->index != n)
        {
            temp = temp->next;
        }
        int y = temp->y;
        return y;
    }
    bool checkNode(string n)
    {
        Node* temp = Head;
        if (Head == NULL)
        {
            return true;
        }
        else
        {
            while (temp != NULL)
            {
                if (temp->name == n)
                {
                    return false;
                }
                temp = temp->next;
            }
            return true;
        }
    }

    string getName(int i)
    {
        Node* curr = Head;
        while (curr->index != i)
        {
            curr = curr->next;
        }
        return curr->name;
    }

    int getIndex(string n)
    {
        Node* temp = Head;
        while (temp->name != n)
        {
            temp = temp->next;
        }
        int x = temp->index;
        return x;
    }
    /*void printDifferentNodes()
     {
         Node* temp = Head;
         cout << "\nName\tIndex\tX\tY" << endl;
         while (temp != NULL)
         {
             cout << temp->name << "\t" << temp->index << "\t" << temp->x << "\t" << temp->y << endl;
             temp = temp->next;
         }
     }*/
};

class Graph
{

private:
    int size;
    int* visited;
    double** adjMatrix;

public:
    Graph() {}

    Graph(int v)
    {
        this->size = v;

        adjMatrix = new double* [size];

        for (int i = 0; i < size; i++)
        {
            adjMatrix[i] = new double[size];

            for (int j = 0; j < size; j++)
            {
                adjMatrix[i][j] = 0;
            }
        }
    }

    void addEdge(int val1, int val2, double weight)
    {

        adjMatrix[val1][val2] = weight;
        adjMatrix[val2][val1] = weight;
    }

    void print_AdjMatrix(differentNodesList* obj)
    {
        cout << "X\t";
        for (int i = 0; i < size; i++)
        {
            cout << obj->getName(i) << "\t";
        }
        cout << endl;
        int t = 0;
        for (int i = 0; i < size; i++)
        {
            t = 0;
            for (int j = 0; j < size; j++)
            {
                if (t == 0)
                {
                    cout << obj->getName(i) << "\t";
                    t = 1;
                }
                cout << adjMatrix[i][j] << "\t";
            }
            cout << endl;
        }
    }

    int degreeofNode_Matrix(string n, differentNodesList* obj)
    {
        int fixedIndex = obj->getIndex(n);
        int counter = 0;

        for (int j = 0; j < size; j++)
        {
            if (adjMatrix[fixedIndex][j] > 0)
            {
                counter++;
            }
        }

        return counter;
    }

    string max_degree_Node(differentNodesList* obj)
    {
        int max = degreeofNode_Matrix(obj->getName(0), obj);
        string maxDegreeNode;

        for (int i = 1; i < size; i++)
        {

            if (degreeofNode_Matrix(obj->getName(i), obj) > max)
            {
                max = degreeofNode_Matrix(obj->getName(i), obj);
                maxDegreeNode = obj->getName(i);
            }
        }
        cout << "Highest Degree Node:\t" << maxDegreeNode << "\nTotal No. of Edges:\t" << max << endl;
        return maxDegreeNode;
    }

    string min_degree_Node(differentNodesList* obj)
    {
        int min = degreeofNode_Matrix(obj->getName(0), obj);
        string minDegreeNode;

        for (int i = 1; i < size; i++)
        {
            if (degreeofNode_Matrix(obj->getName(i), obj) < min)
            {
                min = degreeofNode_Matrix(obj->getName(i), obj);
                minDegreeNode = obj->getName(i);
            }
        }
        cout << "Lowest Degree Node:\t" << minDegreeNode << "\nTotal No. of Edges:\t" << min << endl;
        return minDegreeNode;
    }

    bool checkNeighbour(int start, int triv, differentNodesList* obj)
    {
        if (adjMatrix[start][triv] > 0)
        {
            return true;
        }
        else
            return false;
    }

    void findNeighbours(string n, differentNodesList* obj)
    {
        int fixedIndex = obj->getIndex(n);
        cout << endl
            << n;
        for (int i = 0; i < size; i++)
        {
            if (adjMatrix[fixedIndex][i] > 0)
            {
                cout << "->" << obj->getName(i);
            }
        }
    }
};

static const int width = 1000;
static const int height = 1000;

void Draw(SDL_Renderer* renderer, int x1, int y1, int x2, int y2) {
	SDL_SetRenderDrawColor(renderer, 255, 100, 150, 255);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

int main(int argc, char* args[]) {

	// initialise sdl
	SDL_Init(SDL_INIT_EVERYTHING);

	// create a new sdl window
	SDL_Window* window = SDL_CreateWindow("Mesh", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

	// create a renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	bool running = true;
	SDL_Event event;

    int totalSize = 0;
    ifstream f("sampleInput.txt");
    double x, y;
    double radius = 70;
    double theta = 0;
    string line;
    differentNodesList listObject;
    while (getline(f, line))
    {
        string col1, col2;
        double col3;
        istringstream ss(line);
        ss >> col1 >> col2;
        if (ss >> col3)
        {
            ss >> col3;
        }
        if (listObject.checkNode(col1))
        {
            x = radius * cos(theta);
            y = radius * sin(theta);
            x = x + 500;
            y = y + 500;
            listObject.addNode(col1, totalSize, x, y);
            theta = theta + 5;
            if (theta >= 360)
            {
                radius = radius + 20;
                theta = 0;
            }
            totalSize++;
        }
        if (listObject.checkNode(col2))
        {
            x = radius * cos(theta);
            y = radius * sin(theta);
            x = x + 500;
            y = y + 500;
            listObject.addNode(col2, totalSize, x, y);
            theta = theta + 5;
            if (theta >= 360)
            {
                radius = radius + 20;
                theta = 0;
            }
            totalSize++;
        }
    }

    Graph graphObject(totalSize);

    ifstream openAgain("sampleInput.txt");

    while (getline(openAgain, line))
    {
        string col1, col2;
        double col3;
        istringstream ss(line);
        ss >> col1 >> col2;
        if (ss >> col3)
        {
            ss >> col3;
        }
        graphObject.addEdge(listObject.getIndex(col1), listObject.getIndex(col2), col3);
    }
    //listObject.printDifferentNodes();
    bool check = true;
    int selection;
    string tempInput, trash;

    while (check == true)
    {
        cout << "MENU\n\t1. Show Degree of a Node\n\t2. Node with Maximum Degree"
            << "\n\t3. Node with Minimun Degree\n\t4. Display the Raw Adjacency Matrix"
            << "\n\t5. Show Neighbours of a Node\n\t6. Render Circle\n\t7. Exit\n\t";
        cin >> selection;
        switch (selection)
        {
        case 1:
            cout << "Enter the name of the node: ";
            cin >> tempInput;
            cout << "\n Degree of Node " << tempInput << ": " << graphObject.degreeofNode_Matrix(tempInput, &listObject);
            break;
        case 2:

            trash = graphObject.max_degree_Node(&listObject);
            break;
        case 3:
            trash = graphObject.min_degree_Node(&listObject);
            break;
        case 4:
            graphObject.print_AdjMatrix(&listObject);
            break;
        case 5:
            cout << "Enter the name of the node: ";
            cin >> tempInput;
            graphObject.findNeighbours(tempInput, &listObject);
            break;
        case 6:
	        while (running) {
		        while (SDL_PollEvent(&event)) {
			        if (event.type == SDL_QUIT) {
				        running = false;
			        }
		        }

		        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		        SDL_RenderClear(renderer);
                for (int i = 0; i < totalSize; i++)
                {
                    for (int j = 0; j < totalSize; j++)
                    {
                        if (graphObject.checkNeighbour(i, j, &listObject))
                        {
                            Draw(renderer, listObject.getX(i), listObject.getY(i), listObject.getX(j), listObject.getY(j));
                        }
                    }

                }

		        SDL_RenderPresent(renderer);
	        }

	        SDL_DestroyRenderer(renderer);
	        SDL_DestroyWindow(window);
	        SDL_Quit();
            break;
        case 7:
            check = false;
            break;
        default:
            cout << "Invalid Output, Try again";
            break;
        }
        cout << endl
            << endl;
    }


	return 0;
}