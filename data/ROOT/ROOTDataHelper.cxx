/*
 * ROOTDataHelper.cxx
 *
 *  Created on: Jun 15, 2013
 *      Author: steve
 */

#include "ROOTDataHelper.h"
#include "Data.h"

#include "TH1D.h"
#include "TGraphErrors.h"

#include <iostream>

ROOTDataHelper::ROOTDataHelper() {
	// TODO Auto-generated constructor stub

}

ROOTDataHelper::~ROOTDataHelper() {
	// TODO Auto-generated destructor stub
}

void ROOTDataHelper::fillHistogramData(shared_ptr<Data> data,
		const TH1D* hist_1d) const {
	data->clearData();

	DataStructs::measurement_coordiante temp_coordinate;

	for (int i = 1; i <= hist_1d->GetNbinsX(); i++) {
		shared_ptr<DataStructs::binned_data_point> datapoint(
				new DataStructs::binned_data_point());
		temp_coordinate.value = hist_1d->GetBinCenter(i);
		temp_coordinate.error_low = hist_1d->GetBinWidth(i)/2.0;
		temp_coordinate.error_high = temp_coordinate.error_low;
		datapoint->point.coordinates.push_back(temp_coordinate);
		datapoint->scaling_factor = hist_1d->GetBinWidth(i);
		datapoint->scaling_factor_active = true;

		datapoint->value = hist_1d->GetBinContent(i);
		datapoint->value_error = hist_1d->GetBinError(i);

		if (datapoint->value <= 0.0)
			continue;

		DataPointProxy dpp;
		dpp.setBinnedDataPoint(datapoint);
		data->insertDataPoint(dpp);
	}
}

void ROOTDataHelper::fillGraphData(shared_ptr<Data> data,
		const TGraphErrors* graph_1d) const {
	data->clearData();

	DataStructs::measurement_coordiante temp_coordinate;
	double y;

	for (int i = 1; i <= graph_1d->GetN(); i++) {
		shared_ptr<DataStructs::binned_data_point> datapoint(
				new DataStructs::binned_data_point());
		graph_1d->GetPoint(i, temp_coordinate.value, y);
		temp_coordinate.error_low = graph_1d->GetErrorX(i)/2.0;
		temp_coordinate.error_high = temp_coordinate.error_low;
		datapoint->point.coordinates.push_back(temp_coordinate);
		datapoint->value = y;
		datapoint->value_error = graph_1d->GetErrorY(i);

		if (datapoint->value_error == 0.0)
		  continue;

		DataPointProxy dpp;
		dpp.setBinnedDataPoint(datapoint);
		data->insertDataPoint(dpp);
	}
}
