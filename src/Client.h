/*
 * Client.h
 *
 *  Created on: 1 Apr 2017
 *      Author: ZeLuis
 */

#ifndef SRC_CLIENT_H_
#define SRC_CLIENT_H_

#include "NodeObject.h"

class Client : public NodeObject
{
public:
	/**
	 * Construtor por omissao de um cliente.
	 */
	Client();
	/**
	 * Coloca a zero o contador sequencial de IDs (dos clientes e supermercados).
	 */
	void resetIdCounter();
};


#endif /* SRC_CLIENT_H_ */
