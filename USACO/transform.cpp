/*
ID: zlinai1
PROG: transform
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>

/*
 * Use breadth first search to
 * experiment each transformation so
 * that the number of methods is tested from
 * samllest to the largest*/

using namespace std;


//define the function to compare two matrix
bool equal(char** a, char** b, uint32_t size){
	for(uint32_t i = 0; i<size; i++){
		for(uint32_t j = 0; j<size; j++){
			if(a[i][j] != b[i][j]){
				return false;
			}
		}
	}
	return true;
}

//define the function to release dynamic memory
void release(char** useless, uint32_t size){
	for(uint32_t i = 0; i<size; i++){
		delete [] useless[i];
	}
	delete [] useless;
}

//define the function to create a rotated matrix
char** rotate(char** a, uint32_t size){
	char** temp = new char*[size];
	for(uint32_t i = 0; i<size; i++){
		temp[i] = new char[size];
	}

	for(uint32_t i = 0; i<size; i++){
		for(uint32_t j = 0; j<size; j++){
			temp[j][size-1-i] = a[i][j];
		}
	}
	return temp;
}

/*
void print(char** a, uint32_t size){
	for(uint32_t i = 0; i<size; i++){
		for(uint32_t j = 0; j<size; j++){
				cout<<a[i][j];
		}
		cout<<endl;
	}

}
*/
//define the function to create a reflected matrix
char** reflect(char** a, uint32_t size){
	char** temp = new char*[size];
	for(uint32_t i = 0; i<size; i++){
		temp[i] = new char[size];
	    for(uint32_t j = 0; j<size; j++){
	    	temp[i][j] = a[i][size-1-j];
	    }
	}

	return temp;
}


//define the function to check the rotation result

void checkRotation(uint32_t& result, char** before, char** after, uint32_t size){

	char** temp = rotate(before,size);
	//cout<<"1st rotation: "<<endl;
	//print(temp,size);
	if(equal(after, temp,size)){
		//90 degrees clockwise rotation
		result = 1;
	}else{
		char** useless = temp;
		temp = rotate(useless,size);
		release(useless,size);
		useless = NULL;
		if(equal(after, temp, size)){
			//180 degrees clockwise rotation
			result = 2;
		}else{
			useless = temp;
			temp = rotate(useless,size);
			release(useless,size);
			useless = NULL;
			if(equal(after, temp, size)){
				//270 degrees clockwise rotation
				result = 3;
			}

			release(temp, size);
		}
	}
}

int main() {
    ofstream fout ("transform.out");
    ifstream fin ("transform.in");

    uint32_t size = 0;
    fin>>size;

    char** before = new char*[size];
    char** after = new char*[size];
    //read the matrix
    for(uint32_t i = 0; i<size; i++){
    	before[i] = new char[size];
    	for(uint32_t j = 0; j<size; j++){
    		fin>>before[i][j];
    	}
    }

    for(uint32_t i = 0; i<size; i++){
       after[i] = new char[size];
        for(uint32_t j = 0; j<size; j++){
        	fin>>after[i][j];
        }
    }
    /*
    cout<<"before:"<<endl;
    print(before,size);
    cout<<"after"<<endl;
    print(after,size);
    cout<<endl;
    */
    uint32_t result = 0;

    //check whether the after-matrix can be obtained by #1-3
    checkRotation(result,before,after,size);

    if(result == 0){
    	//check whether the after-matrix can be obtained by #4-5
    	char** temp = reflect(before,size);

    	if(equal(temp, after, size)){
    		//single reflection
    		result = 4;
    	}else{
    		checkRotation(result, temp, after, size);
    		if(result != 0){
    			result = 5;
    		}
    	}
    }

    //check whether the after-matrix can be obtained by 6
    if(result == 0 && equal(before,after,size)){
    	result = 6;
    }

    if(result == 0){
    	result = 7;
    }

    fout<<result<<endl;

    release(before,size);
    release(after,size);
    fin.close();
    fout.close();
    return 0;
}




