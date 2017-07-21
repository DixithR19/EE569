# EE569 Homework Assignment #3
# Date: March 26, 2017
# Name: Dixith Reddy Gomari
# ID: 3098-7664-83
# email: gomari@usc.edu
#
# Compiled on WINDOWS 10 with g++
# Define compiler and linker
CC=g++

All : prob1 prob2
prob1:
@echo “compiling and linking the code”
$(CC) -o t texture.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./t Texture1.raw Texture2.raw Texture3.raw Texture4.raw Texture5.raw Texture6.raw Texture7.raw Texture8.raw Texture9.raw Texture10.raw Texture11.raw Texture12.raw TextureA.raw TextureB.raw TextureC.raw TextureD.raw TextureE.raw TextureF.raw 1 128 128


prob2:
@echo “compiling and linking the code”
$(CC) -o s Segmentation.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./s kitten.raw kitten_segment.raw 3 350 590

For other problems, include the openCV libraries and build the programs and run the code.

