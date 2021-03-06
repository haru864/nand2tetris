// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

  (LOOP)
    // read keyboard input (no input, do nothing)
    @KBD
    D=M
    @index
    M=0
    @color
    M=0
    @FILL_LOOP
    D;JEQ
    @color
    M=-1

    // fill screen
  (FILL_LOOP)
    @index
    D=M
    @8191
    D=D-A
    @CONTINUE
    D;JGT

    @index
    D=M
    @SCREEN
    D=D+A
    @CURRENT
    M=D
    @color
    D=M
    @CURRENT
    A=M
    M=D

    @index
    M=M+1
    @FILL_LOOP
    0;JMP

    // continue loop
  (CONTINUE)
    @LOOP
    0;JMP
