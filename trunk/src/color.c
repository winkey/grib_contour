/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */


#include <string.h>
#include "color.h"

color_scale temp[] = {
  {-33,    "fefefe"},
  {-31.5,  "dedede"},
  {-30,    "9e9e9e"},
  {-28.5,  "6a4f96"},
  {-27,    "744089"},
  {-25.5,  "9d6d6b"},
  {-24,    "b38978"},
  {-22.5,  "ce8b84"},
  {-21,    "ee7191"},
  {-19.5,  "fa71b1"},
  {-18,    "f48be4"},
  {-17.5,  "ee91fe"},
  {-15,    "e784fe"},
  {-13.5,  "b791fe"},
  {-12,    "5eb7fe"},
  {-10.5,  "25bafe"},
  {-9,     "0b99fe"},
  {-7.5,   "188cf4"},
  {-6,     "4b94e1"},
  {-4.5,   "6ba4e1"},
  {-3,     "78bef4"},
  {-1.5,   "9ed7fe"},
  {0,      "def1fe"},
  {1.5,    "5ef5be"},
  {3,      "1ee33e"},
  {4.5,    "27e30b"},
  {6,      "77f525"},
  {7.5,    "e6fe0b"},
  {9,      "f7fe1e"},
  {10.5,   "eafe5e"},
  {12,     "eaf15e"},
  {13.5,   "f7d71e"},
  {15,     "fec71e"},
  {16.5,   "fec15e"},
  {18,     "feae5e"},
  {19.5,   "fe8e1e"},
  {21,     "fe9435"},
  {22.5,   "fec1a1"},
  {24,     "fec1c1"},
  {25.5,   "fe9494"},
  {27,     "fe5e5e"},
  {28.5,   "fe1e1e"},
  {30,     "e91800"},
  {31.5,   "c04b00"},
  {33,     "c07118"},
  {34.1,   "e98b4b"},
  {36,     "de916b"},
  {37.5,   "9e8478"},
  {39,     "7e7e7e"},
  {0,      ""}
};

color_scale t300[] = {
  {-75,	"fefefe"},
  {-74,	"fefbfe"},
  {-73, "fef6fe"},
  {-72,	"fef2fe"},
  {-71,	"feedfe"},
  {-70,	"fee8fe"},
  {-69,	"fee3fe"},
  {-68,	"fedefe"},
  {-67,	"fedafe"},
  {-66,	"fed3fe"},
  {-65,	"fecbfe"},
  {-64,	"fec2fe"},
  {-63,	"fbb7fe"},
  {-62,	"f7abfe"},
  {-61,	"f39efe"},
  {-60,	"ef93fe"},
  {-59,	"ea8bfe"},
  {-58,	"e682fe"},
  {-57,	"d38bfe"},
  {-56,	"b1a4fe"},
  {-55,	"8fbefe"},
  {-54,	"7ecffe"},
  {-53,	"7ed7fe"},
  {-52,	"7ee0fe"},
  {-51,	"7ee8fe"},
  {-50,	"7ef1fe"},
  {-49,	"7ef9fe"},
  {-48,	"7efef9"},
  {-47,	"7efef1"},
  {-46,	"7efee8"},
  {-45,	"7efed9"},
  {-44,	"7efec4"},
  {-43,	"7efeaf"},
  {-42,	"9efe9b"},
  {-41,	"defe88"},
  {-40,	"fef77e"},
  {-39,	"feea7e"},
  {-38,	"fede7e"},
  {-37,	"fed17e"},
  {-36,	"fec47e"},
  {-35,	"feb77e"},
  {-34,	"feab7e"},
  {-33,	"fe9e7e"},
  {-32,	"fe917e"},
  {-31,	"fe847e"},
  {-30,	"fe7e7e"},
	{0,		""}
};

color_scale t500[] = {
  {-47,	"fefefe"},
  {-46,	"fefbfe"},
  {-45, "fef6fe"},
  {-44,	"fef2fe"},
  {-43,	"feedfe"},
  {-42,	"fee8fe"},
  {-41,	"fee3fe"},
  {-40,	"fedefe"},
  {-39,	"fedafe"},
  {-38,	"fed3fe"},
  {-37,	"fecbfe"},
  {-36,	"fec2fe"},
  {-35,	"fbb7fe"},
  {-34,	"f7abfe"},
  {-33,	"f39efe"},
  {-32,	"ef93fe"},
  {-31,	"ea8bfe"},
  {-30,	"e682fe"},
  {-29,	"d38bfe"},
  {-28,	"b1a4fe"},
  {-27,	"8fbefe"},
  {-26,	"7ecffe"},
  {-25,	"7ed7fe"},
  {-24,	"7ee0fe"},
  {-23,	"7ee8fe"},
  {-22,	"7ef1fe"},
  {-21,	"7ef9fe"},
  {-20,	"7efef9"},
  {-19,	"7efef1"},
  {-18,	"7efee8"},
  {-17,	"7efed9"},
  {-16,	"7efec4"},
  {-15,	"7efeaf"},
  {-14,	"9efe9b"},
  {-13,	"defe88"},
  {-12,	"fef77e"},
  {-11,	"feea7e"},
  {-10,	"fede7e"},
  {-9,	"fed17e"},
  {-8,	"fec47e"},
  {-7,	"feb77e"},
  {-6,	"feab7e"},
  {-5,	"fe9e7e"},
  {-4,	"fe917e"},
  {-3,	"fe847e"},
  {-2,	"fe7e7e"},
	{0,		""}
};

color_scale t700[] = {
  {-25,	"ffffff"},
  {-24,	"fff3ff"},
  {-23, "ffe3ff"},
  {-22,	"f7d2f7"},
  {-21,	"ffc2ff"},
  {-20,	"ffb2ff"},
  {-19,	"f79eff"},
  {-18,	"ef8eff"},
  {-17,	"e682ff"},
  {-16,	"c586f7"},
  {-15,	"848ee6"},
  {-14,	"6ba2e6"},
  {-13,	"73beef"},
  {-12,	"7bd7f7"},
  {-11,	"7bf3ff"},
  {-10,	"84fbf7"},
  {-9,	"7bffe6"},
  {-8,	"7bffce"},
  {-7,	"7bffb5"},
  {-6,	"9cfb9c"},
  {-5,	"cefb8c"},
  {-4,	"e6ff7b"},
  {-3,	"efff7b"},
  {-2,	"fffb84"},
  {-1,	"fff77b"},
  {0,		"fff37b"},
  {1,		"ffe77b"},
  {2,		"ffdf7b"},
  {3,		"ffd77b"},
  {4,		"ffce84"},
  {5,		"f7c67b"},
  {6,		"ffbe7b"},
  {7,		"ffb67b"},
  {8,		"f7ae7b"},
  {9,		"ffa27b"},
  {10,	"ff9a84"},
  {11,	"f7967b"},
  {12,	"ff8a7b"},
  {13,	"ff827b"},
  {14,	"ff7d7b"},
  {15,	"f77d7b"},
  {16,	"ff7d7b"},
  {17,	"ff7d7b"},
  {18,	"f77573"},
  {19,	"ff5d63"},
  {20,	"ff494a"},
	{21,	"ff3531"},
	{22,	"ff2019"},
	{23,	"ff0808"},
	{24,	"ff0000"},
	{25,	"ef0000"},
	{26,	"f70000"},
	{27,	"e60000"},
	{28,	"d60000"},
	{29,	"ce0000"},
	{30,	"c50000"},
  {0, ""}
};

color_scale *t850 = t700;
color_scale *t925 = temp;


color_scale rh[] = {
  {0,   "0000ff"},
  {5,   "0800ef"},
  {10,  "1900e6"},
  {15,  "2100de"},
  {20,  "3100ce"},
  {25,  "3a00c5"},
  {30,  "4a00b5"},
  {35,  "5200ad"},
  {40,  "5a009c"},
  {45,  "6b0094"},
  {50,  "7b008c"},
  {55,  "84007b"},
  {60,  "8c006b"},
  {65,  "9c0063"},
  {70,  "a50052"},
  {75,  "b5004a"},
  {80,  "bd003a"},
  {85,  "ce0031"},
  {90,  "de0029"},
  {95,  "e60019"},
  {100, "ef0008"},
  {0, ""}
};

color_scale hgt925[] = {
	{300,		"6b006b"},
  {330,		"9c009c"},
  {360,		"ce00ce"},
  {390,		"ff00ff"},
  {420,		"bd00ff"},
  {450,		"7b00ff"},
  {480,		"0000ff"},
  {510,		"0059ff"},
  {540,		"008aff"},
  {570,		"00beff"},
  {600,		"00ffff"},
  {630,		"00e3ce"},
  {660,		"00ce7b"},
  {690,		"00b200"},
  {720,		"7bce00"},
  {750,		"cee700"},
  {780,		"ffff00"},
  {810,		"ffca00"},
  {840,		"ff9600"},
  {870,		"ff6500"},
  {900,		"ff0000"},
  {0, ""}
};

color_scale hgt850[] = {
	{1000,		"6b006b"},
  {1030,		"9c009c"},
  {1060,		"ce00ce"},
  {1090,		"ff00ff"},
  {1120,		"bd00ff"},
  {1150,		"7b00ff"},
  {1180,		"0000ff"},
  {1210,		"0059ff"},
  {1240,		"008aff"},
  {1270,		"00beff"},
  {1300,		"00ffff"},
  {1330,		"00e3ce"},
  {1360,		"00ce7b"},
  {1390,		"00b200"},
  {1420,		"7bce00"},
  {1450,		"cee700"},
  {1480,		"ffff00"},
  {1510,		"ffca00"},
  {1540,		"ff9600"},
  {1570,		"ff6500"},
  {1600,		"ff0000"},
  {0, ""}
};

color_scale hgt700[] = {
	{2500,		"6b006b"},
  {2535,		"9c009c"},
  {2570,		"ce00ce"},
  {2605,		"ff00ff"},
  {2640,		"bd00ff"},
  {2675,		"7b00ff"},
  {2710,		"0000ff"},
  {2745,		"0059ff"},
  {2780,		"008aff"},
  {2815,		"00beff"},
  {2850,		"00ffff"},
  {2885,		"00e3ce"},
  {2920,		"00ce7b"},
  {2955,		"00b200"},
  {2990,		"7bce00"},
  {3025,		"cee700"},
  {3060,		"ffff00"},
  {3095,		"ffca00"},
  {3130,		"ff9600"},
  {3165,		"ff6500"},
  {3200,		"ff0000"},
  {0, ""}
};

color_scale hgt500[] = {
	{4740,	"6b006b"},
  {4800,	"9c009c"},
  {4860,	"ce00ce"},
  {4920,	"ff00ff"},
  {4980,	"bd00ff"},
  {4940,	"7b00ff"},
  {5100,	"0000ff"},
  {5160,	"0059ff"},
  {5220,	"008aff"},
  {5280,	"00beff"},
  {5340,	"00ffff"},
  {5400,	"00e3ce"},
  {5460,	"00ce7b"},
  {5520,	"00b200"},
  {5580,	"7bce00"},
  {5640,	"cee700"},
  {5700,	"ffff00"},
  {5760,	"ffca00"},
  {5820,	"ff9600"},
  {5880,	"ff6500"},
  {5940,	"ff0000"},
  {0, ""}
};

color_scale hgt300[] = {
	{8300,	"6b006b"},
  {8370,	"9c009c"},
  {8440,	"ce00ce"},
  {8510,	"ff00ff"},
  {8580,	"bd00ff"},
  {8650,	"7b00ff"},
  {8720,	"0000ff"},
  {8790,	"0059ff"},
  {8860,	"008aff"},
  {8930,	"00beff"},
  {9000,	"00ffff"},
  {9070,	"00e3ce"},
  {9140,	"00ce7b"},
  {9210,	"00b200"},
  {9280,	"7bce00"},
  {9350,	"cee700"},
  {9420,	"ffff00"},
  {9490,	"ffca00"},
  {9560,	"ff9600"},
  {9630,	"ff6500"},
  {9700,	"ff0000"},
  {0, ""}
};

color_scale wind[] = {
	{10,	"002e00"},
	{20,	"005d00"},
	{30,	"008b00"},
	{40,	"00b900"},
	{50,	"00e800"},
	{60,	"17ff00"},
	{70,	"46ff00"},
	{80,	"74ff00"},
	{90,	"a2ff00"},
	{100,	"d1ff00"},
	{110,	"ffff00"},
	{120,	"ffd100"},
	{130,	"ffa200"},
	{140,	"ff7400"},
	{150,	"ff4600"},
	{160,	"ff1700"},
	{170,	"ff1717"},
	{180,	"ff4646"},
	{190,	"ff7474"},
	{200,	"ffa2a2"},
	{210,	"ffd1d1"},
	{0, ""}
};
	
color_scale pwat[] = {
	{0,		"fefefe"},
  {4,		"bfbffe"},
  {8,		"c0ffb9"},
  {12,	"fbc1fb"},
  {16,	"fcdfbf"},
  {20,	"fdffbe"},
  {24,	"ffbbc4"},
  {28,	"7e80f9"},
  {32,	"81fd81"},
  {36,	"ff7eff"},
  {40,	"f9c188"},
  {44,	"fbff7f"},
  {48,	"f9827c"},
  {52,	"0002f7"},
  {56,	"05fb00"},
  {60,	"fc01ff"},
  {64,	"ff7f02"},
  {68,	"fffc03"},
  {72,	"fa0300"},
  {76,	"706a6a"},
  {80,	"040002"},
  {0, ""}
};

color_scale cape[] = {
	{0,			"001e69"},
  {200,		"0a3c96"},
  {400,		"1464e6"},
  {600,		"1e73f0"},
  {800,		"2882f5"},
  {1000,	"50aafa"},
  {1200,	"c8e6ff"},
  {1400,	"ffffff"},
  {1600,	"fffaaa"},
  {1800,	"ffe878"},
  {2000,	"ffc03c"},
  {2200,	"ffa000"},
  {2400,	"ff6000"},
  {2600,	"ff3200"},
  {2800,	"e11400"},
  {3000,	"c00000"},
  {3200,	"910000"},
  {0, ""}
};

color_scale slp[] = {
	{0,					"000000"},
	{10000000,	"000000"},
	{0,					""}
};

/*******************************************************************************
	function to get the scale

	args:
							name				the name of the scale

	returns:
							the scale
*******************************************************************************/

color_scale *color_getscale(
	char *name)
{
	color_scale *scales;
											 
	if (!strcmp(name, "RH"))
    scales = rh;
  else if (!strcmp(name, "T"))
		scales = temp;
	else if (!strcmp(name, "TD"))
		scales = temp;
	else if (!strcmp(name, "300rh"))
		scales = rh;
	else if (!strcmp(name, "500rh"))
		scales = rh;
	else if (!strcmp(name, "700rh"))
		scales = rh;
	else if (!strcmp(name, "850rh"))
		scales = rh;
	else if (!strcmp(name, "925rh"))
		scales = rh;
	else if (!strcmp(name, "SLP"))
		scales = slp;
	else if (!strcmp(name, "300t"))
		scales = t300;
	else if (!strcmp(name, "500t"))
		scales = t500;
	else if (!strcmp(name, "700t"))
		scales = t700;
	else if (!strcmp(name, "850t"))
		scales = t850;
	else if (!strcmp(name, "925t"))
		scales = t925;
	else if (!strcmp(name, "300hgt"))
		scales = hgt300;
	else if (!strcmp(name, "500hgt"))
		scales = hgt500;
	else if (!strcmp(name, "700hgt"))
		scales = hgt700;
	else if (!strcmp(name, "850hgt"))
		scales = hgt850;
	else if (!strcmp(name, "925hgt"))
		scales = hgt925;
	else if (!strcmp(name, "300wind"))
		scales = wind;
	else if (!strcmp(name, "500wind"))
		scales = wind;
	else if (!strcmp(name, "700wind"))
		scales = wind;
	else if (!strcmp(name, "850wind"))
		scales = wind;
	else if (!strcmp(name, "925wind"))
		scales = wind;
	else if (!strcmp(name, "pwat"))
		scales = pwat;
	else if (!strcmp(name, "cape"))
		scales = cape;
	else
    scales = slp;
	
	return scales;
}

/*******************************************************************************
	function to get a color from a scale

	args:
							scales			the scale to check
							value				the value to check for in the scale

	returns:
							the color for the value
*******************************************************************************/
 
char *color_checkscale(
	color_scale *scales,
	float value)
{
	color_scale *scale;
	
	for (scale = scales ;
			 value > scale->value && *((scale + 1)->color) != 0;
			 scale++);
	
	return scale->color;
}

