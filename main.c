/*
Midori Lightweight Block Cipher
Md Rasid Ali
*/
#include<stdio.h>

/*defining the beta round constant*/
unsigned char beta[19][16]={{0,0,0,1,0,1,0,1,1,0,1,1,0,0,1,1},{0,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0},{1,0,1,0,0,1,0,0,0,0,1,1,0,1,0,1},{0,1,1,0,0,0,1,0,0,0,0,1,0,0,1,1},{0,0,0,1,0,0,0,0,0,1,0,0,1,1,1,1},{1,1,0,1,0,0,0,1,0,1,1,1,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,1,0},{0,0,0,0,1,0,1,1,1,1,0,0,1,1,0,0},{1,0,0,1,0,1,0,0,1,0,0,0,0,0,0,1},{0,1,0,0,0,0,0,0,1,0,1,1,1,0,0,0},{0,1,1,1,0,0,0,1,1,0,0,1,0,1,1,1},{0,0,1,0,0,0,1,0,1,0,0,0,1,1,1,0},{0,1,0,1,0,0,0,1,0,0,1,1,0,0,0,0},{1,1,1,1,1,0,0,0,1,1,0,0,1,0,1,0},{1,1,0,1,1,1,1,1,1,0,0,1,0,0,0,0},{0,1,1,1,1,1,0,0,1,0,0,0,0,0,0,1},{0,0,0,1,1,1,0,0,0,0,1,0,0,1,0,0},{0,0,1,0,0,0,1,1,1,0,1,1,0,1,0,0},{0,1,1,0,0,0,1,0,1,0,0,0,1,0,1,0}};
/*Below Sbox is used for Midori128*/
unsigned char Sb1[]={0x1,0x0,0x5,0x3,0xe,0x2,0xf,0x7,0xd,0xa,0x9,0xb,0xc,0x8,0x4,0x6};
int shuffle[]={0,10,5,15,14,4,11,1,9,3,12,6,7,13,2,8};
/*Defining MixColumn*//*DOUBTFUL*/
void MixColumn(char state[]){
	for(int i=0;i<4;i++){
		state[i*4]=state[i*4+1]^state[i*4+2]^state[i*4+3];
		state[i*4+1]=state[i*4]^state[i*4+2]^state[i*4+3];
		state[i*4+2]=state[i*4]^state[i*4+1]^state[i*4+3];
		state[i*4+3]=state[i*4]^state[i*4+1]^state[i*4+2];
	}
}
/*Defining the Shuffle Cell Function*/
void ShuffleCell(char state[]){
	unsigned char temp;
	for(int i=0;i<16;i++){
		int swap_index=shuffle[i];
		temp=state[swap_index];
		state[swap_index]=state[i];
		state[i]=temp;
	}
}
/*Defining the AddRoundKey*/
void AddRoundKey(char state[],char key[]){
	for(int i=0;i<16;i++){
		state[i]^=key[i];
	}
}
/*Defining AddRoundKey_with_Beta*/
void  AddRoundKey_with_beta(char state[],char key[],int iteration){
	char temp_key[16];
	for(int i=0;i<16;i++){
		temp_key[i]=key[i]^beta[iteration][i];
	}
	for(int i=0;i<16;i++){
		state[i]^=temp_key[i];
	}
}
/*defining the SubCell function*/
void SSb0(char *cell){
	unsigned char result=*cell;
	result = (result&0x80)>>4 | (result&0x40)>>0 | (result&0x20)>>4 | (result&0x10)>>0 | (result&0x08)<<4 | (result&0x04)<<0 | (result&0x02)<<4 | (result&0x01)<<0;
	result=Sb1[result&0x0f]^(Sb1[(result&0xf0)>>4])<<4;
	result = (result&0x80)>>4 | (result&0x40)>>0 | (result&0x20)>>4 | (result&0x10)<<0 | (result&0x08)<<4 | (result&0x04)<<0 | (result&0x02)<<4 | (result&0x01)<<0;
	*cell=result;
}

void SSb1(char *cell){
	unsigned char result=*cell;
	result = (result&0x80)>>3 | (result&0x40)<<1 | (result&0x20)>>3 | (result&0x10)>>3 | (result&0x08)>>3 | (result&0x04)<<1 | (result&0x02)<<5 | (result&0x01)<<5;
	result=Sb1[result&0x0f]^(Sb1[(result&0xf0)>>4])<<4;
	result = (result&0x80)>>1 | (result&0x40)>>5 | (result&0x20)>>5 | (result&0x10)<<3 | (result&0x08)>>1 | (result&0x04)<<3 | (result&0x02)<<3 | (result&0x01)<<3;
	*cell=result;
}

void SSb2(char *cell){
	unsigned char result=*cell;
	result=(result&0x80)>>6 | (result&0x40)>>2 | (result&0x20)<<2 | (result&0x10)<<2 | (result&0x08)<<2 | (result&0x04)>>2 | (result&0x02)<<2 | (result&0x01)<<2;
	result=Sb1[result&0x0f]^(Sb1[(result&0xf0)>>4])<<4;
	result=(result&0x80)>>2 | (result&0x40)>>2 | (result&0x20)>>2 | (result&0x10)<<2 | (result&0x08)>>2 | (result&0x04)>>2 | (result&0x02)<<6 | (result&0x01)<<2;
	*cell=result;
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
		SSb0(&state[i]);SSb1(&state[i]);SSb2(&state[i]);SSb3(&state[i]);
	}
}
int main(){
	/*Defining the plaintext and key*/
	unsigned char state[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	unsigned char key[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	AddRoundKey(state,key);
	for(int i=0;i<19;i++){
		SubCell(state);
		ShuffleCell(state);
		MixColumn(state);
		AddRoundKey_with_beta(state,key,i);
	}
	SubCell(state);
	AddRoundKey(state,key);
	for(int i=0;i<16;i++){
		printf("%x",state[i]);
	}
	printf("\n");
	return 0;
}
