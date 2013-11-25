/*
 * Data.h
 *
 *  Created on: Jun 15, 2013
 *      Author: steve
 */

#ifndef DATA_H_
#define DATA_H_

#include "DataStructs.h"
#include "DataPointProxy.h"

#include <vector>

class Data {
private:
	// this is the vector that stores the information
	std::vector<DataPointProxy> data_points;

public:
	Data();
	virtual ~Data();

	unsigned int getDimension() const;
	unsigned int getNumberOfDataPoints() const;

	void clearData();

	void insertDataPoints(std::vector<DataPointProxy> & data_points_);
	void insertDataPoint(DataPointProxy & data_point_);
	std::vector<DataPointProxy> & getData();
};

#endif /* BINNEDDATA_H_ */
