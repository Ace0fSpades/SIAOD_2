#include <iostream>
#include <string>
#include <string_view>

using namespace std;



void RLE(string s) {
    int length = s.length();
    int* arr_c = new int [length];
    char* arr_s = new char[length];

    int count = 0;
    int iterator = 0;
    for (int i = 0; i < length; i++) {
        count++;
        if (s[i] != s[i + 1]) {
            arr_c[iterator] = count;
            arr_s[iterator] = s[i];
            count = 0;
            iterator++;
        }
    }
    cout << "Строка: " << s << endl;
    cout << "RLE: ";
    for (int i = 0; i < iterator; i++) {
        cout << arr_c[i] << "|" << arr_s[i] << " ";
    }
    double koef = length / (2.0 * iterator);
    cout << endl << "Коэффициент сжатия: " << koef << endl;

}

void RLE_text_divide(string s, int new_length) {
    int length = s.length();
    int divider = length / new_length;    
    
    int* arr_c = new int[divider];
    string* arr_s = new string[divider];
    for (int i = 0; i < divider; i++) arr_c[i] = -1;
    
    int count = 0;
    int iterator = 0;
    int j = 0;
    for (int i = 0; i < divider; i++) {
        count++;
        if (i != 0) {
            int key = 0;
            for (int l = 0; l < new_length; l++) {
                if (arr_s[i - 1][l] == s[j]) {
                    key++; j++;
                }
                else
                {                    
                    j -= key;
                    int t = 0;
                    while (t < new_length) {
                        arr_s[i] += s[j];
                        t++;
                        j++;
                    }
                    arr_c[i] = count;
                    count = 0;
                    break;
                }
            }
            if (key == new_length) {
                arr_c[i - 1] += count;
                key = 0;
                count = 0;
            };
        }
        else {
            int t = 0;
            while (t < new_length) {
                arr_s[i] += s[j];
                t++;
                j++;
            }
            arr_c[i] = count;
            count = 0;
        }
        
    }
    cout << "Строка: " << s << endl;
    cout << "RLE для разбиения на " << divider << " групп(ы): ";
    for (int i = 0; i < divider; i++) {
        cout << (arr_c[i] == -1 ? 0 : arr_c[i]) << "|" << (arr_s[i].size() == NULL ? "-" : arr_s[i]) << " ";
    }
    double koef = length / (2.0 * divider);
    cout << endl << "Коэффициент сжатия: " << koef << endl;

}

struct Node {
    int offset;
    int length;
    char next;
};

string LZ77(string input)
{
	// Initialized variables
	string result;
	int length, char_info_selc = 0;
	
	
		length = (int)input.length();	// Calculate input string length
		// Check input line length is less than 3
		

		// Declare an arry for final result called 'result_ary'
		int** result_ary = new int* [3];
		for (int i = 0; i < length; ++i)
			result_ary[i] = new int[length];
		// Set result_ary elements value to 0 to prevent previous values
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < length; j++)
				result_ary[i][j] = 0;
		}

		// Declare an arry to store every char info in input string called 'char_info'
		int** char_info = new int* [3];
		for (int i = 0; i < length; ++i)
			char_info[i] = new int[length];
		// Set char_info elements value to 0 to prevent previous values
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < length; j++)
				char_info[i][j] = 0;
		}

		// Set first char info to (0,0,'<first char>')
		result_ary[0][0] = 0;
		result_ary[1][0] = 0;
		result_ary[2][0] = input[0];

		// Set result counter
		int result_count = 1;

		// A loop to perform some operations in every char in input string
		for (int i = 1; i < length; i++)
		{
			// A loop to check input char in position i is equal to any of
			// previous char in input and save this info in char_info array
			for (int j = 0; j < i; j++)
			{
				// Check position of previous view of element i
				if (input[i] == input[j])
				{
					// Set position pointer
					char_info[0][char_info_selc] = i - j;

					// Increase char info array selector by 1
					char_info_selc++;
				}

			}

			// A loop to check length for every char position
			for (int j = 0; j < length; j++)
			{
				// Check current char info array position is not equal to 0
				if (char_info[0][j] != 0)
				{
					// Set start point
					int start = i - char_info[0][j];

					// Set count to calculate length for this char position
					int count = 1;

					// A loop to check length for this char position
					for (int k = 0; k < length; k++)
					{
						// Check next element of start by next element of input
						if (input[start + count] == input[i + count])
							count++;	// Increase count by 1
						else
						{
							char_info[1][j] = count;	// Store count value in length 

							// Check if this input char is the last char
							if (i != (length - 1))
							{
								// Store next char to char info
								// Check this postion is equal to length
								if (char_info[0][j] + count == length)
									char_info[2][j] = 0;	// Set 0 in next char field
								else
									char_info[2][j] = input[char_info[0][j] + count];	// Set the next char
							}
							else
								char_info[2][j] = NULL;		// Set NULL in next char field

							break;	// Stop loop
						}
					}
				}
			}

			// Set large selector
			int large = 0;	// large selector equal 0

			// Loop to check the largest length for every char info
			for (int k = 1; k < length; k++)
			{
				// Check largest
				if (char_info[1][large] == char_info[1][k])
					large = k;	// Set largest
				else if (char_info[1][large] < char_info[1][k])
					large = k;	// Set largest
			}

			// Check largest length is equal to 0
			if (char_info[1][large] == 0)
				char_info[2][large] = input[i];		// Set char info
			else
			{
				i += char_info[1][large];		// increase loop counter by length of the largest char info element
				char_info[2][large] = input[i];		// Set char info
			}

			// Set final result info
			result_ary[0][result_count] = char_info[0][large];
			result_ary[1][result_count] = char_info[1][large];
			result_ary[2][result_count] = char_info[2][large];

			// Increase result counter
			result_count++;

			// Prepare char info array for next char by set it to 0
			for (int z = 0; z < 2; z++)
			{
				for (int j = 0; j < length; j++)
					char_info[z][j] = 0;	// Set every element in char info to 0
			}

			// Prepare char info selector for next char by set it to 0
			char_info_selc = 0;
		}

		// Display final results
		for (int j = 0; j < length; j++)
		{
			if (result_ary[0][j] == 0 && result_ary[1][j] == 0)
			{
				if (result_ary[2][j] != NULL || result_ary[2][j] != 0)
				{
					char z = result_ary[2][j];
					result += to_string(result_ary[0][j]) + "," + to_string(result_ary[1][j]) + "," + z + " ";
				}
			}
			else
			{
				//char z = result_ary[2][j];
				result += to_string(result_ary[0][j]) + "," + to_string(result_ary[1][j]) + ",0 ";
			}
		}

		
		for (int i = 0; i < 3; ++i) {
			{
				delete[] result_ary[i];	delete[] char_info[i];
			}
		}
		delete[] result_ary;
		delete[] char_info;

		return result;
	}

int main()
{
	setlocale(LC_ALL, "rus");
	RLE("aaaaaaaaafffffffff");
	//LZ77("110101011001100001001");
	return 0;
}
	

