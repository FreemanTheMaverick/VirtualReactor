#include <string>
#include <ctime>
#include "Mumbler.h"
#include "Parser.h"
#include "Simulator.h"


int main(int argc,char * argv[]){

	clock_t start=Mumbler_Welcome();

	std::string method;
	double temperature,stepsize;
	int nsteps,print,nmcs,ntss,nnbs;
	Parser_getScalars(argv[1],method,temperature,stepsize,nsteps,print,nmcs,ntss,nnbs,1);
	
	std::string mc_labels[nmcs];
	double mc_gibbss[nmcs];
	double mc_concentrations[nmcs];
	int mc_nsrtss[nmcs];
	int mc_rtss[nmcs*3];
	int mc_nsptss[nmcs];
	int mc_ptss[nmcs*3];
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
	Parser_getVectors(argv[1],mc_labels,mc_gibbss,mc_concentrations,mc_nsrtss,mc_rtss,mc_nsptss,mc_ptss,ts_labels,ts_gibbss,ts_fbarriers,ts_frcs,ts_bbarriers,ts_brcs,ts_nsreactants,ts_reactants,ts_nsproducts,ts_products,nb_labels,nb_nsreactants,nb_reactants,nb_nsproducts,nb_products,1);
	int mc_nstss[nmcs];
	for (int imc=0;imc<nmcs;imc++)
		mc_nstss[imc]=mc_nsrtss[imc]+mc_nsptss[imc];

	Simulator_writeHeaders(nmcs,mc_labels);
	if (method.compare("Eular"))
		Simulator_runEuler(stepsize,nsteps,print,nmcs,ntss,mc_concentrations,ts_nsreactants,ts_reactants,ts_nsproducts,ts_products,mc_nstss,ts_frcs,ts_brcs,1);

	Mumbler_Goodbye(start);
	return 0;
}
