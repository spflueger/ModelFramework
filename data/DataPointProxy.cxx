/*
 * DataPointProxy.cxx
 *
 *  Created on: Jun 16, 2013
 *      Author: steve
 */

#include "DataPointProxy.h"

DataPointProxy::DataPointProxy() {
	// TODO Auto-generated constructor stub
	state = -1;
	is_point_used = false;
}

DataPointProxy::~DataPointProxy() {
	// TODO Auto-generated destructor stub
}

bool DataPointProxy::isBinnedDataPoint() const {
	return (0 == state);
}
bool DataPointProxy::isUnbinnedDataPoint() const {
	return (1 == state);
}

const shared_ptr<DataStructs::binned_data_point> DataPointProxy::getBinnedDataPoint() const {
	return bdp;
}

const shared_ptr<DataStructs::data_point> DataPointProxy::getUnbinnedDataPoint() const {
	return udp;
}

void DataPointProxy::setBinnedDataPoint(
		shared_ptr<DataStructs::binned_data_point> bdp_) {
	state = 0;
	udp.reset();
	bdp = bdp_;
}

void DataPointProxy::setUnbinnedDataPoint(
		shared_ptr<DataStructs::data_point> udp_) {
	state = 1;
	bdp.reset();
	udp = udp_;
}

bool DataPointProxy::isPointUsed() const {
	return is_point_used;
}

void DataPointProxy::setPointUsed(bool is_point_used_) {
	is_point_used = is_point_used_;
}

unsigned int DataPointProxy::getDimension() const {
	unsigned int dimension = 0;
	if (isBinnedDataPoint()) {
		dimension = getBinnedDataPoint()->point.coordinates.size();
	} else if (isUnbinnedDataPoint()) {
		dimension = getUnbinnedDataPoint()->coordinates.size();
	}
  if(0 == dimension) {
  	// if the dimension is 0 either data point is not correctly initialized
  	// TODO: throw an exception here!
  }

	return dimension;
}
