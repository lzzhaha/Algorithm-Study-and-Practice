/*
ID: zlinai1
PROG: combo
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cmath>

typedef std::ofstream ofs;
typedef std::ifstream ifs;

inline bool inset(uint8_t num, uint8_t set[]){
	for(uint8_t i=0; i<5; i++){
		if(num == set[i]){
			return true;
		}
	}
	return  false;
}

/*Take in two numbers within the range [1,N],
 * compute the number of overlapped elements of
 * the "correct set" of num1 and num2.
 * The "coorect set" of a number i is the set contains
 * {i-2, i-1, i, i+1, i+2}, with proper modifications
 * if some elements is out of the range [1,N].
 * */
uint8_t intersect_count(uint8_t num1, uint8_t num2, uint8_t N){
	int count = 0;
	uint8_t set1[5];
	uint8_t set2[5];

	for(int j=-2; j<=2; j++){
		if(num1+j<=0){
			set1[j+2] = (num1+j)+N;
		}else if(num1+j>N){
			set1[j+2] = (num1+j)-N;
		}else{
			set1[j+2] = (num1+j);
		}

		if(num2+j<=0){
			set2[j+2] = (num2+j)+N;
		}else if(num2+j>N){
			set2[j+2] = (num2+j)-N;
		}else{
			set2[j+2] = (num2+j);
		}
   }

   for(uint8_t i=0; i<5; i++){
	   count+=inset(set2[i],set1);
   }
   return count;
}


int main(){
	ifs fin;
	ofs fout;
	fin.open("combo.in");
	fout.open("combo.out");

	int N;
	int John[3];
	int Master[3];
	fin>>N;
	fin>>John[0]>>John[1]>>John[2];
	fin>>Master[0]>>Master[1]>>Master[2];
	if(N<=5){//all combinations are acceptable
		fout<<N*N*N<<std::endl;
	}else{
		/*For each tuple, the possible combination is 5*5*5 = 125,
		 * So the total combination for two tuples is 2*125 - #intersection
		 * */
		int total = 250;
		uint8_t intersection = 1;
		for(uint8_t i=0; i<3;i++){
			intersection*=intersect_count(John[i],Master[i],(uint8_t)N);
		}

		total -= (int)intersection;
		fout<<total<<std::endl;
	}
	fout.close();
	fin.close();
	return 0;
}
