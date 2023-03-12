#include <string>
#include <iostream>
#include <ctime>
#include "Parameters.h"


void Simulator_writeHeaders(int nmcs,std::string * mc_labels){
	std::cout<<"*** Simulation started ***"<<std::endl;
	std::cout<<" step,time(s)";
	for (int imc=0;imc<nmcs;imc++)
		std::cout<<",concentration of "<<mc_labels[imc];
	for (int imc=0;imc<nmcs;imc++)
		std::cout<<",rate of "<<mc_labels[imc];
	std::cout<<std::endl;
}

void Simulator_runEuler(double stepsize,long int nsteps,long int print,int nmcs,int ntss,double * mc_concentrations,int * ts_nsreactants,int * ts_reactants,int * ts_nsproducts,int * ts_products,int * mc_nstss,double * ts_frcs,double * ts_brcs,bool output){
	for (long int istep=0;istep<nsteps;istep++){
		double mc_rates[nmcs]={0};
		for (int its=0;its<ntss;its++){
			int nreactants=ts_nsreactants[its];
			int nproducts=ts_nsproducts[its];
			double frate=ts_frcs[its];
			for (int jmc=0;jmc<nreactants;jmc++)
				frate*=mc_concentrations[ts_reactants[its*3+jmc]];
			double brate=ts_brcs[its];
			for (int jmc=0;jmc<nproducts;jmc++)
				brate*=mc_concentrations[ts_products[its*3+jmc]];
			for (int jmc=0;jmc<nreactants;jmc++)
				mc_rates[ts_reactants[its*3+jmc]]+=-frate+brate;
			for (int jmc=0;jmc<nproducts;jmc++)
				mc_rates[ts_products[its*3+jmc]]+=frate-brate;
//if (its==2 && istep%print==0) std::cout<<mc_rates[3]<<std::endl;
		}
		for (int imc=0;imc<nmcs;imc++)
			mc_concentrations[imc]+=mc_rates[imc]*stepsize;
		if (output && istep%print==0){
			std::cout<<istep<<","<<istep*stepsize;
			for (int imc=0;imc<nmcs;imc++)
				std::cout<<","<<mc_concentrations[imc];
			for (int imc=0;imc<nmcs;imc++)
				std::cout<<","<<mc_rates[imc];
			std::cout<<std::endl;
		}
	}
	if (output) std::cout<<std::endl;
}






/*
void Simulator_Prepare(int nmcs,int ntss,double * mc_concentrations,int * ts_nsreactants,int * ts_reactants,int * ts_nsproducts,int * ts_products,int * mc_nstss,double * mc_rates,double* * ts_concentration_addresses,double* * ts_rate_addresses,bool output){

	if (output) std::cout<<"*** Memory allocation ***"<<std::endl;

	int mc_nsrtss[nmcs];
	int mc_nsptss[nmcs];
	int mc_rtss[nmcs*3];
	int mc_ptss[nmcs*3];

	if (output){
		std::cout<<"Addresses in which to save concentrations:"<<std::endl;
		for (int imc=0;imc<nmcs;imc++){
			std::cout<<" MC"<<imc<<":";
			std::cout<<" "<<&mc_concentrations[imc]<<std::endl;
		}
	}

	for (int its=0;its<ntss;its++){
		if (output) std::cout<<" TS"<<its<<":";
		for (int jmc=0;jmc<ts_nsreactants[its];jmc++){
			ts_concentration_addresses[its*6+jmc]=&mc_concentrations[ts_reactants[its*3+jmc]];
			if (its==0&&jmc==0){
}
			if (output) std::cout<<" "<<&mc_concentrations[ts_reactants[its*3+jmc]]<<"("<<ts_reactants[its*3+jmc]<<")";
		}
		if (output) std::cout<<" -->";
		for (int jmc=0;jmc<ts_nsproducts[its];jmc++){
			ts_concentration_addresses[its*6+ts_nsreactants[its]+jmc]=&mc_concentrations[ts_products[its*3+jmc]];
			if (output) std::cout<<" "<<&mc_concentrations[ts_products[its*3+jmc]]<<"("<<ts_products[its*3+jmc]<<")";
		}
		if (output) std::cout<<std::endl;
	}

	if (output) std::cout<<"Addresses in which to save concentration evolution rates:"<<std::endl;
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
		mc_nstss[imc]=mc_nsrtss[imc]+mc_nsptss[imc];
	}
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
		if (jmc==ts_nsreactants[its] and output) std::cout<<" -->";
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
	if (output) std::cout<<std::endl;
}
*/
