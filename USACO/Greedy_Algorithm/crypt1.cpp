/*
ID: zlinai1
PROG: crypt1
LANG: C++11
*/
#include <iostream>
#include <fstream>

typedef std::ofstream ofs;
typedef std::ifstream ifs;

//Check whether a digit is in the given set of digits
bool inset(uint8_t set[], uint8_t num, uint8_t size){
	for(uint8_t i=0; i<size; i++){
		if(set[i]==num){
			return true;
		}
	}
	return false;
}

//Check whether a produced number satisfies the requirement of solution
bool match(uint16_t num, uint8_t set[], uint8_t size, bool is_partial){
	if(is_partial && num > 999){//Only 3 digits are allowed
		return false;
	}

	while(num!=0){
		uint8_t rem = (uint8_t)(num%10);//check each digit
		if(!inset(set,rem,size)){
			return false;
		}
		num/=10;
	}
	return true;
}
int main(){

	ofs fout;
	ifs fin;
	fin.open("crypt1.in");
	fout.open("crypt1.out");
	uint8_t N;//Number of digits in the set
	fin >> N;
	N = N - '0';

	uint32_t count = 0; //count the qualified solutions
	uint8_t set[9];

	for(uint8_t i=0; i<N; i++){//initialize set
		fin >> set[i];
		set[i]-='0';
	}

	//Try out each possible solution and leave out the unmatched ones
	for(uint8_t i=0; i<N; i++){
		for(uint8_t j=0; j<N; j++){
			for(uint8_t k=0; k<N; k++){
				for(uint8_t l=0; l<N; l++){
					//Calculate the partial product of second digit
					uint16_t ppd1 = set[l] * (set[i]*100+
							set[j]*10 + set[k]);
					if(count == 344){
						std::cout<<"i="<<(int)i<<",j="<<(int)j<<",k="<<(int)k<<",l="<<(int)l<<std::endl;
						std::cout<<"ppd1 = "<<ppd1<<std::endl;
					}
					if(!match(ppd1,set,N,true)){
						continue;
					}
					for(uint8_t z=0; z<N; z++){
					//Calculate the partial product of first digit
						uint16_t ppd2 = set[z] * (set[i]*100+
								set[j]*10 + set[k]);
						if(!match(ppd2,set,N,true)){
							continue;
						}
						if(count == 344){
							std::cout<<"i="<<(int)i<<",j="<<(int)j<<",k="<<(int)k<<",l="<<(int)l<<",z="<<(int)z<<std::endl;
							std::cout<<"ppd1 = "<<ppd1<<std::endl;
							std::cout<<"ppd2 = "<<ppd2<<std::endl;
						}
					//Calculate the final summation
						uint16_t result = ppd1;
						 result += ppd2*10;
						if(count == 344){
							std::cout<<"sum= "<<ppd1<<std::endl;
						}
						if(match(result,set,N,false)){
							count++;
						}

					}
				}
			}
		}
	}

	fout<<count<<std::endl;
	fout.close();
	fin.close();
	return 0;
}
