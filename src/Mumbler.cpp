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

void Mumbler_Goodbye(clock_t start){
	std::cout<<"*** Simulation terminated normally in "<<double(clock()-start)/CLOCKS_PER_SEC<<" s. Thanks for using. ***"<<std::endl;
	std::cout<<"*** If Virtual Reactor hopefully benefits your research or teaching, please cite this website https://github.com/FreemanTheMaverick/VirtualReactor and star it. (:D) ***"<<std::endl;
}

#ifndef NDEBUG
int main(){
	clock_t start=Mumbler_Welcome();
	Mumbler_Goodbye(start);
}
#endif
