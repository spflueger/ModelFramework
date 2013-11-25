/*
 * ROOTPlotter.cxx
 *
 *  Created on: Jun 14, 2013
 *      Author: steve
 */

#include "ROOTPlotter.h"
#include "ModelVisualizationProperties1D.h"

#include "TGraphErrors.h"

#include <iostream>

ROOTPlotter::ROOTPlotter() {
	// TODO Auto-generated constructor stub

}

ROOTPlotter::~ROOTPlotter() {
	// TODO Auto-generated destructor stub
}

TGraphErrors* ROOTPlotter::createGraphFromModel1D(shared_ptr<Model> model,
		ModelVisualizationProperties1D &visualization_properties) {

	TGraphErrors* graph = new TGraphErrors(
			visualization_properties.getEvaluations());

	if (model->init()) {
		std::cout << "Error: not all parameters have been set!" << std::endl;
	}

	double stepsize = (visualization_properties.getPlotRange().range.second
			- visualization_properties.getPlotRange().range.first)
			/ visualization_properties.getEvaluations();
	double x;
	double xtrue;
	for (unsigned int i = 0; i < visualization_properties.getEvaluations(); i++) {
		x = visualization_properties.getPlotRange().range.first + stepsize * i;
		xtrue = x * visualization_properties.getPlotRange().unit_factor;
		graph->SetPoint(
				i,
				x,
				model->evaluate(&xtrue) * visualization_properties.getBinningFactor()
						* visualization_properties.getPlotRange().unit_factor);
		graph->SetPointError(i, 0, 0);
	}
	return graph;
}
