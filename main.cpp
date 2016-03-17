#include"myimage.h"
#include"fileio.h"
#include"imageprocess.h"
#include <iostream>
int main(int argc, char** argv){
	
	ImageProcess ip;
	MyImage m1;
	MyImage m2;
	std::vector<char*> fl;
	
	if(argc!=3){
		system("cat man");
		exit(0);
	}

	FileIO::getInstance().listFile(fl, argv[1]);

	std::cout << "Merging \t1/" << fl.size() << "   ..." << std::endl;

	char* name = new char[100];
	strcpy(name, argv[1]);
	strcat(name, "/");
	strcat(name, fl[0]);
	FileIO::getInstance().readFromFileToImage(m1,name);
	delete name;

	for(int i = 1; i< fl.size(); i++){

		std::cout << "Merging \t"<< i+1 << "/" << fl.size() << "  ..." << std::endl;
		char* name = new char[100];
		strcpy(name, argv[1]);
		strcat(name, "/");
		strcat(name, fl[i]);
		FileIO::getInstance().readFromFileToImage(m2,name);
		ip.lighterMergeWith(m1,m2);
		delete name;
	}
	
	FileIO::getInstance().writeImageToFile(m1,argv[2]);
	std::cout << "done!" << std::endl; 

}
