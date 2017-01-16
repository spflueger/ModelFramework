/*
 * Model2D.h
 *
 *  Created on: Jan 16, 2013
 *      Author: steve
 */

#ifndef MODEL2D_H_
#define MODEL2D_H_

#include "core/Model.h"

class IntegralStrategy2D;

class Model2D: public Model {
private:
	std::pair<double, double> var1_domain_bounds;
	std::pair<double, double> var2_domain_bounds;

	shared_ptr<IntegralStrategy2D> integral_strategy;

public:
	Model2D(std::string name_);
	virtual ~Model2D();

	double getVar1DomainRange();
	double getVar1DomainLowerBound();
	double getVar2DomainRange();
	double getVar2DomainLowerBound();

	void setVar1Domain(double lower_bound, double upper_bound);
	void setVar2Domain(double lower_bound, double upper_bound);

	void setIntegralStrategy(shared_ptr<IntegralStrategy2D> integral_strategy_);

	mydouble Integral(const std::vector<DataStructs::DimensionRange> &ranges
			, mydouble precision);
};

#endif /* MODEL2D_H_ */
