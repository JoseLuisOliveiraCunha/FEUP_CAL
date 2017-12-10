#ifndef SRC_MENU_H_
#define SRC_MENU_H_

#include "SupermarketManager.h"


using namespace std;

class Menu
{
private:
	/**
	 * Este atributo é o gestor de uma cadeia de supermercados sobre o qual
	 * o menu vai operar.
	 */
	SupermarketManager s;
public:
	/**
	 * Construtor da classe Menu.
	 * Chama o metodo mainMenu.
	 *
	 * @param s gestor de supermercados
	 */
	Menu(SupermarketManager s);
	/**
	 * Funcao responsavel pelo menu principal do programa.
	 */
	void mainMenu();
	/**
	 * Funcao responsavel pelo menu de entrega de pedidos.
	 */
	void deliverMenu();
	/**
	 * Funcao responsavel pelo menu de pesquisa.
	 */
	void searchMenu();
};

#endif /* SRC_MENU_H_ */
