#include<stdio.h>
#include<stdlib.h>
#include<stack>
using namespace std;
#define Tankcapacity_X 10
#define Tankcapacity_Y 5
#define Tankcapacity_Z 6
#define Tankempty 0
#define goal 8
#define Maxlength 100

typedef struct{
	int x,y,z;
}State;

const char *action[] = {
    "First State",
    "pourWaterXY",
    "pourWaterXZ",
    "pourWaterYX",
    "pourWaterYZ",
    "pourWaterZX",
    "pourWaterZY"};
void makenull_State(State *state){
	state->x=0;
	state->y=0;
	state->z =0;
}
void print_State(State state){
	printf("\n		X:%d --- Y:%d --- Y:%d", state.x, state.y, state.z);
}
int goal_check(State *state){
	return state->x == goal ;
}
int compareStates(State state1, State state2){
	return (state1.x == state2.x && state1.y==state2.y && state1.z==state2.z);
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
	if(cur_state.x > Tankempty && cur_state.y < Tankcapacity_Y){
		result->x = max(cur_state.x - (Tankcapacity_Y - cur_state.y), Tankempty);
		result->y = min(cur_state.x + cur_state.y, Tankcapacity_Y);
		result->z = cur_state.z;
		return 1;
	}
	return 0;
}
int pourWaterXZ(State cur_state, State *result){
	if(cur_state.x > Tankempty && cur_state.z < Tankcapacity_Z){
		result->x = max(cur_state.x - (Tankcapacity_Z - cur_state.z), Tankempty);
		result->z = min(cur_state.x + cur_state.z, Tankcapacity_Z);
		result->y = cur_state.y;
		return 1;
	}
	return 0;
}
int pourWaterYX(State cur_state, State *result){
	if(cur_state.y > Tankempty && cur_state.x < Tankcapacity_X){
		result->y = max(cur_state.y - (Tankcapacity_X - cur_state.x), Tankempty);
		result->x = min(cur_state.y + cur_state.x, Tankcapacity_X);
		result->z = cur_state.z;
		return 1;
	}
	return 0;
}
int pourWaterYZ(State cur_state, State *result){
	if(cur_state.y > Tankempty && cur_state.z < Tankcapacity_Z){
		result->y = max(cur_state.y - (Tankcapacity_Z - cur_state.z), Tankempty);
		result->z = min(cur_state.y + cur_state.z, Tankcapacity_Z);
		result->x = cur_state.x;
		return 1;
	}
	return 0;
}
int pourWaterZX(State cur_state, State *result){
	if(cur_state.z > Tankempty && cur_state.x < Tankcapacity_X){
		result->z = max(cur_state.z - (Tankcapacity_X - cur_state.x), Tankempty);
		result->x = min(cur_state.z + cur_state.x, Tankcapacity_X);
		result->y = cur_state.y;
		return 1;
	}
	return 0;
}
int pourWaterZY(State cur_state, State *result){
	if(cur_state.z > Tankempty && cur_state.y < Tankcapacity_Y){
		result->z = max(cur_state.z - (Tankcapacity_Y - cur_state.y), Tankempty);
		result->y = min(cur_state.z + cur_state.y, Tankcapacity_Y);
		result->x = cur_state.x;
		return 1;
	}
	return 0;
}
int call_operator(State cur_state, State *result, int option)
{
    switch (option)
    {
    case 1:
        return  pourWaterXY(cur_state, result);
    case 2:
        return  pourWaterXZ(cur_state, result);
    case 3:
        return  pourWaterYX(cur_state, result);
    case 4:
        return  pourWaterYZ(cur_state, result);
    case 5:
        return  pourWaterZX(cur_state, result);
    case 6:
        return  pourWaterZY(cur_state, result);
    default:
        printf("Error calls operators");
        return 0;
    }
}

typedef struct Node
{
    State state;
    struct Node *Parent;
    int no_function;
} Node;

int find_State(State state, stack<Node*> OpenStack)
{
    while (!OpenStack.empty())
    {
        Node *node=OpenStack.top();
        if(compareStates(node->state,state))
            return 1;
        OpenStack.pop();
    }
    return 0;
}
Node* DFS_Algorithm(State state){
    stack<Node*> Open_DFS;
    stack<Node*> Close_DFS;
    Node* root =(Node*)malloc(sizeof(Node));
    root->state=state;
    root->Parent=NULL;
    root->no_function=0;
    Open_DFS.push(root);
    while(!Open_DFS.empty()){
        Node* node=Open_DFS.top();
        Open_DFS.pop();
        Close_DFS.push(node);
        if(goal_check(&node->state)){
            return node;
        }
        int opt;
        for(opt=1; opt<=6; opt++){
            State newstate;
            makenull_State(&newstate);
            if(call_operator(node->state, &newstate, opt)){
                if(find_State(newstate, Close_DFS)|| find_State(newstate, Open_DFS))
                    continue;
                Node* newNode=(Node*) malloc(sizeof(Node));
                newNode->state=newstate;
                newNode->Parent=node;
                newNode->no_function=opt;
                Open_DFS.push(newNode);
            }
        }
    }
    return NULL;
}
void print_WaysToGetGoal(Node* node)
{
    Node way[1000];
    int i=0;
    while (node->Parent != NULL)
    {
        way[i]=*node;
        i++;
        node = node->Parent;
    }  
    int j, no_action=0;
    way [i] = *node;
    for(j=i; j>=0; j--)
    {
        printf("\nAction %d: %s", no_action, action[way[j].no_function]);
        print_State(way[j].state);
        no_action++;
    }
}

int main(){
	State cur_state = {10, 0, 0};
    Node *p = DFS_Algorithm(cur_state);
    print_WaysToGetGoal(p);
	return 0;
}




