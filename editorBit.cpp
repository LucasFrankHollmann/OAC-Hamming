#include <bits/stdc++.h>

int binToDec(int8_t *bin, int qtdBytes)
{
	
	int dec = 0;
	int m=1;
	
	for(int i = 0; i<8*qtdBytes;i++)
	{
		dec += bin[i] * m;
		m*=2;
	}
	
	return dec;
}


int8_t *decToBin(int dec, int qtdBytes)
{
	int8_t *bin = (int8_t*)malloc(16);

	for(int i=0;i<8*qtdBytes;i++)
	{
		bin[i] = dec%2;
		dec/=2;
	}
	
	return bin;
}

void editFile(char *fileName)
{
	FILE *file = fopen(fileName, "rb");
	if(file==NULL)
	{
		printf("Arquivo inexistente\n");
		return;
	}
	fseek(file, 0,SEEK_END);
	int tamFile = ftell(file)/2;
	int16_t *buffer = (int16_t *)malloc(tamFile);
	int8_t *bufferBin = (int8_t *)malloc(tamFile*16);
	fseek(file, 0,SEEK_SET);
	fread(buffer,2,tamFile,file);
	
	fclose(file);
	for(int i=0;i<tamFile;i++)
	{
		int8_t *temp = decToBin(buffer[i],2);
		bufferBin[i*16 + 0] = temp[0];
		bufferBin[i*16 + 1] = temp[1];
		bufferBin[i*16 + 2] = temp[2];
		bufferBin[i*16 + 3] = temp[3];
		bufferBin[i*16 + 4] = temp[4];
		bufferBin[i*16 + 5] = temp[5];
		bufferBin[i*16 + 6] = temp[6];
		bufferBin[i*16 + 7] = temp[7];
		bufferBin[i*16 + 8] = temp[8];
		bufferBin[i*16 + 9] = temp[9];
		bufferBin[i*16 + 10] = temp[10];
		bufferBin[i*16 + 11] = temp[11];
		bufferBin[i*16 + 12] = temp[12];
		bufferBin[i*16 + 13] = temp[13];
		bufferBin[i*16 + 14] = temp[14];
		bufferBin[i*16 + 15] = temp[15];
	}
	
	for(int i=0;i<tamFile*16;i++)
	{
		printf("%d    %d\n", i, bufferBin[i]);
		if(i%8==7)
			printf("\n");
		if(i%16==15)
		{
			printf("---------------------------------------\n");
		}
	}
	while(1)
	{
		printf("Alterar o bit na posição: ");
		int a;
		scanf("%d", &a);
		if(a==-1)
		{
			break;
		}
		
		bufferBin[a] = not bufferBin[a];
		
		for(int i=0;i<tamFile*16;i++)
		{
			printf("%d    %d\n", i, bufferBin[i]);
			if(i%8==7)
				printf("\n");
			if(i%16==15)
			{
				printf("---------------------------------------\n");
			}
		}
	}
	for(int i=0;i<tamFile;i++)
	{
		int8_t *temp = (int8_t*)malloc(16);
		temp[0] = bufferBin[i*16 + 0];
		temp[1] = bufferBin[i*16 + 1];
		temp[2] = bufferBin[i*16 + 2];
		temp[3] = bufferBin[i*16 + 3];
		temp[4] = bufferBin[i*16 + 4];
		temp[5] = bufferBin[i*16 + 5];
		temp[6] = bufferBin[i*16 + 6];
		temp[7] = bufferBin[i*16 + 7];
		temp[8] = bufferBin[i*16 + 8];
		temp[9] = bufferBin[i*16 + 9];
		temp[10] = bufferBin[i*16 + 10];
		temp[11] = bufferBin[i*16 + 11];
		temp[12] = bufferBin[i*16 + 12];
		temp[13] = bufferBin[i*16 + 13];
		temp[14] = bufferBin[i*16 + 14];
		temp[15] = bufferBin[i*16 + 15];
		
		buffer[i] = binToDec(temp,2);
	}
	file = fopen(fileName, "wb");
	if(file==NULL)
	{
		printf("s\n\n\n");
	}
	fseek(file,0,SEEK_SET);
	fwrite(buffer,2,tamFile,file);
	fclose(file);
}

int main(int argc, char *argv[ ])
{
	editFile(argv[1]);
}
