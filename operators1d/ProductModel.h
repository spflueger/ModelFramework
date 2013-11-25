/*
 * ProductModel.h
 *
 *  Created on: Jan 10, 2013
 *      Author: steve
 */

#ifndef PRODUCTMODEL_H_
#define PRODUCTMODEL_H_

#include "Model.h"

class ProductModel: public Model {
private:
	shared_ptr<Model> first, second;
public:
	ProductModel(std::string name_, shared_ptr<Model> first_,
			shared_ptr<Model> second_);

	void initModelParameters();

	double eval() const;

	void updateDomain();
};

#endif /* PRODUCTMODEL_H_ */
