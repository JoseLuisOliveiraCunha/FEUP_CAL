/*
 * SupermarketManager.h
 *
 *  Created on: 1 Apr 2017
 *      Author: ZeLuis
 */

#ifndef SRC_SUPERMARKETMANAGER_H_
#define SRC_SUPERMARKETMANAGER_H_

#include "Graph.h"
#include "Client.h"
#include "Supermercado.h"
#include "Utils.h"
#include <iostream>

using namespace std;
/**
 * Classe que gere uma cadeia de supermercados e os seus clientes
 */
class SupermarketManager {
private:
	/**
	 * Grafo de n�s correspondestes aos clientes e supermercados.
	 */
	Graph<NodeObject*> graph;
	/**
	 * Vetor de apontadores para os clientes desta cadeia de supermercados.
	 */
	vector<Client*> clientList;
	/**
	 * Vetor de apontadores para os supermercados desta cadeia de supermercados.
	 */
	vector<Supermercado*> marketList;

public:
	/**
	 * Construtor por omissao
	 */
	SupermarketManager();
	/**
	 * Adiciona ao grafo os v�rtices correspondentes aos clientes e
	 * supermercados dos vetores clientList e marketList
	 */
	void populateGraph();
	/**
	 * Cria um grafo com um numero de clientes, supermercados
	 * e arestas introduzidos pelo utilizador.
	 */
	void makeGraph();

	/**
	 * Le de um ficheiro as informacoes necessarias para
	 * preencher o vetores clientList e marketList, adicionar os
	 * respetivos nos ao grafo e ainda as suas arestas.
	 */
	void loadGraph();
	/**
	 * Retorna um apontador para o cliente de ID dado.
	 *
	 * @param id ID do cliente
	 * @return um apontador para o cliente de ID dado
	 */
	Client* getClient(int id);
	/**
	 * Pede ao utilizador o ID do cliente e o tamanho do pedido que este cliente pretende efetuar.
	 * Em seguida, encontra o supermercado mais pr�ximo do cliente, adicionando o pedido �
	 * fila de prioridade de pedidos desse supermercado.
	 * Caso nenhum supermercado desta cadeia tenha um caminho at� ao cliente, a fun��o mostra
	 * uma mensagem de erro e retorna.
	 */
	void makeRequest();
	/**
	 * Atribui um pedido de tamanho aletorio a todos os clientes.
	 */
	void makeRandomRequests();
	/**
	 * Retorna o supermercado mais proximo do cliente dado.
	 * Caso nenhum supermercado desta cadeia tenha um caminho at� ao cliente,
	 * a fun��o retorna 'nullptr'.
	 *
	 * @return o supermercado mais proximo do cliente dado
	 */
	Supermercado* findNearestSupermarket(Client* client);

	/**
	 * Pede continuamente ao utilizador o ID de um cliente at� que este corresponda
	 * ao ID de um cliente que exista no vetor clientList.
	 * Retorna esse ID, garantidamente v�lido.
	 *
	 * @return ID do cliente validado
	 */
	int inputClientID();

	/**
	 * Esta fun��o entrega os pedidos pendentes de todos os supermercados.
	 * A abordagem utilizada depender� do parametro 'choice'. Ver fun��o 'deliverRequests'
	 * da classe Supermercado.
	 *
	 * @param choice inteiro que determina a estrat�gia utilizada na entrega dos pedidos
	 */
	void deliverAllRequests(int choice);
	/**
	 * Imprime algumas informa��es tais como o n�mero de clientes e de supermercados
	 * desta cadeia de supermercados. Efetua uma an�lise da densidade e conetividade
	 * do grafo e mostra ainda as suas componentes fortemente conexas.
	 */
	void showInfo();
	/**
	 * Imprime as componentes fortemente conexas do grafo.
	 */
	void stronglyConnectedComponents();
	/**
	 * Pesquisa de string exata
	 * @param T string onde ocorre a pesquisa
	 * @param P string a ser pesquisada
	 * @return retorna true se P ocorre em T, false caso contrario
	 */
	bool kmpMatcher(string T, string P);
	/**
	 * Realiza o preprocessamento da string a ser pesquisada na funcao kmpMatcher
	 * @param P string a ser preprocessada
	 * @return retorna um vetor com o resultado do preprocessamento da string
	 */
	vector<int> prefixComputation(string P);
	/**
	 * Retorna a distancia entre duas strings
	 * @param T string onde a comparacao ocorre
	 * @param P string onde a comparacao ocorre
	 * @return distancia entre as strings
	 */
	int editDistance(string T, string P);
	/**
	 * Imprime as informacoes dos supermercados, se existirem, que se encontram na rua
	 * @param e rua a pesquisar
	 */
	void checkSupermarketExistence(Edge<NodeObject*> e);
	/**
	 * Imprime o nome da(s) rua(s) em que o supermercado se encontra
	 * @param market supermercado a pesquisar
	 */
	void checkStreet(NodeObject* market);
	/**
	 * Realiza a pesquisa exacta de ruas
	 */
	void exactSearchStreet();
	/**
	 * Realiza a pesquisa aproximada de ruas
	 */
	void approximateSearchStreet();
	/**
	 * Realiza a pesquisa exacta de cadeias de supermercados
	 */
	void exactSearchSupermarket();
	/**
	 * Realiza a pesquisa aproximada de cadeias de supermercados
	 */
	void approximateSearchSupermarket();
	/**
	 * Realiza a pesquisa exacta de ruas
	 */
	void exactSearchDistrict();
};

class ComparisonStreetSimilarity
{
public:
	/**
	 * Operador utilizado para a ordenacao da fila de prioridade ruas da funcao approximateSearchStreet,
	 * de modo a que a rua de maior similaridade esteja na cabeca da fila.
	 */
	bool operator()(pair<Edge<NodeObject*>*, int> a, pair<Edge<NodeObject*>*, int> b)
	{
		return (a.second > b.second);
	}
};



#endif /* SRC_SUPERMARKETMANAGER_H_ */
