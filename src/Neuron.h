/*
 * Neuron.h
 *
 *  Created on: 2011-10-20
 *      Author: paul
 */

#ifndef NEURON_H_
#define NEURON_H_

#include <vector>

using namespace std;

class Neuron {
public:
	Neuron(vector<Neuron*> inputNeurons=vector<Neuron*>(),
			   vector<float> weights=vector<float>());
	virtual ~Neuron();
	float getActionPotential();
	void updateActionPotential();
	void addInputNeurons(vector<Neuron*> neurons,
											 vector<float> weights=vector<float>());
	void addOutputNeurons(vector<Neuron*> neurons,
											  vector<float> weights=vector<float>());
	void pinActionPotential(float f);
	void pinActionPotential();
	void unpinActionPotential();
	void overrideOutputFunction(float (*outputFunction)(float));
	void underrideOutputFunction();

	static float (*getDefaultOutputFunction())(float);
	static void setDefaultOutputFunction(float (*outputFunction)(float));
	static void setDefaultWeight(float weight);

private:
	void _addInput(Neuron* neuron, float weight);
	void _addOutput(Neuron* neuron);
	vector<Neuron*> _inputNeurons;
	vector<Neuron*> _outputNeurons;
	vector<float> 	_weights;
	float _actionPotential;
	bool _pinned;
	float (*_overriddenOutputFunction)(float);

	static float (*_defaultOutputFunction)(float);
	static float _defaultWeight;
};

#endif /* NEURON_H_ */
