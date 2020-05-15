#include <iostream>
using std::cin;
#include "../DataStructures/Sorts.h"
#include "../DataStructures/Sorts.cpp"

int main(int argc, char ** argv)
{
	int result(SortingProgram(argc, argv));
	
	int test0[5] {3, 5, 6, 2, 7}; 
	RunBubble(test0, 5);

	int test1[5]{ 5, 2, 5, 3, 6 };
	RunFlaggedBubble(test1, 5);

	int test2[5]{ 7, 4, 3, 2, 0 };
	RunSelection(test2, 5);

	int test3[6]{ 3, 2, 1, 9, 8, 7 };
	RunInsertion(test3, 5);

	int test4[8]{ 9, 8, 7, 6, 5, 4, 3, 2};
	RunShell(test4, 8);

	int test5[4]{ 4, 3, 2, 1 };
	RunHeap(test5, 4);

	int test6[5]{ 5, 4, 3, 2, 1 };
	RunMerge(test6, 5);

	int test7[4]{ 7, 6, 4, 3 };
	RunQuick(test7, 4); 

	return 0;
}