void Simulator_writeHeaders(int nmcs,std::string * mc_labels);

void Simulator_runEuler(double stepsize,int nsteps,int print,int nmcs,int ntss,double * mc_concentrations,int * ts_nsreactants,int * ts_reactants,int * ts_nsproducts,int * ts_products,int * mc_nstss,double * ts_frcs,double * ts_brcs,bool output);
