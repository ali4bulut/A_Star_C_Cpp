#include "vectorC.h"

// typedef struct
// {
//     size_t SIZE;
//     size_t CAP;
//     int *m_buffer;
// } Vector;

// typedef struct
// {
//     size_t SIZE;
//     size_t CAP;
//     int **m_buffer;
// } Vector3;

void Vector_Init(Vector* vec)
{

	int* p = (int*)malloc(2 * sizeof(int));

	vec->m_buffer = p;
	vec->CAP = 2;
	vec->SIZE = 0;
}
void Vector3_Init(Vector3* vec)
{

	int** p = (int**)malloc(2 * sizeof(int*));
	for (int i = 0; i < 2; i++)
	{
		p[i] = (int*)malloc(3 * sizeof(int));
	}

	vec->m_buffer = p;
	vec->CAP = 2;
	vec->SIZE = 0;
}

void A_Star_Vector_Init(A_star_Vector* vec)
{

	Node* p = (Node*)malloc(100 * sizeof(Node));

	vec->m_buffer = p;
	vec->CAP = 100;
	vec->SIZE = 0;
}

void ReAlloc(Vector* vec, size_t newCap)
{

	int* p = (int*)malloc(newCap * sizeof(int));

	if (newCap < vec->SIZE)
		vec->SIZE = newCap;

	for (int i = 0; i < vec->SIZE; i++)
	{
		p[i] = vec->m_buffer[i];
	}

	free(vec->m_buffer);
	vec->m_buffer = p;
	vec->CAP = newCap;
}

void ReAlloc3(Vector3* vec, size_t newCap)
{

	int** p = (int**)malloc(newCap * sizeof(int*));

	for (int i = 0; i < newCap; i++)
	{
		p[i] = (int*)malloc(3 * sizeof(int));
	}

	if (newCap < vec->SIZE)
		vec->SIZE = newCap;

	for (int i = 0; i < vec->SIZE; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			p[i][j] = vec->m_buffer[i][j];
		}
	}

	for (int i = 0; i < vec->SIZE; i++)
	{
		free(vec->m_buffer[i]);
	}
	free(vec->m_buffer);

	vec->m_buffer = p;
	vec->CAP = newCap;
}

void A_Star_Vec_ReAlloc(A_star_Vector* vec, size_t newCap)
{
	Node* p = (Node*)malloc(newCap * sizeof(Node));

	if (newCap < vec->SIZE)
		vec->SIZE = newCap;

	for (int i = 0; i < vec->SIZE; i++)
	{
		p[i] = vec->m_buffer[i];
	}

	free(vec->m_buffer);
	vec->m_buffer = p;
	vec->CAP = newCap;
}

void Add(Vector* vec, int value)
{

	if (vec->SIZE >= vec->CAP)
	{
		ReAlloc(vec, (vec->CAP * 2));
	}
	vec->m_buffer[vec->SIZE] = value;
	vec->SIZE++;
}

void Add3(Vector3* vec, int x, int y, int z)
{

	if (vec->SIZE >= vec->CAP)
	{
		ReAlloc3(vec, (vec->CAP * 2));
	}
	vec->m_buffer[vec->SIZE][0] = x;
	vec->m_buffer[vec->SIZE][1] = y;
	vec->m_buffer[vec->SIZE][2] = z;
	vec->SIZE++;
}

void A_Star_Vec_Add(A_star_Vector* vec, Node* node)
{

	if (vec->SIZE >= vec->CAP)
	{
		A_Star_Vec_ReAlloc(vec, (vec->CAP * 2));
	}

	vec->m_buffer[vec->SIZE].x = node->x;
	vec->m_buffer[vec->SIZE].y = node->y;
	vec->m_buffer[vec->SIZE].parent = node->parent;
	vec->m_buffer[vec->SIZE].Lgoal = node->Lgoal;
	vec->m_buffer[vec->SIZE].Ggoal = node->Ggoal;
	vec->m_buffer[vec->SIZE].isVisited = node->isVisited;

	vec->SIZE++;
}

int Pop(Vector* vec)
{

	int temp = vec->m_buffer[vec->SIZE - 1];

	vec->m_buffer[vec->SIZE - 1] = 0;
	vec->SIZE--;
	if ((vec->CAP / vec->SIZE) == 2)
	{
		ReAlloc(vec, vec->SIZE);
	}

	return temp;
}
void Pop3(Vector3* vec, int* out)
{

	out[0] = vec->m_buffer[vec->SIZE - 1][0];
	out[1] = vec->m_buffer[vec->SIZE - 1][1];
	out[2] = vec->m_buffer[vec->SIZE - 1][2];

	vec->m_buffer[vec->SIZE - 1][0] = 0;
	vec->m_buffer[vec->SIZE - 1][1] = 0;
	vec->m_buffer[vec->SIZE - 1][2] = 0;
	vec->SIZE--;
	if ((vec->CAP / vec->SIZE) == 2)
	{
		ReAlloc3(vec, vec->SIZE);
	}
}

void A_Star_Vec_Pop(A_star_Vector* vec, Node* node)
{

	node->x = vec->m_buffer[vec->SIZE - 1].x;
	node->y = vec->m_buffer[vec->SIZE - 1].y;
	node->parent = vec->m_buffer[vec->SIZE - 1].parent;
	node->Lgoal = vec->m_buffer[vec->SIZE - 1].Lgoal;
	node->Ggoal = vec->m_buffer[vec->SIZE - 1].Ggoal;
	node->isVisited = vec->m_buffer[vec->SIZE - 1].isVisited;

	vec->m_buffer[vec->SIZE - 1].x = 0;
	vec->m_buffer[vec->SIZE - 1].y = 0;
	vec->m_buffer[vec->SIZE - 1].parent = 0;
	vec->m_buffer[vec->SIZE - 1].Lgoal = 0;
	vec->m_buffer[vec->SIZE - 1].Ggoal = 0;
	vec->m_buffer[vec->SIZE - 1].isVisited = 0;
	vec->SIZE--;
	if (vec->SIZE != 0) {

		if ((vec->CAP / vec->SIZE) == 100)
		{
			A_Star_Vec_ReAlloc(vec, vec->SIZE);
		}
	}
}

void PrintVector(Vector* vec)
{

	for (int i = 0; i < vec->SIZE; i++)
	{
		printf("Vector[%i] : %i\r\n", i, vec->m_buffer[i]);
	}
}

void PrintVector3(Vector3* vec)
{

	for (int i = 0; i < vec->SIZE; i++)
	{
		printf("Vector3[%i] : %i, %i, %i\r\n", i, vec->m_buffer[i][0], vec->m_buffer[i][1], vec->m_buffer[i][2]);
	}
}

void A_Start_Vec_Print(A_star_Vector* vec)
{

	for (int i = 1; i < vec->SIZE; i++)
	{
		if(vec->m_buffer[i].parent)
			printf("Vector[%i] : X: %i,  Y: %i Parent: X: %i Y: %i\r\n", i, vec->m_buffer[i].x, vec->m_buffer[i].y, vec->m_buffer[i].parent->x, vec->m_buffer[i].parent->y);

	}
}

// int main()
// {

//     Vector vec;
//     Vector3 vec3;

//     Vector_Init(&vec);
//     Vector3_Init(&vec3);

//     Add3(&vec3, 5, 7, 8);
//     Add3(&vec3, 54, 32, 25);
//     Add3(&vec3, 63, 62, 34);
//     Add3(&vec3, 73, 78, 15);
//     Add3(&vec3, 97, 92, 37);
//     Add3(&vec3, 24, 47, 82);
//     Add3(&vec3, 79, 64, 95);

//     int arr[3] = {0};
//     Pop3(&vec3, arr);
//     Pop3(&vec3, arr);
//     Pop3(&vec3, arr);
//     Pop3(&vec3, arr);

//     printf("Arr[%i] : %i, %i, %i\r\n", 0, arr[0], arr[1], arr[2]);

//     Add(&vec, 5);
//     Add(&vec, 7);
//     Add(&vec, 1);
//     Add(&vec, 61);
//     Add(&vec, 15);
//     Add(&vec, 54);

//     int t = Pop(&vec);
//     t = Pop(&vec);
//     t = Pop(&vec);
//     t = Pop(&vec);

//     Add(&vec, 54);
//     Add(&vec, 24);
//     Add(&vec, 234);
//     Add(&vec, 86);

//     PrintVector(&vec);
//     PrintVector3(&vec3);

//     free(vec.m_buffer);

//     for (int i = 0; i < vec3.SIZE; i++)
//     {
//         free(vec3.m_buffer[i]);
//     }
//     free(vec3.m_buffer);

//     printf("HELLLLLLLOOOOO!!!!!\n");
//     return 0;
// }

#pragma region

//     int **t = (int**)malloc(4 * sizeof(int*));

//     for (int i = 0; i < 4; i++){
//         t[i] = (int*)malloc(4 * sizeof(int));
//     }

//     for (int i = 0; i < 4; i++){
//         for(int j = 0; j < 4; j++){

//             t[i][j] = (i + 1) * 5 * (j + 1);
//         }
//     }

//    for (int i = 0; i < 4; i++){
//         for(int j = 0; j < 4; j++){

//             printf("Value : %i\t", t[i][j]);
//         }
//         printf("\n");
//     }

//     for (int i = 0; i < 4; i++){
//         free(t[i]);
//     }
//     free(t);
#pragma endregion