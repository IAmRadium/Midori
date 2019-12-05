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
	//printf("%d",*cell);
	/*Doing the reverse bit swap*/
	temp1=0x88&(*cell);/*swap 7 with 3*/
	temp1 = (temp1<<4) | (temp1>>4);
	temp2=0x22&(*cell);
	temp2 = (temp2<<4) | (temp2>>4);
	result=0x55&(*cell);
	result^=temp1;
	result^=temp2;
	*cell=result;	
	//printf("\n%d",result);
}

void SSb1(char *cell){
	unsigned char result=*cell;
	result = (result&0x80)>>3 | (result&0x40)<<1 | (result&0x20)>>3 | (result&0x10)>>3 | (result&0x08)>>3 | (result&0x04)<<1 | (result&0x02)<<5 | (result&0x01)<<5;
	result=Sb1[result&0x0f]^(Sb1[(result&0xf0)>>4])<<4;
	//printf("%d\n",result);
	result = (result&0x80)>>1 | (result&0x40)>>5 | (result&0x20)>>5 | (result&0x10)<<3 | (result&0x08)>>1 | (result&0x04)<<3 | (result&0x02)<<3 | (result&0x01)<<3;
	*cell=result;
	printf("%d\n",result);	
}
void SSb2(char *cell){
	unsigned char result=*cell;
	result=(result&0x80)>>6 | (result&0x40)>>2 | (result&0x20)<<2 | (result&0x10)<<2 | (result&0x08)<<2 | (result&0x04)>>2 | (result&0x02)<<2 | (result&0x01)<<2;
	result=Sb1[result&0x0f]^(Sb1[(result&0xf0)>>4])<<4;
	result=(result&0x80)>>2 | (result&0x40)>>2 | (result&0x20)>>2 | (result&0x10)<<2 | (result&0x08)>>2 | (result&0x04)>>2 | (result&0x02)<<6 | (result&0x01)<<2;
	*cell=result;
	//printf("%d",result);
}

void SSb3(char *cell){
	unsigned char result=*cell;
	result = (result&0x80)>>5 | (result&0x40)>>1 | (result&0x20)>>1 | (result&0x10)>>1 | (result&0x08)<<3 | (result&0x04)>>1 | (result&0x02)>>1 | (result&0x01)<<7;
	result=Sb1[result&0x0f]^(Sb1[(result&0xf0)>>4])<<4;
	result = (result&0x80)>>7 | (result&0x40)>>3 | (result&0x20)<<1 | (result&0x10)<<1 | (result&0x08)<<1 | (result&0x04)<<5 | (result&0x02)<<1 | (result&0x01)<<1;
	*cell=result;
}

void SubCell(char state[]){
	for(int i=0;i<16;i++){
		SSb0(&state[i]);
		SSb1(&state[i]);
		SSb2(&state[i]);
		SSb3(&state[i]);
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
