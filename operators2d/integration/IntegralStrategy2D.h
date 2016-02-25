#ifndef INTEGRALSTRATEGY2D_H_
#define INTEGRALSTRATEGY2D_H_

#include <vector>

#include "fit/data/DataStructs.h"

class Model2D;

class IntegralStrategy2D {
public:
	IntegralStrategy2D();
	virtual ~IntegralStrategy2D();

	virtual double Integral(Model2D *model2d, const std::vector<DataStructs::DimensionRange> &ranges,
			double precision) =0;
};

#endif /* INTEGRALSTRATEGY2D_H_ */
