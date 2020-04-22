int i, j;

float **allocate_matrix(int m, int n){
	float **matrix;
	int count;

	matrix = (float **)(calloc(m, sizeof(float *)));

	for(count=0; count<m; count++){
		matrix[count] = (float *)(calloc(n, sizeof(float)));
	}
	return (matrix);
}

float **desalocar_matriz(Matrix matrix){

	if(matrix.elm == NULL) return (NULL);
	if(matrix.row < 1 || matrix.col < 1) {
		printf("Error: Invalid Dimension!\n");
		return (NULL);
	}

	for(i=0; i < matrix.row; i++) free(matrix.elm[i]);
	free(matrix.elm);
	return (NULL);
}

float **create_matrix(Matrix matrix){
	float rand_number;

	if(matrix.row < 1 || matrix.col < 1) {
		printf("Error: Invalid Dimension!\n");
	}
	for(i=0; i< matrix.row; i++){
		rand_number = 0.0;
		for(j=0; j< matrix.col; j++){
			rand_number = 0.0;
			while(rand_number <= 0.00000){
				rand_number = (float)(((rand()%9)*1.182014)/10.0);
			}
			matrix.elm[i][j] = rand_number;
		}
	}
	return (matrix.elm);
}

float **sum_matrix(Matrix matrixY, Matrix matrixZ){
	if(matrixY.row < 1 || matrixY.col < 1 || matrixZ.row < 1 || matrixZ.col < 1) {
		printf("Error: Invalid Dimension!\n");
		return (NULL);
	}else if((matrixY.row != matrixZ.row) || (matrixY.col != matrixZ.col)){
		printf("Error: Impossible sum matrices!\n");
		return (NULL);
	}else{
		Matrix matrix;

		matrix.row = matrixY.row;
		matrix.col = matrixY.col;
		matrix.elm = allocate_matrix(matrix.row, matrix.col);

		for(i=0; i< matrix.row; i++){
			for(j=0; j< matrix.col; j++){
				matrix.elm[i][j] = matrixY.elm[i][j] + matrixZ.elm[i][j];
			}
		}
		return (matrix.elm);
	}
}

float **subtract_matrix(Matrix matrixY, Matrix matrixZ){
	if(matrixY.row < 1 || matrixY.col < 1 || matrixZ.row < 1 || matrixZ.col < 1) {
		printf("Error: Invalid Dimension!\n");
		return (NULL);
	}else{
		Matrix matrix;

		matrix.row = matrixY.row;
		matrix.col = matrixY.col;
		matrix.elm = allocate_matrix(matrix.row, matrix.col);

		for(i=0; i< matrix.row; i++){
			for(j=0; j< matrix.col; j++){
				matrix.elm[i][j] = matrixY.elm[i][j] - matrixZ.elm[i][j];
			}
		}
		return (matrix.elm);
	}
}

float **multiply_matrix(Matrix matrixY, Matrix matrixZ){
	if(matrixY.row < 1 || matrixY.col < 1 || matrixZ.row < 1 || matrixZ.col < 1) {
		printf("Error: Invalid Dimension!\n");
		return (NULL);
	}else if((matrixY.col != matrixZ.row) || ((matrixY.row == 1 && matrixZ.col == 1) && (matrixY.row != 1 && matrixZ.col != 1))){
		printf("Error: Impossible multiply matrices!\n");
		return (NULL);
	}else{
		Matrix matrix;
		float sum_prod;
		int k;

		matrix.row = matrixY.row;
		matrix.col = matrixZ.col;
		matrix.elm = allocate_matrix(matrix.row, matrix.col);

		for(i=0; i< matrix.row; i++){
			for(j=0; j< matrix.col; j++){
				sum_prod = 0;
				for(k=0; k < matrixZ.row; k++){
					sum_prod += matrixY.elm[i][k] * matrixZ.elm[k][j];
					matrix.elm[i][j] = sum_prod;
				}
			}
		}
		return (matrix.elm);
	}
}

float **multiply_matrix_with_scalar(Matrix matrixY, float scalar){
	if(matrixY.row < 1 || matrixY.col < 1) {
		printf("Error: Invalid Dimension!\n");
		return (NULL);
	}else{
		Matrix matrix;

		matrix.row = matrixY.row;
		matrix.col = matrixY.col;
		matrix.elm = allocate_matrix(matrix.row, matrix.col);

		for(i=0; i< matrix.row; i++){
			for(j=0; j< matrix.col; j++){
				matrix.elm[i][j] = matrixY.elm[i][j] * scalar;
			}
		}
		return (matrix.elm);
	}
}

float **transpose(Matrix matrixY){
	if(matrixY.row < 1 || matrixY.col < 1){
		printf("Error: Invalid Dimension!\n");
		return (NULL);
	}else{
		Matrix matrizT;

		matrizT.row = matrixY.col;
		matrizT.col = matrixY.row;
		matrizT.elm = allocate_matrix(matrizT.row, matrizT.col);

		for(j=0; j < matrizT.row; j++){
			for(i=0; i < matrizT.col; i++){
				matrizT.elm[j][i] = matrixY.elm[i][j];
			}
		}
		return (matrizT.elm);
	}
}

float **hadamard_matrix(Matrix matrixY, Matrix matrixZ){
	if(matrixY.row < 1 || matrixY.col < 1 || matrixZ.row < 1 || matrixZ.col < 1) {
		printf("Error: Invalid Dimension!\n");
		return (NULL);
	}else if((matrixY.row != matrixZ.row) || (matrixY.col != matrixZ.col)){
		printf("Error: Impossible hadamard!\n");
		return (NULL);
	}else{
		Matrix matrix;

		matrix.row = matrixY.row;
		matrix.col = matrixY.col;
		matrix.elm = allocate_matrix(matrix.row, matrix.col);

		for(i=0; i< matrix.row; i++){
			for(j=0; j< matrix.col; j++){
				matrix.elm[i][j] = matrixY.elm[i][j] * matrixZ.elm[i][j];
			}
		}
		return (matrix.elm);
	}
}

void show_matrix(Matrix matrix){
	printf("\n");

	for(i=0; i< matrix.row; i++){
		for(j=0; j< matrix.col; j++){
			printf("%f\t", matrix.elm[i][j]);
		}
		printf("\n\n");
	}
}

void dimension(char *name, Matrix dimension){
	printf("%s : %dx%d\n", name, dimension.row, dimension.col);
}
