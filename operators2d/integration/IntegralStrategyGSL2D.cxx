#include "IntegralStrategyGSL2D.h"

#include <cmath>
#include <iostream>

Model2D* IntegralStrategyGSL2D::current_model = 0;

IntegralStrategyGSL2D::IntegralStrategyGSL2D() : T(gsl_rng_default) {
	calls = 500; // keep calls low at first
	maxcalls = 100000;
	gsl_rng_env_setup();
	r = gsl_rng_alloc(T);
	s = gsl_monte_vegas_alloc(2);
}

IntegralStrategyGSL2D::~IntegralStrategyGSL2D() {
	gsl_monte_vegas_free(s);
	gsl_rng_free(r);
}

double IntegralStrategyGSL2D::Integral(Model2D *model2d, double xlow,
		double xhigh, double ylow, double yhigh, double precision) {
	current_model = model2d;

	double result, error;

	double xl[2] = { xlow, ylow };
	double xu[2] = { xhigh, yhigh };

	gsl_monte_function G = { &gsl_func_wrapper, 2, 0 };

	gsl_monte_vegas_init(s);

	while (true) {
		gsl_monte_vegas_integrate(&G, xl, xu, 2, calls, r, s, &result, &error);

		//std::cout << result << " " << error << std::endl;
		//std::cout << calls << std::endl;
		//std::cout << gsl_monte_vegas_chisq(s) << std::endl;

		if (result == 0 && error == 0)
			break;
		//if (fabs(gsl_monte_vegas_chisq(s) - 1.0) < 0.1)
		//	break;
		if (fabs(error / result) < precision)
			break;
		if (maxcalls < calls)
			break;

		if (calls < maxcalls)
			calls *= 2;

	}

	return result;
}
