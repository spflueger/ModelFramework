/*
 * ModelControlParameter.h
 *
 *  Created on: Jun 5, 2013
 *      Author: steve
 */

#ifndef MODELCONTROLPARAMETER_H_
#define MODELCONTROLPARAMETER_H_

#include "ModelStructs.h"
#include "DataStructs.h"

#include <vector>

using std::vector;

class ModelControlParameter {
private:
	vector<ModelStructs::minimization_parameter> parameters;
public:
	ModelControlParameter();
	virtual ~ModelControlParameter();

	virtual double evaluate(const double *par) =0;

	vector<ModelStructs::minimization_parameter>& getParameterList();
};

#endif /* MODELCONTROLPARAMETER_H_ */
