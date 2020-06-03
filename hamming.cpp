#include <bits/stdc++.h>

void printH(int8_t *b) //Apenas para visualização e debug. Printa uma sequencia de bits no formato do hamming.
{
	printf("%d M8\n",b[12]);
	printf("%d M7\n",b[11]);
	printf("%d M6\n",b[10]);
	printf("%d M5\n",b[9]);
	printf("%d C8\n",b[8]);
	printf("%d M4\n",b[7]);
	printf("%d M3\n",b[6]);
	printf("%d M2\n",b[5]);
	printf("%d C4\n",b[4]);
	printf("%d M1\n",b[3]);
	printf("%d C2\n",b[2]);
	printf("%d C1\n",b[1]);
	printf("%d G\n",b[0]);
}


int binToDec(int8_t *bin, int qtdBytes) //converte um número binário (um vetor de bits) para decimal (int). *bin -> vetor de bits || qtdBytes -> quantidade de bytes.
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


int8_t *decToBin(int dec, int qtdBytes) //converte um número decimal (int) para binário (um vetor de bits) . dec -> valor inteiro || qtdBytes -> quantidade de bytes.
{
	int8_t *bin = (int8_t*)malloc(16);

	for(int i=0;i<8*qtdBytes;i++)
	{
		bin[i] = dec%2;
		dec/=2;
	}
	
	return bin;
}


int16_t byteHammingW(int8_t a) //Aplica a escrita do hamming em um único byte. a -> byte que será aplicado hamming. Retorna 2 bytes em um int16_t.
{
	int8_t *b;
	b = (int8_t *) malloc(16);
	
	//--------------------------------- bits de M -----------------------------------------------------------------------------------------------------------------
	b[3] = a%2;
	a/=2;
	
	b[5] = a%2;
	a/=2;
	
	b[6] = a%2;
	a/=2;
	
	b[7] = a%2;
	a/=2;
	
	b[9] = a%2;
	a/=2;
	
	b[10] = a%2;
	a/=2;
	
	b[11] = a%2;
	a/=2;
	
	b[12] = a%2;
	a/=2;
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//--------------------------------- bits de C -----------------------------------------------------------------------------------------------------------------	
	b[1] = b[3] xor b[5] xor b[7] xor b[9] xor b[11];
	
	b[2] = b[3] xor b[6] xor b[7] xor b[10] xor b[11];
	
	b[4] = b[5] xor b[6] xor b[7] xor b[12];
	
	b[8] = b[9] xor b[10] xor b[11] xor b[12];
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//--------------------------------- bit G -----------------------------------------------------------------------------------------------------------------------
	b[0] = b[1] xor b[2] xor b[3] xor b[4] xor b[5] xor b[6] xor b[7] xor b[8] xor b[9] xor b[10] xor b[11] xor b[12] ; 	
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//--------------------------------- bits restantes ----------------------------------------------------------------------------------------------------------
	b[13] = 0;
	b[14] = 0;
	b[15] = 0;
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//--------------------------------- return ---------------------------------------------------------------------------------------------------------------------
	return ((int16_t) binToDec(b,2));
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
}


int8_t byteHammingR(int16_t a, int8_t *r)//Aplica a leitura do hamming em um único byte. a -> byte que será aplicado hamming. r -> resultado (byte corrigido pelo algoritmo de hamming) e é passado por referência. Retorna 1, 2 ou 3 conforme o resultado da correção.
{
	int8_t *b = decToBin((int)a,2);
	
	int8_t *b8 = (int8_t *)malloc(8);
	
	int ret = 0;

	
	//--------------------------------- cálculo c ------------------------------------------------------------------------------------------------------------------	
	int8_t *c = (int8_t *)malloc(4);
	
	c[0] = b[3] xor b[5] xor b[7] xor b[9] xor b[11];
	
	c[1] = b[3] xor b[6] xor b[7] xor b[10] xor b[11];
	
	c[2] = b[5] xor b[6] xor b[7] xor b[12];
	
	c[3] = b[9] xor b[10] xor b[11] xor b[12];
	
	int8_t C = (int8_t)binToDec(c,1);	
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//---------------------------------- c1 ---------------------------------------------------------------------------------------------------------------------------
	int8_t *c1 = (int8_t *)malloc(4);
	
	c1[0] = b[1];
	
	c1[1] = b[2];
	
	c1[2] = b[4];
		
	c1[3] = b[8];
	
	int8_t C1 = (int8_t)binToDec(c1,1);
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//--------------------------------- SEC ------------------------------------------------------------------------------------------------------------------------

	C = C xor C1;
	
	if(C<=12 && C!=0)
	{
		b[C] = not b[C];
		ret = 3;
	}
	else if(C>12)
	{
		ret = 1;
	}
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//--------------------------------- cálculo g ------------------------------------------------------------------------------------------------------------------	
	int8_t g;
	g = b[1] xor b[2] xor b[3] xor b[4] xor b[5] xor b[6] xor b[7] xor b[8] xor b[9] xor b[10] xor b[11] xor b[12];
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//--------------------------------- DED ------------------------------------------------------------------------------------------------------------------------
	g = g xor b[0];
	
	if(g!=0)
	{
		ret = 2;
	}
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//--------------------------------- valor final ----------------------------------------------------------------------------------------------------------------
	b8[0] = b[3];
	b8[1] = b[5];
	b8[2] = b[6];
	b8[3] = b[7];
	b8[4] = b[9];
	b8[5] = b[10];
	b8[6] = b[11];
	b8[7] = b[12];
	
	*r = (int8_t )binToDec(b8,1);
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	return ret;
}

void hammingW(char *arqName)//Aplica a escrita do hamming em um arquivo. *arqName -> nome do arquivo que deseja-se converter.
{
	FILE *hamming; //arquivo para salvar os dados com hamming.
	FILE *original; //arquivo de entrada.
	char *arqName2 = (char*)malloc(100);//nome do arquivo com hamming.
	
	
	//--------------------------------- abre o arquivo original e copia para um buffer ---------------------------------------------------------
	original = fopen(arqName, "rb");
	if(original==NULL)
	{
		printf("Arquivo inexistente\n");
		return;
	}
	
	fseek(original, 0,SEEK_END);
	int tamOriginal = ftell(original);
	
	int8_t *bufferOriginal = (int8_t *)malloc(tamOriginal);
	fseek(original, 0,SEEK_SET);
	fread(bufferOriginal,1,tamOriginal,original);
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//--------------------------------- cálculo do nome do arquivo resultante --------------------------------------------------------------------
	char tempArqName[14];
	strcpy(tempArqName,"-hamming.sotw");
	for(int i = 0;i<(int)strlen(arqName);i++)
	{
		if(arqName[i]=='.')
		{
			for(int j=0;j<(int)strlen(tempArqName);j++)
			{
				arqName2[i+j]=tempArqName[j];
			}
			arqName2[i+13]='\0';
			break;
		}
		arqName2[i] = arqName[i];
	}
	
	char *arqNameExt = (char*)malloc(10);
	
	
	int k = 0;
	int v = 0;
	int i;
	for( i = 0;i<(int)strlen(arqName);i++)
	{
		if(arqName[i]=='.')
		{
			v=1;
		}
		if(v==1)
		{
			arqNameExt[k++]=arqName[i];
		}
	}
	arqNameExt[i]='\0';
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//--------------------------------- aplica hamming e grava em um novo arquivo ----------------------------------------------------------
	int16_t *bufferHamming = (int16_t *)malloc(tamOriginal*2);
	for(int i=0;i<tamOriginal;i++)
	{
		bufferHamming[i] = byteHammingW(bufferOriginal[i]);
	}

	hamming = fopen(arqName2, "wb");
	fseek(hamming,0,SEEK_SET);
	fwrite(bufferHamming,2,tamOriginal,hamming);
	fseek(hamming,0,SEEK_END);
	fwrite(arqNameExt,1,10,hamming);
	
	fclose(hamming);
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void hammingR(char *arqName)//Aplica a leitura do hamming em um arquivo. *arqName -> nome do arquivo que deseja-se converter.
{
	FILE *hamming; //arquivo com hamming;
	FILE *corrected; //arquivo de saída, corrigido com hamming.
	char *arqName2 = (char*)malloc(100);//nome do arquivo de saída.
	
	//--------------------------------- abre o arquivo com hamming e copia para um buffer ----------------------------------------------
	hamming = fopen(arqName, "rb");
	fseek(hamming, -10, SEEK_END);
	
	char *arqNameExt = (char *)malloc(10);
	int tamHamming = ftell(hamming);

	fread(arqNameExt, 1, 10, hamming);
	
	
	
	fseek(hamming, 0, SEEK_SET);
	
	int16_t *bufferHamming = (int16_t*)malloc(tamHamming);
	int8_t *bufferCorrected = (int8_t*)malloc(tamHamming/2);
	fread(bufferHamming, 2, tamHamming/2, hamming);
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//--------------------------------- cálculo do nome do arquivo resultante --------------------------------------------------------------------
	char tempArqName[12];
	strcpy(tempArqName,"-corrected.");
	
	for(int i = 0;i<(int)strlen(arqName);i++)
	{
		if(arqName[i]=='-')
		{
			for(int j=0;j<(int)strlen(tempArqName);j++)
			{
				arqName2[i+j]=tempArqName[j];
			}
			for(int j=0;j<(int)strlen(arqNameExt);j++)
			{
				arqName2[i+10+j]=arqNameExt[j];
			}
			arqName2[i+11+strlen(arqNameExt)]='\0';
			break;
		}
		arqName2[i] = arqName[i];
	}
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//--------------------------------- recuperaap do arquivo --------------------------------------------------------------------------------------------
	corrected = fopen(arqName2, "wb");
	for(int i=0;i<tamHamming/2;i++)
	{
		int8_t erro = byteHammingR(bufferHamming[i],&bufferCorrected[i] );
		if(erro == 1)
		{
			printf("Erro detectado na posição %d (correção impossível)\n", i);
		}
		else if(erro == 2)
		{
			printf("Erro detectado na posição %d e SEC aumentou o erro (correção impossível)\n", i);
		}
		else if(erro == 3)
		{
			printf("Erro detectado na posição %d (correção realizada)\n", i);
		}
	}
	
	fwrite(bufferCorrected,sizeof(char),tamHamming/2,corrected);
	fclose(corrected);
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
}



int main(int argc, char *argv[ ])
{
	if(argc == 1)
	{
		printf("Faltando dois parâmetros:\n		1 - nome do arquivo\n		2 - identificador de leitura ou escrita (-w para escrita || -r para leitura)\n");
		return 0;
	}
	if(argc == 2)
	{
		printf("Faltando um parâmetro:\n		2 - identificador de leitura ou escrita (-w para escrita || -r para leitura)\n");
		return 0;
	}
	if(argc > 3)
	{
		printf("Parâmetros demais!\n");
		printf("Insira os seguintes parâmentros:\n		1 - nome do arquivo\n		2 - identificador de leitura ou escrita (-w para escrita || -r para leitura)\n");
		return 0;
	}
	
	if(strcmp(argv[2],"-w")==0)
	{
		hammingW(argv[1]);
		return 0;
	}
	else if(strcmp(argv[2],"-r")==0)
	{
		hammingR(argv[1]);
		return 0;
	}
	else
	{
		printf("Identificador de leitura/escrita incorreto\n");
	}
	
	
	
	
	
	return 0;
}
