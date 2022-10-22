#include<stdio.h>
#include<stdlib.h>
#include<queue>
using namespace std;



Node* BFS_Algorithm(State state){
    queue<Node*> Open_BFS;
    queue<Node*> Close_BFS;
    Node* root =(Node*)malloc(sizeof(Node));
    root->state=state;
    root->Parent=NULL;
    root->no_function=0;
    Open_BFS.push(root);
    while(!Open_BFS.empty()){
        Node* node=Open_BFS.front();
        Open_BFS.pop();
        Close_BFS.push(node);
        if(goal_check(&node->state)){
            return node;
        }
        int opt;
        for(opt=1; opt<=6; opt++){
            State newstate;
            makenull_State(&newstate);
            if(call_operator(node->state, &newstate, opt)){
                if(find_State(newstate, Close_BFS)|| find_State(newstate, Open_BFS))
                    continue;
                Node* newNode=(Node*) malloc(sizeof(Node));
                newNode->state=newstate;
                newNode->Parent=node;
                newNode->no_function=opt;
                Open_BFS.push(newNode);
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
    Node *p = BFS_Algorithm(cur_state);
    print_WaysToGetGoal(p);
	return 0;
}




