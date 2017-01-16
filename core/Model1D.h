/*
 * Model1D.h
 *
 *  Created on: Jan 16, 2013
 *      Author: steve
 */

#ifndef MODEL1D_H_
#define MODEL1D_H_

#include "Model.h"

class IntegralStrategy1D;

class Model1D: public Model {
private:
	std::pair<double, double> domain_bounds;

  shared_ptr<IntegralStrategy1D> integral_strategy;

public:
  Model1D(std::string name_);
  virtual ~Model1D();

  mydouble Integral(const std::vector<DataStructs::DimensionRange> &ranges, mydouble precision);
  double getDomainRange();
  double getDomainLowerBound();
  const std::pair<double, double>& getDomain() const;
  void setDomain(double lower_bound, double upper_bound);
};

#endif /* MODEL1D_H_ */
