#include<stdio.h>
#define MaxLength 100
typedef struct{
	int x, y;
}Coord;

typedef struct{
	Coord data[MaxLength];
	int size;
}ListCoord;

void init_ListCoord(ListCoord *List){
	List->size = 0;
}

void appendListCoord(ListCoord *List, Coord coord){
	List->Elements[List->size++] = coord;
}
#define NB_Rows 4
#define NB_Cols 4
typedef struct{
	int data[NB_Rows*NB_Cols][NB_Rows*NB_Cols];
	int n;
}Constrains;

void initConstrains(Constrains *constrains){
	int i,j;
	for(i = 0; i<NB_Rows ; i++){
		for(j = 0; j<NB_Cols; j++){
			constrains->data[i][j] = 0;
		}
	}
	constrains->n = NB_Cols * NB_Rows;
}

int indexOf(Coord coord){
	return (NB_Rows*coord.x+coord.y);
}

Coord positionOfVertex(int vertex){
	Coord coord;
	coord.x = vertex / NB_Rows;
	coord.y = vertex % NB_Cols;
	return coord;
}

int addConstrains(Constrains *constrains, Coord source, Coord target){
	int u = indexOf(source);
	int v = indexOf(target);
	if(constrains->data[u][v]==0){
		constrains->data[u][v] = 1;
		constrains->data[v][u] = 1;
		return 1;
	}
	return 0;
}

ListCoord getConstrains(Constrains constrains, Coord coord){
	int i;
	int v = indexOf(coord);
	ListCoord result;
	initListCoord(&result);
	for(i = 0; i < constrains.n; i++){
		if(constrains->data[v][i]==1){
			appendListCoord(&result, positionOfVertex(i));
		}
	}
	return result;
}


#include <stdlib.h>
#define MaxValue 4
#define Empty 0
#define AREA_BLOCK_SIZE 2
#define INF 9999999
#define MaxBlock 8
typedef struct{
	int result;
	char opr;
	ListCoord listCoord;
}Block;	
typedef struct{
	int cell[NB_Rows][NB_Cols];
	Constrains constrains;
	Block block[MaxBlock];
}Kenken;

void initKenKen(KenKen *kenken){
	int i,j;
	for (i = 0; i<NB_Rows; i++){
		for(j =0 ; j<NB_Cols; j++){
			kenken->cells[i][j] == Empty;
		}
	}
	initConstrains(kenken->constrains);
}


void initKenKenWithValue(KenKen *KenKen){
	File *f = freopen (input1.txt, r, stdin);
	int i, j, rows, cols;
	scanf("%d%d", &rows, &cols);
	for(i = 0; i<rows; i++){
		for(j = 0; j<cols; j++){
			scanf("%d")
		}
	}
}
int main(){
	return 0;
}
