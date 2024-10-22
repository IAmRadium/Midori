/*
Midori: Low Energy Lightweight Block Ciphe by subhodeep banik et. al.
Md Rasid Ali, Crypto Research Lab, CSE,  IIT Kharagpur, india
*/
#include<stdio.h>

/*defining the beta round of Midori */
unsigned char beta[19][16]={{0,0,0,1,0,1,0,1,1,0,1,1,0,0,1,1},{0,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0},
			    {1,0,1,0,0,1,0,0,0,0,1,1,0,1,0,1},{0,1,1,0,0,0,1,0,0,0,0,1,0,0,1,1},
			    {0,0,0,1,0,0,0,0,0,1,0,0,1,1,1,1},{1,1,0,1,0,0,0,1,0,1,1,1,0,0,0,0},
			    {0,0,0,0,0,0,1,0,0,1,1,0,0,1,1,0},{0,0,0,0,1,0,1,1,1,1,0,0,1,1,0,0},
			    {1,0,0,1,0,1,0,0,1,0,0,0,0,0,0,1},{0,1,0,0,0,0,0,0,1,0,1,1,1,0,0,0},
			    {0,1,1,1,0,0,0,1,1,0,0,1,0,1,1,1},{0,0,1,0,0,0,1,0,1,0,0,0,1,1,1,0},
			    {0,1,0,1,0,0,0,1,0,0,1,1,0,0,0,0},{1,1,1,1,1,0,0,0,1,1,0,0,1,0,1,0},
			    {1,1,0,1,1,1,1,1,1,0,0,1,0,0,0,0},{0,1,1,1,1,1,0,0,1,0,0,0,0,0,0,1},
			    {0,0,0,1,1,1,0,0,0,0,1,0,0,1,0,0},{0,0,1,0,0,0,1,1,1,0,1,1,0,1,0,0},
			    {0,1,1,0,0,0,1,0,1,0,0,0,1,0,1,0}};
/*Below Sbox is used for Midori128*/
unsigned char Sb1[]={0x1,0x0,0x5,0x3,0xe,0x2,0xf,0x7,0xd,0xa,0x9,0xb,0xc,0x8,0x4,0x6};

/*Defining MixColumn*//*DOUBTFUL*/
void MixColumn(char state[]){
	char cell[16];
	for(int i=0;i<16;i++){
		cell[i]=state[i];	
	}
	for(int i=0;i<4;i++){
		state[i*4]=cell[i*4+1]^cell[i*4+2]^cell[i*4+3];
		state[i*4+1]=cell[i*4]^cell[i*4+2]^cell[i*4+3];
		state[i*4+2]=cell[i*4]^cell[i*4+1]^cell[i*4+3];
		state[i*4+3]=cell[i*4]^cell[i*4+1]^cell[i*4+2];
	}
	
}

/*Defining the Shuffle Cell Function*/
void ShuffleCell(char state[]){
	char cell[16];
	for(int i=0;i<16;i++){
		cell[i]=state[i];	
	}
	state[0]=cell[0];state[1]=cell[10];state[2]=cell[5];state[3]=cell[15];state[4]=cell[14];state[5]=cell[4];state[6]=cell[11];state[7]=cell[1];
	state[8]=cell[9];state[9]=cell[3];state[10]=cell[12];state[11]=cell[6];state[12]=cell[7];state[13]=cell[13];state[14]=cell[2];state[15]=cell[8];

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
	SSb0(&state[0]);SSb0(&state[4]);SSb0(&state[8]);SSb0(&state[12]);
	SSb1(&state[1]);SSb1(&state[5]);SSb1(&state[9]);SSb1(&state[13]);
	SSb2(&state[2]);SSb2(&state[6]);SSb2(&state[10]);SSb2(&state[14]);
	SSb3(&state[3]);SSb3(&state[7]);SSb3(&state[11]);SSb3(&state[15]);
}
int main(){
	/*Test Vectors, given in the original paper; https://eprint.iacr.org/2015/1142.pdf */
	//unsigned char state[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	//unsigned char key[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	//expected ciphertext= c055cbb95996d14902b60574d5e728d6
	unsigned char state[]={0x51,0x08,0x4c,0xe6,0xe7,0x3a,0x5c,0xa2,0xec,0x87,0xd7,0xba,0xbc,0x29,0x75,0x43};
	unsigned char key[]={0x68,0x7d,0xed,0x3b,0x3c,0x85,0xb3,0xf3,0x5b,0x10,0x09,0x86,0x3e,0x2a,0x8c,0xbf};
	//expected ciphertext= 1e0ac4fddff71b4c1801b73ee4afc83d
	/*Key Whitening*/
	AddRoundKey(state,key);
	/*Round Functions*/
	for(int i=0;i<=18;i++){
		SubCell(state);
		ShuffleCell(state);
		MixColumn(state);
		AddRoundKey_with_beta(state,key,i);
	}
	/*Last Round*/
	SubCell(state);
	AddRoundKey(state,key);
	for(int i=0;i<16;i++){
		printf("%x",state[i]);
	}
	printf("\n");
	return 0;
}
