/*Organização e Arquitetura de Computadores

Aluno: Raphael Rodrigues Pereira
Matrícula: 11/0039530
Turma: A*/

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

/*
	______________________________
R	|op |rs |rt |rd |shamt |funct|
	  6   5   5   5    5      6
	_____________________________
I	|op |rs |rt |16 bit imediato|
	  6   5   5         16
	_____________________
J	|op |26 bit endereço|
          6         26
 
 */

enum OPCODES{
	ADDI=0x08,
	ANDI=0x0C,
	BEQ=0x04,
	BNE=0x05,
	EXT=0x00,
	J=0x02,
	JAL=0x03,
	LW=0x23,
	ORI=0x0D,
	SW=0x2B
};

enum FUNCT{
	ADD=0x20,
	NOR=0x27,
	SRA=0x03,
	SUB=0x22,	
	MULT=0x18,
	SLT=0x2A,
	SYSCALL=0x0c,
	JR=0x08,
	MFHI=0x10,
	AND=0x24,
	SLL=0x00,
	MFLO=0x12,
	OR=0x25, 	
	XOR=0x26,
	SRL=0x02
};

//Declaração do banco de registradores
//zero, at, v0, v1, a0, a1, a2, a3, t0, t1, t2, t3, t4, t5, t6, t7, s0, s1, s2, s3, s4, s5, s6, s7, t8, t9, k0, k1, gp, sp, fp, ra, pc, hi, lo;
int32_t registradores[36];

//Declaração do banco de memória
uint32_t mem[4096];

//Imprime o conteúdo da memória a partir do endereço start até o endereço end. O formato pode ser em hexa (‘h’) ou decimal (‘d’)
void dump_Mem(int start, int end, char format, char p_f){
	
	FILE *result;
	
	result = fopen("mem.txt", "w");
	
	int i;
	char hexa[80] = {};
	
	if (start < 0 || start > 4095 || end < 0 || start > 4095){
		exit(0);
	}
	if (p_f == 'p'){
		if (format == 'h'){
			for (i=start;i<end;i++){
				
				sprintf(hexa, "%x", mem[i]);
				
				if ((strlen(hexa)) == 8){
	// 				fprintf(result, "Posição: mem[%d] = 0x%X\n", i, mem[i]);
					printf("Posição: mem[%d] = 0x%X\n", i, mem[i]);
				} else if ((strlen(hexa)) == 7){
	// 				fprintf(result, "Posição: mem[%d] = 0x0%X\n", i, mem[i]);
					printf("Posição: mem[%d] = 0x0%X\n", i, mem[i]);
				} else if ((strlen(hexa)) == 6){
	// 				fprintf(result, "Posição: mem[%d] = 0x00%X\n", i, mem[i]);
					printf("Posição: mem[%d] = 0x00%X\n", i, mem[i]);
				} else if ((strlen(hexa)) == 5){
	// 				fprintf(result, "Posição: mem[%d] = 0x000%X\n", i, mem[i]);
					printf("Posição: mem[%d] = 0x000%X\n", i, mem[i]);
				} else if ((strlen(hexa)) == 4){
	// 				fprintf(result, "Posição: mem[%d] = 0x0000%X\n", i, mem[i]);
					printf("Posição: mem[%d] = 0x0000%X\n", i, mem[i]);
				} else if ((strlen(hexa)) == 3){
	// 				fprintf(result, "Posição: mem[%d] = 0x00000%X\n", i, mem[i]);
					printf("Posição: mem[%d] = 0x00000%X\n", i, mem[i]);
				} else if ((strlen(hexa)) == 2){
	// 				fprintf(result, "Posição: mem[%d] = 0x000000%X\n", i, mem[i]);
					printf("Posição: mem[%d] = 0x000000%X\n", i, mem[i]);
				} else if ((strlen(hexa)) == 1){
	// 				fprintf(result, "Posição: mem[%d] = 0x0000000%X\n", i, mem[i]);
					printf("Posição: mem[%d] = 0x0000000%X\n", i, mem[i]);
				}
			}
		} else if (format == 'd'){
			for (i=start;i<end;i++){
				fprintf(result, "Posição: mem[%d] = %d\n", i, mem[i]);
			}
		}
	} else if (p_f == 'f'){
		for (i=start;i<end;i++){
			
			sprintf(hexa, "%x", mem[i]);
			
			if ((strlen(hexa)) == 8){
 				fprintf(result, "Posição: mem[%d] = 0x%X\n", i, mem[i]);
			} else if ((strlen(hexa)) == 7){
 				fprintf(result, "Posição: mem[%d] = 0x0%X\n", i, mem[i]);
			} else if ((strlen(hexa)) == 6){
 				fprintf(result, "Posição: mem[%d] = 0x00%X\n", i, mem[i]);
			} else if ((strlen(hexa)) == 5){
 				fprintf(result, "Posição: mem[%d] = 0x000%X\n", i, mem[i]);
			} else if ((strlen(hexa)) == 4){
 				fprintf(result, "Posição: mem[%d] = 0x0000%X\n", i, mem[i]);
			} else if ((strlen(hexa)) == 3){
 				fprintf(result, "Posição: mem[%d] = 0x00000%X\n", i, mem[i]);
			} else if ((strlen(hexa)) == 2){
 				fprintf(result, "Posição: mem[%d] = 0x000000%X\n", i, mem[i]);
			} else if ((strlen(hexa)) == 1){
 				fprintf(result, "Posição: mem[%d] = 0x0000000%X\n", i, mem[i]);
			}
		}
	}
	
	fclose(result);
	
}

//Imprime o conteúdo da memória a partir do endereço start até o endereço end. O formato pode ser em hexa (‘h’) ou decimal (‘d’)
void dump_Reg(char format, char p_f){
	
	FILE *result;
	
	result = fopen("reg.txt", "w");
	
	int i;
	char hexa[80] = {};
	
	if (p_f == 'p'){
		printf("REGISTERS\n");
	}
	
	if (format == 'h'){
		for (i=0;i<35;i++){
			if (p_f == 'p'){
				if (i == 0){
	// 				fprintf(result, "Registrador $zero. ");
					printf("$zero = ");
				} else if (i == 1){
	// 				fprintf(result, "Registrador $at. ");
					printf("$at = ");
				} else if (i == 2){
	// 				fprintf(result, "Registrador $v0. ");
					printf("$v0 = ");
				} else if (i == 3){
	// 				fprintf(result, "Registrador $v1. ");
					printf("$v1 = ");
				} else if (i == 4){
	// 				fprintf(result, "Registrador $a0. ");
					printf("$a0 = ");
				} else if (i == 5){
	// 				fprintf(result, "Registrador $a1. ");
					printf("$a1 = ");
				} else if (i == 6){
	// 				fprintf(result, "Registrador $a2. ");
					printf("$a2 = ");
				} else if (i == 7){
	// 				fprintf(result, "Registrador $a3. ");
					printf("$a3 = ");
				} else if (i == 8){
	// 				fprintf(result, "Registrador $t0. ");
					printf("$t0 = ");
				} else if (i == 9){
	// 				fprintf(result, "Registrador $t1. ");
					printf("$t1 = ");
				} else if (i == 10){
	// 				fprintf(result, "Registrador $t2. ");
					printf("$t2 = ");
				} else if (i == 11){
	// 				fprintf(result, "Registrador $t3. ");
					printf("$t3 = ");
				} else if (i == 12){
	// 				fprintf(result, "Registrador $t4. ");
					printf("$t4 = ");
				} else if (i == 13){
	// 				fprintf(result, "Registrador $t5. ");
					printf("$t5 = ");
				} else if (i == 14){
	// 				fprintf(result, "Registrador $t6. ");
					printf("$t6 = ");
				} else if (i == 15){
	// 				fprintf(result, "Registrador $t7. ");
					printf("$t7 = ");
				} else if (i == 16){
	// 				fprintf(result, "Registrador $s0. ");
					printf("$s0 = ");
				} else if (i == 17){
	// 				fprintf(result, "Registrador $s1. ");
					printf("$s1 = ");
				} else if (i == 18){
	// 				fprintf(result, "Registrador $s2. ");
					printf("$s2 = ");
				} else if (i == 19){
	// 				fprintf(result, "Registrador $s3. ");
					printf("$s3 = ");
				} else if (i == 20){
	// 				fprintf(result, "Registrador $s4. ");
					printf("$s4 = ");
				} else if (i == 21){
	// 				fprintf(result, "Registrador $s5. ");
					printf("$s5 = ");
				} else if (i == 22){
	// 				fprintf(result, "Registrador $s6. ");
					printf("$s6 = ");
				} else if (i == 23){
	// 				fprintf(result, "Registrador $s7. ");
					printf("$s7 = ");
				} else if (i == 24){
	// 				fprintf(result, "Registrador $t8. ");
					printf("$t8 = ");
				} else if (i == 25){
	// 				fprintf(result, "Registrador $t9. ");
					printf("$t9 = ");
				} else if (i == 26){
	// 				fprintf(result, "Registrador $k0. ");
					printf("$k0 = ");
				} else if (i == 27){
	// 				fprintf(result, "Registrador $k1. ");
					printf("$k1 = ");
				} else if (i == 28){
	// 				fprintf(result, "Registrador $gp. ");
					printf("$gp = ");
				} else if (i == 29){
	// 				fprintf(result, "Registrador $sp. ");
					printf("$sp = ");
				} else if (i == 30){
	// 				fprintf(result, "Registrador $fp. ");
					printf("$fp = ");
				} else if (i == 31){
	// 				fprintf(result, "Registrador $ra. ");
					printf("$ra = ");
				} else if (i == 32){
	// 				fprintf(result, "Registrador $pc. ");
					printf("$pc = ");
				} else if (i == 33){
	// 				fprintf(result, "Registrador $hi. ");
					printf("$hi = ");
				} else if (i == 34){
	// 				fprintf(result, "Registrador $lo. ");
					printf("$lo = ");
				}
				
				sprintf(hexa, "%X", registradores[i]);
	// 			fprintf(result, "Valor no registrador[%d] = %s\n", i, hexa);
				if ((strlen(hexa)) == 8){
	// 				fprintf(result, "Posição: %d = 0x%X\n", i, registradores[i]);
					printf("0x%X\n", registradores[i]);
				} else if ((strlen(hexa)) == 7){
	// 				fprintf(result, "Posição: %d = 0x0%X\n", i, registradores[i]);
					printf("0x0%X\n", registradores[i]);
				} else if ((strlen(hexa)) == 6){
	// 				fprintf(result, "Posição: %d = 0x00%X\n", i, registradores[i]);
					printf("0x00%X\n", registradores[i]);
				} else if ((strlen(hexa)) == 5){
	// 				fprintf(result, "Posição: %d = 0x000%X\n", i, registradores[i]);
					printf("0x000%X\n", registradores[i]);
				} else if ((strlen(hexa)) == 4){
	// 				fprintf(result, "Posição: %d = 0x0000%X\n", i, registradores[i]);
					printf("0x0000%X\n", registradores[i]);
				} else if ((strlen(hexa)) == 3){
	// 				fprintf(result, "Posição: %d = 0x00000%X\n", i, registradores[i]);
					printf("0x00000%X\n", registradores[i]);
				} else if ((strlen(hexa)) == 2){
	// 				fprintf(result, "Posição: %d = 0x000000%X\n", i, registradores[i]);
					printf("0x000000%X\n", registradores[i]);
				} else if ((strlen(hexa)) == 1){
	// 				fprintf(result, "Posição: %d = 0x0000000%X\n", i, registradores[i]);
					printf("0x0000000%X\n", registradores[i]);
				}
			} else if (p_f == 'f'){
				if (i == 0){
	 				fprintf(result, "$zero = ");
// 					printf("$zero = ");
				} else if (i == 1){
	 				fprintf(result, "$at = ");
// 					printf("$at = ");
				} else if (i == 2){
	 				fprintf(result, "$v0 = ");
// 					printf("$v0 = ");
				} else if (i == 3){
	 				fprintf(result, "$v1 = ");
// 					printf("$v1 = ");
				} else if (i == 4){
	 				fprintf(result, "$a0 = ");
// 					printf("$a0 = ");
				} else if (i == 5){
	 				fprintf(result, "$a1 = ");
// 					printf("$a1 = ");
				} else if (i == 6){
	 				fprintf(result, "$a2 = ");
// 					printf("$a2 = ");
				} else if (i == 7){
	 				fprintf(result, "$a3 = ");
// 					printf("$a3 = ");
				} else if (i == 8){
	 				fprintf(result, "$t0 = ");
// 					printf("$t0 = ");
				} else if (i == 9){
	 				fprintf(result, "$t1 = ");
// 					printf("$t1 = ");
				} else if (i == 10){
	 				fprintf(result, "$t2 = ");
// 					printf("$t2 = ");
				} else if (i == 11){
	 				fprintf(result, "$t3 = ");
// 					printf("$t3 = ");
				} else if (i == 12){
	 				fprintf(result, "$t4 = ");
// 					printf("$t4 = ");
				} else if (i == 13){
	 				fprintf(result, "$t5 = ");
// 					printf("$t5 = ");
				} else if (i == 14){
	 				fprintf(result, "$t6 = ");
// 					printf("$t6 = ");
				} else if (i == 15){
	 				fprintf(result, "$t7 = ");
// 					printf("$t7 = ");
				} else if (i == 16){
	 				fprintf(result, "$s0 = ");
// 					printf("$s0 = ");
				} else if (i == 17){
	 				fprintf(result, "$s1 = ");
// 					printf("$s1 = ");
				} else if (i == 18){
	 				fprintf(result, "$s2 = ");
// 					printf("$s2 = ");
				} else if (i == 19){
	 				fprintf(result, "$s3 = ");
// 					printf("$s3 = ");
				} else if (i == 20){
	 				fprintf(result, "$s4 = ");
// 					printf("$s4 = ");
				} else if (i == 21){
	 				fprintf(result, "$s5 = ");
// 					printf("$s5 = ");
				} else if (i == 22){
	 				fprintf(result, "$s6 = ");
// 					printf("$s6 = ");
				} else if (i == 23){
	 				fprintf(result, "$s7 = ");
// 					printf("$s7 = ");
				} else if (i == 24){
	 				fprintf(result, "$t8 = ");
// 					printf("$t8 = ");
				} else if (i == 25){
	 				fprintf(result, "$t9 = ");
// 					printf("$t9 = ");
				} else if (i == 26){
	 				fprintf(result, "$k0 = ");
// 					printf("$k0 = ");
				} else if (i == 27){
	 				fprintf(result, "$k1 = ");
// 					printf("$k1 = ");
				} else if (i == 28){
	 				fprintf(result, "$gp = ");
// 					printf("$gp = ");
				} else if (i == 29){
	 				fprintf(result, "$sp = ");
// 					printf("$sp = ");
				} else if (i == 30){
	 				fprintf(result, "$fp = ");
// 					printf("$fp = ");
				} else if (i == 31){
	 				fprintf(result, "$ra = ");
// 					printf("$ra = ");
				} else if (i == 32){
	 				fprintf(result, "$pc = ");
// 					printf("$pc = ");
				} else if (i == 33){
	 				fprintf(result, "$hi = ");
// 					printf("$hi = ");
				} else if (i == 34){
	 				fprintf(result, "$lo = ");
// 					printf("$lo = ");
				}
				
				sprintf(hexa, "%X", registradores[i]);
// 	 			fprintf(result, "Valor no registrador[%d] = %s\n", i, hexa);
				if ((strlen(hexa)) == 8){
	 				fprintf(result, "0x%X\n", registradores[i]);
// 					printf("0x%X\n", registradores[i]);
				} else if ((strlen(hexa)) == 7){
	 				fprintf(result, "0x0%X\n", registradores[i]);
// 					printf("0x0%X\n", registradores[i]);
				} else if ((strlen(hexa)) == 6){
	 				fprintf(result, "0x00%X\n", registradores[i]);
// 					printf("0x00%X\n", registradores[i]);
				} else if ((strlen(hexa)) == 5){
	 				fprintf(result, "0x000%X\n", registradores[i]);
// 					printf("0x000%X\n", registradores[i]);
				} else if ((strlen(hexa)) == 4){
	 				fprintf(result, "0x0000%X\n", registradores[i]);
// 					printf("0x0000%X\n", registradores[i]);
				} else if ((strlen(hexa)) == 3){
	 				fprintf(result, "0x00000%X\n", registradores[i]);
// 					printf("0x00000%X\n", registradores[i]);
				} else if ((strlen(hexa)) == 2){
	 				fprintf(result, "0x000000%X\n", registradores[i]);
// 					printf("0x000000%X\n", registradores[i]);
				} else if ((strlen(hexa)) == 1){
	 				fprintf(result, "0x0000000%X\n", registradores[i]);
// 					printf("0x0000000%X\n", registradores[i]);
				}
			}
		}
	} else if (format == 'd'){
		for (i=0;i<35;i++){
			
			if (i == 0){
// 				fprintf(result, "Registrador $zero. ");
				printf("$zero = ");
			} else if (i == 1){
// 				fprintf(result, "Registrador $at. ");
				printf("$at = ");
			} else if (i == 2){
// 				fprintf(result, "Registrador $v0. ");
				printf("$v0 = ");
			} else if (i == 3){
// 				fprintf(result, "Registrador $v1. ");
				printf("$v1 = ");
			} else if (i == 4){
// 				fprintf(result, "Registrador $a0. ");
				printf("$a0 = ");
			} else if (i == 5){
// 				fprintf(result, "Registrador $a1. ");
				printf("$a1 = ");
			} else if (i == 6){
// 				fprintf(result, "Registrador $a2. ");
				printf("$a2 = ");
			} else if (i == 7){
// 				fprintf(result, "Registrador $a3. ");
				printf("$a3 = ");
			} else if (i == 8){
// 				fprintf(result, "Registrador $t0. ");
				printf("$t0 = ");
			} else if (i == 9){
// 				fprintf(result, "Registrador $t1. ");
				printf("$t1 = ");
			} else if (i == 10){
// 				fprintf(result, "Registrador $t2. ");
				printf("$t2 = ");
			} else if (i == 11){
// 				fprintf(result, "Registrador $t3. ");
				printf("$t3 = ");
			} else if (i == 12){
// 				fprintf(result, "Registrador $t4. ");
				printf("$t4 = ");
			} else if (i == 13){
// 				fprintf(result, "Registrador $t5. ");
				printf("$t5 = ");
			} else if (i == 14){
// 				fprintf(result, "Registrador $t6. ");
				printf("$t6 = ");
			} else if (i == 15){
// 				fprintf(result, "Registrador $t7. ");
				printf("$t7 = ");
			} else if (i == 16){
// 				fprintf(result, "Registrador $s0. ");
				printf("$s0 = ");
			} else if (i == 17){
// 				fprintf(result, "Registrador $s1. ");
				printf("$s1 = ");
			} else if (i == 18){
// 				fprintf(result, "Registrador $s2. ");
				printf("$s2 = ");
			} else if (i == 19){
// 				fprintf(result, "Registrador $s3. ");
				printf("$s3 = ");
			} else if (i == 20){
// 				fprintf(result, "Registrador $s4. ");
				printf("$s4 = ");
			} else if (i == 21){
// 				fprintf(result, "Registrador $s5. ");
				printf("$s5 = ");
			} else if (i == 22){
// 				fprintf(result, "Registrador $s6. ");
				printf("$s6 = ");
			} else if (i == 23){
// 				fprintf(result, "Registrador $s7. ");
				printf("$s7 = ");
			} else if (i == 24){
// 				fprintf(result, "Registrador $t8. ");
				printf("$t8 = ");
			} else if (i == 25){
// 				fprintf(result, "Registrador $t9. ");
				printf("$t9 = ");
			} else if (i == 26){
// 				fprintf(result, "Registrador $k0. ");
				printf("$k0 = ");
			} else if (i == 27){
// 				fprintf(result, "Registrador $k1. ");
				printf("$k1 = ");
			} else if (i == 28){
// 				fprintf(result, "Registrador $gp. ");
				printf("$gp = ");
			} else if (i == 29){
// 				fprintf(result, "Registrador $sp. ");
				printf("$sp = ");
			} else if (i == 30){
// 				fprintf(result, "Registrador $fp. ");
				printf("$fp = ");
			} else if (i == 31){
// 				fprintf(result, "Registrador $ra. ");
				printf("$ra = ");
			} else if (i == 32){
// 				fprintf(result, "Registrador $pc. ");
				printf("$pc = ");
			} else if (i == 33){
// 				fprintf(result, "Registrador $hi. ");
				printf("$hi = ");
			} else if (i == 34){
// 				fprintf(result, "Registrador $lo. ");
				printf("$lo = ");
			}
			
// 			fprintf(result, "Posição: %d = %d\n", i, registradores[i]);
			printf("%d\n", registradores[i]);
		}
	}
	
// 	fclose(result);
	printf("\n");
}

//Função que inicializa o banco de memória e o banco de registradores com tudo 0
void init_mem(char caminhoText[], char caminhoData[]){
	
	int i, contadorLinhas = 0;
	int c;
	
	//Inicialização zerada de toda a memória
	for (i=0; i<4096; i++){
		mem[i] = 0x00000000;
		if (i < 36)
			registradores[i] = 0;
	}
	
	FILE *codes;
	FILE *data;
	
	/* LER DE ARQUIVO HEXADECIMAL .txt
	codes = fopen(caminhoText, "r");
	data = fopen(caminhoData, "r");
	
	// segmento codigo
	
	//Pega quantas instruções tem no arquivo de código
	
	while ((c = getc(codes)) != EOF){
		if (c == '\n'){
			contadorLinhas += 1;
		}
	}
// 	printf("linhas = %d", contadorLinhas);
	
	rewind(codes);
	
	if (contadorLinhas < 2048){
		for (i=0; i<contadorLinhas; i++){
			fscanf(codes, "%x", &mem[i]); //Pega o valor em hexa do arquivo e armazena na memória
		}
	} else{
		printf("%d\n", contadorLinhas);
		printf("Código muito grande, ultrapassa 2047 words\n");
		exit(0);
	}
		
	// segmento de dados
	
	//Pega quantas instruções tem no arquivo de código
	
	contadorLinhas = 0;
	
	while ((c = getc(data)) != EOF){
		if (c == '\n'){
			contadorLinhas += 1;
		}
	}
	
	rewind(data);
	
	if (contadorLinhas < 4096){
		for (i=0; i<contadorLinhas; i++){
			fscanf(data, "%x", &mem[i+2048]); //Pega o valor em hexa do arquivo e armazena na memória
		}
	} else{
		printf("Código muito grande, ultrapassa 2047 words");
		exit(0);
	}
	*/
	
	//Abre os arquivos .bin requeridos pelo usuário
	codes = fopen(caminhoText, "rb");
	data = fopen(caminhoData, "rb");
	
	int size;
	
	//Realiza toda a inicialização da memória com os códigos e os dados
	//Aponta para o começo do arquivo de leitura
	fseek (codes, 0, SEEK_END);
	size = ftell(codes);
	rewind(codes);

	for (i = 0; i < size/4; i++) {
		fread(&mem[i], sizeof(mem[i]), 1, codes);
	}
	
	fseek (data, 0, SEEK_END);
	size = ftell(data);
	rewind(data);
	for (i = 2048; i < (size/4)+2048; i++) {
		fread(&mem[i], sizeof(mem[i]), 1, data);
	}
	
	fclose(codes);
	fclose(data);
}

//Lê uma instrução da memória e coloca-a em ri, atualizando o pc para apontar para a próxima instrução
void fetch(uint32_t *ri){
	
// 	printf ("INSTRUÇÃO LIDA:\n");
	*ri = mem[registradores[32]/4]; //Carrega em ri a instrução da memória
	registradores[32] += 4; //Incrementa o pc para a próxima instrução
}

//Funcao para extrair os campos tipo R
void decode_TIPO_R(uint32_t opcode, uint32_t *rs, uint32_t *rt, uint32_t *rd, uint32_t *shamt, uint32_t *funct, uint32_t ri){
	
	*rs = (ri >> 21) & 0x1F;			//Armazena o valor de rs com mascara
	
	*rt = (ri >> 16) & 0x1F;			//Armazena o valor de rt com mascara
	
	*rd = (ri >> 11) & 0x1F;			//Armazena o valor de rs com mascara
	
	*shamt = (ri >> 6) & 0x1F;			//Armazena o valor de shamt com mascara
	
	*funct = ri & 0x3F;				//Armazena o valor de funct com mascara
	
//   	printf ("OPCODE: 0x%X\n", opcode);
//   	printf ("RS: %u\n", *rs);
//   	printf ("RT: %u\n", *rt);
//   	printf ("RD: %u\n", *rd);
//   	printf ("SHAMT: %u\n", *shamt);
//   	printf ("FUNCT: 0x%X\n", *funct);
}

//Funcao para extrair os campos tipo I
void decode_TIPO_I(uint32_t opcode, uint32_t *rs, uint32_t *rt, int16_t *imm16, uint32_t ri){
	
	*rs = (ri >> 21) & 0x1F;			//Armazena o valor de rs com mascara
	
	*rt = (ri >> 16) & 0x1F;			//Armazena o valor de rt com mascara
	
	*imm16 = ri & 0xFFFF;				//Armazena o valor de imm16 com mascara
	
//   	printf ("OPCODE: 0x%X\n", opcode);
//   	printf ("RS: %u\n", *rs);
//   	printf ("RT: %u\n", *rt);
//   	printf ("IMM16: %d\n", *imm16);
}

//Funcao para extrair os campos tipo J
void decode_TIPO_J(uint32_t opcode, uint32_t *imm26, int32_t ri){
	
	*imm26 = ri & 0x3FFFFFF;			//Armazena o valor de imm26 com mascara
	
//   	printf ("OPCODE: 0x%X\n", opcode);
//   	printf ("IMM26: %d\n", *imm26);
}

//Função que identifica a instrução (TIPO R) para o execute
char *identificaInstrucaoTipoR(uint32_t funct){
	
	static char command[12];
	strcpy(command, "");
	
//  	printf ("\nINSTRUÇÃO LIDA: \n");
	
	switch (funct){
		//ADD
		case (0x20):
// 			printf ("ADD");
			strcpy(command, "ADD");
		break;
		//ADDU
		case (0x21):
// 			printf ("ADDU");
			strcpy(command, "ADDU");
		break;
		//AND
		case (0x24):
// 			printf ("AND");
			strcpy(command, "AND");
		break;
		//JR
		case (0x08):
// 			printf ("JR");
			strcpy(command, "JR");
		break;
		//NOR
		case (0x27):
// 			printf ("NOR");
			strcpy(command, "NOR");
		break;
		//OR
		case (0x25):
// 			printf ("OR");
			strcpy(command, "OR");
		break;
		//SLT
		case (0x2A):
// 			printf ("SLT");
			strcpy(command, "SLT");
		break;
		//SLTU
		case (0x2B):
// 			printf ("SLTU");
			strcpy(command, "SLTU");
		break;
		//SLL
		case (0x00):
// 			printf ("SLL");
			strcpy(command, "SLL");
		break;
		//SRL
		case (0x02):
// 			printf ("SRL");
			strcpy(command, "SRL");
		break;
		//SUB
		case (0x22):
// 			printf ("SUB");
			strcpy(command, "SUB");
		break;
		//SUBU
		case (0x23):
// 			printf ("SUBU");
			strcpy(command, "SUBU");
		break;
		//SYSCALL
		case (0x0C):
//  			printf ("SYSCALL");
			strcpy(command, "SYSCALL");
		break;
		//SRA
		case (0x03):
// 			printf ("SRA");
			strcpy(command, "SRA");
		break;
		//XOR
		case (0x26):
// 			printf ("XOR");
			strcpy(command, "XOR");
		break;
		//DIV
		case (0x1A):
// 			printf ("DIV");
			strcpy(command, "DIV");
		break;
		//DIVU
		case (0x1B):
// 			printf ("DIVU");
			strcpy(command, "DIVU");
		break;
		//MFHI
		case (0x10):
// 			printf ("MFHI");
			strcpy(command, "MFHI");
		break;
		//MFLO
		case (0x12):
// 			printf ("MFLO");
			strcpy(command, "MFLO");
		break;
		//MULT
		case (0x18):
// 			printf ("MULT");
			strcpy(command, "MULT");
		break;
		//MULTU
		case (0x19):
// 			printf ("MULTU");
			strcpy(command, "MULTU");
		break;
	}
	
//  	printf("\n");
	
	return command;
}

//Função que identifica a instrução (TIPO I ou J) para o execute
char *identificaInstrucaoTipoI_J(uint32_t opcode){
	
	static char command[12];
	strcpy(command, "");
	
//  	printf ("\nINSTRUÇÃO LIDA: \n");
	
	switch (opcode){
		//ADDI
		case (0x8):
//  			printf ("ADDI");
			strcpy(command, "ADDI");
		break;
		//ADDIU
		case (0x9):
//  			printf ("ADDIU");
			strcpy(command, "ADDIU");
		break;
		//ANDI
		case (0xC):
// 			printf ("ANDI");
			strcpy(command, "ANDI");
		break;
		//BEQ
		case (0x4):
// 			printf ("BEQ");
			strcpy(command, "BEQ");
		break;
		//BNE
		case (0x5):
// 			printf ("BNE");
			strcpy(command, "BNE");
		break;
		//LBU
		case (0x24):
// 			printf ("LBU");
			strcpy(command, "LBU");
		break;
		//LHU
		case (0x25):
// 			printf ("LHU");
			strcpy(command, "LHU");
		break;
		//LL
		case (0x30):
// 			printf ("LL");
			strcpy(command, "LL");
		break;
		//LUI
		case (0xF):
// 			printf ("LUI");
			strcpy(command, "LUI");
		break;
		//LW
		case (0x23):
//  			printf ("LW");
			strcpy(command, "LW");
		break;
		//ORI
		case (0xD):
// 			printf ("ORI");
			strcpy(command, "ORI");
		break;
		//ORI
		case (0xE):
// 			printf ("XORI");
			strcpy(command, "XORI");
		break;
		//SLTI
		case (0xA):
// 			printf ("SLTI");
			strcpy(command, "SLTI");
		break;
		//SLTIU
		case (0xB):
// 			printf ("SLTIU");
			strcpy(command, "SLTIU");
		break;
		//SB
		case (0x28):
// 			printf ("SB");
			strcpy(command, "SB");
		break;
		//SC
		case (0x38):
// 			printf ("SC");
			strcpy(command, "SC");
		break;
		//SH
		case (0x29):
// 			printf ("SH");
			strcpy(command, "SH");
		break;
		//SW
		case (0x2B):
// 			printf ("SW");
			strcpy(command, "SW");
		break;
		//LWC1
		case (0x31):
// 			printf ("LWC1");
			strcpy(command, "LWC1");
		break;
		//LDC1
		case (0x35):
// 			printf ("LDC1");
			strcpy(command, "LDC1");
		break;
		//SWC1
		case (0x39):
// 			printf ("SWC1");
			strcpy(command, "SWC1");
		break;
		//SDC1
		case (0x3D):
// 			printf ("SDC1");
			strcpy(command, "SDC1");
		break;
		//J
		case (0x2):
// 			printf ("J");
			strcpy(command, "J");
		break;
		//JAL
		case (0x3):
// 			printf ("JAL");
			strcpy(command, "JAL");
		break;
		//LB
		case (0x20):
// 			printf("LB");
			strcpy(command, "LB");
		break;
		//LH
		case (0x21):
// 			printf("LH");
			strcpy(command, "LH");
		break;
		//BGTZ
		case (0x07):
// 			printf("BGTZ");
			strcpy(command, "BGTZ");
		break;
		//BLEZ
		case (0x06):
// 			printf("BLEZ");
			strcpy(command, "BLEZ");
		break;
	}
//   	printf("\n");
	
	return command;
}

/*
 * No caso do exemplo do fibonacci
 * 2036 em hexa é igual a 8246, que dividindo por 4 dá 2061,5.
 * Ou seja, o byte a ser printado será a partir do endereço 2061, byte 2
 * Sendo o valor em hexa na posição da memória de 2061 = 0x68540020, 
 * pegaremos então o byte 2 desse valor, sendo 0x54.
 * Após acrescentar o valor de i, pegaremos o próximo byte, sendo 0x68
 * Depois de pegar os 2 bytes, será pego agora o valor 2062, pois já chegou-se
 * no byte 3. Sendo assim, pegará o byte 0 de 2062 (0x69462065), ficando 65.
 * E assim por diante até que se encontre a posição de encerramento, sendo \0.
*/
int32_t lb(int *i){
	
	int aux = *i;
	aux /= 4;
	
	//Pega o endereço efetivo da memória
	int endereco = registradores[4]/4 + aux;
//	printf("aux = %d, endereco = %d\n", aux, endereco);
	
	//Determina o byte
	int col = *i%4;
//	printf("col = %d\n", col);

	int32_t a = ((mem[endereco] >> (col * 8)) & (0xFF));
// 	printf("a = %x\n", a);
 	return a;
	
	getchar();
}

//Função que executa a instrução lida pelo fetch() e decodificada pelo decode()
char execute(char command[12], uint32_t rs, uint32_t rt, uint32_t rd, uint32_t shamt, int16_t imm16, int32_t imm26){
	
	//--------------------------TIPO R-----------------------------------
	if ((strcmp(command, "ADD")) == 0){
		//ADD
		registradores[rd] = registradores[rs] + registradores[rt];
	//} else if (strcmp(command, "ADDU")){
		//ADDU
	} else if ((strcmp(command, "AND")) == 0){
		//AND
		registradores[rd] = registradores[rs] & registradores[rt];
	} else if ((strcmp(command, "JR")) == 0){
		//JR
		registradores[32] = registradores[rs];
	} else if ((strcmp(command, "NOR")) == 0){
		//NOR
		registradores[rd] = ~(registradores[rs]|registradores[rt]);
	} else if ((strcmp(command, "OR")) == 0){
		//OR
		registradores[rd] = registradores[rs]|registradores[rt];
	} else if ((strcmp(command, "SLT")) == 0){
		//SLT
		registradores[rd] = (registradores[rs]<registradores[rt]) ? 1:0;
	//} else if (strcmp(command, "SLTU")){
		//SLTU
	} else if ((strcmp(command, "SLL")) == 0){
		//SLL
		registradores[rd] = registradores[rt] << shamt;
	} else if ((strcmp(command, "SRL")) == 0){
		//SRL
		registradores[rd] = registradores[rt] >> shamt;
	} else if ((strcmp(command, "SUB")) == 0){
		//SUB
		registradores[rd] = registradores[rs] - registradores[rt];
	//} else if ((strcmp(command, "SUBU")) == 0){
		//SUBU
	} else if ((strcmp(command, "SYSCALL")) == 0){
		//SYSCALL
		if (registradores[2] == 10){
			return 'y';
		} else if (registradores[2] == 1) {
			printf("%d", registradores[4]);
		} else if (registradores[2] == 4) {
			
			char c = 'a';
			
			int i = 0, aux;
			
			aux = registradores[4]; //2061
			aux /= 4;
			
			//Armazena o valor do registrador a0 em enderecoFracao, para calcular o valor do byte que está sendo endereçado
			float enderecoFracao = registradores[4];
			
			//Divide por 4 o endereço dado para achar a posição efetiva da memória
			enderecoFracao /= 4;
// 			printf("end frac = %.2f\n", enderecoFracao);
			
			enderecoFracao -= aux;
// 			printf("end frac2 = %.2f\n", enderecoFracao);
			i = enderecoFracao*4;
			
// 			printf("i = %d\n", i);
			
			__fpurge(stdin);
			
			while ((c = lb(&i)) != 0) {				
// 				printf("c- |%d| c2- |%d| c3- |%d|\n", c, c2, c3);
				printf("%c", c);
				i++;
			}
		}
	} else if ((strcmp(command, "SRA")) == 0){
		//SRA
		registradores[rd] = registradores[rt] >> shamt;
	} else if ((strcmp(command, "XOR")) == 0){
		//XOR
		registradores[rd] = registradores[rs] ^ registradores[rt];
	} else if ((strcmp(command, "DIV")) == 0){
		//DIV
		int64_t result;
		result = registradores[rs] / registradores[rt];
		registradores[33] = registradores[rs] % registradores[rt];
		registradores[34] = registradores[rs] / registradores[rt];
	//} else if (strcmp(command, "DIVU")){
		//DIVU
	} else if ((strcmp(command, "MFHI")) == 0){
		//MFHI
		registradores[rd] = registradores[33];
	} else if ((strcmp(command, "MFLO")) == 0){
		//MFLO
		registradores[rd] = registradores[34];
	} else if ((strcmp(command, "MULT")) == 0){
		//MULT
		int64_t temp = (int64_t)(int32_t)registradores[rs] * (int64_t)(int32_t)registradores[rt];
		registradores[33] = (uint32_t)((temp>>32) & 0xFFFFFFFF);
		registradores[34] = (uint32_t)(temp & 0xFFFFFFFF);
	//} else if (strcmp(command, "MULTU")){
		//MULTU
	} else if ((strcmp(command, "BGTZ")) == 0){
		//BGTZ
		if (registradores[rs] > registradores[0]){
			registradores[32] = registradores[32] + (4*imm16);
		}
	} else if ((strcmp(command, "BLEZ")) == 0){
		//BLEZ
		if (registradores[rs] <= registradores[0]){
			registradores[32] = registradores[32] + (4*imm16);
		}
	//-------------------------TIPO I-----------------------------------
	} else if ((strcmp(command, "ADDI")) == 0){
		//ADDI
		registradores[rt] = registradores[rs] + imm16;
	} else if ((strcmp(command, "ADDIU")) == 0){
		//ADDIU
		registradores[rt] = registradores[rs] + imm16;
	} else if ((strcmp(command, "ANDI")) == 0){
		//ANDI
		registradores[rt] = registradores[rs] & imm16;
	} else if ((strcmp(command, "BEQ")) == 0){
		//BEQ
		if (registradores[rs] == registradores[rt]){
			registradores[32] += (4*imm16);
		}
	} else if ((strcmp(command, "BNE")) == 0){
		//BNE
		if (registradores[rs] != registradores[rt]){
			registradores[32] += (4*imm16);
		}
	} else if ((strcmp(command, "LBU")) == 0){
		//LBU -> imm16 % 4
		int endereco = ((registradores[rs]/4) + (imm16/4));
		int col = (endereco % 4);
		registradores[rt] = ((mem[endereco] >> col * 8) & (0xFF));
	} else if ((strcmp(command, "LHU")) == 0){
		//LHU
		int endereco = ((registradores[rs]/4) + (imm16/4));
		int col = (endereco % 4);
		registradores[rt] = ((mem[endereco] >> col * 8) & (0xFFFF));
	//} else if (strcmp(command, "LL")){
		//LL
	} else if ((strcmp(command, "LUI")) == 0){
		//LUI
		registradores[rt] = imm16 << 16;
// 		printf("registradores[%d] = 0x%X\n", rt, registradores[rt]);
	} else if ((strcmp(command, "LW")) == 0){
		//LW
		int endereco = ((registradores[rs]/4) + (imm16/4));
//  		printf("Endereco = %d registradores[%d] = %d\n", endereco, rs, mem[endereco]);
		registradores[rt] = mem[endereco];
	} else if ((strcmp(command, "ORI")) == 0){
		//ORI
		registradores[rt] = registradores[rs] | imm16;
// 		printf("registradores[%d] = 0x%X\n", rt, registradores[rt]);
	} else if ((strcmp(command, "XORI")) == 0){
		//XORI
		registradores[rt] = registradores[rs] ^ imm16;
	} else if ((strcmp(command, "SLTI")) == 0){
		//SLTI
		if (registradores[rs] < imm16) {
			registradores[rt] = 1;
		} else {
			registradores[rt] = 0;
		}
	} else if ((strcmp(command, "SLTIU")) == 0){
		//SLTIU
		if (registradores[rs] < imm16) {
			registradores[rt] = 1;
		} else {
			registradores[rt] = 0;
		}
	} else if ((strcmp(command, "SB")) == 0){
		//SB
		int32_t word8;
		int t1;
		int endereco = ((registradores[rs]/4) + (imm16/4));
		int col = endereco % 4;
		word8 = 0x00FFFFFF >> 8 * (3 - col);
		t1 = 0xFFFFFF00 << 8 * col;
		t1 = t1 | word8;
		t1 = t1 & mem[endereco];
		word8 = registradores[rt];
		word8 = (word8 & 0xFF);
		word8 = (word8 << col * 8);
		word8 = t1 | word8;
		mem[endereco] = registradores[rt];
	//} else if (strcmp(command, "SC")){
		//SC
	} else if ((strcmp(command, "SH")) == 0){
		//SH
		int32_t word8;
		int t1;
		int endereco = ((registradores[rs]/4) + (imm16/4));
		int col = endereco % 4;
		word8 = 0x00FFFFFF >> 8 * (3 - col);
		t1 = 0xFFFFFF00 << 8 * (1 + col);
		t1 = t1 | word8;
		t1 = t1 & mem[endereco];
		word8 = registradores[rt];
		word8 = (word8 & 0xFFFF);
		word8 = (word8 << col * 8);
		word8 = t1 | word8;
		mem[endereco] = registradores[rt];
	} else if ((strcmp(command, "SW")) == 0){
		//SW
		int endereco = ((registradores[rs]/4) + (imm16/4));
//  		printf("rs %d, imm16 %d\n", registradores[rs], imm16);
//  		printf("Endereco %d\n", endereco);
		mem[endereco] = registradores[rt];
//  		printf("mem[%d] = %d\n", endereco, mem[endereco]);
	//} else if (strcmp(command, "LWC1")){
		//LWC1
	//} else if (strcmp(command, "LDC1")){
		//LDC1
	//} else if (strcmp(command, "SWC1")){
		//SWC1
	//} else if (strcmp(command, "SDC1")){
		//SDC1
	} else if ((strcmp(command, "LB")) == 0){
		//LB
		int endereco = ((registradores[rs]/4) + (imm16/4));
		int col = (imm16 % 4);
		registradores[rt] = ((mem[endereco] >> col * 8) & (0xFF));
	} else if ((strcmp(command, "LH")) == 0){
		//LH
		int endereco = ((registradores[rs]/4) + (imm16/4));
		int col = (endereco % 4);
		registradores[rt] = ((mem[endereco] >> col * 8) & (0xFFFF));
	//--------------------------TIPO J-----------------------------------
	} else if ((strcmp(command, "J")) == 0){
		//J
		registradores[32] = 4 * imm26;
	} else if ((strcmp(command, "JAL")) == 0){
		//JAL
//  		printf("registradores[31] = %d registradores[32] = %d\n", registradores[31], registradores[32]);
		registradores[31] = registradores[32];
		registradores[32] = imm26*4;
//  		printf("registradores[31] = %d registradores[32] = %d\n", registradores[31], registradores[32]);
	} else {
 		printf("**************************************\nInstrução não implementada (%s)\n**************************************\n", command);
		return;
	}
}

//Função que administra uma única chamada para as funções: fetch, decode e execute
void step(uint32_t ri, uint32_t opcode, uint32_t rs, uint32_t rt, uint32_t rd, uint32_t shamt, uint32_t funct, int16_t imm16, int32_t imm26, char opcao, char command[12], char *identificaFIM){
	
	char syscall = 'n';
	
	fetch(&ri);
	
	//Armazena o valor de opcode com shift somente
	opcode = ri >> 26;
	
	//Pega os campos correspondentes ao tipo da instrução, sendo R, I ou J
	if (opcode == 0x0){
		decode_TIPO_R(opcode, &rs, &rt, &rd, &shamt, &funct, ri);
	} else if (opcode == 0x2 || opcode == 0x3){
		decode_TIPO_J(opcode, &imm26, ri);
	} else {
		decode_TIPO_I(opcode, &rs, &rt, &imm16, ri);
	}
	
	//Seleciona a intrução a ser executada pelo execute
	if (opcode == 0){
		strcpy(command, identificaInstrucaoTipoR(funct));
	} 
	else {
		strcpy(command, identificaInstrucaoTipoI_J(opcode));
	}
	
// 	printf("-------------------------------------------------\n");
	
	*identificaFIM = execute(command, rs, rt, rd, shamt, imm16, imm26);
}

//Função que roda o código em memória, chamando step
void run(uint32_t ri, uint32_t opcode, uint32_t rs, uint32_t rt, uint32_t rd, uint32_t shamt, uint32_t funct, int16_t imm16, int32_t imm26, char opcao, char command[12], char identificaFIM, char p_f){
	
	int opcao2 = 0;
	int addri, addrf;
	char format;
	
	while ((registradores[32]/4 <= 2048) && (identificaFIM != 'y')){		
		
		if (p_f == 'p'){
			printf("Defina o número da função desejada:\n(1) Step\t\t<Executa uma instrução>\n(2) Run\t\t\t<Executa todo o código e faz o dump dos registradores e da memória ao finalizar>\n(3) dump_mem\t\t<Realiza o dump de memória>\n(4) dump_reg\t\t<Realiza o dump de registradores>\n(5) Exit\t\t<Sai do programa>\n");
			scanf("%d", &opcao2);
			
			if (opcao2 == 1){
					step(ri, opcode, rs, rt, rd, shamt, funct, imm16, imm26, opcao, command, &identificaFIM);
			}
			else if (opcao2 == 2){
				printf("Ao finalizar, foi feito um dump de memoria e de registrador nos arquivos DumpMem.txt e DumpReg.txt\n");
				
				//Apaga o buffer
				__fpurge(stdin);
				
				while ((registradores[32]/4 <= 2048) && (identificaFIM != 'y')){
					step(ri, opcode, rs, rt, rd, shamt, funct, imm16, imm26, opcao, command, &identificaFIM);
				}
				
				exit(0);
			}
			else if (opcao2 == 3){
				printf("Qual o endereço de início? ");
				scanf("%d", &addri);
				printf("Qual o endereço de fim? ");
				scanf("%d", &addrf);
				printf("Qual o formato que deseja? ");
				scanf(" %c", &format);
				getchar();
				
				dump_Mem(addri, addrf, format, p_f);
			} 
			else if (opcao2 == 4){			
				printf("Qual o formato que deseja? ");
				scanf(" %c", &format);
				getchar();
				
				dump_Reg(format, p_f);
			} 
			else if (opcao2 == 5)
				exit(0);
		}
		else if (p_f == 'f'){
			
			//Apaga o buffer
			__fpurge(stdin);
			
			while ((registradores[32]/4 <= 2048) && (identificaFIM != 'y')){
				step(ri, opcode, rs, rt, rd, shamt, funct, imm16, imm26, opcao, command, &identificaFIM);
			}
			
			dump_Mem(0, 4095, 'h', p_f);
			dump_Reg('h', p_f);
		}
	}
}

//Função principal que define valores iniciais, além de chamar a função de iniciar a memória e o banco de registradores, além de chamar a função run
int main(int argc, char *argv[]){
	
	system("clear");
	
	uint32_t ri;
	
	uint32_t opcode, rs, rt, rd, shamt, funct = 0;
	int16_t imm16 = 0;
	int32_t imm26 = 0, pc = 0;
	char opcao, identificaFIM = 'n';
	char command[12];
	
	//Inicializa a memória -> argv[1] = caminho do text, argv[2] = caminho do data
	init_mem(argv[1], argv[2]);
	
	char p_f = argv[3][0];
	
	run(ri, opcode, rs, rt, rd, shamt, funct, imm16, imm26, opcao, command, identificaFIM, p_f);
	
	printf("\n");
	
	return 0;
}