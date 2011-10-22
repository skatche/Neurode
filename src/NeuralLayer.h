/*
 * NeuralLayer.h
 *
 *  Created on: 2011-10-20
 *      Author: paul
 */

#ifndef NEURALLAYER_H_
#define NEURALLAYER_H_

#include <vector>

#include "Neuron.h"

using namespace std;

class NeuralLayer : public vector<Neuron*> {
public:
	NeuralLayer(int nNeurons,
							vector<NeuralLayer*> inputLayers=vector<NeuralLayer*>());
	virtual ~NeuralLayer();
	vector<float> getActionPotentials();
	void updateActionPotentials();
	void addNeurons(int nNeurons);
	void removeNeuron(int index);
private:
	vector<NeuralLayer*> _inputLayers;
	vector<NeuralLayer*> _outputLayers;

	static float (*_outputFunction)(float) = 0;
};

#endif /* NEURALLAYER_H_ */
