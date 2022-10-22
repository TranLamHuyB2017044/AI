#include<stdio.h>
#include<stdlib.h>
#define Max 6
#define down 0
#define up 1
#define Maxlength 100
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
typedef struct
{
    Node *Elements[Maxlength];
    int front, rear;
} Queue;
void makeNull_Queue(Queue *queue)
{
    queue->front = -1;
    queue->rear = -1;
}
int empty(Queue queue)
{
    return queue.front == -1;
}
int full_Queue(Queue queue)
{
    return ((queue.rear - queue.front + 1) % Maxlength) == 0;
}
Node *get_Front(Queue queue)
{
    if (empty(queue))
    {
        printf("Queue is empty");
        return NULL;
    }
    else
        return queue.Elements[queue.front];
}
void del_Queue(Queue *queue)
{
    if (!empty(*queue))
    {
        if (queue->front == queue->rear)
        {
            makeNull_Queue(queue);
        }
        else
            queue->front = (queue->front + 1) % Maxlength;
    }
    else
        printf("Error, ,Delete");
}
void push_Queue(Node *x, Queue *queue)
{
    if (!full_Queue(*queue))
    {
        if (empty(*queue))
        {
            queue->front = 0;
        }
        queue->rear = (queue->rear + 1) % Maxlength;
        queue->Elements[queue->rear] = x;
    }
    else
        printf("Error, Push");
}
int find_State(State state, Queue Q){
    while (!empty(Q))
    {
    	Node *node = get_Front(Q);
        if (compare_state(node->state,state ))
            return 1;
        del_Queue(&Q);
    }
    return 0;
}
Node *BFS_Algorithm(State state){
    Queue Open_BFS;
    Queue Close_BFS;
    makeNull_Queue(&Open_BFS);
    makeNull_Queue(&Close_BFS);
    Node *root = (Node *)malloc(sizeof(Node));
    root->state = state;
    root->parent = NULL;
    root->no_function = 0;
    push_Queue(root, &Open_BFS);
    while (!empty(Open_BFS))
    {
        Node *node = get_Front(Open_BFS);
        del_Queue(&Open_BFS);
        push_Queue(node, &Close_BFS);
        if (goal_state(node->state))
        {
            return node;
        }
        int opt;
        for (opt = 1; opt <= 6; opt++)
        {
            State newstate;
            init_state(&newstate);
            if (call_operator(node->state, &newstate, opt))
            {
                if (find_State(newstate, Close_BFS) || find_State(newstate, Open_BFS))
                    continue;
                Node *newNode = (Node *)malloc(sizeof(Node));
                newNode->state = newstate;
                newNode->parent = node;
                newNode->no_function = opt;
                push_Queue(newNode, &Open_BFS);
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
    Node *p = BFS_Algorithm(cur_state);
    print_WaysToGetGoal(p);
return 0;
}

