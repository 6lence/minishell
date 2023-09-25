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