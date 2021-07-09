# Minishell
With this project I have recreated bash, the aim for this project was to learn how to work with asynchronous programs. 
The main issue for this project was to handle multiple chained commands, for example: "ls -la | cat -e > text.txt". 
How are we going to make sure that the last command receives the information it needs from the earlier commands.

## implemented builtins
### cd
### echo
### env
### exit
### export
### pwd
### unset

## file structure
### libft
This folder contains my libft project. In here you find all the builtin C functions which we have recreated for another school project.
### objs
The makefile will create all its obj files inside this folder so these will not bother you inside the srcs folder the objs folder is a direct copy of the srcs file 
only containing the .o files instead of .c files

### srcs
Inside the srcs folder I have tried to group my functions as logical as possible. Each .c has a maximum of 5 functions each 25 lines of code at maximum.
This has been done to enforce the rule: "Each function does only one thing and nothing more".
* builtins
in here you will find all c files containing function regarding the earlier mentions builtins.

* execution
In this folder you find all .c files related to the execution of the actual commands. In here you find the handling op pipes, redirections and the execution itself

* lexer
In this folder you find all files related to the lexer, in these function the linkedlist with the soon to be executed commands is being created.

* parser
In this folder you find all files related to the parsing of the input, mainly input checking is being done in these functions

* utils
In here you find all functions not necesarrily related to one specific stage of the entire process.

* Makefile the makefile to create this entire program

* minishell (the executable after making the project)

## How it works
Once you clone this repository run make a executable named minishell will be created. If you run this command your command prompt will change to the following:

![Image of command prompt](https://github.com/thimovandermeer/Minishell/blob/master/Schermafbeelding%202021-07-09%20om%2011.38.27.png)

In here you can type any of the bash commands and the executable will handle them. 


