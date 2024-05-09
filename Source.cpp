#include "MyMouse.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <sstream>
#include <time.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>


using namespace std;

//global variables
MyMouse M;
bool g_openStatus = false;
int g_prevOpenedCardNumber = 0;
bool g_DeadCards[12];

//card character data, 1st is the unopened/blank and 8th is dead card
int g_carddata[8][15][15] =
{
	{

		{42,42,42,42,42,42,42,42,42,42,42,42,42,42,42},
		{42,42,42,42,42,42,42,42,42,42,42,42,42,42,42},
		{42,42,42,42,42,42,42,42,42,42,42,42,42,42,42},
		{42,42,42,42,42,42,42,42,42,42,42,42,42,42,42},
		{42,42,42,42,42,42,42,42,42,42,42,42,42,42,42},
		{42,42,42,42,42,42,42,42,42,42,42,42,42,42,42},
		{42,42,42,42,42,42,42,42,42,42,42,42,42,42,42},
		{42,42,42,42,42,42,42,42,42,42,42,42,42,42,42},
		{42,42,42,42,42,42,42,42,42,42,42,42,42,42,42},
		{42,42,42,42,42,42,42,42,42,42,42,42,42,42,42},
		{42,42,42,42,42,42,42,42,42,42,42,42,42,42,42},
		{42,42,42,42,42,42,42,42,42,42,42,42,42,42,42},
		{42,42,42,42,42,42,42,42,42,42,42,42,42,42,42},
		{42,42,42,42,42,42,42,42,42,42,42,42,42,42,42},
		{42,42,42,42,42,42,42,42,42,42,42,42,42,42,42}
},
{

		{49,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
		{219,219,219,219,219,219,219,219,219,219,219,219,49,219,219},
		{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
		{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
		{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
		{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
		{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
		{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
		{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
		{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
		{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
		{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
		{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
		{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
		{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219}
},
{
	{50,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219, 32,  3, 32, 32, 32, 32, 32, 32, 32, 32, 32,  3, 32,219},
	{219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219},
	{219, 32, 32, 32, 32, 32, 32,  3, 32, 32, 32, 32, 32, 32,219},
	{219, 32, 32, 32, 32,  3, 32, 30, 32,  3, 32, 32, 32, 32,219},
	{219, 32, 32,  3, 32, 30, 32,219, 30, 30, 32,  3, 32, 32,219},
	{219, 32, 32, 30, 32,219,219,219,219,219, 32, 30, 32, 32,219},
	{219, 32, 32,219, 32,219,219,219,219,219, 32,219, 32, 32,219},
	{219, 32, 32,219,219,219,219,219,219,219,219,219, 32, 32,219},
	{219, 32, 32,219,219,219,219, 50,219,219,219,219, 32, 30,219},
	{219, 32, 32, 61, 61, 61, 61, 61, 61, 61, 61, 61, 32, 32,219},
	{219, 32, 32,219,  3,219,219,  3,219,219,  3,219, 32, 32,219},
	{219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219},
	{219, 32,  3, 32, 32, 32, 32, 32, 32, 32, 32, 32,  3, 32,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219}
},
{
	{51,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219, 51,219,219,219,219,219,219,219,219,219,219,  3,219},
	{219,219,219,219,219,219,219,219,  3,219,219,219,219,219,219},
	{219,219,219,219,219,  3,219,219,219,219,219,219,219,  3,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,  3,219,219,219,219,219,219,219,219,219,219,  3,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,3,219,219,219,219,219,219,219,219,219,219,219,3,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,3,219,219,219,219,219,219,219,219,219,219,219,3,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,3,219,219,219,219,219,219,219,219,219,3,219,219,219},
	{219,219,219,219,219,219,219,219,3,219,219,219,219,219,219},
	{219,3,219,219,3,219,219,219,219,219,219,219,219,51,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219}
},
{
	{52,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,52,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219}

},
{
	{53,219,219,219,219,219,219,219,219,219,219,219,53,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219}
},
{
	{54,219,219,219,219,219,219,219,219,219,219,219,54,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219}
},
{

	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
	{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219}
},

};

//card color data, 1st is the unopened/blank and 8th is dead card
int g_colordata[8][15][15] =
{
	{
		{240,240,240,240,240,240,240,240,240,240,240,240,240,240,240},
		{240,246,246,246,246,246,246,246,246,246,246,246,246,246,240},
		{240,246,246,246,246,246,246,246,246,246,246,246,246,246,240},
		{240,246,246,246,246,246,246,246,246,246,246,246,246,246,240},
		{240,246,246,246,246,246,246,246,246,246,246,246,246,246,240},
		{240,246,246,246,246,246,246,246,246,246,246,246,246,246,240},
		{240,246,246,246,246,246,246,246,246,246,246,246,246,246,240},
		{240,246,246,246,246,246,246,246,246,246,246,246,246,246,240},
		{240,246,246,246,246,246,246,246,246,246,246,246,246,246,240},
		{240,246,246,246,246,246,246,246,246,246,246,246,246,246,240},
		{240,246,246,246,246,246,246,246,246,246,246,246,246,246,240},
		{240,246,246,246,246,246,246,246,246,246,246,246,246,246,240},
		{240,246,246,246,246,246,246,246,246,246,246,246,246,246,240},
		{240,246,246,246,246,246,246,246,246,246,246,246,246,246,240},
		{240,240,240,240,240,240,240,240,240,240,240,240,240,240,240},
},
{
	{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
	{6,3,3,3,3,3,3,3,3,3,3,3,7,3,6},
	{6,3,3,4,4,7,7,7,7,4,4,4,4,3,6},
	{6,3,3,4,7,7,6,7,7,6,6,6,4,3,6},
	{6,3,3,7,7,3,3,7,7,3,3,6,4,3,6},
	{6,3,3,4,6,3,3,7,7,3,3,6,4,3,6},
	{6,3,3,4,6,3,3,7,7,3,3,6,4,3,6},
	{6,3,3,4,6,3,4,7,7,3,3,6,4,3,6},
	{6,3,3,4,6,3,4,7,7,3,3,6,4,3,6},
	{6,3,3,4,6,3,4,7,7,3,3,6,4,3,6},
	{6,3,3,4,6,3,4,7,7,3,3,6,4,3,6},
	{6,3,3,4,6,3,4,7,7,6,6,6,4,3,6},
	{6,3,3,7,7,7,7,7,7,7,7,7,4,3,6},
	{6,3,3,4,6,3,3,3,3,3,3,3,3,3,6},
	{6,3,3,4,6,6,6,6,6,6,6,6,6,6,6}
},
{
		{15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
		{15,15,4,15,15,15,15,15,15,15,15,15,4,15,15},
		{15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
		{15,15,15,15,15,15,15,4,15,15,15,15,15,15,15},
		{15,15,15,15,15,4,15,15,15,4,15,15,15,15,15},
		{15,15,15,4,15,15,15,15,0,15,15,4,15,15,15},
		{15,15,15,15,15,15,0,15,0,15,15,15,15,15,15},
		{15,15,15,15,15,15,0,15,0,15,15,15,15,15,15},
		{15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
		{15,15,15,15,15,15,15,4,15,15,15,15,15,0,15},
		{15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
		{15,15,15,15,4,15,15,4,15,15,4,15,15,15,15},
		{15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
		{15,15,4,15,15,15,15,15,15,15,15,15,4,15,15},
		{15,15,15,15,15,15,15,15,15,15,15,15,15,15,15}
},
{
	{15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
	{15,4,15,4,4,4,15,15,15,15,15,15,4,15,15},
	{15,4,4,4,15,15,15,4,15,4,4,4,4,4,15},
	{15,4,15,15,15,15,4,4,4,4,4,4,4,15,15},
	{15,15,15,4,4,4,4,4,4,4,4,4,4,4,15},
	{15,15,15,4,4,15,15,15,15,15,4,4,4,15,15},
	{15,15,4,4,4,4,4,4,15,15,4,4,4,4,15},
	{15,15,4,4,4,4,4,4,15,15,4,4,4,15,15},
	{15,4,4,4,4,15,15,15,15,15,4,4,4,4,15},
	{15,15,4,4,4,4,4,4,15,15,4,4,4,15,15},
	{15,4,4,4,4,15,15,15,15,15,4,4,4,15,15},
	{15,15,4,4,4,4,4,4,4,4,4,15,15,15,15},
	{15,4,4,4,4,4,4,4,15,15,15,15,15,4,15},
	{15,15,4,4,15,4,15,15,15,15,4,4,4,15,15},
	{15,15,15,15,15,15,15,15,15,15,15,15,15,15,15}
},
{
		{15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
		{15,15,3,3,3,3,15,4,4,3,3,3,3,15,15},
		{15,3,3,15,15,4,4,4,4,4,15,15,3,3,15},
		{15,3,15,15,15,4,4,4,4,4,15,15,15,3,15},
		{15,15,15,15,15,15,4,4,4,15,15,15,15,15,15},
		{15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
		{15,12,12,12,12,12,12,12,12,12,12,12,12,12,15},
		{15,12,12,12,12,12,12,12,12,12,12,12,12,12,15},
		{15,3,12,12,12,12,12,12,12,12,12,12,12,3,15},
		{15,3,6,6,6,6,6,6,6,6,6,6,6,3,15},
		{15,3,6,6,6,15,6,6,15,6,6,6,6,3,15},
		{15,3,6,6,6,15,15,15,15,6,6,6,6,3,15},
		{15,3,6,6,6,6,6,6,15,6,6,6,6,3,15},
		{15,15,6,6,6,6,6,6,6,6,6,6,6,15,15},
		{15,15,15,15,15,15,15,15,15,15,15,15,15,15,15}
},
{
	{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
	{5,6,6,6,6,6,6,6,6,6,6,6,6,6,5},
	{5,6,5,6,6,6,6,6,6,6,6,6,5,6,5},
	{5,6,6,6,6,6,6,6,6,6,6,6,6,6,5},
	{5,6,6,6,6,6,5,5,6,6,6,6,6,6,5},
	{5,6,6,6,6,5,5,5,5,6,6,6,6,6,5},
	{5,6,6,6,5,5,5,5,5,5,6,6,6,6,5},
	{5,6,6,6,5,5,5,5,5,5,6,6,6,6,5},
	{5,6,6,6,6,5,5,5,5,6,6,6,6,6,5},
	{5,6,6,6,6,6,5,5,6,6,6,6,6,6,5},
	{5,6,6,6,6,6,6,6,6,6,6,6,6,6,5},
	{5,6,6,6,6,6,6,6,6,6,6,6,6,6,5},
	{5,6,5,6,6,6,6,6,6,6,6,6,5,6,5},
	{5,6,6,6,6,6,6,6,6,6,6,6,6,6,5},
	{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5}
},

{
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,4,4,4,4,4,4,4,4,4,4,4,4,4,3},
	{3,4,4,4,4,4,4,4,4,4,4,4,4,4,3},
	{3,4,4,3,4,4,4,4,4,4,4,3,4,4,3},
	{3,4,4,4,4,4,4,3,4,4,4,4,4,4,3},
	{3,4,4,4,4,4,3,4,3,4,4,4,4,4,3},
	{3,4,4,4,4,3,4,4,4,3,4,4,4,4,3},
	{3,4,4,4,3,4,4,3,4,4,3,4,4,4,3},
	{3,4,4,4,4,3,4,4,4,3,4,4,4,4,3},
	{3,4,4,4,4,4,3,4,3,4,4,4,4,4,3},
	{3,4,4,4,4,4,4,3,4,4,4,4,4,4,3},
	{3,4,4,3,4,4,4,4,4,4,4,3,4,4,3},
	{3,4,4,4,4,4,4,4,4,4,4,4,4,4,3},
	{3,4,4,4,4,4,4,4,4,4,4,4,4,4,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
},

	{
		{232,232,232,232,232,232,232,232,232,232,232,232,232,232,232},
		{232,232,232,232,232,232,232,232,232,232,232,232,232,232,232},
		{232,232,232,232,232,232,232,232,232,232,232,232,232,232,232},
		{232,232,232,232,232,232,232,232,232,232,232,232,232,232,232},
		{232,232,232,232,232,232,232,232,232,232,232,232,232,232,232},
		{232,232,232,232,232,232,232,232,232,232,232,232,232,232,232},
		{232,232,232,232,232,232,232,232,232,232,232,232,232,232,232},
		{232,232,232,232,232,232,232,232,232,232,232,232,232,232,232},
		{232,232,232,232,232,232,232,232,232,232,232,232,232,232,232},
		{232,232,232,232,232,232,232,232,232,232,232,232,232,232,232},
		{232,232,232,232,232,232,232,232,232,232,232,232,232,232,232},
		{232,232,232,232,232,232,232,232,232,232,232,232,232,232,232},
		{232,232,232,232,232,232,232,232,232,232,232,232,232,232,232},
		{232,232,232,232,232,232,232,232,232,232,232,232,232,232,232},
		{232,232,232,232,232,232,232,232,232,232,232,232,232,232,232}
	},

};

// sets coordinates to place card
void gotoxy(int x, int y)
{
	COORD coordinate;
	coordinate.X = x;
	coordinate.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

//// saves card data to files for data and color   :  not used any more , array is global
//// filename uses fileno as input
//void SaveCard(int fileno)
//{
//
//	string Datafilename;
//	Datafilename = "CardData" + to_string(fileno) + ".txt";
//	string Colorfilename;
//	Colorfilename = "CardColor" + to_string(fileno) + ".txt";
//
//	ofstream outFileData(Datafilename);
//	ofstream outFileColor(Colorfilename);
//
//
//	for (int i = 0; i < 15; i++) {
//		for (int j = 0; j < 15; j++) {
//			outFileData << g_carddata[fileno][i][j] << " ";
//			outFileColor << g_colordata[fileno][i][j] << " ";
//		}
//		outFileData << endl;
//		outFileColor << endl;
//	}
//	outFileData.close();
//	outFileColor.close();
//
//}

////loads data from file into array  -- not used any more , array is global
//void LoadCard(int fileno)
//{
//
//	string path;
//	path = "CardData" + to_string(fileno) + ".txt";
//
//	ifstream in(path);
//
//	for (int i = 0; i < 15; i++) {
//		for (int j = 0; j < 15; j++) {
//			in >> g_carddata[fileno][i][j];
//		}
//	}
//	in.close();
//
//
//	string path2;
//	path2 = "CardColor" + to_string(fileno) + ".txt";
//
//	ifstream in2(path2);
//
//	for (int i = 0; i < 15; i++) {
//		for (int j = 0; j < 15; j++) {
//			in2 >> g_colordata[fileno][i][j];
//		}
//	}
//	in2.close();
//
//
//}

//displays card data at xy coordinate
void DisplayCard(int fileno, int x, int y )
{

	gotoxy(x, y);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < 15; i++) {     // rows 
		for (int j = 0; j < 15; j++) {
			gotoxy(x + j, y + i);   // columns
			SetConsoleTextAttribute(hConsole, g_colordata[fileno][i][j]);
			cout << char(g_carddata[fileno][i][j]);
		}
		cout << endl;   // row line 
	}


}


int getFileNoFromCardNo(int cardno) {

	int fileno;
	switch (cardno)
	{
	case 1:
		fileno = 1;
		break;
	case 2:
		fileno = 6;

		break;
	case 3:
		fileno = 4;
		break;
	case 4:
		fileno = 3;
		break;
	case 5:
		fileno = 2;
		break;
	case 6:
		fileno = 5;
		break;
	case 7:
		fileno = 4;

		break;
	case 8:
		fileno = 5;
		break;
	case 9:
		fileno = 1;
		break;
	case 10:
		fileno = 6;
		break;
	case 11:
		fileno = 3;
		break;
	case 12:
		fileno = 2;
		break;


	default:
		fileno = 0;
		break;

	}

	return fileno;
}

void DisplayCardFromNumber(int cardno) {

	// note 12 cards are displayed from 6 Files .. so teh File no and Card number are differant .. 
	// when the file number and card number are the same it means that they are a match  ...
	// you can see elow the rows 1 to 6 represent the 6 Card faces where eeach show up 2 times in the 12 images ..

	switch (cardno)
	{
	case 1:
		DisplayCard(1, 0, 0);  // r1, c1
		break;
	case 2:
		DisplayCard(6, 15, 0); // r1 c2 
		break;
	case 3:
		DisplayCard(4, 30, 0); // r1 c3 
		break;
	case 4:
		DisplayCard(3, 45, 0); // r1,c4
		break;
	case 5:
		DisplayCard(2, 60, 0); // r1, c5
		break;
	case 6:
		DisplayCard(5, 75, 0); // r1, c6
		break;
	case 7:
		DisplayCard(4, 0, 15); // r2, c1
		break;
	case 8:
		DisplayCard(5, 15, 15); //r2, c2
		break;
	case 9:
		DisplayCard(1, 30, 15); //r2, c3
		break;
	case 10:
		DisplayCard(6, 45, 15); //r2, c4
		break;
	case 11:
		DisplayCard(3, 60, 15); //r2, c5
		break;
	case 12:
		DisplayCard(2, 75, 15); // r2, c6
		break;


	default:
		break;

	}
}

void displayCardAsBlank(int cardno) {


	// 0-First  Row in the 3D array stores the Blank Card 

	switch (cardno)
	{
	case 1:
		DisplayCard(0, 0, 0);  // r1, c1
		break;
	case 2:
		DisplayCard(0, 15, 0); // r1 c2 
		break;
	case 3:
		DisplayCard(0, 30, 0); // r1 c3 
		break;
	case 4:
		DisplayCard(0, 45, 0); // r1,c4
		break;
	case 5:
		DisplayCard(0, 60, 0); // r1, c5
		break;
	case 6:
		DisplayCard(0, 75, 0); // r1, c6
		break;
	case 7:
		DisplayCard(0, 0, 15); // r2, c1
		break;
	case 8:
		DisplayCard(0, 15, 15); //r2, c2
		break;
	case 9:
		DisplayCard(0, 30, 15); //r2, c3
		break;
	case 10:
		DisplayCard(0, 45, 15); //r2, c4
		break;
	case 11:
		DisplayCard(0, 60, 15); //r2, c5
		break;
	case 12:
		DisplayCard(0, 75, 15); // r2, c6
		break;


	default:
		break;

	}
}

void displayCardAsDead(int cardno) {

	// 7th - Last Row in the 3D array stores the Dead Card face 

	switch (cardno)
	{
	case 1:
		DisplayCard(7, 0, 0);  // r1, c1
		break;
	case 2:
		DisplayCard(7, 15, 0); // r1 c2 
		break;
	case 3:
		DisplayCard(7, 30, 0); // r1 c3 
		break;
	case 4:
		DisplayCard(7, 45, 0); // r1,c4
		break;
	case 5:
		DisplayCard(7, 60, 0); // r1, c5
		break;
	case 6:
		DisplayCard(7, 75, 0); // r1, c6
		break;
	case 7:
		DisplayCard(7, 0, 15); // r2, c1
		break;
	case 8:
		DisplayCard(7, 15, 15); //r2, c2
		break;
	case 9:
		DisplayCard(7, 30, 15); //r2, c3
		break;
	case 10:
		DisplayCard(7, 45, 15); //r2, c4
		break;
	case 11:
		DisplayCard(7, 60, 15); //r2, c5
		break;
	case 12:
		DisplayCard(7, 75, 15); // r2, c6
		break;


	default:
		break;

	}
}




int GetCardNumber(int x, int y)
{
	if (x < 15 and y < 15) {
		return 1;
	}
	if (x > 15 and x < 30 and y < 15) {
		return 2;
	}
	if (x > 30 and x < 45 and y < 15) {
		return 3;
	}
	if (x > 45 and x < 60 and y < 15) {
		return 4;
	}
	if (x > 60 and x < 75 and y < 15) {
		return 5;
	}
	if (x > 75 and x < 90 and y < 15) {
		return 6;
	}
	if (x < 15 and y > 15 and y < 30) {
		return 7;
	}
	if (x > 15 and x < 30 and y > 15 and y < 30) {
		return 8;
	}
	if (x > 30 and x < 45 and y > 15 and y < 30) {
		return 9;
	}
	if (x > 45 and x < 60 and y > 15 and y < 30) {
		return 10;
	}
	if (x > 60 and x < 75 and y > 15 and y < 30) {
		return 11;
	}
	if (x > 75 and x < 90 and y > 15 and y < 30) {
		return 12;
	}

	return 0;

}



int main() {

	DisplayCard(0, 0, 0);
	DisplayCard(0, 15, 0);
	DisplayCard(0, 30, 0);
	DisplayCard(0, 0, 15);
	DisplayCard(0, 75, 15);
	DisplayCard(0, 15, 15);
	DisplayCard(0, 30, 15);
	DisplayCard(0, 45, 0);
	DisplayCard(0, 45, 15);
	DisplayCard(0, 60, 0);
	DisplayCard(0, 60, 15);
	DisplayCard(0, 75, 0);


	gotoxy(100, 0);

	BlockInput(true);
	Sleep(2000);
    BlockInput(false);

	

	while (1)
	{
		M.ReadMouseInput();
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		switch (M.InputRecord.EventType)
		{
		case MOUSE_EVENT:
			if (M.InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{

				int x = M.InputRecord.Event.MouseEvent.dwMousePosition.X;
				int y = M.InputRecord.Event.MouseEvent.dwMousePosition.Y;
				int cardSelected = GetCardNumber(x, y);

				if (g_DeadCards[cardSelected] != true && g_prevOpenedCardNumber != cardSelected  )   // important 
				{
					DisplayCardFromNumber(cardSelected);

					if (g_openStatus) // if g_openstatus 
					{
						int prevFileNo = getFileNoFromCardNo(g_prevOpenedCardNumber);
						int fileSelected = getFileNoFromCardNo(cardSelected);

						// if  match not found

						if (prevFileNo != fileSelected)
						{
							BlockInput(true);
							Sleep(500);
							BlockInput(false);
							displayCardAsBlank(g_prevOpenedCardNumber);
							displayCardAsBlank(cardSelected);
							g_openStatus = false;
							g_prevOpenedCardNumber = 0;  // important 

						}
						else
						{
							g_openStatus = false;

							g_DeadCards[g_prevOpenedCardNumber] = true;
							g_DeadCards[cardSelected] = true;
							
							BlockInput(true);
							Sleep(1000);
							BlockInput(false);

							displayCardAsDead(g_prevOpenedCardNumber);
							displayCardAsDead(cardSelected);

							g_prevOpenedCardNumber = 0;  // important 


						}


					}
					else
					{
						BlockInput(true);
						Sleep(500);
						BlockInput(false);
						g_openStatus = !g_openStatus ;
						g_prevOpenedCardNumber = cardSelected;

					}
					
					


				}





				SetConsoleTextAttribute(hConsole, 240);

				gotoxy(100, 0);
				cout << x << ", " << y << "      ";

				gotoxy(100, 3);
				cout << "open Status " << g_openStatus << " ";


				gotoxy(100, 2);
				cout << "Card Selected " << cardSelected << "    ";

				gotoxy(100, 4);
				cout << "Previous Card no " << g_prevOpenedCardNumber << "   ";

				gotoxy(100, 6);
				cout << "opened - Dead Cards";

				for (int x = 0; x <= 12; x = x + 1) {
					gotoxy(100, x + 8);
					cout << x + 1 << " -- " << g_DeadCards[x + 1];
				}






			}


		}


	}





}



