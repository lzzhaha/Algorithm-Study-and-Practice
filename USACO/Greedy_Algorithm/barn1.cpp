/*
ID: zlinai1
PROG: barn1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct group{
	uint8_t head;
	uint8_t tail;
};

typedef std::vector<group> vec;
typedef std::vector<uint8_t> arr;
typedef std::ofstream ofstream;
typedef std::ifstream ifstream;

int comp(uint8_t i, uint8_t j){
	return i<j;
}

//combine every stall number into one group if their difference is 1
vec initialize(ifstream& fin, uint8_t C){
	vec groups;
	if(C<=0){
		return groups;
	}
	group item;
	arr input;
	int temp;
	for(uint8_t i=0; i<C;i++){
		fin>>temp;
		input.push_back((uint8_t)temp);
	}

	std::sort(input.begin(),input.end(),comp);
	item.head = item.tail = input[0];
	groups.push_back(item);

	for(uint8_t i=1; i<C;i++){
		item.head = item.tail = input[i];
		uint8_t size = groups.size();
		if(groups[size-1].tail+1 == item.head){
			groups[size-1].tail++;
		}else{
			groups.push_back(item);
		}
	}
	return  groups;
}

uint8_t cal_stall(vec& groups){
	uint8_t re = 0;
	vec::iterator it;
	for(it=groups.begin();it!=groups.end();it++){
		re+=(it->tail - it->head +1);
	}
	return re;
}

//re-arrange the group structure to reduce the number of boards
void regroup(vec& groups, uint8_t num_boards){
	uint8_t gap = 2;
	while(true){
		for(uint8_t i=0; i<groups.size()-1; i++){
			if(groups[i+1].head - groups[i].tail == gap){//combine two group if the distance is equal to the gap
				groups[i].tail = groups[i+1].tail;
				groups.erase(groups.begin()+i+1);
				i--;
			}
			if(groups.size() == num_boards){//the number of boards needed is satisfied
				return;
			}
		}
		gap++;
	}
}
int main(){
	ifstream fin;
	ofstream fout;
	fin.open("barn1.in");
	fout.open("barn1.out");
	uint8_t num_boards, S, C;
	int temp;
	fin>>temp;
	num_boards = (uint8_t)temp;
	fin>>temp;
	S = (uint8_t)temp;
	fin>>temp;
	C = (uint8_t)temp;

	vec groups = initialize(fin,C);
	if(groups.size()>num_boards){
		regroup(groups,num_boards);
	}
	int result = (int)cal_stall(groups);
	fout<<result<<std::endl;
	fout.close();
	fin.close();
	return  0;
}

