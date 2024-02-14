#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define N 1000000 // Maximum number of nodes in the mound tree
#define THRESHOLD 50 // Maximum number of attempts to find a suitable insertion point
#define INF 1e9 // A very big integer, which will be returned as value for all empty mounds

typedef int T;


//Structure for nodes of linked lists

typedef struct LNode{
    T value;
    struct LNode* next;
} LNode;


//Structure for nodes of binary tree 

typedef struct MNode{
    LNode* list;
    bool dirty;
} MNode;


//Declaration of array based binary tree

MNode tree[N+1];

//Declaration and Initialization of depth of the tree

int depth = 0;


//Function to return value stored in first node of list pointed by given tree node

int val(MNode n) {
    if (n.list == NULL) {
        return INF;
    }
    return n.list->value;
}


//Function to return a random leaf index of the binary tree

int randLeaf() {
    return (rand() % (1 << (depth - 1))) + (1 << (depth - 1)); // offset + first leaf index
}


//Function to return the index of nth level ancestor of a leaf

int ancestor(int leaf, int n) {
    int tmp = leaf >> n;
    return tmp;
}


//Binary search on a path from a specific leaf to the root node 

int binarySearch(int leaf, T v)
{    
    int left = 0;           //0th level ancestor i.e. the leaf itself
    int right = depth-1;    //(depth - 1)th level ancestor i.e. the root node
    
    if(val(tree[ancestor(leaf, right)]) > v) //If the new node is smaller than the root
    {
        return ancestor(leaf, right);
    }

    while(left < (right-1))     //Binary search
    {
        int mid = (left+right)/2;
        if(val(tree[ancestor(leaf, mid)]) > v)
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }
    return ancestor(leaf, left);
}


//Function to find the node above which we can insert the new value

int findInsertPoint(T v) 
{
    int leaf;

    if(tree[1].list == NULL)  //If tree is empty
    {
        depth++;
        return 1;           //root index
    }

    //Limited attempts to find suitable leaf
    for (int attempts = 0; attempts < THRESHOLD; attempts++)
    {
        leaf = randLeaf();

        if (val(tree[leaf]) >= v) 
        {
            return binarySearch(leaf,v);
        }
    }

    //If attempts exceed, we return the either child of the last unsuitable leaf
    //Essentially, we add a new level to our tree
    depth++;
    return 2 * leaf + (rand() % 2);
}


//The insert function

void insert(T v)
{
    int c = findInsertPoint(v);

    LNode* new_node = (LNode*) malloc(sizeof(LNode));
    new_node->value = v;
    new_node->next = NULL;

    if (tree[c].list == NULL) //If the list at node was empty
    {
        tree[c].list = new_node;
    }

    else 
    {
        LNode* curr_node = tree[c].list;
        tree[c].list=new_node;
        new_node->next = curr_node;
    }
}


//The moundify function

void moundify(int n)
{
    if (n >= (1 << (depth-1)))  //If n is the leaf node
    {
        tree[n].dirty = false;
        return;
    }

    int l = 2 * n;      //Index of left child of n
    int r = 2 * n + 1;  //Index of right child of n

    if(tree[l].dirty == true){
        moundify(l);
    }

    if(tree[r].dirty == true){
        moundify(r);
    }

    //smallest contains the smallest value amongst the node n and its children      
    int smallest = n;   
    if ( l < (1 << depth) && val(tree[l]) < val(tree[smallest])) {
        smallest = l;
    }
    if ( r < (1 << depth) && val(tree[r]) < val(tree[smallest])) {
        smallest = r;
    }

    if (smallest != n)  //If a child is smaller than its parent
    {    
        //swap
        LNode* tmp = tree[n].list;
        tree[n].list = tree[smallest].list;
        tree[smallest].list = tmp;
        
        tree[smallest].dirty = true;
        moundify(smallest);
    }
    
    tree[n].dirty = false;
    return;
}


//Function to extract the minimum inserted value

T extractMin() 
{
    if (tree[1].list == NULL)   //If tree is empty
    {
        printf("Error: Mound is empty.\n");
        exit(1);
    }

    T retval = val(tree[1]);
    LNode* oldlist = tree[1].list;
    tree[1].list = tree[1].list->next;
    tree[1].dirty = true;
    
    moundify(1);
    free(oldlist);
    return retval;
}


//Function to read values for input

void readValues(char * name){
    FILE * fp;
    fp = fopen(name, "r");
    int value;
    int cnt=0;
    while(fscanf(fp, "%d\n", &value) != EOF){
        insert(value);
        cnt++;
    }
    fclose(fp);
}


//Function that repeatedly performs extractMin() operation
//& prints the extracted object each time,
//until all the objects in the mound are exhausted.

void extractAllValues(){
    
    FILE* out=fopen("output.txt","w");
    int cnt=0;
    while(tree[1].list != NULL){
        fprintf(out,"%d \n",extractMin());
        cnt++;
    }

    fclose(out);
    printf("Total number of elements: %d\n",cnt);
}


//The main function

int main(int argc, char* argv[]) {

    // Initialize tree to empty
    for (int i = 1; i <= N; i++) {
        tree[i].list = NULL;
        tree[i].dirty = false;
    }

    readValues(argv[1]);
    extractAllValues();
}