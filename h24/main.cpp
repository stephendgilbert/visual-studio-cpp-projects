/**
 *  @author Put your name here
 *  @date Put the date here
 *  @file main.cpp
 */

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

#include "cs150check.h"
#include "h24.h"

/**
 * Run your program's tests
 */
void runTests()
{
	///////////// Begin a set of tests
	beginTests(); // test heading

    /////// Tests for //////////////////////
	beginFunctionTest("Test the reverse procedure");

	const int SZ = 1024;
    char s[SZ] = "abcdefg";

    reverse(s);
    assertEqualsMsg("Reverse abcdefg.", "gfedcba", s);

    xnyonch(s, "");
    reverse(s);
    assertEqualsMsg("Reverse empty String.", '\0', s[0]);

    xnyonch(s, "x");
    reverse(s);
    assertEqualsMsg("Reverse \"x\".", "x", s);


    xnyonch(s, "xy");
    reverse(s);
    assertEqualsMsg("Reverse \"xy\" OK.", "yx", s);

    xnyonch(s, "xyz");
    reverse(s);
    assertEqualsMsg("Reverse \"xyz\" OK.", "zyx", s);

    xnyonch(s, "xyz");
    reverse(s);
    reverse(s);
    assertEqualsMsg("Reverse \"xyz\" twice OK", "xyz", s);

    xnyonch(s, ".sdrow sselgninaem htiw dellif gnirts gnol yrev emos");
    reverse(s);
    assertEqualsMsg("Reverse a long string.",
            "some very long string filled with meaningless words.", s);

    endFunctionTest(); // end

   ///////// End all test runs /////////////////////////
    endTests();
}


