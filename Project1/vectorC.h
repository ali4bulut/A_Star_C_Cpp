#pragma once
#ifndef INC_VECTORC_H_
#define INC_VECTOR_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    size_t SIZE;
    size_t CAP;
    int* m_buffer;
} Vector;

typedef struct
{
    size_t SIZE;
    size_t CAP;
    int** m_buffer;
} Vector3;

typedef struct Node
{
    int x;
    int y;
    float Lgoal;
    float Ggoal;
    int isVisited;
    struct Node* parent;
} Node;

typedef struct
{
    size_t SIZE;
    size_t CAP;
    Node* m_buffer;
} A_star_Vector;

void Vector_Init(Vector* vec);
void Vector3_Init(Vector3* vec);
void A_Star_Vector_Init(A_star_Vector* vec);
void ReAlloc(Vector* vec, size_t newCap);
void ReAlloc3(Vector3* vec, size_t newCap);
void A_Star_Vec_ReAlloc(A_star_Vector* vec, size_t newCap);
void Add(Vector* vec, int value);
void Add3(Vector3* vec, int x, int y, int z);
void A_Star_Vec_Add(A_star_Vector* vec, Node* node);
int Pop(Vector* vec);
void Pop3(Vector3* vec, int* out);
void A_Star_Vec_Pop(A_star_Vector* vec, Node* node);
void PrintVector(Vector* vec);
void PrintVector3(Vector3* vec);
void A_Start_Vec_Print(A_star_Vector* vec);

#endif