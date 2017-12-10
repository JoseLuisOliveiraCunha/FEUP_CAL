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
	 * Identificador �nico de um n�.
	 */
	int id;
	/**
	 * Distrito onde se localiza o no
	 */
	string distrito;

protected:
	/**
	 * Contador sequencial dos IDs dos n�s (clientes e supermercados).
	 */
	static int id_counter;

public:
	/**
	 * Construtor por omissao de um n�.
	 */
	NodeObject();
	/**
	 * Retorna o ID do n�
	 *
	 * @return ID do n�
	 */
	int getID();
	/**
	 * Retorna o distrito do no
	 *
	 * @return distrito do no
	 */
	string getDistrito();
	/**
	 * Operador de igualde de n�s.
	 * Um n� � igual a outro se tiverem o mesmo ID.
	 */
	bool operator == (const NodeObject &rhs);
};


#endif /* SRC_NODEOBJECT_H_ */
