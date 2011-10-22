//============================================================================
// Name        : Neurode.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "Neuron.h"
using namespace std;

int main() {
	Neuron* n1 = new Neuron();
	n1->pinActionPotential(2.1);
	vector<Neuron*> n1vec (1, n1);
	vector<float> weightvec (1, 2.5);
	Neuron n2 (n1vec, weightvec);
	n2.updateActionPotential();
	cout << "n1 has AP " << n1->getActionPotential()
			 << " and n2 has AP " << n2.getActionPotential() << endl;
	return 0;
}
