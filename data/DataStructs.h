/*
 * DataStructs.h
 *
 *  Created on: Jun 16, 2013
 *      Author: steve
 */

#ifndef DATASTRUCTS_H_
#define DATASTRUCTS_H_

#include <string>
#include <vector>

namespace DataStructs {

struct measurement_coordiante {
	double value;
	double error_low;
	double error_high;
};

struct data_point {
	std::vector<measurement_coordiante> coordinates;
};

// binned data structure
struct binned_data_point {
	// binning/scaling factor
	double scaling_factor;
	bool scaling_factor_active;

	data_point point;
	double value;
	double value_error;

	binned_data_point() :
			value(0.0), value_error(0.0), scaling_factor(1.0), scaling_factor_active(
					false) {
	}
};

enum dimension_unit_prefix {
	PICO, NANO, MICRO, MILLI, CENTI, NONE, KILO, MEGA, GIGA
};

struct dimension_unit_factor {
	static std::string getUnitNamePrefix(dimension_unit_prefix unit_prefix) {
		if (PICO == unit_prefix)
			return "p";
		else if (NANO == unit_prefix)
			return "n";
		else if (MICRO == unit_prefix)
			return "#mu";
		else if (MILLI == unit_prefix)
			return "m";
		else if (CENTI == unit_prefix)
			return "cm";
		else if (NONE == unit_prefix)
			return "";
		else if (KILO == unit_prefix)
			return "k";
		else if (MEGA == unit_prefix)
			return "M";
		else if (GIGA == unit_prefix)
			return "G";
		return "";
	}

	static double getUnitFactor(dimension_unit_prefix unit_prefix) {
		if (PICO == unit_prefix)
			return 1e-12;
		else if (NANO == unit_prefix)
			return 1e-9;
		else if (MICRO == unit_prefix)
			return 1e-6;
		else if (MILLI == unit_prefix)
			return 1e-3;
		else if (CENTI == unit_prefix)
			return 1e-2;
		else if (NONE == unit_prefix)
			return 1.0;
		else if (KILO == unit_prefix)
			return 1e3;
		else if (MEGA == unit_prefix)
			return 1e6;
		else if (GIGA == unit_prefix)
			return 1e9;
		return 1.0;
	}
};

struct dimension_range {
	std::pair<double, double> range;

	double unit_factor;
};

}

#endif /* DATASTRUCTS_H_ */
