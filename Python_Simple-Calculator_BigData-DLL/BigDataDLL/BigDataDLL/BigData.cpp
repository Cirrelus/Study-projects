// BigData.cpp : Defines the exported functions for the DLL.
#include "pch.h"
#include "BigData.h"
#include <algorithm>

// Erase zeros at the start of number
std::string EraseZeros(std::string line)
{
	bool all_zero_flag = true;
	bool negative_flag = false;
	if (line.front() == '-') {
		negative_flag = true;
		line.erase(0, 1);
	}

	// check if the number entierly consists of zeros
	for (auto character : line) 
		if (!all_zero_flag) break;
		else if (character != '0') all_zero_flag = false;
	
	//erase zeros
	if (all_zero_flag) line.erase(0, line.size() - 1);
	else if (line.front() == '0'  && line.size() != 1)
		if (line[line.find_first_not_of('0')] != ',') line.erase(0, line.find_first_not_of('0'));
		else line.erase(0, line.find_first_not_of('0') - 1);

	if (negative_flag) line.insert(line.begin(), '-');

	return line;
}

// Calculate a sum of two numbers
char* Plus(char* arg1, char* arg2)
{
	std::string left_side(arg1);
	std::string right_side(arg2);
	auto point1 = std::find(left_side.rbegin(), left_side.rend(), ','); // position of point from back for first argument
	auto point2 = std::find(right_side.rbegin(), right_side.rend(), ','); // position of point from back for second argument
	std::string Sum; // Sum
	// depends on positivity of arguments
	// 0 if both are positive, 1 if first negative, 2 if second negative, 3 if both negative
	int negative_flag = 0; 

	if (left_side[0] == '-' && right_side[0] != '-') {
		negative_flag = 2;
		left_side.erase(0, 1);
	}
	else if (left_side[0] != '-' && right_side[0] == '-') {
		negative_flag = 1;
		right_side.erase(0, 1);
	}
	else if (left_side[0] == '-' && right_side[0] == '-') {
		negative_flag = 3;
		left_side.erase(0, 1);
		right_side.erase(0, 1);
	}

	// match the number of digits after point
	if (point1 != left_side.rend() && point2 != right_side.rend())
		if (std::distance(left_side.rbegin(), point1) > std::distance(right_side.rbegin(), point2))
			for (int i = 0; i<std::distance(left_side.rbegin(), point1) - std::distance(right_side.rbegin(), point2); i++)
				right_side.insert(right_side.end(), '0');
		else for (int i = 0; i < std::distance(right_side.rbegin(), point2) - std::distance(left_side.rbegin(), point1); i++)
				left_side.insert(left_side.end(), '0');

	int point = (std::find(left_side.begin(), left_side.end(), ',') != left_side.end())
		? std::distance(left_side.rbegin(), std::find(left_side.rbegin(), left_side.rend(), ',')) : 0;

	if (point != 0) {
		left_side.erase(std::remove(left_side.begin(), left_side.end(), ','), left_side.end());
		right_side.erase(std::remove(right_side.begin(), right_side.end(), ','), right_side.end());
	}

	// calculate sum
	if (negative_flag == 1) Sum = right_side - left_side;
	else if (negative_flag == 2) Sum = left_side - right_side;
	else Sum = left_side + right_side;

	if (point != 0) Sum.insert(Sum.begin() + (Sum.size() - point), ',');
	
	Sum = EraseZeros(Sum);
		
	if (negative_flag == 3) Sum.insert(Sum.begin(), '-');

	char* Answer = new char[Sum.length() + 1];
	strcpy(Answer, Sum.c_str());
	return Answer;
}

std::string Plus(std::string left_side, std::string right_side)
{
	auto point1 = std::find(left_side.rbegin(), left_side.rend(), ','); // position of point from back for first argument
	auto point2 = std::find(right_side.rbegin(), right_side.rend(), ','); // position of point from back for second argument
	std::string Sum; // Sum
	// depends on positivity of arguments
	// 0 if both are positive, 1 if first negative, 2 if second negative, 3 if both negative
	int negative_flag = 0;

	if (left_side[0] == '-' && right_side[0] != '-') {
		negative_flag = 2;
		left_side.erase(0, 1);
	}
	else if (left_side[0] != '-' && right_side[0] == '-') {
		negative_flag = 1;
		right_side.erase(0, 1);
	}
	else if (left_side[0] == '-' && right_side[0] == '-') {
		negative_flag = 3;
		left_side.erase(0, 1);
		right_side.erase(0, 1);
	}

	// match the number of digits after point
	if (point1 != left_side.rend() && point2 != right_side.rend())
		if (std::distance(left_side.rbegin(), point1) > std::distance(right_side.rbegin(), point2))
			for (int i = 0; i < std::distance(left_side.rbegin(), point1) - std::distance(right_side.rbegin(), point2); i++)
				right_side.insert(right_side.end(), '0');
		else for (int i = 0; i < std::distance(right_side.rbegin(), point2) - std::distance(left_side.rbegin(), point1); i++)
			left_side.insert(left_side.end(), '0');

	int point = (std::find(left_side.begin(), left_side.end(), ',') != left_side.end())
		? std::distance(left_side.rbegin(), std::find(left_side.rbegin(), left_side.rend(), ',')) : 0;

	if (point != 0) {
		left_side.erase(std::remove(left_side.begin(), left_side.end(), ','), left_side.end());
		right_side.erase(std::remove(right_side.begin(), right_side.end(), ','), right_side.end());
	}

	// calculate sum
	if (negative_flag == 1) Sum = right_side - left_side;
	else if (negative_flag == 2) Sum = left_side - right_side;
	else Sum = left_side + right_side;

	if (point != 0) Sum.insert(Sum.begin() + (Sum.size() - point), ',');
	
	Sum = EraseZeros(Sum);

	if (negative_flag == 3) Sum.insert(Sum.begin(), '-');

	return Sum;
}

std::string operator+(std::string arg1, std::string arg2)
{
	std::string answer; // answer
	int digit; // stores current sum of digits
	bool carriege_flag = false; // whether or not current sum is more than 9

	// match the number of digits
	while (arg1.length() < arg2.length())
		arg1.insert(arg1.begin(), '0');

	while (arg1.length() > arg2.length())
		arg2.insert(arg2.begin(), '0');

	//sum two arguments by digits
	for (auto it1 = arg1.rbegin(), it2 = arg2.rbegin(); it1 != arg1.rend() && it2 != arg2.rend(); it1++, it2++)
	{
		//calculate current digit
		digit = *it1 + *it2 - '0' * 2;

		//add to answer
		answer += (carriege_flag) ? (digit + 1) % 10 + '0' : digit % 10 + '0';

		//form carriege flag
		if (digit + carriege_flag > 9) carriege_flag = true;
		else carriege_flag = false;
	}

	if (carriege_flag) answer += "1";
	std::reverse(answer.begin(), answer.end());
	return answer;
}

// Calculate a subtruction of two numbers
char* Minus(char* arg1, char* arg2)
{
	std::string left_side(arg1);
	std::string right_side(arg2);
	auto point1 = std::find(left_side.rbegin(), left_side.rend(), ','); // position of point from back for first argument
	auto point2 = std::find(right_side.rbegin(), right_side.rend(), ','); // position of point from back for second argument
	std::string Subtruct; // answer
	int negative_flag = 0; // whether or not whole subtraction is negative

	if (left_side[0] == '-' && right_side[0] != '-') {
		left_side.erase(0, 1);
	}
	else if (left_side[0] != '-' && right_side[0] == '-') {
		negative_flag = 3;
		right_side.erase(0, 1);
	}
	else if (left_side[0] == '-' && right_side[0] == '-') {
		negative_flag = 1;
		left_side.erase(0, 1);
		right_side.erase(0, 1);
	}
	else if (left_side[0] != '-' && right_side[0] != '-') negative_flag = 2;

	// match the number of digits after point
	if (point1 != left_side.rend() && point2 != right_side.rend())
		if (std::distance(left_side.rbegin(), point1) > std::distance(right_side.rbegin(), point2))
			for (int i = 0; i < std::distance(left_side.rbegin(), point1) - std::distance(right_side.rbegin(), point2); i++)
				right_side.insert(right_side.end(), '0');
		else for (int i = 0; i < std::distance(right_side.rbegin(), point2) - std::distance(left_side.rbegin(), point1); i++)
			left_side.insert(left_side.end(), '0');

	if (negative_flag == 1) Subtruct = right_side - left_side;
	else if (negative_flag == 2) Subtruct = left_side - right_side;
	else Subtruct = left_side + right_side;

	Subtruct = EraseZeros(Subtruct);

	if (negative_flag == 3) Subtruct.insert(Subtruct.begin(), '-');

	char* Answer = new char[Subtruct.length() + 1];
	strcpy(Answer, Subtruct.c_str());
	return Answer;
}

std::string Minus(std::string left_side, std::string right_side)
{
	auto point1 = std::find(left_side.rbegin(), left_side.rend(), ','); // position of point from back for first argument
	auto point2 = std::find(right_side.rbegin(), right_side.rend(), ','); // position of point from back for second argument
	std::string Subtruct; // answer
	int negative_flag = 0; // whether or not whole subtraction is negative

	if (left_side[0] == '-' && right_side[0] != '-') {
		left_side.erase(0, 1);
	}
	else if (left_side[0] != '-' && right_side[0] == '-') {
		negative_flag = 3;
		right_side.erase(0, 1);
	}
	else if (left_side[0] == '-' && right_side[0] == '-') {
		negative_flag = 1;
		left_side.erase(0, 1);
		right_side.erase(0, 1);
	}
	else if (left_side[0] != '-' && right_side[0] != '-') negative_flag = 2;

	// match the number of digits after point
	if (point1 != left_side.rend() && point2 != right_side.rend())
		if (std::distance(left_side.rbegin(), point1) > std::distance(right_side.rbegin(), point2))
			for (int i = 0; i < std::distance(left_side.rbegin(), point1) - std::distance(right_side.rbegin(), point2); i++)
				right_side.insert(right_side.end(), '0');
		else for (int i = 0; i < std::distance(right_side.rbegin(), point2) - std::distance(left_side.rbegin(), point1); i++)
			left_side.insert(left_side.end(), '0');

	if (negative_flag == 1) Subtruct = right_side - left_side;
	else if (negative_flag == 2) Subtruct = left_side - right_side;
	else Subtruct = left_side + right_side;

	Subtruct = EraseZeros(Subtruct);

	if (negative_flag == 3) Subtruct.insert(Subtruct.begin(), '-');

	return Subtruct;
}

std::string operator-(std::string arg1, std::string arg2)
{
	std::string answer; // answer
	int subtract; // stores current subtraction of digits
	std::reverse_iterator<std::string::const_iterator> it1; //iterator for lengthier argument
	std::reverse_iterator<std::string::const_iterator> it2; //iterator for other argument
	bool carriege_flag = false; // whether or not current subtraction is negative
	int negative_flag = 0; // whether or not whole subtraction is negative
	bool assigned_flag = false; // whether or not the iterators were assigned

	// match the number of digits
	while (arg1.length() < arg2.length())
		arg1.insert(arg1.begin(), '0');

	while (arg1.length() > arg2.length())
		arg2.insert(arg2.begin(), '0');

	// assign iterators and set negative flag 
	if (arg1 > arg2) {
		it1 = arg1.rbegin();
		it2 = arg2.rbegin();
		negative_flag = false;
		assigned_flag = true;
	}
	else if (arg1 < arg2) {
		it1 = arg2.rbegin();
		it2 = arg1.rbegin();
		negative_flag = true;
		assigned_flag = true;
	}
	if (!assigned_flag) return "0";

	// subtraction two arguments by digits
	while ((!negative_flag && it1 != arg1.rend() && it2 != arg2.rend()) ||
		(negative_flag && it1 != arg2.rend() && it2 != arg1.rend()))
	{
		if (*it1 == ',') answer += ',';
		else
		{
			//calculate subtract
			subtract = *it1 - *it2;

			//account previous carriege flag
			if (carriege_flag) subtract--;

			//form carriege flag
			if (subtract < 0) carriege_flag = true;
			else carriege_flag = false;

			//calculate current digit
			answer += (subtract < 0) ? (10 + subtract) + '0' : subtract + '0';

			//advance iterators
			it1++;
			it2++;
		}
	}

	if (negative_flag) answer += "-";
	std::reverse(answer.begin(), answer.end());
	return answer;
}

char* Multiply(char* arg1, char* arg2)
{
	std::string left_side(arg1);
	std::string right_side(arg2);
	bool negative_flag = false; // whether or not the answer is negative
	// set negative flag
	if (left_side[0] == '-' && right_side[0] == '-') {
		negative_flag = false;
		left_side.erase(0, 1);
		right_side.erase(0, 1);
	}
	else if (left_side[0] == '-' || right_side[0] == '-') {
		negative_flag = true;
		if (left_side[0] == '-') left_side.erase(0, 1);
		else right_side.erase(0, 1);
	}

	// match the number of digits
	while (left_side.length() < right_side.length())
		left_side.insert(left_side.begin(), '0');

	while (left_side.length() > right_side.length())
		right_side.insert(right_side.begin(), '0');

	if (left_side.length() == 1 && right_side.length() == 1) {
		std::string answer = std::to_string((left_side[0] - '0')*(right_side[0] - '0'));
		char* answer_cstr = new char[answer.length() + 1];
		strcpy(answer_cstr, answer.c_str());
		return answer_cstr;
	}

	auto point1 = std::find(left_side.rbegin(), left_side.rend(), ','); // position of point from back for first argument
	auto point2 = std::find(right_side.rbegin(), right_side.rend(), ','); // position of point from back for second argument

	int point = 0;
	point += (point1 != left_side.rend()) ? std::distance(left_side.rbegin(), point1) : 0;
	point += (point2 != right_side.rend()) ? std::distance(right_side.rbegin(), point2) : 0;

	if (point != 0) {
		left_side.erase(std::remove(left_side.begin(), left_side.end(), ','), left_side.end());
		right_side.erase(std::remove(right_side.begin(), right_side.end(), ','), right_side.end());
	}

	std::string answer; // answer
	std::string left1 = left_side.substr(0, left_side.size() / 2); //left half of first argument
	std::string right1 = left_side.substr(left_side.size() / 2, left_side.size()); // right half of first argument
	std::string left2 = right_side.substr(0, right_side.size() / 2); //left half of second argument
	std::string right2 = right_side.substr(right_side.size() / 2, right_side.size()); // right half of second argument

	// Karatsuba algorithm
	std::string left = Multiply(left1, left2);
	std::string right = Multiply(right1, right2);
	std::string center = Minus(Multiply(Plus(left1, right1), Plus(left2, right2)), Plus(right, left));

	// resize center and left for addition
	for (int i = 0; i < left_side.size() - left_side.size() / 2; i++)
		center.append("0");
	for (int i = 0; i < (left_side.size() - left_side.size() / 2) * 2; i++)
		left.append("0");

	// calculate answer
	answer = Plus(left, Plus(center, right));

	if (point != 0) answer.insert(answer.begin() + (answer.size() - point), ',');

	if (negative_flag) answer.insert(answer.begin(), '-');

	char* answer_cstr = new char[answer.length() + 1];
	strcpy(answer_cstr, answer.c_str());
	return answer_cstr;
}

// Calculate a multiplication of two numbers
std::string Multiply(std::string left_side, std::string right_side)
{
	bool negative_flag = false; // whether or not the answer is negative
	// set negative flag
	if (left_side[0] == '-' && right_side[0] == '-') {
		negative_flag = false;
		left_side.erase(0, 1);
		right_side.erase(0, 1);
	}
	else if (left_side[0] == '-' || right_side[0] == '-') {
		negative_flag = true;
		if (left_side[0] == '-') left_side.erase(0, 1);
		else right_side.erase(0, 1);
	}

	// match the number of digits
	while (left_side.length() < right_side.length())
		left_side.insert(left_side.begin(), '0');

	while (left_side.length() > right_side.length())
		right_side.insert(right_side.begin(), '0');

	if (left_side.length() == 1 && right_side.length() == 1) return std::to_string((left_side[0] - '0')*(right_side[0] - '0'));

	auto point1 = std::find(left_side.rbegin(), left_side.rend(), ','); // position of point from back for first argument
	auto point2 = std::find(right_side.rbegin(), right_side.rend(), ','); // position of point from back for second argument
	
	int point = 0;
	point += (point1 != left_side.rend()) ? std::distance(left_side.rbegin(), point1) : 0;
	point += (point2 != right_side.rend()) ? std::distance(right_side.rbegin(), point2) : 0;

	if (point != 0) {
		left_side.erase(std::remove(left_side.begin(), left_side.end(), ','), left_side.end());
		right_side.erase(std::remove(right_side.begin(), right_side.end(), ','), right_side.end());
	}

	std::string answer; // answer
	std::string left1 = left_side.substr(0, left_side.size() / 2); //left half of first argument
	std::string right1 = left_side.substr(left_side.size() / 2, left_side.size()); // right half of first argument
	std::string left2 = right_side.substr(0, right_side.size() / 2); //left half of second argument
	std::string right2 = right_side.substr(right_side.size() / 2, right_side.size()); // right half of second argument
	
	// Karatsuba algorithm
	std::string left = Multiply(left1, left2);
	std::string right = Multiply(right1, right2);
	std::string center = Minus(Multiply(Plus(left1, right1), Plus(left2, right2)), Plus(right, left));

	// resize center and left for addition
	for (int i = 0; i < left_side.size() - left_side.size() / 2; i++)
		center.append("0");
	for (int i = 0; i < (left_side.size() - left_side.size() / 2) * 2; i++)
		left.append("0");

	// calculate answer
	answer = Plus(left, Plus(center, right));

	if (point != 0) answer.insert(answer.begin() + (answer.size() - point), ',');

	if (negative_flag) answer.insert(answer.begin(), '-');
	return answer;
}

char* Divide(char* arg1, char* arg2)
{
	std::string left_side(arg1);
	std::string right_side(arg2);
	// check if second argument is zero
	right_side = EraseZeros(right_side);
	if (right_side == "0") throw std::overflow_error("Divide by zero exception");

	bool negative_flag = false; // whether or not the answer is negative
	// set negative flag
	if (left_side[0] == '-' && right_side[0] == '-') {
		negative_flag = false;
		left_side.erase(0, 1);
		right_side.erase(0, 1);
	}
	else if (left_side[0] == '-' || right_side[0] == '-') {
		negative_flag = true;
		if (left_side[0] == '-') left_side.erase(0, 1);
		else right_side.erase(0, 1);
	}

	auto point1 = std::find(left_side.begin(), left_side.end(), ','); // position of point from back for first argument
	auto point2 = std::find(right_side.rbegin(), right_side.rend(), ','); // position of point from back for second argument
	int point = 0; // position of point from start for answer

	point += (point1 != left_side.end()) ? std::distance(left_side.begin(), point1) : 0;
	point += (point2 != right_side.rend()) ? std::distance(right_side.rbegin(), point2) : 0;

	std::string dividend; // dividend
	std::string digit; // digit of answer for current iteration
	std::string remainder = "0"; // remainder
	std::string temp; // temporary variable for iteration
	std::string answer = ""; // answer
	int remainder_after_point_count = 0; // counter for the remainder

	// calculate answer
	for (auto it : left_side) {
		// prepare for current step
		digit = "0";
		dividend = Plus(Multiply(remainder, "10"), std::string(1, it));
		temp = Minus(dividend, right_side);

		// calculate current digit
		while (temp.front() != '-') {
			dividend = temp;
			digit = Plus(digit, "1");
			temp = Minus(temp, right_side);
		}

		// update answer and remainder
		answer += digit;
		remainder = dividend;
	}

	// add point and remove zeros
	if (point != 0) answer.insert(answer.begin() + point, ',');
	answer = EraseZeros(answer);

	// calculate remainder 
	remainder = EraseZeros(remainder);
	if (remainder != "0") {
		// if there is no point add one
		if (point == 0) {
			answer += ',';
			point++;
		}
		// calculate n digits where n is the size of second argument 
		while (remainder_after_point_count < right_side.size()) {
			// prepare for current step
			digit = "0";
			remainder += '0';
			temp = Minus(remainder, right_side);

			// calculate current digit
			while (temp.front() != '-') {
				remainder = temp;
				digit = Plus(digit, "1");
				temp = Minus(temp, right_side);
			}

			// update answer and counter
			answer += digit;
			remainder_after_point_count++;
		}
	}

	// delete zeroes from the end (delete point if there is no non zero digits after it)
	if (point != 0) {
		std::reverse(answer.begin(), answer.end());
		answer = EraseZeros(answer);
		std::reverse(answer.begin(), answer.end());
		if (answer.back() == ',') answer.pop_back();
	}

	char* answer_cstr = new char[answer.length() + 1];
	strcpy(answer_cstr, answer.c_str());
	return answer_cstr;
}

// Calculate a division of two numbers
std::string Divide(std::string left_side, std::string right_side)
{
	// check if second argument is zero
	right_side = EraseZeros(right_side);
	if (right_side == "0") throw std::overflow_error("Divide by zero exception");

	bool negative_flag = false; // whether or not the answer is negative
	// set negative flag
	if (left_side[0] == '-' && right_side[0] == '-') {
		negative_flag = false;
		left_side.erase(0, 1);
		right_side.erase(0, 1);
	}
	else if (left_side[0] == '-' || right_side[0] == '-') {
		negative_flag = true;
		if (left_side[0] == '-') left_side.erase(0, 1);
		else right_side.erase(0, 1);
	}

	auto point1 = std::find(left_side.begin(), left_side.end(), ','); // position of point from back for first argument
	auto point2 = std::find(right_side.rbegin(), right_side.rend(), ','); // position of point from back for second argument
	int point = 0; // position of point from start for answer

	point += (point1 != left_side.end()) ? std::distance(left_side.begin(), point1) : 0;
	point += (point2 != right_side.rend()) ? std::distance(right_side.rbegin(), point2) : 0;

	std::string dividend; // dividend
	std::string digit; // digit of answer for current iteration
	std::string remainder = "0"; // remainder
	std::string temp; // temporary variable for iteration
	std::string answer = ""; // answer
	int remainder_after_point_count = 0; // counter for the remainder

	// calculate answer
	for (auto it : left_side) {
		// prepare for current step
		digit = "0";
		dividend = Plus(Multiply(remainder, "10"), std::string(1, it));
		temp = Minus(dividend, right_side);

		// calculate current digit
		while (temp.front() != '-') {
			dividend = temp;
			digit = Plus(digit, "1");
			temp = Minus(temp, right_side);
		}
		
		// update answer and remainder
		answer += digit;
		remainder = dividend;
	}

	// add point and remove zeros
	if (point != 0) answer.insert(answer.begin() + point, ',');
	answer = EraseZeros(answer);

	// calculate remainder 
	remainder = EraseZeros(remainder);
	if (remainder != "0") {
		// if there is no point add one
		if (point == 0) {
			answer += ',';
			point++;
		}
		// calculate n digits where n is the size of second argument 
		while (remainder_after_point_count < right_side.size()) {
			// prepare for current step
			digit = "0";
			remainder += '0';
			temp = Minus(remainder, right_side);

			// calculate current digit
			while (temp.front() != '-') {
				remainder = temp;
				digit = Plus(digit, "1");
				temp = Minus(temp, right_side);
			}

			// update answer and counter
			answer += digit;
			remainder_after_point_count++;
		}
	}

	// delete zeroes from the end (delete point if there is no non zero digits after it)
	if (point != 0) {
		std::reverse(answer.begin(), answer.end());
		answer = EraseZeros(answer);
		std::reverse(answer.begin(), answer.end());
		if (answer.back() == ',') answer.pop_back();
	}
	
	return answer;
}
