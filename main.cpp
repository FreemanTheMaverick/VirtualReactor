#include <string>
#include <iostream>
#include "Parser.h"

int main(int argc,char * argv[]){

	double temperature,stepsize;
	int nsteps,print,nmcs,ntss,nnbs,nthreads;
	Parser_getScalars(argv[1],temperature,stepsize,nsteps,print,nmcs,ntss,nnbs,nthreads,1);
	
	std::string mc_labels[nmcs];
	double mc_gibbss[nmcs];
	double mc_concentrations[nmcs];
	std::string ts_labels[ntss];
	double ts_gibbss[ntss];
	double ts_fbarriers[ntss];
	double ts_frcs[ntss];
	double ts_bbarriers[ntss];
	double ts_brcs[ntss];
	int ts_nsreactants[ntss];
	int ts_reactants[3*ntss];
	int ts_nsproducts[ntss];
	int ts_products[3*ntss];
	std::string nb_labels[nnbs];
	int nb_nsreactants[nnbs];
	int nb_reactants[3*nnbs];
	int nb_nsproducts[nnbs];
	int nb_products[3*nnbs];
	Parser_getVectors(argv[1],mc_labels,mc_gibbss,mc_concentrations,ts_labels,ts_gibbss,ts_fbarriers,ts_frcs,ts_bbarriers,ts_brcs,ts_nsreactants,ts_reactants,ts_nsproducts,ts_products,nb_labels,nb_nsreactants,nb_reactants,nb_nsproducts,nb_products,1);

	return 0;
}
