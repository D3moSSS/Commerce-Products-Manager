#pragma once
#include <qapplication.h>
#include <iostream>
#include "UiProducts.h"
#include <iterator>
#include "test.h"
#include <vector>
#include "undo.h"
#include "ProductRepoProb.h"
#include "gui.h"

using namespace std;

int main(int argc , char* argv[]) {
	test test;
	test.testALL();
	ProductRepoFile repo("produse.txt");
	QApplication a(argc, argv);
	//ProductRepoProb repo;
	//ProductRepo repo;
	Cos cos(repo);
	ProductServ serv(repo, cos);
	//UiProducts ui(serv);
	//ui.meniu();
	MdGUI gui{ serv };
	gui.setWindowTitle("Produse din comert");
	gui.resize(900, 550);
	gui.show();

	return a.exec();
}