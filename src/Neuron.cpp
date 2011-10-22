/*
 * Neuron.cpp
 *
 *  Created on: 2011-10-20
 *      Author: paul
 */

#include <vector>
#include <algorithm>

#include "Neuron.h"

using namespace std;

float (*Neuron::_defaultOutputFunction)(float) = 0;
float Neuron::_defaultWeight = 0;

Neuron::Neuron(vector<Neuron*> inputNeurons, vector<float> weights)
			: _actionPotential(0), _pinned(false), _overriddenOutputFunction(0)
{
	int nInputs = (int)inputNeurons.size();
	int nWeights = (int)weights.size();
	if (nInputs != nWeights) {
		_weights = vector<float>(nInputs, _defaultWeight);
	}
	else {
		_weights = weights;
	}
	_inputNeurons = inputNeurons;
	for (int i = 0; i < (int)_inputNeurons.size(); i++)
		_inputNeurons[i]->_addOutput(this);
}



Neuron::~Neuron()
{
	// TODO Auto-generated destructor stub
}



float Neuron::getActionPotential()
{
	return _actionPotential;
}



void Neuron::updateActionPotential()
{
	if (not _pinned) {
		vector<float> weightedInputs = _weights;
		for (int i = 0; i < (int)_weights.size(); i++)
			weightedInputs[i] *= _inputNeurons[i]->getActionPotential();
		float weightedSum = 0;
		for (int i = 0; i < (int) weightedInputs.size(); i++)
			weightedSum += weightedInputs[i];

		if (_overriddenOutputFunction)
			_actionPotential = (*_overriddenOutputFunction)(weightedSum);
		else if (_defaultOutputFunction)
			_actionPotential = (*_defaultOutputFunction)(weightedSum);
		else
			_actionPotential = weightedSum;
	}
}



void Neuron::addInputNeurons(vector<Neuron*> neurons, vector<float> weights)
{
	int nNeurons = (int) neurons.size();
	int nWeights = (int) weights.size();
	if (nWeights != nNeurons)
		weights = vector<float>(nNeurons, _defaultWeight);

	for (int i = 0; i < nNeurons; i++) {
		_addInput(neurons[i], weights[i]);
		neurons[i]->_addOutput(this);
	}
}



void Neuron::addOutputNeurons(vector<Neuron*> neurons, vector<float> weights)
{
	int nNeurons = (int) neurons.size();
	int nWeights = (int) weights.size();
	if (nWeights != nNeurons)
		weights = vector<float>(nNeurons, _defaultWeight);

	for (int i = 0; i < nNeurons; i++) {
		_addOutput(neurons[i]);
		neurons[i]->_addInput(this, weights[i]);
	}
}



void Neuron::overrideOutputFunction(float (*outputFunction)(float))
{
	_overriddenOutputFunction = outputFunction;
}



void Neuron::underrideOutputFunction(void)
{
	_overriddenOutputFunction = 0;
}



void Neuron::setDefaultOutputFunction(float (*outputFunction)(float))
{
	_defaultOutputFunction = outputFunction;
}



void Neuron::setDefaultWeight(float weight)
{
	_defaultWeight = weight;
}

void Neuron::_addInput(Neuron *neuron, float weight)
{
	vector<Neuron*>::iterator it = find(_inputNeurons.begin(),
																			_inputNeurons.end(),
																			neuron);
	if (it == _inputNeurons.end()) {
		_inputNeurons.push_back(neuron);
		_weights.push_back(weight);
	}
}



float (*Neuron::getDefaultOutputFunction())(float)
{
	return _defaultOutputFunction;
}

void Neuron::pinActionPotential(float f)
{
	_actionPotential = f;
	_pinned = true;
}

void Neuron::pinActionPotential()
{
	_pinned = true;
}

void Neuron::unpinActionPotential()
{
	_pinned = false;
}



void Neuron::_addOutput(Neuron *neuron)
{
	vector<Neuron*>::iterator it = find(_outputNeurons.begin(),
																			_outputNeurons.end(),
																			neuron);
	if (it == _outputNeurons.end()) {
		_outputNeurons.push_back(neuron);
	}
}
