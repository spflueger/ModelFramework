/*
 * Data.cxx
 *
 *  Created on: Jun 15, 2013
 *      Author: steve
 */

#include "Data.h"

Data::Data() {
}

Data::~Data() {
	// TODO Auto-generated destructor stub
}

unsigned int Data::getNumberOfDataPoints() const {
	return data_points.size();
}

void Data::clearData() {
	data_points.clear();
}

void Data::insertDataPoints(std::vector<DataPointProxy> &data_points_) {
	for (unsigned int i = 0; i < data_points_.size(); i++) {
		insertDataPoint(data_points_[i]);
	}
}
void Data::insertDataPoint(DataPointProxy &data_point_) {
	// only check if data point dimension matches to the previous one
	// if not skip this point or throw exception
	if(0 < data_points.size()) {
	  if(data_points[data_points.size()-1].getDimension() != data_point_.getDimension()) {
	  	// we will just skip it, better would be throwing an exception
	  	return;
	  }
	}
	data_points.push_back(data_point_);
}

std::vector<DataPointProxy>& Data::getData() {
	return data_points;
}
