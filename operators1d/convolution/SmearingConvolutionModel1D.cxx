/*
 * SmearingConvolutionModel1D.cxx
 *
 *  Created on: Jul 9, 2013
 *      Author: steve
 */

#include "SmearingConvolutionModel1D.h"

#include <iostream>

SmearingConvolutionModel1D::SmearingConvolutionModel1D(std::string name_,
		shared_ptr<Model1D> first_, shared_ptr<Model1D> second_) :
		Model1D(name_) {
	first = first_;
	second = second_;
	addModelToList(first);
	addModelToList(second);

	//set some properties of the convolution
	divisions = 300;
}

SmearingConvolutionModel1D::~SmearingConvolutionModel1D() {
	// TODO Auto-generated destructor stub
}

void SmearingConvolutionModel1D::initModelParameters() {

}

double SmearingConvolutionModel1D::eval(const double *x) const {
	// slice the function

	// for each slice

	// integrate each part

	// then scale the normed version of the other function at that postition
	// with the integral value

	// then evaluate the scaled function at the position x

	// accumulate all values and return
}

void SmearingConvolutionModel1D::updateDomain() {
	// first we need to check if user defined a domain for his models
	if (first->getDomainRange() == 0) {
		std::cout << "Warning: The domain of the model " << first->getName()
				<< " used for the convolution is not defined!" << std::endl;
	} else if (second->getDomainRange() == 0) {
		std::cout << "Warning: The domain of the model " << second->getName()
				<< " used for the convolution is not defined!" << std::endl;
	} else {
		setDomain(first->getDomain().first + second->getDomain().first,
				first->getDomain().second + second->getDomain().second);
	}
}
