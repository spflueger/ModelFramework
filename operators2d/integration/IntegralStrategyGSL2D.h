#ifndef INTEGRALSTRATEGYGSL2D_H_
#define INTEGRALSTRATEGYGSL2D_H_

#include "IntegralStrategy2D.h"

#include "core/Model2D.h"

#include <gsl/gsl_math.h>
#include <gsl/gsl_monte.h>
#include <gsl/gsl_monte_vegas.h>

class IntegralStrategyGSL2D: public IntegralStrategy2D {
private:
	static Model2D *current_model;

	const gsl_rng_type *T;
	gsl_rng *r;
	gsl_monte_vegas_state *s;
	size_t calls;
	size_t maxcalls;

	static double gsl_func_wrapper(double *x, size_t dim, void *params) {
		Model2D *current_model_temp = current_model;
		double value = current_model->eval(x);
		current_model = current_model_temp;
		return value;
	}
public:
	IntegralStrategyGSL2D();
	virtual ~IntegralStrategyGSL2D();

	double Integral(Model2D *model2d, double xlow, double xhigh, double ylow,
			double yhigh, double precision);
};
#endif /* INTEGRALSTRATEGYGSL2D_H_ */