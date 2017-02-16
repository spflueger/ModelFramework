/*
 * ModelMinimizationControlParameter.h
 *
 *  Created on: Jun 6, 2013
 *      Author: steve
 */

#ifndef MODELMINIMIZATIONCONTROLPARAMETER_H_
#define MODELMINIMIZATIONCONTROLPARAMETER_H_

#include "ModelControlParameter.h"
#include "SharedPtr.h"

class Model;

class ModelMinimizationControlParameter: public ModelControlParameter {
	private:
	shared_ptr<Model> model;
public:
	ModelMinimizationControlParameter();
	virtual ~ModelMinimizationControlParameter();

  mydouble evaluate(const mydouble *pars);
};

#endif /* MODELMINIMIZATIONCONTROLPARAMETER_H_ */
