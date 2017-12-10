/*
 * SupermarketManager.cpp
 *
 *  Created on: 1 Apr 2017
 *      Author: ZeLuis
 */

#include "SupermarketManager.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "Utils.h"

using namespace std::chrono;

SupermarketManager::SupermarketManager()
{

}

void SupermarketManager::populateGraph(){
	for(unsigned int i = 0; i < clientList.size(); i++){
		graph.addVertex(clientList[i]);
	}

	for(unsigned int i = 0; i < marketList.size(); i++){
		graph.addVertex(marketList[i]);
	}
}

void SupermarketManager::makeGraph()
{
	srand(time(NULL));
	vector <string> streets;
	vector <string> chains;
	vector <string> districts;
	string filename, temp;

	//fulfill vector with street names
	filename = "graphs/streets.txt";
	ifstream streetFile;
	streetFile.open(filename);
	while(getline(streetFile, temp))
		streets.push_back(temp);
	streetFile.close();

	//fulfill vector with chain names
	filename = "graphs/cadeias.txt";
	ifstream chainFile;
	chainFile.open(filename);
	while(getline(chainFile, temp))
		chains.push_back(temp);
	chainFile.close();

	//fulfill vector with district names
	filename = "graphs/districts.txt";
	ifstream districtFile;
	districtFile.open(filename);
	while(getline(districtFile, temp))
		districts.push_back(temp);
	chainFile.close();

	filename = "graphs/";
	cout << "Name of the graph file to create: ";
	cin >> temp;
	cin.ignore(1000, '\n');
	filename += temp;

	int numClients;
	cout << "Number of clients (max. 1000): ";
	numClients = readNumber(1,1000);

	int numSupermarkets;
	cout << "Number of supermarkets (max. 50): ";
	numSupermarkets = readNumber(1,50);

	int numEdges;
	int maxEdges = (numClients+numSupermarkets)*(numClients+numSupermarkets-1);
	cout << "Number of edges (max. " << maxEdges << "): ";
	numEdges = readNumber(0,maxEdges);

	ofstream file;
	file.open(filename);

	file << "//Nr clients\n";
	file << numClients << "\n";
	file << "//1 supermarket per line (nr of trucks)\n";

	int cont = 0;
	while(cont < numSupermarkets)
	{
		file << rand()%10 + 1 << " " << chains[rand()%chains.size()] << endl;
		cont++;
	}


	file << "//Edges (src, dest, weight, street, district)\n";

	cont = 0;
	vector<AuxEdge> edges;
	int src, dest, w;
	int numVertices = numClients+numSupermarkets;
	while(cont < numEdges)
	{
		if(cont>=maxEdges/2)
		{ //reverse the existing edges
			for(int i = 0; i<edges.size() && cont<numEdges; i++)
			{
				file << edges[i].dest << " " << edges[i].src << " " << edges[i].w << " " << edges[i].rua << " - " << edges[i].distrito << "\n";
				cont++;
			}
		}
		else{
			AuxEdge e;
			do{
				src = rand()%numVertices + 1;
				do{
					dest = rand()%numVertices + 1;
				}
				while(dest==src);
				w = rand()%10 + 1;
				e.src = src;
				e.dest = dest;
				e.w = w;
				e.distrito = districts[rand()%districts.size()];
				e.rua = "Rua";
				do{
					e.rua += " " + streets[rand()%streets.size()];
				}
				while(rand()%2 == 0);
			}
			while(e.exists(edges));
			edges.push_back(e);
			file << e.src << " " << e.dest << " " << e.w << " " << e.rua << " - " << e.distrito << "\n";
			cont++;
		}
	}
	file << "//This is here for graph population";
}

void SupermarketManager::loadGraph(){
	ifstream file;
	string filename = "";

	while(!file.is_open())
	{
		filename = "graphs/";
		cout << "Insert the desired graph file name (.txt):";
		string temp;
		cin >> temp;
		cin.ignore(1000, '\n');
		filename += temp;
		file.open(filename);
	}

	graph = Graph<NodeObject*>();
	clientList.resize(0);
	marketList.resize(0);
	Client* c = new Client();
	c->resetIdCounter();

	int stage = 0;
	int numberRead = 0, numberRead2 = 0;
	double numberRead3 = 0;
	string rua;
	string cadeia;
	string distrito;
	string line, temp;
	stringstream sstream;
	std::size_t pos;

	while(getline(file, line)){
		if(line[0] != '/'){
			switch(stage){
			case 1:
			{
				sstream << line;
				sstream >> numberRead;
				sstream.str("");
				sstream.clear();
				for(int i = 0; i < numberRead; i++){
					Client * c = new Client();
					clientList.push_back(c);
				}
				break;
			}
			case 2:
			{
				pos = line.find(" ");
				temp = line.substr(0, pos);
				line = line.substr(pos + 1);
				cadeia = line;
				sstream << temp;
				sstream >> numberRead;
				sstream.str("");
				sstream.clear();
				Supermercado* s = new Supermercado(numberRead, cadeia);
				marketList.push_back(s);
				break;
			}

			case 3:
			{
				pos = line.find(" ");
				temp = line.substr(0, pos);
				line = line.substr(pos + 1);
				sstream << temp;
				sstream >> numberRead;
				sstream.str("");
				sstream.clear();

				pos = line.find(" ");
				temp = line.substr(0, pos);
				line = line.substr(pos + 1);
				sstream << temp;
				sstream >> numberRead2;
				sstream.str("");
				sstream.clear();

				pos = line.find(" ");
				temp = line.substr(0, pos);
				line = line.substr(pos + 1);
				sstream << temp;
				sstream >> numberRead3;
				sstream.str("");
				sstream.clear();

				pos = line.find("-");
				temp = line.substr(0, pos-1);
				line = line.substr(pos + 2);
				rua = temp;

				distrito = line;

				NodeObject* node1;
				NodeObject* node2;
				for(unsigned int i = 0; i < clientList.size(); i++)
				{
					if(clientList[i]->getID() == numberRead)
					{
						node1 = clientList[i];
					}
					else if(clientList[i]->getID() == numberRead2)
					{
						node2 = clientList[i];
					}
				}
				for(unsigned int i = 0; i < marketList.size(); i++)
				{
					if(marketList[i]->getID() == numberRead)
					{
						node1 = marketList[i];
					}
					else if(marketList[i]->getID() == numberRead2)
					{
						node2 = marketList[i];
					}
				}
				graph.addEdge(node1, node2, numberRead3, rua, distrito);
				break;
			}
			}
		}
		else{
			stage++;
			if(stage == 3){
				populateGraph();
			}
		}
	}
	file.close();
	this->showInfo();
}

void SupermarketManager::showInfo()
{
	cout << "Number of clients: "<< clientList.size()<<endl;
	cout << "Number of supermarkets: "<< marketList.size()<<endl;
	for(unsigned int i = 0; i< marketList.size();i++)
		cout << "	ID: "<< marketList[i]->getID() << ", number of trucks: "
		<< marketList[i]->getNumberTrucks() << ", chain: " << marketList[i]->getCadeiaSupermercado() << endl;

	//analise da densidade
	int numVertices = graph.getVertexSet().size();
	int numEdges = 0;
	for(int i = 0; i < numVertices;i++)
	{
		numEdges += graph.getVertexSet()[i]->getNumEdges();
	}
	if(magnitudeOrder(numEdges) < magnitudeOrder(numVertices*numVertices))
		cout << "The graph is sparse" << endl;
	else
		cout << "The graph is dense" << endl;

	if(numEdges == numVertices*(numVertices-1))
		cout << "The graph is complete" << endl;

	//analise da conetividade
	bool flag = true;
	for(int i = 0; i < numVertices ;i++)
	{
		graph.dijkstra(graph.getVertexSet()[i]);
		for(int j = 0; j < numVertices; j++)
		{
			if(graph.getVertexSet()[j]->getDist()== INT_INFINITY && j!=i)
			{
				flag = false;
			}
		}
	}
	if(flag)
		cout << "The graph is strongly connected" << endl;

	stronglyConnectedComponents();
}

Client* SupermarketManager::getClient(int id){
	Client* ret = nullptr;
	for(unsigned int i = 0; i < clientList.size(); i++){
		if(clientList[i]->getID() == id){
			ret = clientList[i];
		}
	}
	return ret;
}


void SupermarketManager::makeRequest(){
	int clientID;
	int requestSize;

	clientID = inputClientID();
	Client* client = getClient(clientID);

	cout << "Request size (max " << MAX_REQUEST_SIZE << "): ";
	requestSize = readNumber(1, MAX_REQUEST_SIZE);
	Pedido *request = new Pedido(client, requestSize);
	Supermercado* s = findNearestSupermarket(client);
	if(s == nullptr)
	{
		cout << "There are no supermarkets accessible to this client." << endl;
		return;
	}
	Vertex<NodeObject*>* clientVertex = graph.getVertex(client);
	request->setDistance(clientVertex->getDist());
	s->addRequest(request);

	cout << "The supermarket in charge for this client is: " << s->getID() << endl;
	cout << "Number of pending requests for this supermarket: " << s->getRequestNumber() << endl;
}

void SupermarketManager::makeRandomRequests()
{
	srand(time(NULL));

	for(int i = 0; i < clientList.size();i++)
	{
		int requestSize = rand()%50+1;
		Client* client = getClient(clientList[i]->getID());
		Pedido *request = new Pedido(clientList[i], requestSize);
		Supermercado* s = findNearestSupermarket(client);
		if(s != nullptr)
		{
			Vertex<NodeObject*>* clientVertex = graph.getVertex(client);
			request->setDistance(clientVertex->getDist());
			s->addRequest(request);
		}
	}
}

int SupermarketManager::inputClientID()
{
	bool valid = false;
	int id;
	while(!valid)
	{
		cout << "Client ID: ";
		id = readNumber(0,std::numeric_limits<int>::max());
		for(unsigned int i = 0; i < this->clientList.size(); i++)
		{
			if(clientList[i]->getID()==id) {
				valid = true;
			}
		}
	}
	return id;
}

Supermercado* SupermarketManager::findNearestSupermarket(Client* client){
	Vertex<NodeObject*>* clientVertex = graph.getVertex(client);
	int minDist = INT_INFINITY;
	Supermercado* s = nullptr;

	for(unsigned int i = 0; i < marketList.size(); i++){
		Vertex<NodeObject*>* marketVertex = graph.getVertex(marketList[i]);
		graph.dijkstra(marketVertex);
		if(clientVertex->getDist() < minDist){
			minDist = clientVertex->getDist();
			s = marketList[i];
		}
	}

	return s;
}

void SupermarketManager::deliverAllRequests(int choice){
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	for(unsigned int i = 0; i < this->marketList.size(); i++){
		Vertex<NodeObject*>* marketVertex = graph.getVertex(marketList[i]);
		graph.dijkstra(marketVertex);
		cout << "Supermarket " << marketList[i]->getID() << ":" << endl;
		marketList[i]->deliverRequests(graph, choice);
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(t2-t1).count();

	cout << "Execution time: " << duration << " microseconds" << endl;
}

void SupermarketManager::stronglyConnectedComponents()
{
	vector<NodeObject*> vec;

	vec = graph.dfs();

	// Create a reversed graph
	Graph<NodeObject*> gr = graph.getTranspose();

	for(int i = 0; i < gr.getVertexSet().size();i++)
	{
		gr.getVertexSet()[i]->setVisited(false);
	}

	cout << "The following are strongly connected components: " << endl;
	for(int i = vec.size()-1; i >=0; i--)
	{
		Vertex<NodeObject*> *v = gr.getVertex(vec[i]);
		if(!v->getVisited())
		{
			gr.dfsPrint(v);
			cout << endl;
		}
	}
}

bool SupermarketManager::kmpMatcher(string T, string P){
	int n =T.length();
	int m = P.length();
	vector<int>pi = prefixComputation(P);
	int q = -1;
	for(int i = 0; i<n;i++){
		while(q>-1 && P[q+1]!=T[i])
			q = pi[q];
		if(P[q+1]==T[i])
			q++;
		if(q==m-1)
			return true;
	}
	return false;
}
vector<int> SupermarketManager::prefixComputation(string P){
	int m = P.length();
	vector<int> pi(m);
	int k = -1;
	pi[0]=-1;
	for(int i = 1; i < m;i++){
		while(k>-1 && P[k+1]!=P[i]){
			k = pi[k];
		}
		if(P[k+1] == P[i]){
			k = k+1;
		}
		pi[i] = k;
	}
	return pi;
}

int SupermarketManager::editDistance(string T, string P){
	int D[T.length() + 1];
	for(int j = 0; j <= T.length(); j++){
		D[j] = j;
	}

	int old, neww;
	for(int i = 1; i <= P.length(); i++){
		old = D[0];
		D[0]=i;
		for(int j = 1; j <= T.length(); j++){
			if(P[i-1] == T[j-1]){
				neww = old;
			}
			else{
				neww = 1 + min(min(old, D[j]), D[j-1]);
			}
			old = D[j];
			D[j] = neww;
		}
	}
	return D[T.length()];
}

void SupermarketManager::checkSupermarketExistence(Edge<NodeObject*> e){
	bool foundSrc = false;
	bool foundDest = false;
	cout << "Supermercados: " << endl;
	for(int i = 0; i<marketList.size() && (!foundSrc || !foundDest); i++) {
		if(!foundSrc && *(e.getSrc()->getInfo())==*marketList[i]){
			cout << "ID: "<< marketList[i]->getID() << ", Cadeia: " << marketList[i]->getCadeiaSupermercado() << endl;
			foundSrc = true;
		}
		if(!foundDest && *(e.getDest()->getInfo())==*marketList[i]){
			cout << "ID: "<< marketList[i]->getID() << ", Cadeia: " << marketList[i]->getCadeiaSupermercado() << endl;
			foundDest = true;
		}

	}
	if(!foundSrc && !foundDest){
		cout << "Nao existem." << endl;
	}
	cout << endl;
}

void SupermarketManager::exactSearchStreet(){
	vector<string> ruas;
	cout << "Introduce the desired street name to search for: ";
	string street;
	getline(cin, street);

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	vector<Edge<NodeObject*>> edges = graph.getEdges();
	bool foundFlag = false;

	for(int i = 0; i<edges.size(); i++) {
		if(kmpMatcher(edges[i].getRua(), street) && find(ruas.begin(), ruas.end(), edges[i].getRua()) == ruas.end()){
			cout << edges[i].getRua() << endl;
			checkSupermarketExistence(edges[i]);
			ruas.push_back(edges[i].getRua());
			foundFlag = true;
		}
	}
	if(!foundFlag)
		cout << "Lugar desconhecido.\n";

	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(t2-t1).count();

	cout << "Execution time: " << duration << " microseconds" << endl;
}

void SupermarketManager::approximateSearchStreet(){
	vector<string> ruasAnalisadas;
	priority_queue<pair<Edge<NodeObject*>*, int>, vector<pair<Edge<NodeObject*>*, int>>, ComparisonStreetSimilarity> ruas;
	cout << "Introduce the desired street name to search for: ";
	string street;
	getline(cin, street);

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	vector<Edge<NodeObject*>> edges = graph.getEdges();
	int distance;
	for(int i = 0; i<edges.size(); i++) {
		if(find(ruasAnalisadas.begin(), ruasAnalisadas.end(), edges[i].getRua()) == ruasAnalisadas.end()){
			distance = editDistance(edges[i].getRua(), street);
			ruasAnalisadas.push_back(edges[i].getRua());
			ruas.push(pair<Edge<NodeObject*>*,int> (&edges[i], distance));
		}
	}

	int i = 0;
	int size = ruas.size();
	int DISTANCIA_MAXIMA = street.length()/5;
	while(i<size){
		if(ruas.top().second <= DISTANCIA_MAXIMA){
			cout << ruas.top().first->getRua() << " - ";
			checkSupermarketExistence(*(ruas.top().first));
			ruas.pop();
			i++;
		}
		else if(i == 0){ //caso nao haja nenhum com distancia suficiente, é impresso a primeira rua apenas
			cout << ruas.top().first->getRua() << " - ";
			checkSupermarketExistence(*(ruas.top().first));

			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(t2-t1).count();
			cout << "Execution time: " << duration << " microseconds" << endl;

			return;
		}
		else{
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(t2-t1).count();
			cout << "Execution time: " << duration << " microseconds" << endl;

			return;
		}
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2-t1).count();
	cout << "Execution time: " << duration << " microseconds" << endl;
}

void SupermarketManager::checkStreet(NodeObject* market){
	vector<string> ruas;
	cout << "Street(s): " << endl;
	vector<Edge<NodeObject*>> edges = graph.getEdges();
	for(int i = 0; i< edges.size();i++)
	{
		if(find(ruas.begin(), ruas.end(), edges[i].getRua()) == ruas.end() && (*market == *(edges[i].getDest()->getInfo()) || *market == *(edges[i].getSrc()->getInfo()))){
			cout << edges[i].getRua() << endl;
			ruas.push_back(edges[i].getRua());
		}
	}
	cout << endl;
}

void SupermarketManager::exactSearchSupermarket(){
	cout << "Introduce the desired supermarkets chain to search for: ";
	string chain;
	getline(cin, chain);

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	bool foundFlag = false;
	for(int i = 0; i< marketList.size(); i++) {
		if(kmpMatcher(marketList[i]->getCadeiaSupermercado(), chain)){
			cout << marketList[i]->getCadeiaSupermercado() << ", ID: " << marketList[i]->getID() << endl;
			checkStreet(marketList[i]);
			foundFlag = true;
		}
	}
	if(!foundFlag)
		cout << "Lugar desconhecido.\n";

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2-t1).count();
	cout << "Execution time: " << duration << " microseconds" << endl;
}

void SupermarketManager::approximateSearchSupermarket(){
	priority_queue<pair<NodeObject*, int>, vector<pair<NodeObject*, int>>, ComparisonMarketSimilarity> markets;
	cout << "Introduce the desired supermarkets chain name to search for: ";
	string chain;
	getline(cin, chain);

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	int distance;
	for(int i = 0; i<marketList.size(); i++) {
		distance = editDistance(marketList[i]->getCadeiaSupermercado(), chain);
		markets.push(pair<NodeObject*,int> (marketList[i], distance));
	}

	int i = 0;
	int size = markets.size();
	int DISTANCIA_MAXIMA = chain.length()/5;
	while(i<size){
		if(markets.top().second <= DISTANCIA_MAXIMA){
			cout << ((Supermercado*)markets.top().first)->getCadeiaSupermercado() << ", ID: " << ((Supermercado*)markets.top().first)->getID() << endl;
			checkStreet(markets.top().first);
			markets.pop();
			i++;
		}
		else if(i == 0){ //caso nao haja nenhum com distancia suficiente, é impresso a primeira rua apenas
			cout << ((Supermercado*)markets.top().first)->getCadeiaSupermercado() << ", ID: " << ((Supermercado*)markets.top().first)->getID() << endl;
			checkStreet(markets.top().first);

			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(t2-t1).count();
			cout << "Execution time: " << duration << " microseconds" << endl;

			return;
		}
		else{
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(t2-t1).count();
			cout << "Execution time: " << duration << " microseconds" << endl;

			return;
		}
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2-t1).count();
	cout << "Execution time: " << duration << " microseconds" << endl;
}

void SupermarketManager::exactSearchDistrict(){
	vector<string> ruas;
	cout << "Introduce the desired district name to search for: ";
	string district;
	getline(cin, district);

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	vector<Edge<NodeObject*>> edges = graph.getEdges();
	bool foundFlag = false;
	for(int i = 0; i<edges.size(); i++) {
		if(kmpMatcher(edges[i].getDistrito(), district) && find(ruas.begin(), ruas.end(), edges[i].getRua()) == ruas.end()){
			cout << edges[i].getRua() << " - " << edges[i].getDistrito() << endl;
			checkSupermarketExistence(edges[i]);
			ruas.push_back(edges[i].getRua());
			foundFlag = true;
		}
	}
	if(!foundFlag)
		cout << "Distrito desconhecido.\n";

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2-t1).count();
	cout << "Execution time: " << duration << " microseconds" << endl;
}
