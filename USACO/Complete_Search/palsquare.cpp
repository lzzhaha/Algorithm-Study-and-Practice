/*
ID: zlinai1
PROG: palsquare
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cstring>
#define N 300

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

int main(){
	std::ifstream in;
	std::ofstream out;
	in.open("palsquare.in");
	out.open("palsquare.out");

	uint8_t base ;
	char temp[3];
	in.getline(temp,3);
	if(std::strlen(temp)== 2){
		temp[0] = (temp[0]-'0')*10;
		temp[1] = temp[1]-'0';
		base = temp[0]+temp[1];
	}else{
		temp[0] = (temp[0]-'0');
		base = temp[0];
	}

	for(uint16_t i=1; i<N;i++){
		std::string origin = change_base(i,(uint32_t)base);
		std::string square = change_base(i*i,(uint32_t)base);

		if(is_pal(square)){
			out<<origin<<" "<<square<<std::endl;
		}
	}
	out.close();
	in.close();
	return 0;
}
