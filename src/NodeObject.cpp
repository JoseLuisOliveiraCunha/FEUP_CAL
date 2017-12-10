/*
 * NodeObject.cpp
 *
 *  Created on: 1 Apr 2017
 *      Author: ZeLuis
 */

#include "NodeObject.h"

int NodeObject::id_counter = 0;


NodeObject::NodeObject(){
	this->id_counter++;
	this->id = id_counter;

}

int NodeObject::getID(){
	return this->id;
}

string NodeObject::getDistrito(){
	return distrito;
}
bool NodeObject::operator == (const NodeObject &rhs){
	return this->id==rhs.id;
}
