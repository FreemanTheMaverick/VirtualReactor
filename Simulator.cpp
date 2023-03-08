#include <string>
#include <iostream>
#include <ctime>
#include <omp.h>
#include "Parameters.h"


void Simulator_Prepare(std::string method,double stepsize,int nsteps,int print,int nmcs,int ntss,int nthreads,std::string * mc_labels,double * mc_concentrations,std::string * ts_labels,double * ts_frcs,double * ts_brcs,int * ts_nsreactants,int * ts_reactants,int * ts_nsproducts,int * ts_products,bool output){

	if (output) std::cout<<"*** Memory allocation ***"<<std::endl;

	int mc_nsrtss[nmcs];
	int mc_nsptss[nmcs];
	int mc_rtss[nmcs*3];
	int mc_ptss[nmcs*3];
	double mc_rates[nmcs*6];
	if (output) std::cout<<"Addresses where to save concentration evolution rates:"<<std::endl;
	for (int imc=0;imc<nmcs;imc++){
		if (output) std::cout<<" MC"<<imc<<":";
		mc_nsrtss[imc]=0;
		mc_nsptss[imc]=0;
		for (int jts=0;jts<ntss;jts++){
			bool found=0;
			for (int kreactant=0;kreactant<ts_nsreactants[jts] && not found;kreactant++){
				if (ts_reactants[jts*3+kreactant]==imc){
					found=1;
					if (output) std::cout<<" "<<&mc_rates[imc*6+mc_nsrtss[imc]+mc_nsptss[imc]]<<"(as a reactant of TS"<<jts<<")";
					mc_rtss[imc*3+mc_nsrtss[imc]]=jts;
					mc_nsrtss[imc]++;
				}
			}
			for (int kproduct=0;kproduct<ts_nsproducts[jts] && not found;kproduct++){
				if (ts_products[jts*3+kproduct]==imc){
					found=1;
					if (output) std::cout<<" "<<&mc_rates[imc*6+mc_nsrtss[imc]+mc_nsptss[imc]]<<"(as a product of TS"<<jts<<")";
					mc_ptss[imc*3+mc_nsptss[imc]]=jts;
					mc_nsptss[imc]++;
				}
			}
		}
		std::cout<<std::endl;
	}
	int mc_tsindeces[nmcs];
	for (int imc=0;imc<nmcs;imc++){
		mc_tsindeces[imc]=imc*6;
	}
	double* ts_rate_addresses[ntss*6];
	for (int its=0;its<ntss;its++){
		if (output) std::cout<<" TS"<<its<<":";
		int jmc=0;
		for (int kmc=0;kmc<nmcs;kmc++){
			for (int lts=0;lts<mc_nsrtss[kmc];lts++){
				if (its==mc_rtss[kmc*3+lts]){
					ts_rate_addresses[its*6+jmc]=&mc_rates[mc_tsindeces[kmc]];
					if (output) std::cout<<" "<<ts_rate_addresses[its*6+jmc]<<"(MC"<<kmc<<")";
					jmc++;
					mc_tsindeces[kmc]++;
				}
			}
		}
		if (jmc==ts_nsreactants[its]) std::cout<<" -->";
		for (int kmc=0;kmc<nmcs;kmc++){
			for (int lts=0;lts<mc_nsptss[kmc];lts++){
				if (its==mc_ptss[kmc*3+lts]){
					ts_rate_addresses[its*6+jmc]=&mc_rates[mc_tsindeces[kmc]];
					if (output) std::cout<<" "<<ts_rate_addresses[its*6+jmc]<<"(MC"<<kmc<<")";
					jmc++;
					mc_tsindeces[kmc]++;
				}
			}
		}
		if (output) std::cout<<std::endl;
	}
}
