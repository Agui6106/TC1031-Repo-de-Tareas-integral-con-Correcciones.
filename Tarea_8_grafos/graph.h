/* =========================================== //
    Jose Alberto Aguilar Sanchez - A01735612
    Grafos y busquedas
// =========================================== */

#ifndef Graph_H
#define Graph_H

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;

// Clase principal Grafo
class Graph {
	private:
		//Variables
		int edgesList; // Lista
		int edgesMat; // Matriz
		int nodes; // Nodos
    	vector<int> *adjList; // Vecotr
		int *adjMatrix; // Matriz adjunta

	public:
		//Constructores
		Graph(int);
		Graph();

		// -- METODOS -- //

		// Creamos listas y matriz
		void addEdgeAdjList(int, int);
		void addEdgeAdjMatrix(int, int);

		void loadGraphList(string, int);
  		void loadGraphMat(string, int, int);
		
		// Metodos principales
		void sortAdjList();
		string printAdjList();
		string printAdjMat();
		string printAdjMat_clean();

		// -- DFS -- //
		string DFS(int, int);
		string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int>>&);

		// -- BFS -- //
		string BFS(int, int);
		string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int>>&);

		// Contiene?
		bool contains(list<int>, int);

		// Guardamos el path y los nodos vistados
		string print_visited(list<int>);
		string print_path(vector<vector<int>>&,int ,int);
};

// Construcotr por omision
Graph::Graph() {
	edgesList = edgesMat = 0;
}

// Construcotr por paramatros 
Graph::Graph(int n) {
	nodes = n;
	adjList = new vector<int>[nodes];
	adjMatrix = new int [nodes*nodes];

	for (int i = 0; i < nodes*nodes; i++) adjMatrix[i] = 0;

	edgesList = edgesMat = 0;
}

// Cargamos la lista del grafo
void Graph::loadGraphList(string data, int a){
	adjList = new vector<int>[a];
	nodes = a;
	int u, v, i = 0;
	while ( i < data.size()) {
			u = (int)data[i+1] - 48;
			v = (int)data[i+3] - 48;
			i = i + 6;
			addEdgeAdjList(u,v);
	}
	sortAdjList();
}

// Cargamos la matriz del grafo
void Graph::loadGraphMat(string data, int a, int b){
	adjMatrix = new int [a*b];
	nodes = a;
	for (int i = 0; i < a*b; i++)
		adjMatrix[i] = 0;
	int u, v, i = 0;
	while (i < data.size()) {
		u = (int)data[i+1] - 48;
		v = (int)data[i+3] - 48;
		i = i + 6;
		addEdgeAdjMatrix(u,v);
	}
}

// Agregamos un valor a la lista
void Graph::addEdgeAdjList(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
	edgesList++;
}

// Agregamos un valor a la matriz
void Graph::addEdgeAdjMatrix(int u, int v){
	adjMatrix[u*nodes+v] = 1;
	adjMatrix[v*nodes+u] = 1;
	edgesMat++;
}

// Regresamos la lista
string Graph::printAdjList(){
	  stringstream aux;
		for (int i = 0; i < nodes; i++){
	        aux << "vertex "
	             << i << " :";
	        for (int j = 0; j < adjList[i].size(); j ++){
							 aux << " " << adjList[i][j];
					}
	        aux << " ";
    }
		return aux.str();

}

// Ordenamos la lista
void Graph::sortAdjList(){
	for (int i = 0; i < nodes; i++)
		sort(adjList[i].begin(),adjList[i].end());
}

// Regresamnos la matriz
string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
	   for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
		 }
  }
	return aux.str();
}

// Imprimimos la matriz de manera legible
string Graph::printAdjMat_clean(){
	stringstream aux;
	aux << "\n nodes \t|";
	for (int i = 0; i < nodes; i++){
			aux << "\t" << i ;
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
			aux << "__________";
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
		 aux << i << "\t|";
	   for (int j = 0; j < nodes; j++){
			 aux << "\t" << adjMatrix[i*nodes+j];
		 }
	   aux << "\n";
  }
	return aux.str();
}

//DFS
// Utilizamos un Stack como auxiliar para guardar los nodos que se visitaron
string Graph::DFS(int start, int goal){
	stack<int> st;
	list<int> visited;
	vector<vector<int>> paths(nodes, vector<int>(1,0));
	st.push(start);
	string ans = depthHelper(start, goal, st, visited, paths);
	ans += print_path(paths, start, goal);
	return ans;
}

// Recorremos todo el grafo
string Graph::depthHelper(int current,
						  int goal,
						  stack<int> &st,
						  list<int> &visited,
						  vector<vector<int>> &paths) {
	if (current == goal) {
		return print_visited(visited);
	} else if (st.empty()) {
		return " node not found";
	} else {
		current = st.top();
		st.pop();
		visited.push_back(current);
		for (int i = 0; i < adjList[current].size(); i++) {
			if (!contains(visited, adjList[current][i])) {
				st.push(adjList[current][i]);
				paths[adjList[current][i]][0] = current;
			}
		}
		return depthHelper(current, goal, st, visited, paths);
	}
	
}

//BFS
// Guardamos todos los nodos visitados en una cola
string Graph::BFS(int start, int goal) {
	queue<int> qu;
	list<int> visited;
	vector<vector<int>> paths(nodes, vector<int>(1,0));
	qu.push(start);
	visited.push_back(start);
	string ans = breadthHelper(start, goal, qu, visited, paths);
	ans += print_path(paths, start, goal);
	return ans;
}

//Metodo auxiliar de BFS, recorremos el grafo en su anchura
string Graph::breadthHelper(int current,
							int goal,
							queue<int> &qu,
							list<int> &visited,
							vector<vector<int>> &paths) {
	if (current == goal) {
		return print_visited(visited);
	} else if (!qu.empty()) {
		current = qu.front();
		qu.pop();
		for (int i = 0; i < adjList[current].size(); i++) {
			if (!contains(visited, adjList[current][i])) {
				qu.push(adjList[current][i]);
				visited.push_back(adjList[current][i]);
				paths[adjList[current][i]][0] = current;
				if (adjList[current][i] == goal) return print_visited(visited);
			}
		}
		return breadthHelper(current, goal, qu, visited, paths);
	}

	return " node not found";
}

// Contiene? (Para revisar si ya pasamos por ese nodo en las listas)
bool Graph::contains(list<int> ls, int node){
		list<int>::iterator it;
		it = find(ls.begin(), ls.end(), node);
		if(it != ls.end())
			return true;
		else
			return false;
}

// Guardamos el path y los nodos vistados //

// Imprimimos los vistados
string Graph::print_visited(list<int> q){
	stringstream aux;
	aux << "visited: ";
	while (!q.empty()){
		aux << q.front() << " ";
		q.pop_front();
    }
	return aux.str();
}

// Imprimimos el camino tomado
string Graph::print_path(vector<vector <int>> &path, int start, int goal){
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	stringstream aux;
	aux  << "path:";
	while (node != start) {
		reverse.push(node);
    	node = path[node][0];
    }
	reverse.push(start);
	while (!reverse.empty()) {
		aux << " " << reverse.top() ;
		reverse.pop();
    }
	return aux.str();
}


#endif