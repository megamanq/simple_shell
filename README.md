 Simple Shell

#description
This is a project on creating a shell in C

#steps
- First we started with creating a simple file that passes the betty checks
- Then we created a UNIX command line that displays a prompt and always ends with a new prompt
- The prompt is displayed again each time a command has been executed.
- The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
- The command lines are made only of one word. No arguments will be passed to programs.
- If an executable cannot be found, print an error message and display the prompt again.
- Handle errors
- Handle command lines with arguments
- Handle the PATH
- Create a fork file
- Implement the exit built-in, that exits the shell
- Implement the env built-in, that prints the current environment
- Create a new getline function using static variables
- Use a buffer to read many chars at once and call the least possible the read system call
- handle arguments for the built-in exit
- Implement the setenv and unsetenv builtin commands where setenv Initialize a new environment variable, or modify an existing one
  unsetenv Remove an environment variable
- Implement the builtin command cd
- Handle the commands separator 
- Handle the && and || shell logical operators
- Implement the alias builtin command
- Handle variables replacementwhich includes  the $? variable and $$ variable
- Handle comments (#)

##Usage

Run (gcc) compiler and [./] command

##Contact
[Github profile]
(https://github.com/megamanq)
(https://github.com/Wilsdouglas)
