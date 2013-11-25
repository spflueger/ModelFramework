/*
 * ProductModel.cxx
 *
 *  Created on: Jan 10, 2013
 *      Author: steve
 */

#include "ProductModel.h"

#include <iostream>

ProductModel::ProductModel(std::string name_, shared_ptr<Model> first_,
		shared_ptr<Model> second_) :
		Model1D(name_) {
	first = first_;
	second = second_;

	addModelToList(first);
	addModelToList(second);
}

void ProductModel::initModelParameters() {

}

double ProductModel::eval() const {
	return first->eval() * second->eval();
}

void ProductModel::updateDomain() {
	// first we need to check if user defined a domain for his models
	if (first->getDomainRange() == 0 || second->getDomainRange() == 0) {
		std::cout
				<< "Warning: Some of the models used for the multiplication have not"
						" defined any domains!" << std::endl;
	} else {
		setDomain(std::max(first->getDomain().first, second->getDomain().first),
				std::min(first->getDomain().second, second->getDomain().second));
	}
}
