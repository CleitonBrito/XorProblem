#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include "Struct.h"
#include "Matrix.c"
#include "NeuralNetwork.c"

#ifndef BOOL
    #define boolean
    	typedef enum {false, true} Boolean;
	#endif

Matrix matrixA, matrixB, matrixC, target_inputs[4], target_output[4], input;

int menu(){
	int option;
    printf("============================\n");
    printf("====== XOR PROBLEM ML ======\n");
    printf("============================\n\n");
	printf("--------- MENU ---------\n\n");
	printf("0 - EXIT\n");
	printf("1 - TRAIN NETWORK\n");
	printf("2 - USE\n");

	printf("\nCHOOSE YOUR OPTION: ");
	scanf("%d", &option);
	return option;
}

void training(){
	create_network(2,3,1);

	target_inputs[0].row = 2;
	target_inputs[0].col = 1;
	target_inputs[1].row = 2;
	target_inputs[1].col = 1;
	target_inputs[2].row = 2;
	target_inputs[2].col = 1;
	target_inputs[3].row = 2;
	target_inputs[3].col = 1;

	target_inputs[0].elm = allocate_matrix(target_inputs[0].row, target_inputs[0].col);
	target_inputs[0].elm[0][0] = 1;
	target_inputs[0].elm[1][0] = 1;

	target_inputs[1].elm = allocate_matrix(target_inputs[1].row, target_inputs[1].col);
	target_inputs[1].elm[0][0] = 1;
	target_inputs[1].elm[1][0] = 0;

	target_inputs[2].elm = allocate_matrix(target_inputs[2].row, target_inputs[2].col);
	target_inputs[2].elm[0][0] = 0;
	target_inputs[2].elm[1][0] = 1;

	target_inputs[3].elm = allocate_matrix(target_inputs[3].row, target_inputs[3].col);
	target_inputs[3].elm[0][0] = 0;
	target_inputs[3].elm[1][0] = 0;

	target_output[0].row = 1;
	target_output[0].col = 1;
	target_output[1].row = 1;
	target_output[1].col = 1;
	target_output[2].row = 1;
	target_output[2].col = 1;
	target_output[3].row = 1;
	target_output[3].col = 1;

	target_output[0].elm = allocate_matrix(target_output[0].row, target_output[0].col);
	target_output[0].elm[0][0] = 0;

	target_output[1].elm = allocate_matrix(target_output[1].row, target_output[1].col);
	target_output[1].elm[0][0] = 1;

	target_output[2].elm = allocate_matrix(target_output[2].row, target_output[2].col);
	target_output[2].elm[0][0] = 1;

	target_output[3].elm = allocate_matrix(target_output[3].row, target_output[3].col);
	target_output[3].elm[0][0] = 0;


	printf("\n------------------------\n");
    printf("TRAINING NETWORK\n");
    printf("------------------------\n\n");
	int index, i, j, total_training, max_generation, current_generation;
	float result;

	Boolean training;
	training = true;
	total_training = 10000;
	max_generation = 30;
	current_generation = 0;

	while(training){
		for(i=0; i < total_training; i++){
			index = rand() % 4;
			training_network(target_inputs[index], target_output[index]);
		}
		current_generation += 1;
		printf("TRAINING...\n");

		if(predict(target_inputs[3]) < 0.04 && predict(target_inputs[1]) > 0.98){
			training = false;
			printf("\n------------\n");
			printf("TREINED!\n");
			printf("------------\n\n");

		}else if(current_generation >= max_generation){
			training = false;
			printf("\n------------\n");
			printf("ERROR: UNTRAINED!\n");
			printf("------------\n\n");
		}
	}
	system ("cls");
}

void use(){
	printf("--------- MODEL ----------\n");
	printf("[1][1] = [0]\n");
	printf("[0][1] = [1]\n");
	printf("[1][0] = [1]\n");
	printf("[0][0] = [0]\n");
	printf("-------------- -----------\n\n");
	input.row = 2;
	input.col = 1;
	input.elm = allocate_matrix(input.row, input.col);


	printf("Enter TWO values between 0 e 1\n\n");

	do{
		printf("Enter the FIRST value: ");
		scanf("%f", &input.elm[0][0]);
	}while(input.elm[0][0] < 0 || input.elm[0][0] > 1);
	printf("------------------------\n");

	do{
		printf("Enter the SECOND value: ");
		scanf("%f", &input.elm[1][0]);
	}while(input.elm[1][0] < 0 || input.elm[1][0] > 1);
	printf("------------------------\n");
	printf("\nRESULT: %d\n\n", (int)round(predict(input)));
}

int main(){
	int menu_option;
	training();
	menu_option = menu();

	while (menu_option!=0){
        system ("cls");
		if (menu_option==1){
			srand(time(NULL));
			training();
		}else if(menu_option==2){
			use();
		}
		menu_option=menu();
	}

}
