#Q1
description: reverse a given input file
compile: g++ 2023201009_A1_Q1.cpp
run:  ./a.out <input_file_name>
##Approach
    ->take input file name or file path as input from command line arguement
    ->open input file and create an output file 
    ->move the read/write pointer to the end of the file 
    ->read the file in chunks of 100000B
    ->reverse these chunks using a reverse() function and write it into the output file

#Q2
description: given two indices- start and end, reverse the file outside these indices 
compile: g++ 2023201009_A1_Q2.cpp
run:  ./a.out <input_file_name> <start_index> <end_index>
##Approach:
    ->take input file name or file path as input from command line arguement
    ->open input file and create an output file 
    ->break the problem in three parts
    ->first reverse the file from 0 to (start-1) index and write it into output file
    ->read the file from start to end index and write to output file
    ->reverse the file from (start+1) to file_end index and write it into output file
    ->do the above reads in chunks of 100000B


#Q3
description: given the input file path, output file path, directory path from Ist Question, check if the files are reverse of each other, and proint the file/directory permissions
compile: g++ 2023201009_A1_Q3.cpp
run:  ./a.out <newfile> <oldfile> <directory>
##Approach:
    ->check if given directory exists using access system call
    ->to check if new file is reverse of old file, we read the old file from start and the new file from end
    ->read both files in chunks of size 100000B or less and see if they match
    ->to check file permissions use stat system call

