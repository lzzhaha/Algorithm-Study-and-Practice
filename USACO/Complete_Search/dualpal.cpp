/*
ID: zlinai1
PROG: dualpal
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cstring>


std::string change_base(uint32_t val, uint32_t base){
	std::string re;
	assert(val>0);
	uint32_t remainder;
	while(val!=0){
		remainder = val%base;
		val/=base;

		if(remainder<10){
			re.insert(0,1,(char)('0'+remainder));
		}else{
			re.insert(0,1,(char)('A'+remainder-10));
		}
	}

	return re;
}

bool is_pal(std::string s){
	int len = s.length();
	for(int i=0, j=len-1; i<=j;i++,j--){
		if(s[i]!=s[j]){
			return false;
		}
	}
	return true;
}

bool is_dualpal(uint32_t S){
	uint8_t pal_count = 0;
	std::string s;
	for(uint8_t i=2; i<=10; i++){
		s = change_base(S,(uint32_t)i);
		if(is_pal(s)){
			pal_count++;
		}
		if(pal_count==2){
			return true;
		}
	}
	return false;
}

int main(){
	std::ifstream in;
	std::ofstream out;
	in.open("dualpal.in");
	out.open("dualpal.out");

	uint32_t N, S;
	in >> N;
	in >> S;
	uint32_t count = 0;
	while(count<N){
		S++;
		if(is_dualpal(S)){
			count++;
			out<<S<<std::endl;
		}
	}

	out.close();
	in.close();
	return 0;
}
