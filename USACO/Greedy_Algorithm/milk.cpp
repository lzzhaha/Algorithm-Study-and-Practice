/*
ID: zlinai1
PROG: milk
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

typedef std::ifstream ifstream;
typedef std::ofstream ofstream;

struct farmer{
	uint32_t price;
	uint32_t amount;
};

typedef std::vector<farmer> farmers;

farmers get_farmers(ifstream& fin, uint16_t num_farmers){
	farmers f;

	for(uint16_t i=0; i<num_farmers; i++){
		farmer person;
		fin >> person.price;
		fin >> person.amount;
		f.push_back(person);
	}
	return f;
}

bool compare(const farmer& f1, const farmer& f2){

	return f1.price < f2.price;
}

int main(){
	ofstream fout;
	ifstream fin;
	fout.open("milk.out");
	fin.open("milk.in");

	uint32_t N;
	uint16_t M;
	fin >> N;
	fin >> M;
	uint32_t cost = 0;

	farmers f = get_farmers(fin,M);
	std::sort(f.begin(),f.end(),compare);

	farmers::iterator it;
	for(it=f.begin(); it!=f.end(); it++){
		for(uint32_t i=0; i<it->amount && N>0; i++){
			cost += it->price;
			N--;
		}

		if(N==0){
			break;
		}
	}

	fout<<cost<<std::endl;

	fout.close();
	fin.close();
	return 0;
}
