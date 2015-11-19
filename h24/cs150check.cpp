/**
 * Basic unit tests for CS 150
 * @author Steve G.
 * @version Fall 2014.
 * This is the implementation file.
 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#include "cs150check.h"
vector<unsigned> hashes = {
    2461783841, 2687617302, 264664557, 2635101917, 1815802190, 2855245159, 255225524, 312902595,
    1078274570, 496303788, 2553645844, 268319887, 1663691076, 866979739, 2560061122, 463910714,
    264892541, 3118753804, 1016425405, 253081963, 1039863946, 260371046, 237122234, 698542838,
    1579964043, 1918964391, 356421290, 2815422184, 3798089648, 1116843119, 3950135287, 1671025955,
    2090699240, 1572878954, 321617546, 478192737, 1608266012, 518472408, 1096647674, 3807262900,
    4161114351, 1434117068, 255928152, 3508792489, 261960984, 1403165171, 3948999334, 66142293,
    1331743683, 105981685, 1834228666, 3937871629, 254039598, 3272938340, 517395891, 806545338,
    3575077838, 3844928954, 3946159020, 2851975323, 619276919, 640704201, 3678616872, 267237090,
    1741575136, 289125547, 195476602, 4071774957, 508776486, 257947158, 2650957992, 887909045,
    276041410, 651920713, 59214197, 1444362249, 3832258132, 987018928, 2090443711, 282956632,
    239279114, 1821733158, 817022874, 1176025824, 662690875, 1671025956, 939433943, 2198886601,
    634428706, 2328988008, 2425679341, 819150045, 1951360153, 1096646648, 2550874533, 2311899352,
    692300903, 1991892412, 4166136625, 131805571, 2259341208, 2700532192, 1366848630, 351081029,
    4089525313, 498995194, 528392527, 2786602237, 186415757, 193491492, 3575542393, 2545737717,
    473173554, 353965539, 1336633000, 113559789, 195397265, 76708977, 2301932304, 79175716,
    2772107734, 2932630594, 432592726, 914794267, 255627415, 59214161, 1138789272, 2122371763,
    1906017303, 4219303338, 3579306618, 2179673679, 1172108124, 4165843027, 3526946358, 2318791544,
    3737173661, 1671025955, 3836078558, 2090699436, 2090484555, 102958883, 2079322827, 168122040,
    2498694510, 265409055, 4072387752, 274902859, 35243509
};

/**
 * Global variables for scoring points.
 */
int possible = 0;
int fail = 0;
static const string UNDERLINE(70,'-');

static int allPossible = 0;
static int allFail = 0;

void xnyonch(char * dest, const char * src)
{
	strcpy(dest, src);
}


void _failReportDifference(const string& msg, double expected, double tolerance, double diff)
{
    ios::fmtflags f(cerr.flags());
    cerr.setf(ios::fixed);
    cerr.precision(4);
    cerr << "   X " << msg << ": expected [" << expected;;
    cerr.setf(ios::scientific);
    cerr << "] within tolerance [" << tolerance;
    cerr << "] but answer off by [" << diff;
    cerr << "]" << endl;
    cerr.flags(f);
    fail++;
}

void _successReport(const string& msg)
{
    cerr << "   + " << msg << endl;
}

void _failReport(const string& msg)
{
    cerr << "   X " << msg << endl;
    fail++;
}

void failMsg(const string& msg)
{
    possible++;
    _failReport(msg);
}

void passMsg(const string& msg) {
    possible++;
    _successReport(msg);
}

//////////// OVERLOADED VERSION OF ASSERT_EQUALS ///////////////////////
void _assertEquals(const string& msg, const string& expected, const string& actual)
{
    possible++;
    if (expected != actual)
    {
        _failReportEquals(msg, expected, actual);
    }
    else
        _successReport(msg);
}

void _assertEquals(const string& msg, int expected, int actual)
{
    possible++;
    if (expected != actual)
    {
        _failReportEquals(msg, expected, actual);
    }
    else
        _successReport(msg);
}

void _assertEquals(const string&, double, double)
{
    cerr << "XXX DO NOT USE assertEquals(double, double)" << endl;
    cerr << "      USE assertDoubleEquals(double expect, double actual, double tolerance) instead." << endl;
}
void _assertEquals(const string& msg, double expected, double actual, double tolerance)
{
    _assertEquals("", msg, expected, actual, tolerance);
}

void _assertEquals(const string& xmsg, const string& msg, double expected, double actual, double tolerance)
{
    possible++;
    double diff = abs(actual - expected);
    if (diff <= tolerance)
    {
        _successReport(xmsg + "; " + msg);
    }
    else
    {
        _failReportDifference(xmsg + ", " + msg, expected, tolerance, diff);
    }
}

void _assertTrue(bool cond, const string& msg)
{
    possible++;
    if (!cond)
    {
        _failReport(msg + " should be true, but is false.");
    }
    else
        _successReport(msg);
}

void _assertFalse(bool cond, const string& msg)
{
    possible++;
    if (cond)
    {
        _failReport(msg + " should be false, but is true.");
    }
    else
        _successReport(msg);
}

void beginTests()
{
    cerr << "TESTING " << ASSIGNMENT << ", " << STUDENT << endl;
    cerr << UNDERLINE << endl;
    allPossible = allFail = 0;
}

void beginFunctionTest(const string& functionName)
{
    possible = fail = 0;
    cerr << "Checking function: " << functionName << " -------------------" << endl;
}

void endFunctionTest()
{
    cerr << UNDERLINE << endl << "  Tests passing "
        << (possible - fail) << "/" << possible
        << " ("
        << fixed << setprecision(0)
        << (static_cast<double>(possible - fail) / possible) * 100.0
        << "%)." << endl << endl;

    allPossible += possible;
    allFail += fail;
}

static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

std::string base64_encode(const char* bytes_to_encode, size_t in_len)
{
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (in_len--)
    {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3)
        {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = static_cast<unsigned char>(((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4));
            char_array_4[2] = static_cast<unsigned char>(((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6));
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4) ; i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = static_cast<unsigned char>(((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4));
        char_array_4[2] = static_cast<unsigned char>(((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6));
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while ((i++ < 3))
            ret += '=';

    }

    return ret;

}

unsigned myhash(const std::string& str)
{
    unsigned hash = 5381;
    for (size_t i = 0; i < str.size(); ++i)
        hash = 33 * hash + (unsigned char)str[i];
    return hash;
}

void endTests()
{
    double percent = (static_cast<double>(allPossible - allFail) / allPossible) * 100.0;
    cerr << UNDERLINE << endl << "ALL TESTS -- PASS "
        << (allPossible - allFail) << "/" << allPossible
        << " ("
        << fixed << setprecision(0)
        << percent
        << "%)." << endl << UNDERLINE << endl;
//    cout << "myhash(STUDENT)->" << myhash(STUDENT) << endl;
    if (find(hashes.begin(), hashes.end(), myhash(STUDENT)) != hashes.end())
    {
        ostringstream out;
        out << fixed << setprecision(2) << static_cast<unsigned>(time(0))
                << ":" << STUDENT << ":" << ASSIGNMENT << ":" << percent << "%";
        string coding = out.str();
        cerr << base64_encode(coding.c_str(), coding.length()) << endl;
//    cerr << "allPossible = " << allPossible << endl;
//    cerr << "allFail = " << allFail << endl;
    }
    else
    {
        cerr << STUDENT << " NOT FOUND IN MY CS150 ROSTER." << endl;
        cerr << "PLEASE CHECK THE VALUE YOU ASSIGNED TO STUDENT." << endl;
    }
}

//// Code from cs150io.hxx
void replaceAll(string& str, const std::string& from, const std::string& to)
{
    if(from.empty()) return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

int runIOTests(const string& testFile)
{
    beginTests();
    ifstream in;
    in.open(testFile.c_str());
    if (! in)
    {
        cerr << "Cannot find \"" << testFile << "\" with your input and output." << endl;
        return -1;
    }

    int result = 0;
    string line;
    while (getline(in, line))
    {
        string::size_type mid = line.find('|');
        if (mid == string::npos)
        {
            cerr << "Test file is not properly formed. No tests run." << endl;
            return -1;
        }
        string input = line.substr(0, mid);
        replaceAll(input, "\\n", "\n");
        string expected = line.substr(mid + 1);
        replaceAll(expected, "\\n", "\n");

        ostringstream sout;
        istringstream sin(input);

        try
        {
            result = run(sin, sout);
        }
        catch (exception& e)
        {
            cerr << " X CRASH for input " << input << ": " << e.what() << endl;
            possible++;
            fail++;
            continue;
        }

        string actual = sout.str();
        string::size_type beg = actual.find('[');
        string::size_type end = actual.find(']');

        if (beg == string::npos || end == string::npos || beg >= end)
        {
            cerr << "Test not properly formed on line: " << line << "; Tests cancelled." << endl;
            return -1;
        }
        else
        {
            actual = actual.substr(beg + 1, end - beg - 1);
        }

        assertEqualsMsg("Input of " + input, expected, actual);
    }
    allPossible = possible;
    allFail = fail;

    endTests();

    return result;
}

int ARGC = 0;
char ** ARGV = 0;

/**
 * Main file for all testing and regular running.
 * @param argc
 * @param argv
 * @return
 */
int main(int, char **)
{
    runTests();
    return 0;
}

int run(istream&, ostream&)
{
    // Add your code here

    return 0;
}


string ASSIGNMENT = "H24";          // Add the assignment name as specified
string TESTFILE = "";  // Modify if you change the name
string TESTING = "";

