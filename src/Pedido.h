#ifndef PEDIDO_H_
#define PEDIDO_H_

#include "Client.h"
#include <limits>
using namespace std;

#define MAX_REQUEST_SIZE 50
#define INT_INFINITY std::numeric_limits<int>::max()

class Pedido
{
private:
	/**
	 * Apontador para o cliente que efetuou o pedido.
	 */
	Client* destination;
	/**
	 * Tamanho do pedido.
	 */
	int tamanho = 0;
	/**
	 * Distancia do cliente que efetuou o pedido ao supermercado encarregue pelo mesmo.
	 */
	int distance = INT_INFINITY;
public:
	/**
	 * Contrutor do pedido.
	 *
	 * @param destination cliente que efetuou o pedido
	 * @param tamanho tamanho do pedido
	 */
	Pedido(Client* destination, int tamanho)
	{
		this->destination = destination;
		this->tamanho = tamanho;
	}
	/**
	 * Retorna o ID do cliente que fez o pedido
	 *
	 * @return o ID do cliente que fez o pedido
	 */
	int getClientID(){return this->destination->getID();};
	/**
	 * Retorna um apontador para o cliente que fez o pedido
	 *
	 * @return um apontador para o cliente que fez o pedido
	 */
	Client* getDestination(){return this->destination;};
	/**
	 * Retorna o tamanho do pedido
	 *
	 * @return o tamanho do pedido
	 */
	int getTamanho(){return this->tamanho;};
	/**
	 * Atribui um valor inteiro ao tamanho do pedido.
	 *
	 * @param tamanho valor a atribuir ao tamanho do pedido
	 */
	void setTamanho(int tamanho){this->tamanho = tamanho;};
	/**
	 * Soma um valor ao tamanho do pedido. Se esta operação exceder a
	 * capacidade maxima definida para os pedidos, o pedido
	 * ficará com o tamanho máximo.
	 *
	 * @param incremento valor a somar ao tamanho do pedido
	 */
	void addTamanho(int incremento){this->tamanho = (tamanho + incremento > MAX_REQUEST_SIZE) ? MAX_REQUEST_SIZE : tamanho + incremento;};
	/**
	 * Retorna a distancia do cliente que efetuou o pedido ao supermercado encarregue pelo mesmo.
	 *
	 * @return distancia do cliente que efetuou o pedido ao supermercado encarregue pelo mesmo.
	 */
	int getDistance(){return distance;};
	/**
	 * Atribui um valor inteiro à distancia do pedido.
	 *
	 * @param distance valor a atribuir à distancia do pedido
	 */
	void setDistance(int distance){this->distance = distance;};

};

#endif /* PEDIDO_H_ */
