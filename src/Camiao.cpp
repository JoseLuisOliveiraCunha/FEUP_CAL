#include "Camiao.h"

void Camiao::printItenerario(int supermarketID, int pos)
{
	bool flag = !itenerario.empty();
	if(flag)
	{
		cout << "	Camiao " << pos << ": ";
		cout << supermarketID << " -> ";
	}
	while(!itenerario.empty())
	{
		int id;
		id = itenerario.front()->getClientID();
		cout << id;
		if(itenerario.size()>1)
			cout << " -> ";
		itenerario.pop();
	}
	if(flag)
		cout << " (total distance: " << this->getDistanceCovered() << ")\n";
}
