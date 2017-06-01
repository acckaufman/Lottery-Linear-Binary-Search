//This program holds an array of the same ten 5-digit lottery numbers that a user always plays,
//and allows the user to input that week's winning number to determine if they have won.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//Constant integers
const int NUM_TICKETS = 10;
const int MIN_VALUE = 00000;
const int MAX_VALUE = 99999;

//Function prototypes
int getWinningNum();
void sortArray(int[], int);
int linearSearch(const int[], int, int);
int binarySearch(const int[], int, int);

int main()
{
	//Initialize the array with the user's ten numbers
	int tickets[NUM_TICKETS] = { 13579, 62483, 26791, 77777, 26792, 79422, 33445, 85647, 55555, 93121 };

	//Initialize other variables
	int winningNumber;	//Winning number input by the user
	int results;		//Hold search results
	char again;			//Ask the user to repeat the program

	//For testing purposes only: display the contents of the original array
	//	for(int index = 0; index < NUM_TICKETS; index++)
	//		cout << "Element 1: " << tickets[index] << endl;
	//	cout << endl;

	//Sort the array in ascending order
	sortArray(tickets, NUM_TICKETS);

	//For testing purposes only: display the contents of the sorted array
	//	for(int index = 0; index < NUM_TICKETS; index++)
	//		cout << "Element 1: " << tickets[index] << endl;
	//	cout << endl;

	do
	{
		cout << endl << "This program currently holds your list of ten lottery numbers." << endl;
		cout << "Enter the winning number for this week that you would like to search for: ";

		winningNumber = getWinningNum();
		cin.ignore();

		//Carry out the linear search
		results = linearSearch(tickets, NUM_TICKETS, winningNumber);
		if (results == -1)
			cout << endl << "According to the linear search, you did not win this week." << endl << endl;
		else
		{
			cout << endl << "The winning number of " << winningNumber << " was found by the linear search." << endl;
			cout << "Congratulations!  You won this week." << endl << endl;
		}
		
		//Carry out the binary search
		results = binarySearch(tickets, NUM_TICKETS, winningNumber);
		if (results == -1)
			cout << "According to the binary search, you did not win this week." << endl << endl;
		else
		{
			cout << endl << "The winning number of " << winningNumber << " was found by the binary search." << endl;
			cout << "Congratulations!  You won this week." << endl << endl;
		}

		cout << "Would you like to run the program again? (y/n): ";
		again = cin.get();
		cin.ignore();

	} while (again == 'y' || again == 'Y');

}

int getWinningNum()
{
	int value;

	//Get the winning number from the user
	cin >> value;

	//Validate the input
	while(value < 00000 || value > 99999)
	{
		cout << "You must input a value between 00,000 and 99,999." << endl;
		cout << "Enter the winning number for this week that you would like to search for: ";
		cin >> value;
	}
	return value;
}

void sortArray(int array[], int elements)
{
	//This function makes use of a bubble sort method, since the array being used in this program is small.

	bool swap;		//Flag variable to tell the loop if a swap occurred in each iteration
	int temp;		//Temporary storage for one of the values to be swapped

	do
	{
		swap = false;
		for (int count = 0; count < (elements - 1); count++)
		{
			if (array[count] > array[count + 1])
			{
				temp = array[count];				//Temporarily store the value in the current element
				array[count] = array[count + 1];	//Swap the smaller value to array[count]
				array[count + 1] = temp;				//Swap the larger value stored in temp into the next array element
				swap = true;						//A swap occurred, so flag the loop to repeat and check the array again
			}
		}
	} while (swap);	//Repeat the entire loop to check the array every time a swap occurs.
					//If a swap did not occur, then the elements are already in order.
}

//Pass the array, the number of array elements, and the winning number input by the user
int linearSearch(const int array[], int elements, int value)
{
	int index = 0;		//Subscript for array element being searched
	int position = -1;	//Holds position of value if found, otherwise used to return negative value (not a possible subscript)
	bool found = false;	//Flag

	while (index < elements && !found)	//Repeat as long as there are elements to search and value is not found
	{
		if (array[index] == value)
		{
			found = true;
			position = index;
		}
		index++;		//Increment the index to search the next element
	}

	return position;	//Return the position if value was found, otherwise -1
}

//Pass the array, the number of array elements, and the winning number input by the user
int binarySearch(const int array[], int elements, int value)
{
	//Note: this function assumes that the array being used is sorted in ascending order.

	int first = 0;				//First array element to be searched
	int last = elements - 1;	//Last array element
	int middle;					//Halfway between first and last elements being searched
	int position = -1;			//Holds position of value in array, if found, otherwise used to return negative value (not a possible subscript)
	bool found = false;			//Flag

	while (first <= last && !found)		//Repeat as long as there are still elements to search and the value has not yet been found
	{
		middle = (first + last) / 2;	//Determine the middle element of the array
		if (array[middle] == value)
		{
			found = true;		//No need to proceed further, set flag to true
			position = middle;	//To return the position where the value was found
		}
		else if (array[middle] > value)	//If the middle element is greather than the value being searched for,
			last = middle - 1;			//we set the new last element to the one before the middle element, and search the lower half
		else
			first = middle + 1;			//Otherwise, set the new first element to the one after the middle, and search the upper half
	}

	return position;		//Return either the position of the value found, or -1 (default value) if it wasn't found
}