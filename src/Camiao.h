/*
 * Camiao.h
 *
 *  Created on: 31/03/2017
 *      Author: PC
 */

#ifndef CAMIAO_H_
#define CAMIAO_H_

#include <queue>
#include <iostream>
#include "Graph.h"
#include "Pedido.h"

using namespace std;

class Camiao
{
private:
	/**
	 * Capacidade de armazenamento maxima do camiao.
	 * Um camiao pode armazenar varios pedidos, tendo cada um deles
	 * um determinado tamanho.
	 */
	const int capacidadeMaxima = 100;
	/**
	 * Capacidade que esta a ser usada pelo camiao, ou seja, a soma
	 * dos tamanhos dos pedidos armazenados pelo camiao neste momento.
	 */
	int capacidadeUsada = 0;
	/*
	 * Fila de apontadores para os pedidos que serao atendidos pelo camiao.
	 */
	queue<Pedido*> itenerario;
	/**
	 * Distancia total percorrida pelo camiao no seu itenerario.
	 */
	int distanceCovered = 0;

public:
	/**
	 * Construtor por omissao de um camiao.
	 */
	Camiao(){};
	/**
	 * Coloca a zeros a capacidade usada e a distancia percorrida pelo camiao.
	 */
	void reset(){capacidadeUsada = 0; distanceCovered = 0;};
	/**
	 * Adiciona um pedido ao itenerario a ser realizado pelo camiao.
	 * Atualiza a capacidade usada pelo camiao, somando-lhe o tamanho do pedido.
	 *
	 * @param pedido apontador para o pedido a adicionar ao camiao
	 */
	void addPedido(Pedido* pedido){itenerario.push(pedido); capacidadeUsada+=pedido->getTamanho();};
	/**
	 * Retorna a capacidade atualmente usada pelo camiao
	 *
	 * @return a capacidade atualmente usada pelo camiao
	 */
	int getCapacidadeUsada(){return this->capacidadeUsada;};
	/**
	 * Retorna a capacidade maxima do camiao
	 *
	 * @return a capacidade maxima do camiao
	 */
	int getCapacidadeMaxima(){return this->capacidadeMaxima;};
	/**
	 * Retorna a distancia total percorrida no itenerario do camiao
	 *
	 * @return a distancia total percorrida no itenerario do camiao
	 */
	int getDistanceCovered(){return this->distanceCovered;};
	/**
	 * Adiciona uma distancia a distancia total percorrida pelo camiao
	 *
	 * @param distance distancia a adicionar
	 */
	void addDistance(int distance){this->distanceCovered += distance;};
	/**
	 * Retorna o itenerario do camiao
	 *
	 * @return o itenerario do camiao
	 */
	queue<Pedido*> getItenerario(){return this->itenerario;};
	/**
	 * Imprime o itenerario do camiao de número 'pos' pertencente
	 * ao supermercado de ID 'supermarketID'.
	 * O ID de um supermercado é atribuido sequencialmente aquando da
	 * leitura do ficheiro do grafo. Cada supermercado tem um vetor
	 * de camioes, sendo o numero de cada camiao obtido somando 1 ao
	 * seu indice nesse vetor.
	 *
	 * @param supermarketID ID do supermercado que possui este camiao
	 * @param pos numero deste camiao
	 */
	void printItenerario(int supermarketID, int pos);
};

#endif /* CAMIAO_H_ */
