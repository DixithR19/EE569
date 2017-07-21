# EE569 Homework Assignment #1
# Date: February 5, 2017
# Name: Dixith Reddy Gomari
# ID: 3098-7664-83
# email: gomari@usc.edu
#
# Compiled on WINDOWS 10 with g++
# Define compiler and linker
CC=g++

All : prob1 prob2 prob3 prob4 prob5 prob6 prob7 prob8 prob9 prob10 prob11 prob12 prob13 prob14 prob15
prob1:
@echo “compiling and linking the code”
$(CC) -o mirror mirror.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./mirror dog.raw mirror.raw 3 300 300

prob2:
@echo “Problem 1”
@echo “compiling and linking the code”
$(CC) -o img Imageresize.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./img dog.raw re1.raw re2.raw re3.raw 3 300 300 200 200 400 400 600 600

prob3:
@echo “Problem 1”
@echo “compiling and linking the code”
$(CC) -o comp comp.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./comp beach.raw dog.raw comp.raw 3 808 1914 300 300

prob4:
@echo “Problem 1”
@echo “compiling and linking the code”
$(CC) -o cmy cmy.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./cmy parrot.raw c1.raw c2.raw c3.raw 3 512 384
./cmy building.raw c11.raw c22.raw c33.raw 3 789 600

prob5:
@echo “Problem 1”
@echo “compiling and linking the code”
$(CC) -o hsl HSL.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./hsl cat.raw d1.raw d2.raw d3.raw 3 600 398
./hsl dolphin.raw d11.raw d22.raw d33.raw 3 640 480

prob6:
@echo “Problem 1”
@echo “compiling and linking the code”
$(CC) -o sepia sepia.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./sepia beach.raw a1.raw a2.raw 3 1914 808

prob7:
@echo “Problem 1”
@echo “compiling and linking the code”
$(CC) -o blend blend.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./blend top_layer.raw bottom_layer.raw blend.raw 3 890 900

prob8:
@echo “Problem 1”
@echo “compiling and linking the code”
$(CC) -o hse HistEqA.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./hse tulip_dark.raw a.raw 1 400 366
./hse tulip_bright.raw b.raw 1 400 366
./hse tulip_mix.raw c.raw 1 400 366

prob9:
@echo “Problem 1”
@echo “compiling and linking the code”
$(CC) -o hse HistEqA1.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./hse tulip_mix.raw aa.raw 1 400 366

prob10:
@echo “Problem 1”
@echo “compiling and linking the code”
$(CC) -o hse HistEqB1.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./hse tulip_dark.raw p.raw 1 400 366
./hse tulip_bright.raw q.raw 1 400 366
./hse tulip_mix.raw r.raw 1 400 366

prob11:
@echo “Problem 1”
@echo “compiling and linking the code”
$(CC) -o hse hse_color_a.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./hse bedroom.raw bed.raw 3 940 400

prob12:
@echo “Problem 1”
@echo “compiling and linking the code”
$(CC) -o hse hse_color.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./hse bedroom.raw bed1.raw 3 940 400 bed2.raw

prob13:
@echo “Problem 1”
@echo “compiling and linking the code”
$(CC) -o hse hse_advanced.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./hse forest_1.raw forest1.raw 3 960 600
./hse forest_2.raw forest2.raw 3 550 413

prob14:
@echo “Problem 1”
@echo “compiling and linking the code”
$(CC) -o noise noiseimage.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./noise pepper_noisy.raw aa1.raw 3 512 512 pepper.raw

prob15:
@echo “Problem 1”
@echo “compiling and linking the code”
$(CC) -o nlm nlm.cpp
@echo “running the program, usage: solution
inputImageName outputImageName”
./nlm pepper_noisy.raw ab1.raw 3 512 512 pepper.raw
./nlm sailboat_noisy.raw ab2.raw 3 512 512 sailboat.raw