#define LEARNING_RATE 0.1

Matrix bias_ih, bias_ho, weigth_ih, weigth_ho, soma;
int i, j;

float **sigmoid(Matrix matrixSigmoid){

	for(i=0; i < matrixSigmoid.row; i++){
		for(j=0; j < matrixSigmoid.col; j++){
			matrixSigmoid.elm[i][j] = 1/(1+exp(-matrixSigmoid.elm[i][j]));
		}
	}
	return (matrixSigmoid.elm);
}

float **dsigmoid(Matrix matrixDSigmoid){

	for(i=0; i < matrixDSigmoid.row; i++){
		for(j=0; j < matrixDSigmoid.col; j++){
			matrixDSigmoid.elm[i][j] = matrixDSigmoid.elm[i][j] * (1 - matrixDSigmoid.elm[i][j]);
		}
	}
	return (matrixDSigmoid.elm);
}

int **create_network(int i_node, int h_node, int o_node){
	bias_ih.row = h_node;
	bias_ih.col = 1;
	bias_ih.elm = allocate_matrix(bias_ih.row, bias_ih.col);
	bias_ih.elm = create_matrix(bias_ih);

	bias_ho.row = o_node;
	bias_ho.col = 1;
	bias_ho.elm = allocate_matrix(bias_ho.row, bias_ho.col);
	bias_ho.elm = create_matrix(bias_ho);

	weigth_ih.row = h_node;
	weigth_ih.col = i_node;
	weigth_ih.elm = allocate_matrix(weigth_ih.row, weigth_ih.col);
	weigth_ih.elm = create_matrix(weigth_ih);

	weigth_ho.row = o_node;
	weigth_ho.col = h_node;
	weigth_ho.elm = allocate_matrix(weigth_ho.row, weigth_ho.col);
	weigth_ho.elm = create_matrix(weigth_ho);

}

void training_network(Matrix p_input, Matrix p_target){
	 Matrix hidden, hidden_T, output, output_error, dsigmoid_output, gradient,
			weigths_ho_deltas, weigths_ho_T, hidden_error, d_hidden, input_T,
			gradient_H, weigths_ih_deltas;

//	//FEEDFORWARD

	// INPUT TO HIDDEN
	hidden.row = weigth_ih.row;
	hidden.col = p_input.col;
	hidden.elm = allocate_matrix(hidden.row, hidden.col);
	hidden.elm = multiply_matrix(weigth_ih, p_input);

	hidden.elm = sum_matrix(hidden, bias_ih);
	hidden.elm = sigmoid(hidden);

//	// HIDDEN TO OUTPUT
	output.row = weigth_ho.row;
	output.col = hidden.col;
	output.elm = allocate_matrix(output.row, output.col);
	output.elm = multiply_matrix(weigth_ho, hidden);
	output.elm = sum_matrix(output, bias_ho);
	output.elm = sigmoid(output);

//	//BACKPROPAGATION

//	//OUTPUT TO HIDDEN
	output_error.row = p_target.row;
	output_error.col = p_target.col;
	output_error.elm = allocate_matrix(output_error.row, output_error.col);
	output_error.elm = subtract_matrix(p_target, output);

	dsigmoid_output.row = output.row;
	dsigmoid_output.col = output.col;
	dsigmoid_output.elm = allocate_matrix(dsigmoid_output.row, dsigmoid_output.col);
	dsigmoid_output.elm = dsigmoid(output);

	hidden_T.row = hidden.col;
	hidden_T.col = hidden.row;
	hidden_T.elm = allocate_matrix(hidden_T.row, hidden_T.col);
	hidden_T.elm = transpose(hidden);

	gradient.row = dsigmoid_output.row;
	gradient.col = dsigmoid_output.col;
	gradient.elm = allocate_matrix(gradient.row, gradient.col);
	gradient.elm = hadamard_matrix(dsigmoid_output, output_error);

	gradient.elm = multiply_matrix_with_scalar(gradient, LEARNING_RATE);

	// Adjust Bias O to H
	bias_ho.elm = sum_matrix(bias_ho, gradient);

	// Adjust Weigths O to H
	weigths_ho_deltas.row = gradient.row;
	weigths_ho_deltas.col = hidden_T.col;
	weigths_ho_deltas.elm = allocate_matrix(weigths_ho_deltas.row, weigths_ho_deltas.col);
	weigths_ho_deltas.elm = multiply_matrix(gradient, hidden_T);

	weigth_ho.elm = sum_matrix(weigth_ho, weigths_ho_deltas);

//	// HIDDEN TO INPUT
	weigths_ho_T.row = weigth_ho.col;
	weigths_ho_T.col = weigth_ho.row;
	weigths_ho_T.elm = allocate_matrix(weigths_ho_T.row, weigths_ho_T.col);
	weigths_ho_T.elm = transpose(weigth_ho);

	hidden_error.row = weigths_ho_T.row;
	hidden_error.col = output_error.col;
	hidden_error.elm = allocate_matrix(hidden_error.row, hidden_error.col);
	hidden_error.elm = multiply_matrix(weigths_ho_T, output_error);

	d_hidden.row = hidden.row;
	d_hidden.col = hidden.col;
	d_hidden.elm = allocate_matrix(d_hidden.row, d_hidden.col);
	d_hidden.elm = dsigmoid(hidden);

	input_T.row = p_input.col;
	input_T.col = p_input.row;
	input_T.elm = allocate_matrix(input_T.row, input_T.col);
	input_T.elm = transpose(p_input);

	gradient_H.row = d_hidden.row;
	gradient_H.col = d_hidden.col;
	gradient_H.elm = allocate_matrix(gradient_H.row, gradient_H.col);
	gradient_H.elm = hadamard_matrix(d_hidden, hidden_error);

	gradient_H.elm = multiply_matrix_with_scalar(gradient_H, LEARNING_RATE);

	// Adjust Bias O to H
	bias_ih.elm = sum_matrix(bias_ih, gradient_H);
	// Adjust Weigths H to I
	weigths_ih_deltas.row = gradient_H.row;
	weigths_ih_deltas.col = input_T.col;
	weigths_ih_deltas.elm = allocate_matrix(weigths_ih_deltas.row, weigths_ih_deltas.col);
	weigths_ih_deltas.elm = multiply_matrix(gradient_H, input_T);

	weigth_ih.elm = sum_matrix(weigth_ih, weigths_ih_deltas);
}

float predict(Matrix p_input){
	Matrix hidden, output;

	// INPUT TO HIDDEN
	hidden.row = weigth_ih.row;
	hidden.col = p_input.col;
	hidden.elm = allocate_matrix(hidden.row, hidden.col);
	hidden.elm = multiply_matrix(weigth_ih, p_input);
	hidden.elm = sum_matrix(hidden, bias_ih);
	hidden.elm = sigmoid(hidden);

	// HIDDEN TO OUTPUT
	output.row = weigth_ho.row;
	output.col = hidden.col;
	output.elm = allocate_matrix(output.row, output.col);
	output.elm = multiply_matrix(weigth_ho, hidden);
	output.elm = sum_matrix(output, bias_ho);
	output.elm = sigmoid(output);

	return (output.elm[0][0]);
}



