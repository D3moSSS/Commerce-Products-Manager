#include "test.h"
#include "assert.h"
#include <iostream>
#include "Validator.h"
#include <map>
#include "MyExceptie.h"
#include "ProductRepoProb.h"


void test::testCreare() noexcept{
	Product pr("312312", "321312", 123, "dsad");
	vector<Product> vc;
	vc.push_back(pr);
	ProductRepo repo(vc);
	Cos cos(repo);
	ProductServ serv(repo,cos);
	assert(repo.size() == 1);
	assert(serv.size() == 1);

	const ProductRepo& Repo2 = serv.getAll();

	Product pr1 = Repo2.get_i(0);
	pr.setName("vasilica");
	pr.setType("banana");
	pr.setPrice(13);
	pr.setProducer("Mihai");

	assert(pr.getName() == "vasilica");
	assert(pr.getType()  == "banana");
	assert(pr.getPrice() == 13);
	assert(pr.getProducer() == "Mihai");

}
void test::testAdaugare() {

	int price = Validator::validatePrice("123");
	int price1 = Validator::validatePrice("dsa");
	assert(price == 123);
	assert(price1 == -1);
	Product pr("312312", "321312", 123, "dsad");
	ProductRepo repo;
	repo.addProduct(pr);
	repo.addProduct(pr);
	repo.addProduct(pr);
	repo.addProduct(pr);
	repo.addProduct(pr);
	repo.addProduct(pr);
	repo.addProduct(pr);
	repo.addProduct(pr);
	repo.addProduct(pr);
	repo.addProduct(pr);
	repo.addProduct(pr);
	repo.addProduct(pr);
	ProductRepo repo1 = repo.getAll();
	repo1 = repo;
	Cos cos(repo);
	ProductServ serv(repo,cos);
	Product pr2 = serv.get_i(0);

	assert(serv.size() == 12);
	try {
		serv.addProduct(pr);
	}catch(...){
		assert(true);
	}
}

void test::testStergere() {
	Product pr("312312", "321312", 123, "dsad");
	ProductRepo repo;
	Cos cos(repo);
	ProductServ serv(repo ,cos);
	Product pr1("31231211", "321312", 123, "dsad");
	serv.addProduct(pr);
	serv.addProduct(pr1);
	serv.deleteProduct(pr1.getName());
	assert(serv.size() == 1);

	try {
		serv.deleteProduct(pr1.getName());
	}
	catch (...) {
		assert(true);
	}
}

void test::testUpdate() {
	Product pr("312312", "321312", 123, "dsad");
	ProductRepo repo;
	Cos cos(repo);
	ProductServ serv(repo,cos);
	Product pr1("312312", "sad", 41, "fds");
	serv.addProduct(pr);
	serv.modifyProduct("312312" , pr1);
	ProductRepo repo1 = serv.getAll();

	assert(repo1[0].getType() == "sad");
	assert(repo1[0].getPrice() == 41);
	assert(repo1[0].getProducer() == "fds");

	try {
		serv.modifyProduct("Vasile" , pr);
	}
	catch (...) {
		assert(true);
	}


}
void test::testCautare() {

	Product pr("312312", "321312", 123, "dsad");
	ProductRepo repo;
	Cos cos(repo);
	ProductServ serv(repo,cos);
	serv.addProduct(pr);

	const int& i = Validator::validateName(pr.getName(), serv.getAll());
	assert(i == 0);

	Product pr1 = serv.cautare(pr);
	assert(pr1 == pr);
	Product pr2("312312d", "321312", 123, "dsad");
	try {
		serv.cautare(pr2);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void test::testPrint() {

	Product pr("312312", "321312", 123, "dsad");
	ProductRepo repo;
	Cos cos(repo);
	ProductServ serv(repo, cos);
	serv.addProduct(pr);


}

void test::testOperator() {

	Product pr("312312", "321312", 123, "dsad");
	Product pr1("312313", "321312", 123, "dsad");
	Product pr2("312312", "321313", 123, "dsad");
	Product pr3("312312", "321312", 124, "dsad");
	Product pr4("312312", "321312", 123, "dsadd");

	ProductRepo rep;
	rep.addProduct(pr);
	Cos cos(rep);
	ProductServ serv(rep, cos);
	Product c = serv[0];
	assert(c.getName() == "312312");
	assert(pr == pr1 == 0);
	assert(pr == pr2 == 0);
	assert(pr == pr3 == 0);
	assert(pr == pr4 == 0);
	assert(pr == pr == 1);

	assert(pr != pr1 == 1);
	assert(pr != pr2 == 1);
	assert(pr != pr3 == 1);
	assert(pr != pr4 == 1);
	assert(pr != pr == 0);
}

void test::testSort() {

	ProductRepo c;
	Product pr("vasile1", "popescu", 1, "dasdas");
	c.addProduct(pr);
	pr = Product("vasile2", "popescu2", 3, "dasdas");
	c.addProduct(pr);
	pr = Product("vasile4", "popescu2", 4, "dasdas");
	c.addProduct(pr);
	pr = Product("vasile3", "popescu", 2, "dasdas");
	c.addProduct(pr);
	pr = Product("vasile6", "popesca", 5, "dasdas");
	c.addProduct(pr);
	pr = Product("vasile6", "popescu", 7, "dasdas");
	c.addProduct(pr);
	pr = Product("vasile6", "popescp", 9, "dasdas");
	c.addProduct(pr);
	pr = Product("vasile7", "popesc", 6, "dasdas");
	c.addProduct(pr);

	Cos cos(c);
	ProductServ serv(c, cos);

	ProductRepo rep_sort = serv.sort(0,cmp_name);
	assert(rep_sort[0].getName() == "vasile1");
	rep_sort = serv.sort(1, cmp_name);
	assert(rep_sort[0].getName() == "vasile7");
	rep_sort = serv.sort(0, cmp_price);
	assert(rep_sort[0].getPrice() == 1);
	rep_sort = serv.sort(1, cmp_price);
	assert(rep_sort[0].getPrice() == 9);
	rep_sort = serv.sort(0, cmp_name_type);
	assert(rep_sort[0].getType() == "popescu");
	rep_sort = serv.sort(1, cmp_name_type);
	assert(rep_sort[3].getType() == "popesca");


}

void test::filtrare() {

	ProductRepo c;
	Product pr("vasile1", "popescu", 1, "dasdas");
	c.addProduct(pr);
	pr = Product("vasile2", "popescu2", 3, "dasdas");
	c.addProduct(pr);
	pr = Product("vasile2", "popescu2", 4, "dasdas");
	c.addProduct(pr);
	pr = Product("vasile4", "popescu", 2, "dasdas");
	c.addProduct(pr);
	pr = Product("vasile3", "popesca", 5, "dasdas");
	c.addProduct(pr);
	pr = Product("vasile3", "popescu", 7, "dasdas");
	c.addProduct(pr);
	pr = Product("vasile3", "popesc", 6, "dasdassad");
	c.addProduct(pr);

	Cos cos(c);
	ProductServ serv(c, cos);

	vector<Product> rez = serv.filtrare("1", "vasile2");
	assert(rez.size() == 2);
	rez = serv.filtrare("2", "dasdas");
	assert(rez.size() == 6);
	rez = serv.filtrare("3", "2");
	assert(rez.size() == 1);

}

void test::costest() {

	ProductRepo c;
	Product pr("vasile1", "popescu", 1, "dasdas");
	c.addProduct(pr);
	Cos cos(c);
	ProductServ serv(c , cos);

	serv.adaugaCos(pr);
	assert(serv.size_cos() == 1);

	serv.randomADD_serv(5);
	assert(serv.size_cos() == 6);

	vector<Product> cos2 = serv.getAll_cos();
	assert(cos2.size() == 6);


	serv.emptyCos();
	assert(serv.size_cos() == 0);



}

void test::raportType() {

	ProductRepoProb c;
	c.setPrb1000();
	Product pr("vasile1", "popescu", 1, "dasdas");
	c.addProduct(pr);
	Product pr1("vasile2", "popescu", 1, "dasdas");
	c.addProduct(pr1);
	Product pr2("vasile3", "popescu", 1, "dasdas");
	c.addProduct(pr2);
	Product pr3("vasile4", "popescu2", 1, "dasdas");
	c.addProduct(pr3);
	Product pr4("vasile5", "popescu2", 1, "dasdas");
	c.addProduct(pr4);
	c.deleteProduct("vasile5");
	c.addProduct(pr4);
	c.modifyProduct("vasile5", pr3);
	vector<Product> vec = c.getAll_1();
	Product pr9 = c[0];
	pr9 = c.get_i(0);
	c.size();
	try {
		c[10];
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		c.get_i(10);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	Product mr("asda", "Das", 12, "ASd");
	Product m = c.cautare(pr1);
	try {
		c.cautare(mr);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	Cos cos(c);
	ProductServ serv(c, cos);

	map<string, DTO> dic = serv.raportType();
	assert(dic["popescu"].getNr() == 3);
	assert(dic["popescu2"].getNr() == 2);
	assert(dic["popescu"].getType() == "popescu");
	assert(dic["popescu2"].getType() == "popescu2");
}

void test::undo() {

	try {
		ProductRepoFile c1("a");
		assert(false);
	}
	catch (MyException& ca) {
		assert(ca.what() == "Can't open file a");
	}

	ProductRepoFile c("testProduse.txt");
	Cos cos(c);
	ProductServ serv(c, cos);

	try {
		serv.undo();
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	Product pr("vasile1", "popescu", 1, "dasdas");
	serv.addProduct(pr);
	Product pr1("vasile2", "popescu", 1, "dasdas");
	serv.addProduct(pr1);
	Product pr2("vasile3", "popescu", 1, "dasdas");
	serv.addProduct(pr2);
	Product pr3("vasile4", "popescu2", 1, "dasdas");
	serv.addProduct(pr3);
	Product pr4("vasile5", "popescu2", 1, "dasdas");
	serv.addProduct(pr4);

	serv.undo();
	assert(serv.size() == 5);

	Product pr6("vasile1", "a", 2, "a");
	serv.modifyProduct("vasile1", pr6);

	Product p = serv.get_i(1);

	assert(p.getType() == "a");
	serv.undo();
	Product p1 = serv.get_i(1);
	assert(p1.getType() == "popescu");
	serv.randomADD_serv(10);
	serv.deleteProduct("vasile1");
	serv.undo();
	serv.deleteProduct("vasile1");
	serv.deleteProduct("vasile2");
	serv.deleteProduct("vasile3");
	serv.deleteProduct("vasile4");
	assert(serv.size() == 1);
	serv.exportHTML("test.html");
	serv.exportCSV("test.csv");
}


void test::testALL() {
	testCreare();
	testAdaugare();
	testStergere();
	testUpdate();
	testCautare();
	testPrint();
	testOperator();
	testSort();
	filtrare();
	costest();
	raportType();
	undo();
}


