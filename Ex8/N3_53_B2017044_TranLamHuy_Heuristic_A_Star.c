#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define Cols 3
#define Rows 3
#define EMPTY 0
#define Max_operator 4
#define MaxLength 500


const char*  Action[]= {"Frist state",
				 "Move cell EMPTY to UP",
				 "Move cell EMPTY to DOWN",
				 "Move cell EMPTY to RIGHT",
				 "Move cell EMPTY to LEFT"
};
typedef struct{
	int EightPuzzel[Rows][Cols];
	int emptyRow;
	int emptyCol;
}State;

void Print_state(State state){
	int i,j;
	printf("\n------------\n");
	for(i=0;i<Rows;i++){
		for(j=0;j<Cols;j++)
			printf("| %d ", state.EightPuzzel[i][j]);
		printf("|\n");	
	}
	printf("------------\n");
}
int compareState(State state1, State state2){
	if(state1.emptyRow != state2.emptyRow || state1.emptyCol != state2.emptyCol)
		return 0;
	int i,j;
	for(i=0;i<Rows;i++)
		for(j=0;j<Cols;j++)
			if(state1.EightPuzzel[i][j] != state2.EightPuzzel[i][j])
				return 0;
	return 1;
}
int goal_check(State state, State goal){
	return compareState(state, goal);
}
int up(State state, State *result){
	*result = state;
	int empRowCurrent = state.emptyRow, empColCurrent = state.emptyCol;
	if (empRowCurrent > 0){
		result->emptyRow = empRowCurrent - 1;
		result->emptyCol = empColCurrent;
		result->EightPuzzel[empRowCurrent][empColCurrent] = state.EightPuzzel[empRowCurrent-1][empColCurrent];
		result->EightPuzzel[empRowCurrent-1][empColCurrent] = EMPTY;	
		return 1;
	}
	return 0;
}
int down(State state, State *result){
	*result = state;
	int empRowCurrent = state.emptyRow, empColCurrent = state.emptyCol;
	if (empRowCurrent < 2){
		result->emptyRow = empRowCurrent + 1;
		result->emptyCol = empColCurrent;
		result->EightPuzzel[empRowCurrent][empColCurrent] = state.EightPuzzel[empRowCurrent+1][empColCurrent];
		result->EightPuzzel[empRowCurrent+1][empColCurrent] = EMPTY;
		return 1;	
	}
	return 0;
}
int left(State state, State *result){
	*result = state;
	int empRowCurrent = state.emptyRow, empColCurrent = state.emptyCol;
	if (empColCurrent > 0 ){
		result->emptyRow = empRowCurrent;
		result->emptyCol = empColCurrent -1;
		result->EightPuzzel[empRowCurrent][empColCurrent] = state.EightPuzzel[empRowCurrent][empColCurrent-1];
		result->EightPuzzel[empRowCurrent][empColCurrent-1] = EMPTY;
		return 1;	
	}
	return 0;
}
int right(State state, State *result){
		*result = state;
	int empRowCurrent = state.emptyRow, empColCurrent = state.emptyCol;
	if (empColCurrent <2 ){
		result->emptyRow = empRowCurrent;
		result->emptyCol = empColCurrent +1;
		result->EightPuzzel[empRowCurrent][empColCurrent] = state.EightPuzzel[empRowCurrent][empColCurrent+1];
		result->EightPuzzel[empRowCurrent][empColCurrent+1] = EMPTY;
		return 1;	
	}
	return 0;
}
int callOPerators(State state, State *result, int opt){
	switch(opt){
		case 1: return up(state, result);
		case 2: return down(state, result);
		case 3: return left(state, result);
		case 4: return right(state, result);
		default : return 0;		
	}
}
typedef struct Node{
	State state;
	struct Node *parent;
	int no_function;
	int f,g,h;
}Node;

int heuristic(State state, State goal){
	int row,col, count =0;
	for(row = 0; row<Rows;row++)
		for(col =0; col<Cols;col++)
			if(state.EightPuzzel[row][col] != goal.EightPuzzel[row][col])
				count ++;
	return count;			
				
}
int heuristic2(State state, State goal){
	int count = 0;
	int col,row,col_g,row_g;
	for(row=0;row<Rows;row++){
		for(col=0;col<Cols;col++){
			if(state.EightPuzzel[row][col] != EMPTY){
				for(row_g=0;row_g<Rows;row_g++){
					for(col_g = 0 ; col_g <Cols; col_g++){
						if(state.EightPuzzel[row][col] == goal.EightPuzzel[row_g][col_g]){
							count += abs(row-row_g) + abs(col - col_g);
							col_g = Cols;//break loop cols_g
							row_g = Rows;//break loop row_g
						}		
					}
				}
			}	
		}
	}
	return count;
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

Node* A_star(State state, State goal){
	List Open_A_Star, Close_A_Star;
	makenull(&Open_A_Star);
	makenull(&Close_A_Star);
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->parent = NULL;
	root->no_function = 0;
	root->g = 0;
	root->h = heuristic2(root->state, goal);
	root->f = root->g + root->h;
	pushList(root,Open_A_Star.size+1, &Open_A_Star);
	while(!empty(Open_A_Star)){
		Node* node = element_at(1, Open_A_Star);
		delete_list(1,&Open_A_Star);
		pushList(node, Close_A_Star.size+1, &Close_A_Star);
		if(goal_check(node->state, goal))
			return node;
		int opt;
		for(opt=1;opt<=Max_operator;opt++){
			State newstate;
			newstate = node->state;
			if(callOPerators(node->state, &newstate, opt)){
				Node* newnode = (Node*)malloc(sizeof(Node));
				newnode->state = newstate;
				newnode->parent = node;
				newnode->no_function = opt;
				newnode->g = newnode->g+1;
				newnode->h = heuristic2(newstate, goal);
				newnode->f = newnode->g + newnode->h;
				int pos_Open, pos_Close;
				Node* nodeFoundOpen = find_state(newstate, Open_A_Star, &pos_Open);
				Node* nodeFoundClose= find_state(newstate, Close_A_Star, &pos_Close);
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
		printf("\n Action %d: %s", no_action, Action[element_at(i, listprint)->no_function]);
		Print_state(element_at(i, listprint)->state);
		no_action++;
	}
}
int main(){
	State state;
	state.emptyCol = 1;
	state.emptyRow = 1;
	state.EightPuzzel[0][0] = 1;
	state.EightPuzzel[0][1] = 2;
	state.EightPuzzel[0][2] = 3;
	state.EightPuzzel[1][0] = 8;
	state.EightPuzzel[1][1] = 0;
	state.EightPuzzel[1][2] = 4;
	state.EightPuzzel[2][0] = 7;
	state.EightPuzzel[2][1] = 6;
	state.EightPuzzel[2][2] = 5;	
	State goal;
	goal.emptyCol = 0;
	goal.emptyRow = 1;
	goal.EightPuzzel[0][0] = 2;
	goal.EightPuzzel[0][1] = 8;
	goal.EightPuzzel[0][2] = 1;
	goal.EightPuzzel[1][0] = 0;
	goal.EightPuzzel[1][1] = 4;
	goal.EightPuzzel[1][2] = 3;
	goal.EightPuzzel[2][0] = 7;
	goal.EightPuzzel[2][1] = 6;
	goal.EightPuzzel[2][2] = 5;
	Node* p = A_star(state, goal);
	print_WayToGetGoal(p);		
	return 0;
}
