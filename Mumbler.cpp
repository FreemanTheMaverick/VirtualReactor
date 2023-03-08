#include <string>
#include <ctime>
#include <iostream>

clock_t Mumbler_Welcome(){
	std::cout<<"***************************************************************"<<std::endl;
	std::cout<<"*                                                             *"<<std::endl;
	std::cout<<"*                        Virtual Reactor                      *"<<std::endl;
	std::cout<<"*                                                             *"<<std::endl;
	std::cout<<"* Simulation of concentration evolution in chemical reactions *"<<std::endl;
	std::cout<<"*                                                             *"<<std::endl;
	std::cout<<"*                      ZHANG Yichi @ HKUST                    *"<<std::endl;
	std::cout<<"*                                                             *"<<std::endl;
	std::cout<<"***************************************************************"<<std::endl;
	std::cout<<std::endl;
	return clock();
}

void Mumbler_writeHeaders(int nmcs,std::string * mc_labels){
	std::cout<<"*** Simulation started ***"<<std::endl;
	std::cout<<" step,time(s)";
	for (int imc=0;imc<nmcs;imc++)
		std::cout<<",concentration of "<<mc_labels[imc];
	for (int imc=0;imc<nmcs;imc++)
		std::cout<<",rate of "<<mc_labels[imc];
	std::cout<<std::endl;
}

void Mumbler_Goodbye(clock_t start){
	std::cout<<"*** Simulation terminated normally. Thanks for using. ***"<<std::endl;
	std::cout<<"*** Elapsed time: "<<double(clock()-start)/CLOCKS_PER_SEC<<" s ***"<<std::endl;
}

#ifndef NDEBUG
int main(){
	clock_t start=Mumbler_Welcome();
	Mumbler_Goodbye(start);
}
#endif
