/*
 * NodeObject.h
 *
 *  Created on: 1 Apr 2017
 *      Author: ZeLuis
 */

#ifndef SRC_NODEOBJECT_H_
#define SRC_NODEOBJECT_H_

#include <string>
using namespace std;

class NodeObject {
private:
	/**
	 * Identificador único de um nó.
	 */
	int id;
	/**
	 * Distrito onde se localiza o no
	 */
	string distrito;

protected:
	/**
	 * Contador sequencial dos IDs dos nós (clientes e supermercados).
	 */
	static int id_counter;

public:
	/**
	 * Construtor por omissao de um nó.
	 */
	NodeObject();
	/**
	 * Retorna o ID do nó
	 *
	 * @return ID do nó
	 */
	int getID();
	/**
	 * Retorna o distrito do no
	 *
	 * @return distrito do no
	 */
	string getDistrito();
	/**
	 * Operador de igualde de nós.
	 * Um nó é igual a outro se tiverem o mesmo ID.
	 */
	bool operator == (const NodeObject &rhs);
};


#endif /* SRC_NODEOBJECT_H_ */
