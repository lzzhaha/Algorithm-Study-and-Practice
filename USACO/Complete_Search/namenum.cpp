 	
#include <iostream>
#include <fstream>
#include <cstring>

#define MAX_NAME_LENGTH 12

struct letter_group{
	char letter1;
	char letter2;
	char letter3;
};

letter_group groups[8]=
{
		{'A','B','C'},
		{'D','E','F'},
		{'G','H','I'},
		{'J','K','L'},
		{'M','N','O'},
		{'P','R','S'},
		{'T','U','V'},
		{'W','X','Y'},
};

uint16_t read_file(char**& names, uint8_t digit, std::ifstream &fin){
	names = new char*[5000];
	uint16_t count = 0;
	switch(digit){
		case 2://read names starting with A,B,C
			do{
				names[count] = new char[MAX_NAME_LENGTH+1];
				fin.getline(names[count],MAX_NAME_LENGTH+1,'\n');
			}while(names[count++][0]!='D');
			break;

		case 3://read names starting with D,E,F
			names[0] = new char[MAX_NAME_LENGTH+1];
			do{
				fin.getline(names[0],MAX_NAME_LENGTH+1,'\n');
			}while(names[0][0]!='D');
			count = 1;
			do{
				names[count] = new char[MAX_NAME_LENGTH+1];
				fin.getline(names[count],MAX_NAME_LENGTH+1,'\n');
			}while(names[count++][0]!='G');
			break;

		case 4://read names starting with G,H,I
			names[0] = new char[MAX_NAME_LENGTH+1];
			do{
				fin.getline(names[0],MAX_NAME_LENGTH+1,'\n');
			}while(names[0][0]!='G');
			count = 1;
			do{
				names[count] = new char[MAX_NAME_LENGTH+1];
				fin.getline(names[count],MAX_NAME_LENGTH+1,'\n');
			}while(names[count++][0]!='J');
			break;

		case 5://read names starting with J,K,L
			names[0] = new char[MAX_NAME_LENGTH+1];
			do{
				fin.getline(names[0],MAX_NAME_LENGTH+1,'\n');
			}while(names[0][0]!='J');
			count = 1;
			do{
				names[count] = new char[MAX_NAME_LENGTH+1];
				fin.getline(names[count],MAX_NAME_LENGTH+1,'\n');
			}while(names[count++][0]!='M');
			break;

		case 6://read names starting with M,N,O
			names[0] = new char[MAX_NAME_LENGTH+1];
			do{
				fin.getline(names[0],MAX_NAME_LENGTH+1,'\n');
			}while(names[0][0]!='M');
			count = 1;
			do{
				names[count] = new char[MAX_NAME_LENGTH+1];
				fin.getline(names[count],MAX_NAME_LENGTH+1,'\n');
			}while(names[count++][0]!='P');
			break;

		case 7://read names starting with P,R,S
			names[0] = new char[MAX_NAME_LENGTH+1];
			do{
				fin.getline(names[0],MAX_NAME_LENGTH+1,'\n');
			}while(names[0][0]!='P');
			count = 1;
			do{
				names[count] = new char[MAX_NAME_LENGTH+1];
				fin.getline(names[count],MAX_NAME_LENGTH+1,'\n');
			}while(names[count++][0]!='T');
			break;

		case 8://read names starting with T,U,V
			names[0] = new char[MAX_NAME_LENGTH+1];
			do{
				fin.getline(names[0],MAX_NAME_LENGTH+1,'\n');
			}while(names[0][0]!='T');
			count = 1;
			do{
				names[count] = new char[MAX_NAME_LENGTH+1];
				fin.getline(names[count],MAX_NAME_LENGTH+1,'\n');
			}while(names[count++][0]!='W');
			break;

		default://read names starting with W,X,Y
			names[0] = new char[MAX_NAME_LENGTH+1];
			do{
				fin.getline(names[0],MAX_NAME_LENGTH+1,'\n');
			}while(names[0][0]!='D');
			count = 1;
			do{
				names[count] = new char[MAX_NAME_LENGTH+1];
				fin.getline(names[count],MAX_NAME_LENGTH+1,'\n');
			}while(names[count++][0]!='G');

	}

	//remove the extra names
	delete[] names[--count];
	return count;
}

uint16_t filter(char**& names, uint8_t match_pos, letter_group groups, uint16_t num_names){
	char** temp = new char*[num_names];
	uint16_t new_count = 0;
	for(uint16_t i=0; i<num_names; i++){
		if(names[i][match_pos] == groups.letter1 ||
		   names[i][match_pos] == groups.letter2 ||
		   names[i][match_pos] == groups.letter3){

			temp[new_count] = new char[MAX_NAME_LENGTH+1];
			std::strcpy(temp[new_count++],names[i]);
		}
	}
	for(uint16_t i=0;i<num_names;i++){
			delete[] names[i];
	}
	delete[] names;
	names = temp;
	return new_count;
}

uint16_t select_length(char**& names, uint16_t num_names, uint8_t length){
	char** temp = new char*[num_names];
	uint16_t new_count = 0;
	for(uint16_t i=0;i<num_names;i++){
		if(std::strlen(names[i]) == length){
			temp[new_count] = new char[MAX_NAME_LENGTH+1];
			std::strcpy(temp[new_count++],names[i]);
		}
	}

	for(uint16_t i=0;i<num_names;i++){
				delete[] names[i];
	}
	delete[] names;
	names = temp;
	return new_count;
}



int main(){
	std::ofstream fout;
	std::ifstream fin;
	std::ifstream dic;

	fout.open("namenum.out");
	fin.open("namenum.in");
	dic.open("dict.txt");
	uint8_t match_pos = 0;
	uint8_t digit;
	uint16_t num_names;

	//array that holds the result
	char** names;
	char digits[MAX_NAME_LENGTH+1];

	fin.getline(digits,MAX_NAME_LENGTH+1,'\n');
	uint8_t it =0;

	do{
		if(digits[it]=='\0'){
			num_names = select_length(names, num_names, it);
			break;
		}else{
			digit = digits[it++] - '0';
		}

		if(match_pos == 0){//read from file and check first character
			num_names = read_file(names, digit,dic);
		}else{//filter the names by looking at letters in match_pos
			num_names = filter(names,match_pos,groups[digit-2],num_names);
		}
		match_pos++;
	}while(true);

	for(uint16_t i=0;i<num_names;i++){
		fout<<names[i]<<std::endl;
	}
	if(num_names == 0){//No valid name available
		fout<<"NONE"<<std::endl;
	}
	for(uint16_t i=0;i<num_names;i++){
		delete[] names[i];
	}
	fout.close();
	fin.close();
	dic.close();
	delete[] names;
	return 0;
}
