#include <stdio.h>
#include <stdlib.h>
#define MAX 5
struct Vert
{
	char word;
          bool visit;
};
int queue[MAX];               //queue variables
int rear = -1,front = 0,queueCount = 0;
struct Vert* lstVert[MAX];     //graph variables //array of vertices
int adjMat[MAX][MAX];             //adjacency matrix
int vCount = 0;                 //vertex count
void insert(int data)                //queue functions
{
	queue[++rear] = data;
          queueCount++;
}
int removeData()
{
	queueCount--;
          return queue[front++]; 
}
bool isQueueEmpty()
{
	return queueCount == 0;
}
void addVert(char word)            //graph functions //add vertex to the vertex list
{
	struct Vert* vert=(struct Vert*)malloc(sizeof(struct Vert));
          vert->word =word;  
          vert->visit = false;     
          lstVert[vCount++] = vert;
}
void addEdge(int start,int end)        //add edge to edge array
{
	adjMat[start][end] = 1;
          adjMat[end][start] = 1;
}
void display(int vertIndex)    //display the vertex
{
	printf("%c ",lstVert[vertIndex]->word);
}       
int AdjUnvisitVert(int vertIndex)       //get the adjacent unvisited vertex
{
	int i;
	for(i = 0; i<vCount; i++) 
	{
		if(adjMat[vertIndex][i]==1 && lstVert[i]->visit==false)
                    return i;
          }
	return -1;
}
void bfs() 
{
	int i;
	lstVert[0]->visit = true;       //mark first node as visited
          display(0);                     //display the vertex
          insert(0);                            //insert vertex index in queue
          int unvisitVert;
          while(!isQueueEmpty())
	{
		int tempVert=removeData();     //get the unvisited vertex of vertex which is at front of the queue
                    while((unvisitVert=AdjUnvisitVert(tempVert))!=-1)   //no adjacent vertex found
                    {
	          	lstVert[unvisitVert]->visit = true;
                              display(unvisitVert);
                              insert(unvisitVert);               
                    }
          }   
          for(i = 0;i<vCount;i++)                 //queue is empty, search is complete, reset the visited flag        
          {
		lstVert[i]->visit=false;
          }    
}
int main()
{
	int i, j;
	for(i = 0; i<MAX; i++) // set adjacency
	{
		for(j = 0; j<MAX; j++) // matrix to 0
                    adjMat[i][j] = 0;
          }
          addVert('S');   // 0
          addVert('A');   // 1
          addVert('B');   // 2
          addVert('C');   // 3
          addVert('D');   // 4
          addEdge(0, 1);    // S - A
          addEdge(0, 2);    // S - B
          addEdge(0, 3);    // S - C
          addEdge(1, 4);    // A - D
          addEdge(2, 4);    // B - D
          addEdge(3, 4);    // C - D
	printf("\nBreadth First Search: ");
          bfs();
	return 0;
}
