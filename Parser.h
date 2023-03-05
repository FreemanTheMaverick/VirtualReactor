void Parser_getScalars(char * filename,double & temperature,double & stepsize,int & nsteps,int & print,int & nmcs,int & ntss,int & nnbs,int & nthreads,bool output);

void Parser_getVectors(char * filename,std::string * mc_labels,double * mc_gibbss,double * mc_concentrations,std::string * ts_labels,double * ts_gibbss,double * ts_fbarriers,double * ts_frcs,double * ts_bbarriers,double * ts_brcs,int * ts_nsreactants,int * ts_reactants,int * ts_nsproducts,int * ts_products,std::string * nb_labels,int * nb_nsreactants,int * nb_reactants,int * nb_nsproducts,int * nb_products,bool output);
