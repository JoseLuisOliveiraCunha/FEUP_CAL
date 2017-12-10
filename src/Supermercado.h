#ifndef SUPERMERCADO_H_
#define SUPERMERCADO_H_

#include <vector>
#include <queue>
#include <stack>
#include "Graph.h"
#include "Pedido.h"
#include "Camiao.h"
#include "NodeObject.h"
#include "Utils.h"

using namespace std;

class Supermercado : public NodeObject
{
private:
	/**
	 * Fila de prioridade dos pedidos do supermercado.
	 * Estes sao organizados por tamanho, estando na cabeça
	 * da fila o pedido de menor tamanho.
	 */
	priority_queue<Pedido*, vector<Pedido*>, ComparisonRequestSize> pedidos;
	/**
	 * Vetor de apontadores para os camiões do supermercado.
	 */
	vector<Camiao*> camioes;
	/**
	 * Cadeia a que o supermercado pertence
	 */
	string cadeiaSupermercado;

public:
	/**
	 * Contrutor do supermercado. O número de camiões que
	 * o supermercado possuirá é igual 'nrTrucks'.
	 *
	 * @param nrTrucks número de camiões que o supermercado possuirá
	 * @param cadeia cadeia a que o supermercado pertence
	 */
	Supermercado(int nrTrucks, string cadeia);
	/**
	 * Adiciona um apontador para um pedido à fila de prioridade pedidos,
	 * tendo em conta que adicionar vários pedidos de um mesmo cliente apenas atualiza
	 * o tamanho do pedido desse cliente, não criando novas instâncias na fila de prioridade.
	 *
	 * @param request pedido a adicionar à fila de prioridade 'pedidos'
	 */
	void addRequest(Pedido *request);
	/**
	 * Retorna o número de pedidos deste supermercado, ou seja, o
	 * tamanho da fila de prioridade pedidos.
	 *
	 * @return o número de pedidos deste supermercado
	 */
	int getRequestNumber();
	/**
	 * Entrega aos clientes deste supermercado todos os seus pedidos pendentes.
	 * Caso 'choice' seja 0 pretende-se que os camiões tranportem o máximo
	 * de pedidos numa só viagem.
	 * Caso 'choice' seja 1 o objectivo será que os camiões percorram uma distância
	 * total mínima ao entregar os pedidos.
	 *
	 * @param graph grafo da cadeia de supermercados considerada
	 * @param choice inteiro que determina a estratégia utilizada na entrega dos pedidos
	 */
	void deliverRequests(Graph<NodeObject*> graph, int choice);
	/**
	 * Distribui os pedidos pelos camiões, determinando seu itenerário
	 * de modo a que cada camião transporte o número máximo de pedidos em cada viagem.
	 *
	 * @param graph grafo da cadeia de supermercados considerada
	 */
	void fillTrucksSize(Graph<NodeObject*> graph);
	/**
	 * Distribui os pedidos pelos camiões, determinando seu itenerário
	 * de modo a que cada camião percorra uma distância
	 * total mínima ao entregar os pedidos.
	 *
	 * @param graph grafo da cadeia de supermercados considerada
	 */
	void fillTrucksDistance(Graph<NodeObject*> graph);
	/**
	 * Retorna o número de camiões deste supermercado.
	 *
	 * @return o número de camiões deste supermercado.
	 */
	int getNumberTrucks();
	/**
	 * Retorna cadeia de supermercados a que pertence este supermercado.
	 *
	 * @return a cadeia deste supermercado.
	 */
	string getCadeiaSupermercado();
};

#endif /* SUPERMERCADO_H_ */
