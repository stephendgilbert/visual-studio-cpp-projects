#include <string>
#include <iostream>
using namespace std;
string STUDENT = "sgilbert";     // Add your name Blackboard/occ-email ID

#include "h24.h"

// Add your code here
void reverse(char * s)
{
	char * beg = s;
	while (*s) s++;
	s--;
	while (beg < s)
		swap(*s--, *beg++);
}
