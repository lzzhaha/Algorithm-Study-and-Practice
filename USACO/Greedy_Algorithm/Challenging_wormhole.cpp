/*
ID: zlinai1
PROG: wormhole
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>

struct point{
	uint32_t x;
	uint32_t y;
};

typedef std::ofstream ofs;
typedef std::ifstream ifs;
typedef std::vector<point> points;
typedef std::vector<int> vec;

//Check whether a certain combination is a loop
bool is_loop(vec& pair, vec& next_right,uint8_t N){
	//Simulate entering each point
	for(uint8_t i=0; i<N; i++){
		int entrance = (int)i;
		int exit = pair[i];

		/*the exit of an entrance is the pair[entrance]
		 * after entering the entrance, the cow either
		 * enters the next_right points of the exit,
		 * or never enters holes again.
		 * if there is a loop then the entrance will never be -1,
		 * otherwise, after N iteration, the entrance must become -1
		 * */
		for(uint8_t j=0; j<N; j++){
			entrance = next_right[exit];
			if(entrance == -1){
				break;
			}else{
				exit = pair[entrance];
			}
		}

		if(entrance != -1){
			return true;
		}
	}

	return false;
}

/*traverse through every possible combination of points pair by recursion,
 *and check whehter there is a loop.
 * */
uint32_t combination_count(vec& pair, vec& next_right, uint8_t N){
	uint8_t i;
	//find pair point for each point in pt
	for(i=0; i<N;i++){
		if(pair[i]==-1){
			break;
		}
	}

	if(i == N){//All points have been paired
		if(is_loop(pair,next_right, N)){//The current combination is a loop
			return 1;
		}else{
			return 0;
		}
	}

	uint32_t count = 0;// the return value

	for(uint8_t j=i+1; j<N; j++){//find the pair of i in those points which have larger indices
		if(pair[j] == -1){//the pt[j] is available
			pair[j] = i;
			pair[i] = j;

			//recursively pair the remaining points and perform counting
			count+= combination_count(pair,next_right,N);

			//reset pair to prepare for new combination
			pair[i] = -1;
			pair[j] = -1;
		}
	}

	return count;
}

int main(){
	ofs fout;
	ifs fin;
	fout.open("wormhole.out");
	fin.open("wormhole.in");
	int N;
	fin>>N;
	points pt(N);
	vec pair(N,-1);//stores the indices of the points paired with the one at certain position

	/*stores the indices of the points to the right of the one at certain position
	 * if there is no point to the right of pt[i], then next_right[i] = -1
	 * */
	vec next_right(N,-1);

	for(uint8_t i=0; i<(uint8_t)N; i++){
		fin>>pt[i].x>>pt[i].y;
	}

	//fill the next_right
	for(uint8_t i=0; i<(uint8_t)N; i++){
		for(uint8_t j=0; j<(uint8_t)N; j++){
			if(pt[i].y == pt[j].y && pt[i].x <pt[j].x){
				if(next_right[i]==-1 || pt[j].x - pt[i].x < pt[next_right[i]].x-pt[i].x){
					next_right[i] = j;
				}
			}
		}
	}

	fout<<combination_count(pair,next_right,(uint8_t)N)<<std::endl;
	fout.close();
	fin.close();
	return 0;
}
