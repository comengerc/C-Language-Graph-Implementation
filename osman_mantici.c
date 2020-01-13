

// 				OSMAN MANTICI
//  STUDENT NUMBER: 150117505
// DATA STRUCTURES PROJECT #3


#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 


typedef enum
{
    false = ( 1 == 0 ),
    true = ( ! false )
} bool;
  
// A structure to represent an adjacency list node 
	struct AdjListNode {
	 
    	int id;
		char *dest; 
    	struct AdjListNode *next; 
	}; 
  
// A structure to represent an adjacency list 
	struct AdjList {
	 
    	struct AdjListNode *head;  
	}; 
  
// A structure to represent a graph. A graph is an array of adjacency lists. 
// Size of array will be V (number of vertices in graph) 
	struct Graph {
	 
    	int V; 
    	struct AdjList* array; 
	}; 
  
// A utility function to create a new adjacency list node 
	struct AdjListNode* newAdjListNode(int dest) {
	 
		struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
		newNode->dest = dest; 
		newNode->next = NULL; 
		return newNode; 
	} 
  
// A utility function that creates a graph of V vertices 
	struct Graph* createGraph(int V) {
	 
		struct Graph* graph =  (struct Graph*) malloc(sizeof(struct Graph)); 
		graph->V = V; 
  
    // Create an array of adjacency lists.  Size of array will be V 
		graph->array =  (struct AdjList*) malloc(V * sizeof(struct AdjList)); 
  
    // Initialize each adjacency list as empty by making head as NULL 
		int i; 
		for (i = 0; i < V; ++i) {
		
			graph->array[i].head = NULL;
		}
		return graph; 
	} 
  
// Adds an edge to an undirected graph 
	void addEdge(struct Graph* graph, int src, int dest) { 
    // Add an edge from src to dest.  A new node is added to the adjacency list of src.  The node is added at the begining 
		struct AdjListNode* newNode = newAdjListNode(dest); 
		newNode->next = graph->array[src].head; 
		graph->array[src].head = newNode;
	} 
  
// A utility function to print the adjacency list representation of graph 


	void insertlink(char* name, int id, struct AdjListNode** head) {
		
		struct AdjListNode *temp= (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
		temp = *head;
		struct AdjListNode *newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode)); 
			
		newNode->dest = name;
		newNode->id = id;
		newNode->next = NULL;
		
		if(*head == NULL){
			*head = newNode;
			return ;
		}
		
		while(temp->next!= NULL){
			temp = temp->next;
		}
		
		temp->next = newNode;
		return;	
	}


	int getIdByName(char *name, struct AdjListNode **head) {
	
		struct AdjListNode *temp = *head;
	
		int ID=0;
		while(temp!=NULL){
		
			if(strcmp(temp->dest,name)==0){
				ID=temp->id;
				break;
			}
			temp=temp->next;
		}
		return ID;
	}

	char* getNameById(struct AdjListNode **head, int Id) {
	
		struct AdjListNode *temp = *head;
	
		char* name; 
		while(temp!=NULL){
			
			if(temp->id==Id){
				name = temp->dest;
				break;
			}
			temp=temp->next;
		}
		return name;
	}


	void printAdjList(struct Graph* graph, struct AdjListNode** head) { 

		printf("There is the Adjacency List of each person:\n");
		
		struct AdjListNode *temp = *head;
		
	    int v; 
    	for (v = 0; v < graph->V; ++v) { 
    	
	        struct AdjListNode* pCrawl = graph->array[v].head; 
    	    printf("\n Adjacency list of vertex %s\n ", getNameById(&temp, v)); 
        	
			while (pCrawl) { 
	
	            printf("-> %s", getNameById(&temp, pCrawl->dest)); 
				pCrawl = pCrawl->next; 
        	} 
			printf("\n"); 
    	} 
	} 


	int** printAdjMatrix(struct Graph* graph, struct AdjListNode** head, int v ) {
	
		printf("\nThere is the Adjacency Matrix of the graph:\n");
		
		struct AdjListNode *temp = *head;
		
		int **matrix = (int **)malloc(sizeof(int *)*v);
		
		int i=0;
		int j=0;
		int k =0;
		
		for(i=0; i<v; i++) {
			matrix[i]=(int *)malloc(sizeof(int)*v);
			for(j=0; j<v; j++) {
				matrix[i][j]=0;
			}
		}
		
		printf("\t");
		for(i=0; i<v; i++) {
					
			printf("%s\t", getNameById(&temp, i));
			
		}
		
		printf("\n");
		for(i=0; i<v; i++) {
			
			struct AdjListNode* pCrawl = graph->array[i].head;
			printf("%s\t", getNameById(&temp, i));
			
			while(pCrawl) { 

				k=pCrawl->dest;
				pCrawl = pCrawl->next;	
				matrix[i][k]=1;
        	}
        	
        	for(j=0; j<v; j++) {
        		
        		if(matrix[i][j]==1) {
        			printf("%d\t", matrix[i][j]);
				}
				else{
					printf("%d\t", matrix[i][j]);
				}
			}        	
			printf("\n");
		}
		printf("\n");
		
		return matrix;
	}
	
	
	double* computeDegreeCentrality(struct Graph* graph, int v ) {
		
		double* DegreeCent = (double *)malloc(sizeof(double)*v);
		double count=0;

		int i=0;
		for(i=0; i<v; i++) {
			
			struct AdjListNode* pCrawl = graph->array[i].head;
			
			count =0;
			while(pCrawl) {
			
				pCrawl = pCrawl->next;	
				count++;
			}
			count = count/(v-1); 			
			DegreeCent[i] = count;
		}
		return DegreeCent;
	}
	
	
	int minDistance(int dist[], bool sptSet[]) { 
  
		// Initialize min value 
		int min = INT_MAX, min_index; 
		int v;
		for (v = 0; v < 10; v++) {
		
			if (sptSet[v] == false && dist[v] <= min) {
			
				min = dist[v], min_index = v; 
   			}
   		}
		return min_index; 
	} 
   
   
	int printSolution(int dist[], int n) {
	 
		printf("Vertex   Distance from Source\n"); 
		int i;
		for (i = 0; i < n; i++) {
	
			printf("%d \t %d\n", i, dist[i]); 
		}
	}	 
   

	int shortestPath(int** graph, int src, int V) { 

		int total=0;
		int dist[V]; 
   
		bool sptSet[V]; 
   
     // Initialize all distances as INFINITE and stpSet[] as false 
	 	int i;
		for(i = 0; i < V; i++) {
		
        	dist[i] = INT_MAX, sptSet[i] = false; 
		}
     	// Distance of source vertex from itself is always 0 
		dist[src] = 0; 
   
		// Find shortest path for all vertices 
		int count;
		for(count = 0; count < V-1; count++) {
		 
			// Pick the minimum distance vertex from the set of vertices not 
			// yet processed. u is always equal to src in the first iteration. 
			int u = minDistance(dist, sptSet); 
   
			// Mark the picked vertex as processed 
			sptSet[u] = true; 
   
			// Update dist value of the adjacent vertices of the picked vertex. 
			int v;
			
			for(v = 0; v < V; v++)  {

				if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX  && dist[u]+graph[u][v] < dist[v]) {

					dist[v] = dist[u] + graph[u][v]; 
				}
			}
		} 
		
		int l=0;
		for(l=0; l<V; l++){
			
			total = total + dist[l] ; 
		}
		return total;
	} 
   
	
	double* computeClosenessCentrality( int** matrix, int v ) {
		
		int i=0;
		
		double* ClosenessCent = (double *)malloc(sizeof(double)*v);
		
		for(i=0; i<v; i++) {
			
			ClosenessCent[i] =    (  (double)(v-1)/(double)shortestPath(matrix, i, v) );
		}
		
		return ClosenessCent;
	}
	

// Driver program to test above functions 
	int main() { 

		FILE *fileptr;
		fileptr = fopen("input.txt", "r");
		
		char count[100];
		
		int count_line=0;
		
		while(!feof(fileptr)){
			
			fgets(count, 50, fileptr );
			count_line++;
		}
		fseek(fileptr, 0, SEEK_SET);
    
		char temp[60];
		int i=0;
		
		struct AdjListNode* HEAD =NULL ;

		struct AdjListNode* stabil ;
		stabil = HEAD;
			
		while(!feof(fileptr)) {
			
			fgets(temp, 60, fileptr );
			
			char* source = strdup(strtok(temp, "; "));	
			insertlink(source, i, &HEAD);
			i++;
		}
		fseek(fileptr, 0, SEEK_SET);


	    struct Graph* graph = createGraph(count_line); 
    
		while(!feof(fileptr)) {
			
			fgets(temp, 60, fileptr );


			char* source = strdup(strtok(temp, "\n"));
			
			char* source0 = strdup(strtok(source, "; "));

			int sourceId = getIdByName(source0, &HEAD);
			
			while(source!=NULL) {
		
				char* destination = strdup(strtok(NULL, ", "));
			
				if(destination==NULL){
					break;
				}
		
				int destinationId = getIdByName(destination, &HEAD);	
			
				if(strcmp(destination,"\n")==0){
					break;
				}	
				
				addEdge(graph, sourceId, destinationId);
			}
			i++;
		}
		fseek(fileptr, 0, SEEK_SET);		
		
		int v;
		v = graph->V ;
		
		int** adjMatrix;
		adjMatrix =	printAdjMatrix( graph, &HEAD, v);
		
		double* degreeCent;
		degreeCent = computeDegreeCentrality( graph, v);
		
		double* closenessCent;
		closenessCent = computeClosenessCentrality( adjMatrix, v );
		
		puts("Source\tDegree Centrality\tCloseness Centrality\tBetwenness Centrality");
	
		int x=0;
		for(x=0; x<v;x++){
			printf("%s\t\t", getNameById(&HEAD, x));
			printf("%.2f\t\t\t", degreeCent[x]);
			printf("%.2f", closenessCent[x] );
			printf("\n");
		}
			
		fclose(fileptr);
	    return 0; 	
	}
	
	
	

	
	
