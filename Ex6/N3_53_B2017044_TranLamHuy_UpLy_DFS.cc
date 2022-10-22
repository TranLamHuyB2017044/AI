#include<stdio.h>
#include<stdlib.h>
#include<stack>
#define Max 6
#define down 0
#define up 1
using namespace std;
typedef struct{
	int A[Max]; 
}State;

const char* action[] = { "Frist state ",
						 "Change 1 2 3",
						 "Change 2 3 4",
						 "Change 3 4 5",
						 "Change 4 5 6"	
};
void init_state(State *state){
	int i;
	for(i=0;i<Max;i++)
		state->A[i] = down;
}
int goal_state(State state){
	int i;
	for(i=0;i<Max;i++){
		if(state.A[i]!=up)
			return 0;
	}
	return 1;
	
}
int change_status(int  state){
	return state == up ? down : up; 
}
void print_state(State state){
	int i;
	printf("\t");
	for(i=0;i<Max;i++)
		printf("%d ", state.A[i]);
	printf("\n");
}
int isChange(State state, int x, int y, int z){
	return state.A[x]!=up || state.A[y]!=up || state.A[z]!=up;
}
int compare_state(State state_x, State state_y){
	int i;
	for(i=0;i<Max;i++)
		if(state_x.A[i]!=state_y.A[i])
			return 0;
	return 1;		
}
int change_state(State cur_state, State *result, int x, int y, int z){
	int i;
	if(isChange(cur_state, x, y, z)){
		*result = cur_state;
        result->A[x] = change_status(cur_state.A[x]);
        result->A[y] = change_status(cur_state.A[y]);
        result->A[z] = change_status(cur_state.A[z]);
        return 1;
	}
	return 0;
}
int call_operator(State cur_state, State *result, int opt)
{
    switch (opt)
    {
    case 1:
        return change_state(cur_state, result, 0, 1, 2);
    case 2:
        return change_state(cur_state, result, 1, 2, 3);
    case 3:
        return change_state(cur_state, result, 2, 3, 4);
    case 4:
        return change_state(cur_state, result, 3, 4 , 5);
    default:
        return 0;
    }
}
typedef struct Node{
    State state;
    struct Node *parent;
    int no_function;
} Node;
int findState(State state, stack<Node *> OpenStack){
    while (!OpenStack.empty())
    {
        if (compare_state(state, OpenStack.top()->state))
            return 1;
        OpenStack.pop();
    }
    return 0;
}
Node *DFS_Algorithm(State state){
    stack<Node*> Open, Close;
    Node *root;
    root = (Node *)malloc(sizeof(Node));
    root->state = state;
    root->parent = NULL;
    root->no_function = 0;
    root->no_function;
    Open.push(root);
    while (!Open.empty())
    {
        Node *node;
        node = Open.top();
        Open.pop();
        Close.push(node);
        if (goal_state(node->state))
            return node;

        for (int opt = 1; opt <= 4; opt++)
        {
            State newState;
            init_state(&newState);
            if (call_operator(node->state, &newState, opt))
            {

                if (findState(newState, Open) || findState(newState, Close))
                    continue;
                Node *newNode = (Node *)malloc(sizeof(Node));
                newNode->state = newState;
                newNode->parent = node;
                newNode->no_function = opt;
                Open.push(newNode);
            }
        }
    }
    return NULL;
}
void print_WaysToGetGoal(Node* node){
    Node way[1000];
    int i=0;
    while (node->parent != NULL){
        way[i]=*node;
        i++;
        node = node->parent;
    }
    int j, no_action=0;
    way [i] = *node;
    for(j=i; j>=0; j--){ 
		printf("\nAction %d: %s ", no_action, action[way[j].no_function]);
        printf("\n");
		print_state(way[j].state);
        no_action++;
    }
}

int main(){
    State cur_state = {0,1,0,1,0,1};
    Node *p = DFS_Algorithm(cur_state);
    print_WaysToGetGoal(p);
return 0;
}
