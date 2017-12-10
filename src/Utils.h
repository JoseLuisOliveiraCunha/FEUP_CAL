#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <iostream>
#include <limits>
#include "Pedido.h"
#include "NodeObject.h"
#include <vector>

using namespace std;
/**
 * Pede continuamente ao utilizador um inteiro entre 'min' e 'max'.
 * Retorna esse valor assim que seja v�lido.
 *
 * @param min valor minimo do intervalo aceite
 * @param max valor m�ximo do intervalo aceite
 * @return o primeiro inteiro v�lido introduzido pelo utilizador
 */
int readNumber(int min, int max);

/**
 * Retorna a ordem de grandeza do n�mero dado.
 * Esta fun��o � utilizada no m�todo 'showInfo' da classe SupermarketManager
 * com a finalidade de verificar se um grafo � denso ou esparso.
 *
 * @param num o n�mero cuja ordem de grandeza se pretende calcular
 */
int magnitudeOrder(int num);

class ComparisonRequestSize
{
public:
	/**
	 * Operador utilizado para a ordena��o da fila de prioridade 'pedidos' da classe Supermercado,
	 * de modo a que o pedido de menor tamanho esteja � cabe�a da fila.
	 */
	bool operator()(Pedido* a, Pedido* b)
	{
		return (a->getTamanho() > b->getTamanho());
	}
};



class ComparisonMarketSimilarity
{
public:
	/**
	 * Operador utilizado para a ordena��o da fila de prioridade markets da funcao approximateSearchSupermarket,
	 * de modo a que a rua de maior similaridade esteja � cabe�a da fila.
	 */
	bool operator()(pair<NodeObject*, int> a, pair<NodeObject*, int> b)
	{
		return (a.second > b.second);
	}
};

class ComparisonRequestDistance
{
public:
	/**
	 * Operador utilizado para a ordena��o da fila de prioridade 'pedidos' da classe Supermercado,
	 * de modo a que o pedido de menor distancia ao supermercado considerado esteja � cabe�a da fila.
	 */
	bool operator()(Pedido* a, Pedido* b)
	{
		return (a->getDistance() > b->getDistance());
	}
};

class AuxEdge
{
public:
	/**
	 * Fonte, destino e peso da aresta.
	 */
	int src, dest, w;
	/**
	 * Rua e distrito da aresta.
	 */
	string rua, distrito;
	/**
	 * Construtor por omissao.
	 */
	AuxEdge(){src = 0; dest = 0; w=0;};
	/**
	 * Construtor que atribui valores aos atributos da classe.
	 *
	 * @param src fonte da aresta
	 * @param dest destino da aresta
	 * @param w peso da aresta
	 * @param rua rua da aresta
	 * @param distrito distrito da aresta
	 */
	AuxEdge(int src, int dest, int w, string rua, string distrito){this->src = src;this->dest=dest;this->w=w;this->rua=rua;this->distrito=distrito;};
	/**
	 * Operador de igualdade desta classe.
	 * Duas AuxEdge sao iguais se tiverem a mesma fonte e destino ou tiverem a mesma rua.
	 *
	 * @param rhs AuxEdge a comparar
	 * @return true se as AuxEdge sao iguais e false caso contrario
	 */
	bool operator==(const AuxEdge &rhs){return (src==rhs.src && dest==rhs.dest) || (src==rhs.dest && dest==rhs.src) || rua==rhs.rua;};
	/**
	 * Funcao que indica se esta AuxEdge existe no vetor dado.
	 *
	 * @param edges vetor de AuxEdges
	 * @return true se esta AuxEdge existe no vetor dado e false caso contrario
	 */
	bool exists(vector<AuxEdge> edges)
	{
		bool flag = false;
		for(int i = 0; i < edges.size();i++)
		{
			if(edges[i]==*(this))
				flag = true;
		}
		return flag;
	}
	/**
	 * Funcao que troca o sentido de uma AuxEdge.
	 *
	 * @return AuxEdge com o sentido trocado.
	 */
	AuxEdge reverse(){
		return AuxEdge(this->dest, this->src, this->w, this->rua, this->distrito);
	}
};



#endif /* SRC_UTILS_H_ */
