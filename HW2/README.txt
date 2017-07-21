# EE569 Homework Assignment #2
# Date: February 26, 2017
# Name: Dixith Reddy Gomari
# ID: 3098-7664-83
# email: gomari@usc.edu
#
# Compiled on WINDOWS 10 with g++
# Define compiler and linker
CC=g++

All : prob1 prob2 prob3 prob4 prob5 prob6 prob7 prob8 prob9
prob1:
@echo “compiling and linking the code”
$(CC) -o w Warp.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./w cup2.raw cup2_final.raw 3 500 500
./w cup1.raw cup1_final.raw 3 500 500

prob2:
@echo “compiling and linking the code”
$(CC) -o p Puzzle.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./p piece.raw Hillary.raw Trump.raw Hillary_Final.raw Trump_Final.raw 3 500 500 512 512

prob3:
@echo “compiling and linking the code”
$(CC) -o h Homographic.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./h field.raw trojans.raw tro_homo.raw 3 648 972 197 350
g++ -o b Blend.cpp
./b field.raw tro_homo.raw aa.raw 3 972 648

prob4:
@echo “compiling and linking the code”
$(CC) -o dither dither.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./dither man.raw I2.raw I4.raw I8.raw A4.raw Four_colors.raw 1 512 512

prob5:
@echo “compiling and linking the code”
$(CC) -o errdif errdif.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./err man.raw FS.raw JJN.raw Stucki.raw 1 512 512

prob6:
@echo “compiling and linking the code”
$(CC) -o s Shrink.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./s squares.raw shrink.raw 1 480 480

prob7:
@echo “compiling and linking the code”
$(CC) -o t Thin.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./t letterE.raw Thin.raw 1 480 480

prob8:
@echo “compiling and linking the code”
$(CC) -o Ske Skeleton.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./Ske letterE.raw Ske.raw 1 480 480

prob9:
@echo “compiling and linking the code”
$(CC) -o bob Board_b.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./bob board.raw no_holes.raw 1 480 480