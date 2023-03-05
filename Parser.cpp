#include <string>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

nlohmann::json Parser_readFile(char * filename){
	std::ifstream file(filename);
	nlohmann::json json;
	file>>json;
	return json;
}

void Parser_getScalars(char * filename,double & temperature,double & stepsize,int & nsteps,int & print,int & nmcs,int & ntss,int & nnbs,int & nthreads,bool output){
	nlohmann::json json=Parser_readFile(filename);
	temperature=json.at("temperature");
	stepsize=json.at("stepsize");
	nsteps=json.at("nsteps");
	print=json.at("print");
	nmcs=json.at("nmcs");
	ntss=json.at("ntss");
	nnbs=json.at("nnbs");
	nthreads=json.at("nthreads");
	if (output){
		std::cout<<"*** Overall settings ***"<<std::endl;
		std::cout<<"Temperature (K): "<<temperature<<std::endl;
		std::cout<<"Step size (s): "<<stepsize<<std::endl;
		std::cout<<"# of steps: "<<nsteps<<std::endl;
		std::cout<<"Frequency of printing: "<<print<<std::endl;
		std::cout<<"# of molecules and compleces: "<<nmcs<<std::endl;
		std::cout<<"# of transition states: "<<ntss<<std::endl;
		std::cout<<"# of non-barrier steps: "<<nnbs<<std::endl;
		std::cout<<"# of parallelized threads: "<<nthreads<<std::endl;
	}
}

void Parser_getVectors(char * filename,std::string * mc_labels,double * mc_gibbss,double * mc_concentrations,std::string * ts_labels,double * ts_gibbss,int * ts_nsreactants,int * ts_reactants,int * ts_nsproducts,int * ts_products,std::string * nb_labels,int * nb_nsreactants,int * nb_reactants,int * nb_nsproducts,int * nb_products,bool output){
	nlohmann::json json=Parser_readFile(filename);
	int nmcs=json.at("nmcs");
	for (int imc=0;imc<nmcs;imc++){
		mc_labels[imc]=json.at("mc_labels").at(imc);
		mc_gibbss[imc]=json.at("mc_gibbss").at(imc);
		mc_concentrations[imc]=json.at("mc_concentrations").at(imc);
	}
	int ntss=json.at("ntss");
	for (int its=0;its<ntss;its++){
		ts_labels[its]=json.at("ts_labels").at(its);
		ts_gibbss[its]=json.at("ts_gibbss").at(its);
		ts_nsreactants[its]=json.at("ts_nsreactants").at(its);
		for (int ireactant=0;ireactant<ts_nsreactants[its];ireactant++)
			ts_reactants[its*3+ireactant]=json.at("ts_reactants").at(its).at(ireactant);
		ts_nsproducts[its]=json.at("ts_nsproducts").at(its);
		for (int iproduct=0;iproduct<ts_nsproducts[its];iproduct++)
			ts_products[its*3+iproduct]=json.at("ts_products").at(its).at(iproduct);
	}
	int nnbs=json.at("nnbs");
	for (int inb=0;inb<nnbs;inb++){
		nb_labels[inb]=json.at("nb_labels").at(inb);
		nb_nsreactants[inb]=json.at("nb_nsreactants").at(inb);
		for (int ireactant=0;ireactant<nb_nsreactants[inb];ireactant++)
			nb_reactants[inb*3+ireactant]=json.at("nb_reactants").at(inb).at(ireactant);
		nb_nsproducts[inb]=json.at("nb_nsproducts").at(inb);
		for (int iproduct=0;iproduct<nb_nsproducts[inb];iproduct++)
			nb_products[inb*3+iproduct]=json.at("nb_products").at(inb).at(iproduct);
	}
	if (output){
		std::cout<<"*** Molecules and compleces ***"<<std::endl;
		for (int imc=0;imc<nmcs;imc++){
			std::cout<<"MC "<<imc<<":"<<std::endl;
			std::cout<<" Label: "<<mc_labels[imc]<<std::endl;
			std::cout<<" Gibbs free energy (kcal/mol): "<<mc_gibbss[imc]<<std::endl;
			std::cout<<" Concentrations (mol/L): "<<mc_concentrations[imc]<<std::endl;
		}
		std::cout<<std::endl;
		for (int its=0;its<ntss;its++){
			std::cout<<"*** Transition states ***"<<std::endl;
			std::cout<<"TS "<<its<<":"<<std::endl;
			std::cout<<" Label: "<<ts_labels[its]<<std::endl;
			std::cout<<" Gibbs free energy (kcal/mol): "<<ts_gibbss[its]<<std::endl;
			std::cout<<" Reactants:";
			for (int ireactant=0;ireactant<ts_nsreactants[its];ireactant++)
				std::cout<<" "<<ts_reactants[its*3+ireactant];
			std::cout<<std::endl;
			std::cout<<" Products:";
			for (int iproduct=0;iproduct<ts_nsproducts[its];iproduct++)
				std::cout<<" "<<ts_products[its*3+iproduct];
			std::cout<<std::endl;
		}
		std::cout<<std::endl;
		for (int inb=0;inb<nnbs;inb++){
			std::cout<<"*** Non-barrier steps ***"<<std::endl;
			std::cout<<"NB "<<inb<<":"<<std::endl;
			std::cout<<" Label: "<<nb_labels[inb]<<std::endl;
			std::cout<<" Reactants:";
			for (int ireactant=0;ireactant<nb_nsreactants[inb];ireactant++)
				std::cout<<" "<<nb_reactants[inb*3+ireactant];
			std::cout<<std::endl;
			std::cout<<" Products:";
			for (int iproduct=0;iproduct<nb_nsproducts[inb];iproduct++)
				std::cout<<" "<<nb_products[inb*3+iproduct];
			std::cout<<std::endl;
		}
	}
}


#ifndef NDEBUG
int main(int argc,char * argv[]){

	double temperature,stepsize;
	int nsteps,print,nmcs,ntss,nnbs,nthreads;
	Parser_getScalars(argv[1],temperature,stepsize,nsteps,print,nmcs,ntss,nnbs,nthreads,1);
	
	std::string mc_labels[nmcs];
	double mc_gibbss[nmcs];
	double mc_concentrations[nmcs];
	std::string ts_labels[ntss];
	double ts_gibbss[ntss];
	int ts_nsreactants[ntss];
	int ts_reactants[3*ntss];
	int ts_nsproducts[ntss];
	int ts_products[3*ntss];
	std::string nb_labels[nnbs];
	int nb_nsreactants[nnbs];
	int nb_reactants[3*nnbs];
	int nb_nsproducts[nnbs];
	int nb_products[3*nnbs];
	Parser_getVectors(argv[1],mc_labels,mc_gibbss,mc_concentrations,ts_labels,ts_gibbss,ts_nsreactants,ts_reactants,ts_nsproducts,ts_products,nb_labels,nb_nsreactants,nb_reactants,nb_nsproducts,nb_products,1);

	return 0;
}
#endif
