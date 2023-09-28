// Display the prompt
prompt = "minishell$ "
display(prompt)

// Wait for user input
input = readline()

// Parse the input
tokens = parse(input)

// Identify the command and its arguments
command = tokens[0]
arguments = tokens[1:]

// Execute the command
if command exists in system:
    execute(command, arguments)
else:
    display("Command not found: " + command)

typedef struct s_data
{
    int exit_code; // Add this member to store the exit code
} t_data;

/* for debuggin 
   lldb your_program

run: Start your program with any specified arguments.
breakpoint set --file your_source_file.c --line 42: Set a breakpoint at line 42 of your source code file.
continue: Continue execution until the next breakpoint or program exit.
next: Execute the next line of code (step over).
step: Execute the next line of code, entering functions (step into).
print variable_name: Print the value of a variable.
bt (or backtrace): Display a backtrace of the call stack.
*/