/******************************************************************************
** Program Filename: Calculator.cpp 
** Author: Ben Johnson
** Date: February 18, 2018
** Description: The calculator has for differnt functions: a binary to
**	decimal converter, a decimal to binary converter, a grade 
**	calculator with or without weights and a standard four function 
**	calculator. 
** Input: User inputed strings of expressions and numbers.
** Output: Results of calculations based on input from user.
******************************************************************************/

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

void get_option();
bool check_dec(string input);
bool check_grade_option(string input);
int get_pos_int(string input);
float get_float(string input);

/******************************************************************************
** Function: Intial Prompt
** Description: Prints the main explanation of the program to the screen 
** 	telling the user to choose an option.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
void intial_prompt()
{
	cout << "\n";
	cout << "************************************************************" << endl;
	cout << "                  Multipurpose Calculator" << endl;	
	cout << "                       By Ben Johnson" << endl;
	cout << "************************************************************" << endl;
	cout << "\n";
	cout << "                  This is a calculator!" << endl;
	cout << "This calculator can preform 4 differnt types of calculations." << endl;
	cout << "\nWhich calculation would you like to perform?\n" << endl;
	cout << "Enter 1 to go to Standard Calculator" << endl;
	cout << "Enter 2 to go to Binary to Decmial Converter" << endl;
	cout << "Enter 3 to go to Decimal to Binary Converter" << endl;
	cout << "Enter 4 to go to Grade Calculator" << endl;
	cout << "Enter 5 to Exit the Program" << endl;
}

/******************************************************************************
** Function: Print Options
** Description: Lists all of the options of the calculator.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
void print_options()
{
	cout << "\n************************************************************" << endl;
	cout << "\nWhich calculation would you like to perform?\n" << endl;
	cout << "Enter 1 to go to Standard Calculator" << endl;
	cout << "Enter 2 to go to Binary to Decmial Converter" << endl;
	cout << "Enter 3 to go to Decimal to Binary Converter" << endl;
	cout << "Enter 4 to go to Grade Calculator" << endl;
	cout << "Enter 5 to Exit the Program" << endl;
}

/******************************************************************************
** Function: Reprompt
** Description: Prints the options of either doing another calculation
** 	or quiting the program.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
void reprompt()
{
	cout << "\n************************************************************" << endl;
	cout << "\nWould you like to perform another calculation?\n" << endl;
	cout << "Enter 1 to perform another calculation."  << endl;
	cout << "Enter 2 to quit the program." << endl;
	string input = "";
	getline(cin, input);
	while(!check_grade_option(input))
	{
		cout << "You entered an invalid option." << endl;
		cout << "Please enter a valid option." << endl;
		getline(cin, input);
	}
	if(get_pos_int(input) == 1)
	{	
		print_options();
		get_option();	
	}
	else
	{
		cout << "\n************************************************************\n" << endl;
	}
}

/******************************************************************************
** Function: Check Option
** Description: Checks if the input is a valid option
** Parameters: string input: the user input to test.
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
bool check_option(string input)
{
	if(input.length() > 1 || input.length() <= 0)
	{
		return false;
	}
	if(input[0] < '1' || input[0] > '5')
	{
		return false;
	}
	return true;
}

/******************************************************************************
** Function: Parse Option
** Description: converts the inputed string to an integer value.
** Parameters: string input: the user input to convert.
** Pre-Conditions: The input needs to be a valid option.
** Post-Conditions: None
******************************************************************************/
int parse_option(string input)
{
	int result = 0;
	for(int i = 0; i < input.length(); i++)
	{
		result += (input[i] - 48) * pow(10, input.length()-i-1);
	}
	return result;
}

/******************************************************************************
** Function: Are Letters
** Description: checks if the string contains letters or weird characters.
** Parameters: string input: the user input to check.
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
bool are_letters(string input)
{
	for(int i = 0; i < input.length(); i++)
	{
		if((input[i] < 48 || input[i] > 57) 
		 && input[i] != ' ' && input[i] != '+' 
		 && input[i] != '-' && input[i] != '*' 
		 && input[i] != '/' && input[i] != '.') 
			return true;
	}
	return false;
}

/******************************************************************************
** Function: Minimum Expression
** Description: checks if the string contains at least 2 spaces, 2 numbers
**	and 1 operator.
** Parameters: string input: the user input to check.
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
bool minimum_expression(string input)
{
	int spaces = 0, opers = 0, nums = 0;
	for(int i = 0; i < input.length(); i++)
	{
		if(input[i] == ' ')
			spaces++;
		if(input[i] >= 48 && input[i] <= 57)
			nums++;
		if(input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
			opers++;
	}
	if(spaces < 2 || opers < 1 || nums < 2)
		return false;
	return true;
}

/******************************************************************************
** Function: Multiple Decimals
** Description: checks if the string contains multiple decimals in a 
**	single number.
** Parameters: string input: the user input to check.
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
bool multiple_decimal(string input)
{
	int count = 0;
	for(int i = 0; i < input.length(); i++)
	{
		if(input[i] == ' ')
			count = 0;
		if(input[i] == '.')
			count++;
		if(count > 1)
			return true;
	}
	return false;
}

/******************************************************************************
** Function: Check Spaces
** Description: checks if the string has properly formatted spaces.
** Parameters: string input: the user input to check.
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
bool check_spaces(string input)
{
	for(int i = 0; i < input.length(); i++)
	{
		if(input[i] == ' ' && ((input[i+1] >= 48 && input[i+1] <= 57)
	        || input[i+1] == '.') && ((input[i-1] >= 48 && input[i-1] <= 57) 
		|| input[i-1] =='.'))
			return false;
		if(input[i] == ' ' && 
		  (input[i-1] == '+' || input[i-1] == '*' || input[i-1] == '/') && 
		  (input[i+1] == '+' || input[i+1] == '*' || input[i+1] == '/'))
			return false; 
		if(input[i] == ' ' && (input[i+1] == ' ' || input[i-1] == ' '))
			return false;
	}
	return true;
}

/******************************************************************************
** Function: Check Operators
** Description: checks if the string has properly formatted operators.
** Parameters: string input: the user input to check.
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
bool check_operators(string input)
{
	for(int i = 0; i < input.length(); i++)
	{
		if((input[i] == '+' || input[i] == '*' || input[i] == '/') &&
		    (input[i-1] != ' ' || input[i+1] != ' '))
			return false;
		if(i > 0 && input[i] == '-' && 
		            input[i-1] != ' ' && input[i+1] != ' ')
		{
			if(input[i-1] != ' ' || ((input[i+1] < 48 || input[i+1] > 57) 
			&& input[i+1] != '.'))
				return false;
		}
		if(input[i] == ' ' && input[i-1] == '-' && input[i+1] == '-' && 
		  (input[i-2] != ' ' || (input[i+2] != '.' && 
		  (input[i+2] < 48 || input[i+2] > 57))))
			return false;
	}
	return true;
}

/******************************************************************************
** Function: Check First and Last Letters
** Description: checks if the string has a valid first and last character.
** Parameters: string input: the user input to check.
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
bool check_first_last_letters(string input)
{
	if(input.length() < 5 || input[0] == ' ' || input[input.length()-1] == ' ') 
		return false;
	if(input[input.length()-1] == '+' || input[input.length()-1] == '-' ||
	   input[input.length()-1] == '*' || input[input.length()-1] == '/')
		return false;
	if(input[0] == '+' || input[0] == '*' || input[0] == '/')
		return false;
	if(input[0] == '-' && input[1] == ' ')
		return false;
	return true;
}

/******************************************************************************
** Function: Check Expression
** Description: Checks that the string is a valid expression that can
**	be evaluated with only numbers and operators seperated by single
**	spaces. No spaces at the beginning or ::the end.
** Parameters: string input: the user inputed expression to check.
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
bool check_expression(string input)
{
	if(input.length() < 5) 
		return false;
	if(!check_first_last_letters(input))
		return false;
	if(are_letters(input))
		return false;
	if(!minimum_expression(input))
		return false;
	if(!check_spaces(input))
		return false;
	if(!check_operators(input))
		return false;
	if(multiple_decimal(input))
		return false;
	return true; 
}

/******************************************************************************
** Function: Do Operation
** Description: Takes in two float values and an operator and does the
**	proper operation on the two float values.
** Parameters: char op: the operator to preform on the numbers.
**	       float num1: the first number/operand.
**	       float num2: the second number/operand.
** Pre-Conditions: op is a valid operator character.
** Post-Conditions: None
******************************************************************************/
float do_operation(char op, float num1, float num2)
{
	if(op == '+')
		return num1 + num2;
	else if(op == '-')
		return num1 - num2;
	else if(op == '*')
		return num1 * num2;
	else
		return num1 / num2;
}

/******************************************************************************
** Function: Get First Number
** Description: Finds and converts the first number in a user inputed 
**	excpression. 
** Parameters: string input: the string to convert.
** Pre-Conditions: input is a valid expression.
** Post-Conditions: None.
******************************************************************************/
float get_first_num(string input)
{
	int i = 0;
	for(i; i < input.length(); i++)
	{
		if(input[i] == ' ')
		{
			break;
		}
	}
	return get_float(input.substr(0, i));
}

/******************************************************************************
** Function: Get First Space
** Description: Finds the first space in the string
** Parameters: string input:  the strin to check over.
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
int get_first_space(string input)
{	
	int i = 0;
	for(i; i < input.length(); i++)
	{
		if(input[i] == ' ')
		{
			break;
		}
	}
	return i;
}

/******************************************************************************
** Function: Evaluate Evpression
** Description: recursivly converts an expression into a final resluting
**	float value.
** Parameters:  float num1: the first number in the expression
**		string input: the rest of the expression
** Pre-Conditions: input must be a valid expression.
** Post-Conditions: None
******************************************************************************/
float evaluate_expression(float num1, string input)
{
	if(input.length() == 0)
	{
		return num1;
	}
	int k = 3;
	for(k; k < input.length(); k++)
	{
		if(input[k] == ' ')
		{
			break;
		}
	}
	float num2 = get_float(input.substr(3, k - 3));
	num1 = do_operation(input[1], num1, num2);
	return evaluate_expression(num1, input.substr(k, input.length()-k));
}

/******************************************************************************
** Function: Get Evpression
** Description: gets user input until inputed expression is valid.
** Parameters:  None
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
string get_expression()
{
	string input = "";
	getline(cin, input);
	while(!check_expression(input))
	{
		cout << "You entered an invalid expression." << endl;
		cout << "Please enter a valid expression." << endl;
		getline(cin, input);
	}
	return input;
}

/******************************************************************************
** Function: Standard Calcluator 
** Description: prompts and takes valid input of an expression to evaluate.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
void standard_calc()
{
	cout << "\n************************************************************" << endl;
	cout << "\nYou are in the standard calculator option.\n" << endl;
	cout << "Give me an expression to caclulate." << endl;
	cout << "Format: number space operator space number" << endl;
	string input = get_expression();
	float num1 = get_first_num(input);
	int i = get_first_space(input);
	float result  =  evaluate_expression(num1, input.substr(i, input.length()-i));
	if(isinf(result) || isnan(result))
	{
		cout << "\nThere was a divide by zero error." << endl;
		cout << "If you want a result don't divide by zero." << endl;
	}
	else
		cout << "\nResult of expression is: " << result << endl;
	reprompt();
}

/******************************************************************************
** Function: Check Binary 
** Description: checks if the user inputed string is a valid binary value.
** Parameters: string input: the user input to check.
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
bool check_bin(string input)
{
	if(input.length() <= 0 || input.length() > 31)
		return false;
	for(int i = 0; i < input.length(); i++)
	{
		if(input[i] != '0' && input[i] != '1')
		{
			return false;
		}	
	}
	return true;
}

/******************************************************************************
** Function: Get Decimal 
** Description: converts a binary string to a decimal value.
** Parameters: string input:  the user inputed binary string to convert.
** Pre-Conditions: input must be a valid binary string.
** Post-Conditions: None
******************************************************************************/
void get_dec(string input)
{
	int result = 0;
	for(int i = 0; i < input.length(); i++)
	{
		result += (input[i] - 48) * pow(2, input.length() - i - 1);
	}
	cout << "\nThe decimal value of the binary string is: " << result << endl;
	reprompt();
}

/******************************************************************************
** Function: Convert Binary to Decimal
** Description: prompts and takes in binary string to convert to decimal.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
void convert_bin_to_dec()
{
	cout << "\n************************************************************" << endl;
	cout << "\nYou are in the binary to decimal converter.\n" << endl;
	cout << "Enter a binary number to be converted to decimal." << endl;
	string input = "";
	getline(cin, input);
	while(!check_bin(input))
	{
		cout << "You entered an invalid binary value." << endl;
		cout << "Please enter a valid binary number." << endl;
		getline(cin, input);
	}
	get_dec(input);
}

/******************************************************************************
** Function: Check Decimal
** Description: checks if the user input is a positive integer.
** Parameters: string input: the user input to check.
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
bool check_dec(string input)
{
	if(input.length() > 10 || (input.length() == 10 && input[0] != '1'))
		return false;
	for(int i = 0; i < input.length(); i++)
	{
		if(input[i] < 48 || input[i] > 57)
		{
			return false;
		}	
	}
	return true;
}

/******************************************************************************
** Function: Get Binary
** Description: converts a string to a binary value.
** Parameters: int input: the user inputed decimal value.
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
void get_bin(int input)
{
	string bin = "";
	int num = input;
	if(input == 0)
		bin = "0";
	while(input > 0)
	{
		bin = char(input % 2 + 48) + bin;	
		input /= 2;
	}
	cout << "\nThe binary value of " << num  << " is: " << bin << endl;
	reprompt();
}

/******************************************************************************
** Function: Get Positive Integer
** Description: converts a string to a positive integer.
** Parameters: string input: the user inputed string to convert.
** Pre-Conditions: input is a valid positive integer.
** Post-Conditions: None
******************************************************************************/
int get_pos_int(string input)
{
	int result = 0;
	for(int i = 0;  i < input.length(); i++)
	{
		result += (input[i] - 48) * pow(10, input.length() - i -1);
	}
	return result;
}

/******************************************************************************
** Function: Convert Decimal to Binary
** Description: gets input from user to cnvert to binary.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
void convert_dec_to_bin()
{
	cout << "\n************************************************************" << endl;
	cout << "\nYou are in the decimal to binary converter.\n" << endl;
	cout << "Enter a decimal number to be converted to binary." << endl;
	string input = "";
	getline(cin, input);
	while(!check_dec(input))
	{
		cout << "You entered an invalid decimal value." << endl;
		cout << "Please enter a valid decimal number." << endl;
		getline(cin, input);
	}
	get_bin(get_pos_int(input));

}

/******************************************************************************
** Function: Average Value
** Description: calculates average of grades and prints the result.
** Parameters:  float sum: the sum of the grades.
**		int grade_num: the number of inputed grades.
** Pre-Conditions: the number of grades is not zero.
** Post-Conditions: None
******************************************************************************/
void average_value(float sum, int grade_num)
{
	float average = sum / grade_num;
	cout << "\nthe average of the grades is: " << average << endl;
	cout << "\n";
	reprompt();
}

/******************************************************************************
** Function: Weighted Average Value 
** Description: calculates weighted average of grades and prints the
**	result. 
** Parameters:  float sum: the total of the grades
**		int grade_num: number of inputed grades
**		int weight: the weight of the grades in percents.
** Pre-Conditions: the number of grades is not zero.
** Post-Conditions: None
******************************************************************************/
void weighted_average_value(float sum, int grade_num, int weight)
{
	float average = sum / grade_num * (weight / 100.0);
	cout << "\nthe average of the grades is: " << average << endl;
	cout << "\n";
	reprompt();
}

/******************************************************************************
** Function: Get Negative Float
** Description: Converts a string to a negative float
** Parameters: string input: user input to be converted
** Pre-Conditions: input must be a valid float value.
** Post-Conditions: None
******************************************************************************/
float get_neg_float(string input)
{
	float total = 0;
	int decimal = input.length();
	for(int i = 0; i < input.length(); i++)
	{
		if(input[i] == '.')
			decimal = i;
	}
	for(int i = 1; i < input.length(); i++)
	{
		if(i  < decimal)
			total += (input[i] - 48) * pow(10, decimal - i - 1);
		if(i > decimal)
			total += (input[i] - 48) * pow(10,decimal - i);
	}
	return total * -1;
}

/******************************************************************************
** Function: Get Float
** Description: Converts a string to a float
** Parameters: string input: user input to be converted
** Pre-Conditions: input must be a valid float value.
** Post-Conditions: None
******************************************************************************/
float get_float(string input)
{
	if(input[0] == '-')
		return get_neg_float(input);
	float total = 0;
	int decimal = input.length();
	for(int i = 0; i < input.length(); i++)
	{
		if(input[i] == '.')
		{
			decimal = i;
			break;
		}
	}
	for(int i = 0; i < input.length(); i++)
	{
		if(i < decimal)
			total += (int(input[i]) - 48) * pow(10, decimal - i - 1);
		if(i > decimal)
			total += (int(input[i]) - 48) * pow(10,decimal - i);
	}
	return total;
}

/******************************************************************************
** Function: Get Grades
** Description: Prompts and takes in all of the grades to be averaged. 
** Parameters:  int grade_num: number of inputed grades.
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
float get_grades(int grade_num)
{
	int i = 0;
	float sum = 0;
	string input = "";
	do{
		getline(cin, input);
		if(check_dec(input))
		{
			sum += get_float(input);
			i++;
		}
	}while( i < grade_num);
	return sum;
}

/******************************************************************************
** Function: Normal Grade Calculation
** Description: Prompts and takes in all of the grades to be averaged. 
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
void normal_grade_calc()
{
	cout << "\nEnter the number of grades you want to average." << endl;
	string input = "";
	getline(cin, input);
	while(!check_dec(input))
	{
		cout << "invalid input, please give a valid number." << endl;
		getline(cin, input);	
	}
	int grade_num = get_pos_int(input);
	cout << "\nEnter all of the grades you wish to average." << endl;
	float sum = get_grades(grade_num);	
	average_value(sum, grade_num);
}

/******************************************************************************
** Function: Get Weight
** Description: gets the weight the grades should have.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
int get_weight()
{
	string number = "";
	cout << "\nEnter the weight that these grades should have.";
	cout << "\n(In percent form)" << endl;
	getline(cin, number);
	while(!check_dec(number))
	{
		cout << "invalid input, please give a valid number." << endl;
		getline(cin, number);	
	}
	return get_pos_int(number);

}

/******************************************************************************
** Function: Weighted Grade Calculation
** Description: Prompts and takes in all of the grades with a weight to
**	be averaged.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
void weighted_grade_calc()
{
	cout << "\nEnter the number of grades you want to average." << endl;
	string input = "", number = "";
	getline(cin, input);
	while(!check_dec(input))
	{
		cout << "invalid input, please give a valid number." << endl;
		getline(cin, input);	
	}
	int grade_num = get_pos_int(input);
	int weight = get_weight();
	cout << "\nEnter all of the grades you wish to average." << endl;
	float sum = get_grades(grade_num);	
	weighted_average_value(sum, grade_num, weight);
}

/******************************************************************************
** Function: Check Grade Option
** Description: checks that the user input is a valid option.
** Parameters: string input: the user inputed option.
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
bool check_grade_option(string input)
{
	if(input.length() == 0)
	{
		return false;
	}
	for(int i = 0; i < input.length(); i++)
	{
		if(input[i] != '1' && input[i] != '2')
		{
			return false;
		}
	}
	return true;
}

/******************************************************************************
** Function: Grade Calculator 
** Description: Calculates the total grade from a list of inputed grades
**	and determines if the average should be weighted or not.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
void grade_calc()
{
	cout << "\n************************************************************" << endl;
	cout << "\nYou are in the grade calculator option.\n" << endl;
	cout << "Would you like to do a nonweighted or a weighted average?\n" << endl;
	cout << "Enter 1 to preform a standard grade calculation." << endl;
	cout << "Enter 2 to preform a weighted grade calculation." << endl;
	string input = "";
	getline(cin, input);
	while(!check_grade_option(input))
	{
		cout << "You entered an invalid option." << endl;
		cout << "Please enter a valid option." << endl;
		getline(cin, input);
	}
	if(get_pos_int(input) == 1)
		normal_grade_calc();
	else
		weighted_grade_calc();

}

/******************************************************************************
** Function: Choose Calculator
** Description: Runs the proper calculation.
** Parameters: int option: the user inputed option.
** Pre-Conditions: option is a valid option for the type of calculation.
** Post-Conditions: None
******************************************************************************/
void choose_calc(int option)
{
	if(option == 1)
		standard_calc();

	else if(option == 2)
		convert_bin_to_dec();

	else if(option == 3)
		convert_dec_to_bin();

	else if(option == 4)
		grade_calc();

	else
		cout << "\n************************************************************\n" << endl;
		return;
}

/******************************************************************************
** Function: Get Option
** Description: Gets the user input and determines which type of 
**	calculation to perform.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
void get_option()
{
	string input = "";
	getline(cin, input); 
	while(!check_option(input))
	{
		cout << "You entered an invalid option." << endl;
		cout << "Please choose a valid option." << endl;
		getline(cin, input);
	}
	int option = parse_option(input);
	choose_calc(option);
}

/******************************************************************************
** Function: Main
** Description: The main function of the program, it prints the intial 
**	prompt and calls the function to choose the type of 
**	calculator.
** Parameters: None.
** Pre-Conditions: None.
** Post-Conditions: None.
******************************************************************************/
int main()
{
	intial_prompt();
	get_option();
	
	return 0;
}
