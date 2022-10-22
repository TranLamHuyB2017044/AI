#include<stdio.h>
#include<stdlib.h>
#define Tankcapacity_X 9
#define Tankcapacity_Y 4
#define empty 0
#define goal 6

#define Maxlength 100
const char* action[] = {"First State", "pour Water Full X", "pour Water Full Y",
 						"pour Water empty X", "pour Water empty Y",
  						"pour Water X to Y", "pour Water Y to X"};
typedef struct{
	int x,y;
}State;

void makenull_State(State *state){
	state->x=0;
	state->y=0;
}
void print_State(State state){
	printf("\n		X:%d --- Y:%d", state.x, state.y);
}
int goal_check(State *state){
	return (state->x == goal || state->y==goal);
}
int compareStates(State state1, State state2){
	return (state1.x == state2.x && state1.y==state2.y);
}
int pourWaterFullX(State cur_state, State *result){
	if(cur_state.x < Tankcapacity_X){
		result->x= Tankcapacity_X;
		result->y = cur_state.y;
		return 1;
	}
	return 0;
}
int pourWaterFullY(State cur_state, State *result){
	if(cur_state.y < Tankcapacity_Y){
		result->y= Tankcapacity_Y;
		result->x = cur_state.x;
		return 1;
	}
	return 0;
}
int pourWaterEmptyX(State cur_state, State *result){
	if(cur_state.x > empty){
		result->x = empty;
		result->y = cur_state.y;
		return 1;
	}
	return 0;
}
int pourWaterEmptyY(State cur_state, State *result){
	if(cur_state.y > empty){
		result->y = empty;
		result->x = cur_state.x;
		return 1;
	}
	return 0;
}
int max(int a, int b){
	if (a > b){
		return a;
	}
	return b;
}
int min(int a, int b){
	if( a < b ){
		return a;
	}
	return b;
}
int pourWaterXY(State cur_state, State *result){
	if(cur_state.x > empty && cur_state.y < Tankcapacity_Y){
		result->x = max(cur_state.x - (Tankcapacity_Y - cur_state.y), empty);
		result->y = min(cur_state.x + cur_state.y, Tankcapacity_Y);
		return 1;
	}
	return 0;
}
int pourWaterYX(State cur_state, State *result){
	if(cur_state.y > empty && cur_state.x < Tankcapacity_X){
		result->y = max(cur_state.y - (Tankcapacity_X - cur_state.x), empty);
		result->x = min(cur_state.y + cur_state.x, Tankcapacity_X);
		return 1;
	}
	return 0;
}
int call_operator(State cur_state, State *result, int option){
	switch(option){
		case 1 : return pourWaterFullX(cur_state, result);
		case 2 : return pourWaterFullY(cur_state, result);
		case 3 : return pourWaterEmptyX(cur_state, result);
		case 4 : return pourWaterEmptyY(cur_state, result);
		case 5 : return pourWaterXY(cur_state, result);
		case 6 : return pourWaterYX(cur_state, result);
		default : printf("Error call operators");
			return 0; 
	}
}
typedef struct Node{
	State state;
	struct Node *parent;
	int no_function;
}Node;
typedef struct{
	Node* Element[Maxlength];
	int Top_idx;
}Stack;
void makenull_Stack(Stack *S){
	S->Top_idx = Maxlength;
}

int empty_Stack(Stack S){
	return S.Top_idx==Maxlength;
}

int full_Stack(Stack *S){
	return S->Top_idx==0;
}
Node* top(Stack S){
	if(!empty_Stack(S))
		return S.Element[S.Top_idx];
	return NULL;		
}
void push(Node* x, Stack *stack){
	if(full_Stack(stack)){
		printf("Erorr! Stack is full");
	}
	else{
		stack->Top_idx -= 1;
		stack->Element[stack->Top_idx]=x;
	}
}
void pop(Stack *S){
	if(!empty_Stack(*S))
		S->Top_idx+=1;
	else printf("Erorr! Stack is empty");	
}


int find_State(State state, Stack openStack){
	while (!empty_Stack(openStack)){
		if(compareStates(top(openStack)->state, state))
			return 1;
		pop(&openStack);	
	}
	return 0;
}
Node* DFS(State state){
	Stack open;
	Stack close;
	makenull_Stack(&open);
	makenull_Stack(&close);
	//tao node trang thai cha
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->parent = NULL;
	root->no_function = 0;
	push(root, &open);
	while (!empty_Stack(open)){
		Node* node = top(open);
		pop(&open);
		push(node, &close);
		//kiem tra dinh lay ra co phai goal ?
		if(goal_check(&node->state))
			return node;
		int opt;
		for(opt =1; opt<=6;opt++){
			State newstate;
			makenull_State(&newstate);
			if(call_operator(node->state, &newstate, opt)){
				if(find_State(newstate, open) || find_State(newstate, close))
					continue;
				Node* newnode = (Node*)malloc(sizeof(Node));
				newnode->state = newstate;
				newnode->parent = node;
				newnode->no_function=opt;
				push(newnode, &open); 	
			}
		}	
	}
	return NULL;
}
void print_WaysToGetGoal(Node* node){
	Stack stackPrint;
	makenull_Stack(&stackPrint);
	while(node->parent!=NULL){
		push(node, &stackPrint);
		node = node->parent;
	}
	push(node, &stackPrint);
	int no_action = 0;
	while (!empty_Stack(stackPrint)){
		printf("\n Action %d: %s", no_action, action[top(stackPrint)->no_function]);
		print_State(top(stackPrint)->state);
		pop(&stackPrint);
		no_action++;
	}
}
int main(){
	
	State cur_state = {0 ,0};
	Node* p = DFS(cur_state);
	print_WaysToGetGoal(p);


	return 0;
}
