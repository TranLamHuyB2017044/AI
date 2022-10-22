#include<stdio.h>
#include<stdlib.h>
#define Max_Vertices 5
#define MaxLength 500
typedef struct{
	int neigbor[Max_Vertices];
	int h;
}Vertices;

typedef struct{
	int num_vertices;
	Vertices v[Max_Vertices];
}Graph;

void init_Graph(int num_vertices,Graph *G){
	G->num_vertices = num_vertices;
	int i,j;
	for(i = 0; i< num_vertices;i++){
		for(j=0;j<num_vertices;j++){
			G->v[i].h = 0;
			G->v[i].neigbor[j] = 0;
		}
	}
		
}

const char name[] = {'A', 'B', 'C', 'D', 'G'};


typedef struct{
	int vertex;
}State;


int compareState(State state1, State state2){
	return state1.vertex == state2.vertex;
}

typedef struct Node{
	State state;
	struct Node *parent;
	int no_function;
	int f,g,h;
}Node;

void printState(State state, Node *node)
{
    printf("  %c (g = %d, h = %d, f = %d)\n", name[state.vertex], node->g, node->h, node->f);
}

typedef struct{
	Node* Element[MaxLength];
	int size;
}List;

void makenull(List *list){
	list->size = 0;
}
int empty(List list){
	return list.size ==0; 
}
int full(List L){
	return L.size == MaxLength;
}
Node* element_at(int p, List L){
	return L.Element[p-1];
}
void pushList(Node* x, int position, List *list){
    if(!full(*list)){
        int p;
        for(p=list->size; p>=position; p--){
            list->Element[p]=list->Element[p-1];
        }
        list->Element[position-1]=x;
        list->size++;
    }
    else printf("List is full");
}
void delete_list(int position, List *list){
	if(empty(*list))
		printf("list is empty!\n");
	else if(position <1 || position>list->size)
		printf("Position is not possible to delete\n");
	else {
		int i;
		for(i=position-1;i<list->size;i++)
			list->Element[i] = list->Element[i+1];
		list->size--;	
	}		
}
Node* find_state(State state, List list, int *position){
	int i ;
	for(i=1;i<=list.size;i++)
		if(compareState(state,element_at(i, list)->state)){
			*position = i;
			return element_at(i, list);
		}
	return NULL;	
}
void sort_List(List *list){
	int i,j;
	for(i=0;i<list->size;i++)
		for(j=i+1;j<list->size;j++)
			if(list->Element[i]->f>list->Element[j]->f){
				Node* node = list->Element[i];
				list->Element[i] = list->Element[j];
				list->Element[j] = node;
			}
}
int goal_check(State state, State goal){
	return compareState(state, goal);
}
Node* A_Star(Graph G,State state, State goal){
	List Open_A_Star, Close_A_Star;
	makenull(&Open_A_Star);
	makenull(&Close_A_Star);
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->parent = NULL;
	root->g = 0;
	root->h = G.v[state.vertex].h;
	root->f = root->g + root->h;
	pushList(root,Open_A_Star.size+1, &Open_A_Star);
	while(!empty(Open_A_Star)){
		Node* node = element_at(1, Open_A_Star);
		delete_list(1,&Open_A_Star);
		pushList(node, Close_A_Star.size+1, &Close_A_Star);
		if(goal_check(node->state, goal))
			return node;
		int opt;
		for(opt=0;opt<G.num_vertices;opt++){
			State newstate;
			if(G.v[node->state.vertex].neigbor[opt]>0){
				Node* newnode = (Node*)malloc(sizeof(Node));
				newnode->state.vertex = opt;
				newnode->parent = node;
				newnode->g = node->g+ G.v[node->state.vertex].neigbor[opt];
				newnode->h = G.v[opt].h;
				newnode->f = newnode->g + newnode->h;
				int pos_Open, pos_Close;
				Node* nodeFoundOpen = find_state(newnode->state, Open_A_Star, &pos_Open);
				Node* nodeFoundClose= find_state(newnode->state, Close_A_Star, &pos_Close);
				if(nodeFoundOpen==NULL && nodeFoundClose==NULL){
					pushList(newnode, Open_A_Star.size+1, &Open_A_Star);
				}
				else if(nodeFoundOpen!=NULL && nodeFoundOpen->g > newnode->g){
					delete_list(pos_Open, &Open_A_Star);
					pushList(newnode, pos_Open, &Open_A_Star);
				}
				else if(nodeFoundClose!=NULL && nodeFoundClose->g > newnode->g){
					delete_list(pos_Close, &Close_A_Star);
					pushList(newnode, Open_A_Star.size+1, &Open_A_Star);
				}
			}
		}
		sort_List(&Open_A_Star);
	}
	return NULL;
}

void print_WayToGetGoal(Node* node){
	List listprint;
	makenull(&listprint);
	while(node->parent!=NULL){
		pushList(node, listprint.size+1, &listprint);
		node = node->parent;
	}
	pushList(node, listprint.size+1, &listprint);
	int no_action = 0, i;
	for(i=listprint.size;i>0;i--){
		printState(element_at(i, listprint)->state, element_at(i, listprint));
		if(i!=1){
			printf("-->");
		}
		no_action++;
	}
}
int main(){
	int i,j;
	Graph Gr;
	freopen("text.txt", "r", stdin);
	init_Graph(Max_Vertices, &Gr);
	for(i=0; i<Max_Vertices;i++){
		int x;
		scanf("%d", &x);
		Gr.v[i].h = x;
		for(j = 0; j< Max_Vertices; j++){
			scanf("%d", &x);
			Gr.v[i].neigbor[j] = x;	
		}
	}
	State A,G;
	A.vertex = 0;
	G.vertex = 4;
	Node *result = A_Star(Gr, A, G);
	print_WayToGetGoal(result);
	return 0;
}
