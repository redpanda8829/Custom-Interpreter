#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to find variable in the global vars array
int findVariable(char variable, int *variables) {
    if (variable < 'a' || variable > 'z') {
        fprintf(stderr, "Error: Invalid variable '%c'\n", variable);
        exit(EXIT_FAILURE);
    }
    return variables[variable - 'a'];
}

// Function to set/update values of variables in global vars array
void setVariable(char variable, int value, int *variables) {
    variables[variable - 'a'] = value;
}

int main(int argc, char *argv[]) {
    FILE *infp;
    int vars[26];
    char line[256];
    
    infp = stdin;
    if(argc>1){
    	infp = fopen(argv[1],"r");
	if(infp==NULL){
		perror("open");
		exit(1);
	}
    }
    while (fgets(line, sizeof(line), infp) != NULL) {
        
	char operation[10];
        char operand1, operand2;
        int value;
	// Avoiding lines that start with #
	if(line[0]=='#')
		continue;
	
        // Remove trailing newline character
        line[strcspn(line, "\n")] = 0;

        // Parse the operation and operands
        sscanf(line, "%s %c %*s %c", operation, &operand1, &operand2);
	
        switch (operation[0]) {
            case 's':
		if (strcmp(operation,"set")==0){
                value = atoi(line + 8);  // Skip "set x to " part	
                setVariable(operand1, value, vars);
		}
		else if (strcmp(operation, "subtract")==0){
		setVariable(operand2, (findVariable(operand2, vars) - findVariable(operand1, vars)), vars);
		}
                break;
            case 'a':
                setVariable(operand2, findVariable(operand2, vars) + findVariable(operand1, vars), vars);
                break;
            case 'm':
		value = findVariable(operand1, vars) * findVariable(operand2, vars);
                setVariable(operand1, value , vars);
		break;
            case 'd':
                {
                    int divisor = findVariable(operand2, vars);
                    if (divisor == 0) {
                        fprintf(stderr, "Error: Division by zero\n");
                        exit(EXIT_FAILURE);
                    }
                    setVariable(operand1, findVariable(operand1, vars) / divisor, vars);
                }
                break;
            case 'p':
                printf("%d\n", findVariable(operand1, vars));
                break;
            default:
                fprintf(stderr, "Error: Unknown operation '%s'\n", operation);
                exit(EXIT_FAILURE);
        }
    }

    return 0;
}

