/*
 * StepFunction1D.h
 *
 *  Created on: Jun 14, 2013
 *      Author: steve
 */

#ifndef STEPFUNCTION1D_H_
#define STEPFUNCTION1D_H_

#include "core/Model1D.h"

class StepFunction1D: public Model1D {
private:
  shared_ptr<ModelPar> amplitude;
  shared_ptr<ModelPar> edge;
  bool falling_edge;

public:
	StepFunction1D(std::string name_, bool falling_edge_);
	virtual ~StepFunction1D();

  double eval(const double *x) const;

  void initModelParameters();

  void updateDomain();
};

#endif /* STEPFUNCTION1D_H_ */
