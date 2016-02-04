Scheme LOGO in C

Warnings: 

1. This is development verison, so if you find any errors/problems do not hesitate to write.

2. The program was written by means of high standards, however, the authors are not responsible for any damages that result from the use of this program. Use it at your own risk.



Authors:

Mateusz Hofman
cynamonized@gmail.com                       
Cracow University of Technology
Krakow, Poland


Radoslaw Kycia
rkycia@pk.edu.pl                       
Cracow University of Technology
Krakow, Poland


Brief descritpion:

Implementation of LOGO in Scheme language. It is based on Guile and uses OpenGL for drawing. It uses threads.

Bibliography:

[1] Guile, http://www.gnu.org/software/guile/

[2] Emebedding Guile in C, http://www.gnu.org/software/guile/docs/guile-tut/tutorial.html


Dependence:

1. Guile
2. Posix Threads
3. OpenGL
4. Glut
5. GCC

Warnings:
1. It is a protoype writtend to show "proof of concept" and can and should be extended.


Commands

- To compile and run type: make run 
  
  Executable is in ./bin directory

- To clean executables: make clean

- To load script first compile program(make main.x) and then load: ./main.x < scriptName.scm




Directory structure:

 - ./ - main directory contains Makefile
 - /Scripts - contains Scheme/Logo scripts to draw basic figures


