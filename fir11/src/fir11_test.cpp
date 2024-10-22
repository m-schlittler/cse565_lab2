/*
	Filename: fir_test.h
		FIR lab wirtten for WES/CSE237C class at UCSD.
		Testbench file
		Calls fir() function from fir.cpp
		Compares the output from fir() with out.gold.dat
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "fir11_kernel.h"
//#include <iostream>
#include <fstream>

int main () {
  const int    SAMPLES=600;
  FILE         *fp, *fin;

  data_t signal, output;
  int i;
  signal = 0;

  //fin=fopen("input.dat","r");
  std::ifstream file_in;
  std::ofstream file_out;
  file_in.open("input.dat");
  file_out.open("out.dat");

  for (i=0;i<SAMPLES;i++) {  

	//read in signal
    file_in >> signal;
	//Call the HLS block
    fir(&output,signal);
    // Save the results.
    file_out << output << std::endl;
    
    printf("%i %d %d\n",i,signal,output);
  }

  file_in.close();
  file_out.close();


  //Comparing results with the golden output.
  printf ("Comparing against output data \n");
    if (system("diff -w out.dat out.gold.fir11.dat")) {
  	fprintf(stdout, "*******************************************\n");
  	fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
  	fprintf(stdout, "*******************************************\n");
       return 1;
    } else {
  	fprintf(stdout, "*******************************************\n");
  	fprintf(stdout, "PASS: The output matches the golden output!\n");
  	fprintf(stdout, "*******************************************\n");
       return 0;
    }

}

