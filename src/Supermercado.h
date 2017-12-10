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
	 * Estes sao organizados por tamanho, estando na cabe�a
	 * da fila o pedido de menor tamanho.
	 */
	priority_queue<Pedido*, vector<Pedido*>, ComparisonRequestSize> pedidos;
	/**
	 * Vetor de apontadores para os cami�es do supermercado.
	 */
	vector<Camiao*> camioes;
	/**
	 * Cadeia a que o supermercado pertence
	 */
	string cadeiaSupermercado;

public:
	/**
	 * Contrutor do supermercado. O n�mero de cami�es que
	 * o supermercado possuir� � igual 'nrTrucks'.
	 *
	 * @param nrTrucks n�mero de cami�es que o supermercado possuir�
	 * @param cadeia cadeia a que o supermercado pertence
	 */
	Supermercado(int nrTrucks, string cadeia);
	/**
	 * Adiciona um apontador para um pedido � fila de prioridade pedidos,
	 * tendo em conta que adicionar v�rios pedidos de um mesmo cliente apenas atualiza
	 * o tamanho do pedido desse cliente, n�o criando novas inst�ncias na fila de prioridade.
	 *
	 * @param request pedido a adicionar � fila de prioridade 'pedidos'
	 */
	void addRequest(Pedido *request);
	/**
	 * Retorna o n�mero de pedidos deste supermercado, ou seja, o
	 * tamanho da fila de prioridade pedidos.
	 *
	 * @return o n�mero de pedidos deste supermercado
	 */
	int getRequestNumber();
	/**
	 * Entrega aos clientes deste supermercado todos os seus pedidos pendentes.
	 * Caso 'choice' seja 0 pretende-se que os cami�es tranportem o m�ximo
	 * de pedidos numa s� viagem.
	 * Caso 'choice' seja 1 o objectivo ser� que os cami�es percorram uma dist�ncia
	 * total m�nima ao entregar os pedidos.
	 *
	 * @param graph grafo da cadeia de supermercados considerada
	 * @param choice inteiro que determina a estrat�gia utilizada na entrega dos pedidos
	 */
	void deliverRequests(Graph<NodeObject*> graph, int choice);
	/**
	 * Distribui os pedidos pelos cami�es, determinando seu itener�rio
	 * de modo a que cada cami�o transporte o n�mero m�ximo de pedidos em cada viagem.
	 *
	 * @param graph grafo da cadeia de supermercados considerada
	 */
	void fillTrucksSize(Graph<NodeObject*> graph);
	/**
	 * Distribui os pedidos pelos cami�es, determinando seu itener�rio
	 * de modo a que cada cami�o percorra uma dist�ncia
	 * total m�nima ao entregar os pedidos.
	 *
	 * @param graph grafo da cadeia de supermercados considerada
	 */
	void fillTrucksDistance(Graph<NodeObject*> graph);
	/**
	 * Retorna o n�mero de cami�es deste supermercado.
	 *
	 * @return o n�mero de cami�es deste supermercado.
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
