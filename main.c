/*
Midori Lightweight Block Cipher
Md Rasid Ali
*/
#include<stdio.h>

/*Below Sbox is used for Midori128*/
char Sb1[]={0x1,0x0,0x5,0x3,0xe,0x2,0xf,0x7,0xd,0xa,0x9,0xb,0xc,0x8,0x4,0x6};

/*Defining the AddRoundKey*/
void AddRoundKey(char state[],char key[]){
	for(int i=0;i<16;i++){
	}
}
/*defining the SubCell function*/
void SSb0(char *cell){
	//*cell=0xdb;
	//printf("\n%d",*cell);
	/*taking the 7th and 3rd bit*/
	unsigned char temp1=0x88&(*cell);/*swap 7 with 3*/        //    y = (x << 2) | (x >> (8 - 2));
	/*making circular shift to interchange the positions*/
	temp1 = (temp1<<4) | (temp1>>4);
	/*taking the 2th and 6rd bit*/
	unsigned char temp2=0x22&(*cell);
	temp2 = (temp2<<4) | (temp2>>4);
	unsigned char result=0x55&(*cell);
	result^=temp1;
	result^=temp2;
	*cell=result;
	temp1=result&0x0f;//4bit LSB
	temp1=Sb1[temp1];
	temp2=result&0xf0;//
	temp2=temp2>>4;
	temp2=Sb1[temp2];
	temp2=temp2<<4;
	temp1=temp1^temp2;
	*cell=temp1;
	//printf("\n%d",temp1);
}

void SSb1(char *cell){
	*cell=0xdb;
	//printf("\n%d",*cell);
	/*taking the 7th and 3rd bit*/
	unsigned char temp1=0x88&(*cell);/*swap 7 with 3*/        //    y = (x << 2) | (x >> (8 - 2));
	/*making circular shift to interchange the positions*/
	temp1 = (temp1<<4) | (temp1>>4);
	/*taking the 2th and 6rd bit*/
	unsigned char temp2=0x22&(*cell);
	temp2 = (temp2<<4) | (temp2>>4);
	unsigned char result=0x55&(*cell);
	result^=temp1;
	result^=temp2;
	//*cell=result;
	temp1=result&0x0f;//4bit LSB
	temp1=Sb1[temp1];
	temp2=result&0xf0;//
	temp2=temp2>>4;
	temp2=Sb1[temp2];
	temp2=temp2<<4;
	temp1=temp1^temp2;
	*cell=temp1;
	printf("\n%d",temp1);
}
/*
void SSb2(char *cell){
	continue;
}
void SSb3(char *cell){
	continue;
}*/
void SubCell(char state[]){
	for(int i=0;i<16;i++){
		SSb0(&state[i]);
		SSb1(&state[i]);/*
		SSb2(&state[i]);
		SSb3(&state[i]);*/
		break;
	}
}
int main(){
	/*Defining the plaintext and key*/
	char state[]={0x01,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	char key[]={0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	AddRoundKey(state,key);
	/*for(int i=0;i<16;i++)
		printf("%d",pt[i]);
	*/
	for(int i=0;i<15;i++){
		SubCell(state);
		break;
	}
	return 0;
}
