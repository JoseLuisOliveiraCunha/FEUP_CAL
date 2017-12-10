#include "Supermercado.h"


Supermercado::Supermercado(int nrTrucks, string cadeia) : NodeObject()
{
	for(int i = 0; i < nrTrucks; i++){
		camioes.push_back(new Camiao ());
	}
	this->cadeiaSupermercado = cadeia;
}

int Supermercado::getNumberTrucks()
{
	return camioes.size();
}

void Supermercado::addRequest(Pedido *request){
	vector<Pedido*> temp;
	bool clientFound = false;

	if(this->pedidos.size() > 0)
	{//verify if there's already a request for the same client
		while(!this->pedidos.empty())
		{
			Pedido *p = this->pedidos.top();
			if(p->getClientID() == request->getClientID())
			{
				p->addTamanho(request->getTamanho());
				clientFound = true;
			}
			temp.push_back(p);
			this->pedidos.pop();
		}

		for(unsigned int i = 0; i < temp.size(); i++)
		{
			this->pedidos.push(temp[i]);
		}

	}

	if(!clientFound)
	{
		this->pedidos.push(request);
	}

}

int Supermercado::getRequestNumber(){
	return this->pedidos.size();
}

string Supermercado::getCadeiaSupermercado(){
	return cadeiaSupermercado;
}
void Supermercado::deliverRequests(Graph<NodeObject*> graph, int choice){
	while(!pedidos.empty())
	{
		if(choice == 0)
			fillTrucksSize(graph);
		else
			fillTrucksDistance(graph);
		for(unsigned int i = 0; i < camioes.size(); i++)
		{
			camioes[i]->printItenerario(this->getID(), i+1);
			camioes[i]->reset();
		}
		cout << "All trucks returned to the supermarket \n";
	}
}

void Supermercado::fillTrucksSize(Graph<NodeObject*> graph){
	bool trucksAvailable = true;
	stack<Pedido*> stackPedidosTemp;
	unsigned int index = 0;

	bool updateQueue = false;

	while(!this->pedidos.empty() && trucksAvailable)
	{
		if(index < this->camioes.size())
		{
			Pedido* p = pedidos.top();
			if(camioes[index]->getCapacidadeUsada() + p->getTamanho() <= camioes[index]->getCapacidadeMaxima())
			{
				Vertex<NodeObject*>* currentClientVertex = graph.getVertex(p->getDestination());
				if(!camioes[index]->getItenerario().empty())
				{
					Vertex<NodeObject*>* lastClientVertex = graph.getVertex(camioes[index]->getItenerario().back()->getDestination());
					graph.dijkstra(lastClientVertex);
					if(currentClientVertex->getDist() != INT_INFINITY)
					{
						camioes[index]->addPedido(p);
						camioes[index]->addDistance(currentClientVertex->getDist());
						updateQueue = true;
					}
					else
					{
						stackPedidosTemp.push(p);
					}
				}
				else
				{
					Vertex<NodeObject*>* marketVertex = graph.getVertex(this);
					graph.dijkstra(marketVertex);
					camioes[index]->addPedido(p);
					camioes[index]->addDistance(currentClientVertex->getDist());
				}
			}
			else
			{
				index++;
				updateQueue = true;
				stackPedidosTemp.push(p);
			}
			pedidos.pop();
			if(updateQueue)
			{
				while(!stackPedidosTemp.empty())
				{
					Pedido* q = stackPedidosTemp.top();
					stackPedidosTemp.pop();
					pedidos.push(q);
				}
				updateQueue = false;
			}
		}
		else
		{
			trucksAvailable = false;
		}
	}
	while(!stackPedidosTemp.empty())
	{
		Pedido* p = stackPedidosTemp.top();
		stackPedidosTemp.pop();
		pedidos.push(p);
	}
}

void Supermercado::fillTrucksDistance(Graph<NodeObject*> graph)
{
	bool trucksAvailable = true;
	priority_queue<Pedido*, vector<Pedido*>, ComparisonRequestDistance> pedidosDistance;
	priority_queue<Pedido*, vector<Pedido*>, ComparisonRequestSize> pedidosCopy = this->pedidos;
	while(!pedidosCopy.empty()){
		Pedido* p = pedidosCopy.top();
		pedidosDistance.push(p);
		pedidosCopy.pop();
	}

	bool updateQueue = false;

	stack<Pedido*> stackPedidosTemp;
	unsigned int index = 0;
	while(!pedidosDistance.empty() && trucksAvailable)
	{
		if(index < this->camioes.size())
		{
			Pedido* p = pedidosDistance.top();
			if(camioes[index]->getCapacidadeUsada() + p->getTamanho() <= camioes[index]->getCapacidadeMaxima())
			{
				Vertex<NodeObject*>* currentClientVertex = graph.getVertex(p->getDestination());
				if(!camioes[index]->getItenerario().empty())
				{
					Vertex<NodeObject*>* lastClientVertex = graph.getVertex(camioes[index]->getItenerario().back()->getDestination());
					graph.dijkstra(lastClientVertex);
					if(currentClientVertex->getDist() != INT_INFINITY)
					{
						camioes[index]->addPedido(p);
						camioes[index]->addDistance(currentClientVertex->getDist());
						updateQueue = true;
					}
					else
					{
						stackPedidosTemp.push(p);
					}
				}
				else
				{
					Vertex<NodeObject*>* marketVertex = graph.getVertex(this);
					graph.dijkstra(marketVertex);
					camioes[index]->addPedido(p);
					camioes[index]->addDistance(currentClientVertex->getDist());
				}
			}
			else
			{
				stackPedidosTemp.push(p);
			}
			pedidosDistance.pop();
			if(updateQueue)
			{
				while(!stackPedidosTemp.empty())
				{
					Pedido* q = stackPedidosTemp.top();
					stackPedidosTemp.pop();
					pedidosDistance.push(q);
				}
				updateQueue = false;
			}
			if(pedidosDistance.size()==0)
			{
				index++;
				while(!stackPedidosTemp.empty())
				{
					Pedido* q = stackPedidosTemp.top();
					stackPedidosTemp.pop();
					pedidosDistance.push(q);
				}
			}
		}
		else
		{
			trucksAvailable = false;
		}
	}
	while(!stackPedidosTemp.empty())
	{
		Pedido* q = stackPedidosTemp.top();
		stackPedidosTemp.pop();
		pedidosDistance.push(q);
	}
	while(!pedidos.empty()){
		pedidos.pop();
	}
	while(!pedidosDistance.empty()){
		pedidos.push(pedidosDistance.top());
		pedidosDistance.pop();
	}

}
