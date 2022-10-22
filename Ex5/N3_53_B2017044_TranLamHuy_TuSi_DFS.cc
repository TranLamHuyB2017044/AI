#include<stdio.h>
#include<stdlib.h>
#include<stack> 
using namespace std;
#define Tank_Demon 3
#define Tank_Clerics 3

const char *action[] = {"First_State","Move1Clerics", "Move2Clerics", "Move1Demon", "Move2Demon", "Move1ClericsAnd1Demon"};
    typedef struct{
    int Demon,Clerics;
    char ship;
}State;
void init_state(State *state){
    state->Clerics = 0;
    state->Demon = 0;
    state->ship = ' ';
}
int Win_Game(State *state){
    return state->Clerics == 0 && state->Demon==0 && state->ship =='B';
}
int Game_over(State *state){
    if (state->Clerics>Tank_Clerics || state->Demon>Tank_Demon || state->Demon<0 || state->Clerics <0)
    {
        return 1;
    }
    
    if (state->Clerics==state->Demon ||
    (state->Clerics == 0 && state->Demon <=Tank_Demon) ||
    (state->Clerics == Tank_Clerics && state->Demon <=Tank_Demon)){
    return 0;
    }
    return 1;
}
void print_State(State state){

    printf("\n%d -----:%d----:%c\n", state.Clerics, state.Demon, state.ship);
}
int compareStates(State state1, State state2){
    return (state1.Clerics == state2.Clerics && state1.Demon==state2.Demon && state1.ship==state2.ship);
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
int Move1Clerics(State cur_state, State *result){
    result->Demon = cur_state.Demon;
    if(cur_state.ship=='A'){
        result->Clerics=cur_state.Clerics -1;
        result->ship='B';
    }

    else if(cur_state.ship=='B'){
        result->Clerics = cur_state.Clerics+1;
        result->ship = 'A';
        }
    if(!Game_over(result))
        return 1;

    return 0;
}
int Move1Demon(State cur_state, State *result){
    result->Clerics = cur_state.Clerics;
    if(cur_state.ship=='A'){
        result->Demon=cur_state.Demon -1;
        result->ship='B';
    }

    else if(cur_state.ship=='B'){
        result->Demon = cur_state.Demon+1;
        result->ship = 'A';
    }
    if(!Game_over(result))
        return 1;

    return 0;
}
int Move2Clerics(State cur_state, State *result){
    result->Demon = cur_state.Demon;
    if(cur_state.ship=='A'){
        result->Clerics = cur_state.Clerics -2;
        result->ship = 'B';
    }
    else if(cur_state.ship=='B'){
        result->Clerics = cur_state.Clerics +2;
        result->ship = 'A';
    }
    if(!Game_over(result))
        return 1;
    return 0;
}
int Move2Demon(State cur_state, State *result){
    result->Clerics = cur_state.Clerics;
    if(cur_state.ship=='A'){
        result->Demon = cur_state.Demon -2;
        result->ship = 'B';
    }
    else if(cur_state.ship=='B'){
        result->Demon = cur_state.Demon +2;
        result->ship = 'A';
    }
    if(!Game_over(result))
        return 1;

    return 0;
}
int Move1C_1D(State cur_state, State *result){
    if(cur_state.ship=='A'){
        result->Clerics = cur_state.Clerics - 1;
        result->Demon = cur_state.Demon -1;
        result->ship = 'B';
    }
    else if (cur_state.ship == 'B'){
        result->Clerics = cur_state.Clerics + 1;
        result->Demon = cur_state.Demon +1;
        result->ship = 'A';
    }
    if(!Game_over(result))
        return 1;
    return 0;
}
int call_operator(State cur_state, State *result, int option)
{
    switch (option){
        case 1:
        return Move1Clerics(cur_state, result);
        case 2:
        return Move2Clerics(cur_state, result);
        case 3:
        return Move1Demon(cur_state, result);
        case 4:
        return Move2Demon(cur_state, result);
        case 5:
        return Move1C_1D(cur_state, result);
        default:
        printf("Error calls operators");
    return 0;
    }
}
typedef struct Node{
    State state;
    struct Node *Parent;
    int no_function;
}Node;
int find_State(State state,stack<Node*> OpenStack){
    while (!OpenStack.empty()){
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
        if(Win_Game(&node->state)){
            return node;
        }
        int opt;
        for(opt=1; opt<=5; opt++){
            State newstate;
            init_state(&newstate);
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
void print_WaysToGetGoal(Node* node){
    Node way[1000];
    int i=0;
    while (node->Parent != NULL){
        way[i]=*node;
        i++;
        node = node->Parent;
    }
    int j, no_action=0;
    way [i] = *node;
    for(j=i; j>=0; j--){
        printf("\nAction %d: %s ", no_action, action[way[j].no_function]);
        print_State(way[j].state);
        no_action++;
    }
}
int main(){
    State cur_state = {3, 3, 'A'};
    Node *p = DFS_Algorithm(cur_state);
    print_WaysToGetGoal(p);
return 0;
}
