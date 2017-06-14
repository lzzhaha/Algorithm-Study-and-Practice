/*
ID: zlinai1
PROG: milk2
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

//a struct representing the milking timeslot
struct timeslot{
	uint32_t start;
	uint32_t end;
};

//A function comparing two timeslot object for sort
int cmp(const void* a, const void* b){
	timeslot* a1 = (timeslot*)a;
	timeslot* b1 = (timeslot*)b;
	if(a1->start < b1->start){
		return -1;
	}else if(a1->start > b1->start){
		return 1;
	}else{
		return 0;
	}
}


int main() {
    ofstream fout ("milk2.out");
    ifstream fin ("milk2.in");

    //read the input file content
    uint32_t num ;
    fin>> num;
    const uint32_t N = num;
    timeslot t[N];
    for(uint32_t i = 0; i<N;i++){
    	fin >> t[i].start;
    	fin >> t[i].end;
    }

    //Sort the timeslot array in ascending order by start time
    qsort(t,N,sizeof(t[0]),cmp);

    vector<timeslot> afterMerge;
    cout<<"t:"<<endl;
    for(auto k:t){
    	cout<<k.start<<" "<<k.end<<endl;
    }
    //Merge the consecutive timeslots into one timeslot and put it into the afterMerge vector
    //3 cases: contain, consecutive, separate
    for(uint32_t i = 0; i<= N-1; i++){
    	timeslot temp = t[i];
    	if(i<N-1){
    	//Consecutive or contain timeslots found
    		while(temp.end >= t[i+1].start){
    			if(t[i+1].end > temp.end){
    				//consecutive case
    				//two timeslots is merged as one
    				temp.end = t[i+1].end;
    			}
    			i++;
    		}
    	}
    	afterMerge.push_back(temp);

    }


    uint32_t longestMilk = 0;
    uint32_t longestNoMilk = 0;
    cout<<"afterMerge.size():"<<afterMerge.size()<<endl;
    //find the longest time respectively by traversing the vectorl
    for(uint32_t j = 0; j< afterMerge.size()-1; j++){
    	uint32_t gap = afterMerge[j+1].start - afterMerge[j].end;
    	if(gap > longestNoMilk){
    		longestNoMilk = gap;
    		cout<<"NoMilk: "<<longestNoMilk<<endl;
    	}
    	uint32_t duration = afterMerge[j].end - afterMerge[j].start;

    	if(longestMilk < duration){
    		longestMilk = duration;

    	}
    }

    uint32_t lastDuration = afterMerge[afterMerge.size()-1].end - afterMerge[afterMerge.size()-1].start;
    longestMilk = (longestMilk>=lastDuration)?longestMilk:lastDuration;

    fout<<longestMilk<<" "<<longestNoMilk<<endl;
    fout.close();
    fin.close();
    return 0;
}




