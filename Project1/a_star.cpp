#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vectorC.h"

#define INF 999999

// typedef struct Node
// {
//     int x;
//     int y;
//     double Lgoal;
//     double Ggoal;
//     int isVisited;
//     struct Node *parent;
// } Node;


void swap(Node* node1, Node* node2) {
	Node temp = *node1;

	*node1 = *node2;
	*node2 = temp;
}

void coctailSortReverse(A_star_Vector* vec) {
	int index = 0;
	int last = vec->SIZE - 1;


	for (int i = index; i <= last - 1; i++) {
		if (vec->m_buffer[i].Ggoal < vec->m_buffer[i + 1].Ggoal) {
			swap(&vec->m_buffer[i], &vec->m_buffer[i + 1]);
		}
	}
	last--;
	for (int i = last; i >= index + 1; i--) {
		if (vec->m_buffer[i].Ggoal > vec->m_buffer[i - 1].Ggoal) {
			swap(&vec->m_buffer[i], &vec->m_buffer[i - 1]);
		}
	}
	//index++;

}


int compare(A_star_Vector* vec, int x, int y, int* index) {
	if (!vec->SIZE)
		return 0;

	for (int i = 0; i < vec->SIZE; i++) {
		if (vec->m_buffer[i].x == x && vec->m_buffer[i].y == y) {
			*index = i;
			return 1;
		}
	}
	return 0;

}

void printMaze(char* maze, int row, int col)
{

	printf("--------------------------------\n");
	for (int i = 0; i < row; i++)
	{
		printf("|");
		for (int j = 0; j < col; j++)
		{
			printf(" %c ", *((maze + i * col) + j));
		}
		printf("|\n");
	}
	printf("--------------------------------\n");
}

void Init_Node(Node* node, int x, int y, Node* parent)
{
	node->x = x;
	node->y = y;
	node->Lgoal = INF;
	node->Ggoal = INF;
	node->isVisited = 0;
	node->parent = parent;
}

float Range(Node* node1, Node* node2)
{
	return (float)((node1->x - node2->x) * (node1->x - node2->x) + (node1->y - node2->y) * (node1->y - node2->y));
}

void A_Star(char* maze, int row, int col, int Sx, int Sy, int Ex, int Ey, char* maze2)
{

	Node start = { 0 };
	Node end = { 0 };
	start.x = Sx;
	start.y = Sy;
	start.Lgoal = 0;
	start.Ggoal = INF;
	start.isVisited = 0;
	start.parent = NULL;
	end.x = Ex;
	end.y = Ey;
	end.Lgoal = 0;
	end.Ggoal = 0;
	end.isVisited = 0;
	end.parent = NULL;

	A_star_Vector neighbors;
	A_star_Vector path;
	A_star_Vector openSet;
	A_star_Vector closeSet;


	A_Star_Vector_Init(&neighbors);
	A_Star_Vector_Init(&path);
	A_Star_Vector_Init(&openSet);
	A_Star_Vector_Init(&closeSet);

	A_Star_Vec_Add(&openSet, &start);

	Node* current = NULL;
	Node tempPop;

	for (int k = 0; k < row*col; k++)
	{
		Node curr = openSet.m_buffer[openSet.SIZE - 1];
		A_Star_Vec_Pop(&openSet, &tempPop);

		current = &curr;
		A_Star_Vec_Add(&closeSet, current);

		A_Star_Vec_Add(&path, current);

		if (current->x == end.x && current->y == end.y)
			break;

		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (i == 0 && j == 0)
					continue;
				int newX = current->x + i;
				int newY = current->y + j;
				if (newX < 0 || newY < 0 || newX > col - 1 || newY > row - 1 || *((maze + newY * col) + newX) != ' ')
				{
					continue;
				}

				Node* temp = (Node*)malloc(sizeof(Node));
				Init_Node(temp, newX, newY, &closeSet.m_buffer[closeSet.SIZE - 1]);
				A_Star_Vec_Add(&neighbors, temp);
				free(temp);
			}
		}

		float min = INF;
		int Index = 0;
		for (int i = 0; i < neighbors.SIZE; i++)
		{
			if (!neighbors.m_buffer[i].isVisited) {
				neighbors.m_buffer[i].Lgoal = current->Lgoal + Range(current, &neighbors.m_buffer[i]);
				neighbors.m_buffer[i].Ggoal = neighbors.m_buffer[i].Lgoal + Range(&end, &neighbors.m_buffer[i]);
				neighbors.m_buffer[i].isVisited = 1;

				if (compare(&openSet, neighbors.m_buffer[i].x, neighbors.m_buffer[i].y, &Index)) {
					if (neighbors.m_buffer[i].Ggoal > current->Ggoal) {
						continue;
					}
				}

				A_Star_Vec_Add(&openSet, &neighbors.m_buffer[i]);
				*(maze + (neighbors.m_buffer[i].y * col) + neighbors.m_buffer[i].x) = '*';

			}
		}
		coctailSortReverse(&openSet);
	}

	A_Start_Vec_Print(&path);
	Node* parentTemp = &path.m_buffer[path.SIZE - 1];
	while (parentTemp != NULL) {

		*(maze2 + parentTemp->y * col + parentTemp->x) = '*';
		parentTemp = parentTemp->parent;
	}
}

int main(void)
{

	char maze[10][10] = { {'s', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
						  {'#', ' ', '#', '#', '#', '#', '#', ' ', ' ', ' '},
						  {' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' '},
						  {' ', ' ', ' ', '#', ' ', '#', '#', ' ', ' ', ' '},
						  {' ', '#', '#', '#', ' ', '#', ' ', ' ', ' ', ' '},
						  {' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' '},
						  {' ', ' ', ' ', '#', ' ', '#', '#', ' ', ' ', ' '},
						  {' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' '},
						  {' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' '},
						  {' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' '} };

	char maze2[10][10] = { {'s', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
						  {'#', ' ', '#', '#', '#', '#', '#', ' ', ' ', ' '},
						  {' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' '},
						  {' ', ' ', ' ', '#', ' ', '#', '#', ' ', ' ', ' '},
						  {' ', '#', '#', '#', ' ', '#', ' ', ' ', ' ', ' '},
						  {' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' '},
						  {' ', ' ', ' ', '#', ' ', '#', '#', ' ', ' ', ' '},
						  {' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' '},
						  {' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' '},
						  {' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' '} };

	printMaze(&maze[0][0], 10, 10);
	A_Star(&maze[0][0], 10, 10, 0, 0, 9, 9, &maze2[0][0]);
	printMaze(&maze[0][0], 10, 10);
	printMaze(&maze2[0][0], 10, 10);


	return 0;
}