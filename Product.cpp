#include "Product.h"
#include <iostream>

using std::string;

Product::Product(string name, string type, int price, string producer) {
	this->name = name;
	this->price = price;
	this->producer = producer;
	this->type = type;
}

Product::Product(const Product& other) {
	this->name = other.name;
	this->type = other.type;
	this->price = other.price;
	this->producer = other.producer;

}

string Product::getName() const {
	return this->name;
}

string Product::getType() const {
	return this->type;
}

int Product::getPrice() const noexcept{
	return this->price;
}

string Product::getProducer() const {
	return this->producer;
}

void Product::setName(string nameNew){
	this->name = nameNew;
}

void Product::setType(string typeNew){
	this->type = typeNew;
}

void Product::setPrice(int priceNew){
	this->price = priceNew;
}

void Product::setProducer(string producerNew){
	this->producer = producerNew;
}


void Product::operator =(const Product& pr) noexcept {

	this->setName(pr.getName());
	this->setType(pr.getType());
	this->setPrice(pr.getPrice());
	this->setProducer(pr.getProducer());
}


int Product::operator ==(const Product& pr) const noexcept{

	if (this->name == pr.name)
		if (this->type == pr.type)
			if (this->price == pr.price)
				if (this->producer == pr.producer)
					return 1;
				else
					return 0;
			else
				return 0;
		else
			return 0;
	else
		return 0;

}

int Product::operator !=(const Product& pr) const noexcept{

	if (this->name == pr.name)
		if (this->type == pr.type)
			if (this->price == pr.price)
				if (this->producer == pr.producer)
					return 0;
				else
					return 1;
			else
				return 1;
		else
			return 1;
	else
		return 1;

}

std::ostream& operator<<(std::ostream& cout, const Product& product)
{
	cout << "Name: " << product.getName() << "| Type: " << product.getType() << "| Price: " << std::to_string(product.getPrice()) << "| producer: " << product.getProducer();
	return cout;
}

bool cmp_name(const Product& pr1, const Product& pr2) {
	if (pr1.getName() < pr2.getName())
		return true;
	else
		return false;
}

bool cmp_price(const Product& pr1, const Product& pr2) {
	if (pr1.getPrice() < pr2.getPrice())
		return true;
	else
		return false;
}

bool cmp_name_type(const Product& pr1, const Product& pr2) {
	if (pr1.getName() < pr2.getName())
		return true;
	else if (pr1.getName() == pr2.getName())
		if (pr1.getType() < pr2.getType())
			return true;
		else
			return false;
	else
		return false;
}