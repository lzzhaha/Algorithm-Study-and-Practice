/*
ID: zlinai1
PROG: skidesign
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

typedef std::ofstream ofs;
typedef std::ifstream ifs;

int main(){
	ifs fin;
	ofs fout;
	fin.open("skidesign.in");
	fout.open("skidesign.out");

	int N;
	fin>>N;
	std::vector<uint8_t> heights(N);
	for(uint16_t i=0; i<(uint16_t)N; i++){
		int temp;
		fin>>temp;
		heights[i] = temp;
	}
	int shift_amount = sizeof(int)*8-1;
	int mask = 1 << shift_amount;
	int min_cost = (-1) ^ mask;

	/*For each possible range which has max-min = 17, calculate the correspoding
	 * cost to move the heights into the range
	 * */
	for(uint8_t lower=0; lower<=83; lower++){
		int cost = 0;
		for(uint16_t j=0; j<N; j++){
			if(heights[j] < lower){//the height is lower than lower bound so add to it
				cost += (lower-heights[j])*(lower-heights[j]);
			}else if(heights[j] > lower+17){//the height is higher than upper bound so subtract from it
				cost += (heights[j]-lower-17)*(heights[j]-lower-17);
			}
		}

		if(cost < min_cost){
			min_cost = cost;
		}
	}

	fout<<min_cost<<std::endl;

	fout.close();
	fin.close();
	return 0;
}
