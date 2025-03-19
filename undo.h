#pragma once
#include "Product.h"
#include "ProductRepo.h"

class undoAction {
public:
	void virtual doUndo()=0;
	virtual ~undoAction() = default;
};


class undoAdd : public undoAction {
	Product prd;
	repoAbstract& repo;
public:

	undoAdd(repoAbstract& repo , const Product& prd) : prd{ prd }, repo{ repo } {}

	void doUndo() override {
		repo.deleteProduct(prd.getName());
	}
};

class undoDelete : public undoAction {
	Product prd;
	repoAbstract& repo;
public:
	undoDelete(repoAbstract& repo , const Product& prd) : prd{ prd }, repo{ repo } {}

	void doUndo() override {
		repo.addProduct(prd);
	}
};

class undoModify : public undoAction {
private:
	Product pr;
	Product newpr;
	repoAbstract& repo;
public:
	undoModify(Product& pr, Product& newpr, repoAbstract& repo) : pr{ pr }, newpr{ newpr }, repo{ repo } {}

	void doUndo() override {
		repo.modifyProduct(pr.getName(), newpr);
	}
};