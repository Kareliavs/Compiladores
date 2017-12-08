/*
 * scanner.cpp
 *
 */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include<stdlib.h>
#include<vector>
using namespace std;

char caracter = ' '; // variable para almacenar caracter de archivo
char dato=' ';
int recorrido = 0;
int x=-1;
char alfa[62] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
    'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', '+', '-', '*', '/', '%', '<', '>', '!', '=', ';', ',', '(', ')', 'V', 'F', '"',
    char(39), '|', 'Y', 'O', 'N', ' ', '#', char(10), '@', '.'};


int xpos=-1;
vector<char> listarecorrido;
//primera tabla compacta
int tabla1[200][3] = {

		{0,0,47},
		{1,47,1},
		{2,48,1},
		{3,49,1},
		{4,50,1},
		{5,51,1},
		{6,52,1},
		{7,53,1},
		{8,54,1},
		{9,55,3},
		{10,58,1},
		{11,59,1},
		{12,60,1},
		{13,61,1},
		{14,62,1},
		{15,63,1},
		{16,64,1},
		{17,65,1},
		{18,66,1},
		{19,67,1},
		{20,68,1},
		{21,69,1},
		{22,70,1},
		{23,71,1},
		{24,72,1},
		{25,73,1},
		{26,74,1},
		{27,75,1},
		{28,76,2},
		{29,78,2},
		{30,80,1},
		{31,81,2},
		{32,83,1},
		{33,84,1},
		{34,85,1},
		{35,86,1},
		{36,87,1},
		{37,88,1},
		{38,89,1},
		{39,90,2},
		{40,92,1},
		{41,93,1},
		{42,94,1},
		{43,95,1},
		{44,96,2},
		{45,98,1},
		{46,99,1},
		{47,100,6},
		{48,106,1},
		{49,107,1},
		{50,108,1},
		{51,109,1},
		{52,110,1},
		{53,111,1},
		{54,112,1},
		{55,113,1},
		{56,114,2},
		{57,116,1},
		{58,117,1},
		{59,118,1},
		{60,119,1},
		{61,120,1},
		{62,121,1},
		{63,122,1},
		{64,123,1},
		{65,124,1},
		{66,125,1},
		{67,126,2},
		{68,128,1},
		{69,129,1},
		{70,130,1},
		{71,131,1},
		{72,132,1},
		{73,133,1},
		{74,134,1},
		{75,135,2},
		{76,137,1},
		{77,138,2},
		{78,140,1},
		{79,141,1},
		{80,142,1},
		{81,143,1},
		{82,144,1},
		{83,145,1},
		{84,146,1},
		{85,147,2},
		{86,149,1},
		{87,150,1},
		{88,151,1},
		{89,152,1},
		{90,153,1},
		{91,154,2},
		{92,156,1},
		{93,157,1},
		{94,158,1},
		{95,159,1},
		{96,160,2},
		{97,162,2},
		{98,164,1},
		{99,165,1},
		{100,166,1},
		{101,167,1},
		{102,168,1},
		{103,169,1},
		{104,170,2},
		{105,172,1},
		{106,173,1},
		{107,174,1},
		{108,175,1},
		{109,176,1},
		{110,177,1},
		{111,178,1},
		{112,179,1},
		{113,180,1},
		{114,181,2},
		{115,183,1},
		{116,184,1},
		{117,185,1},
		{118,186,2},
		{119,188,1},
		{120,189,1},
		{121,190,1},
		{122,191,1},
		{123,192,1},
		{124,193,1},
		{125,194,1},
		{126,195,2},
		{127,197,1},
		{128,198,1},
		{129,199,1},
		{130,200,1},
		{131,201,1},
		{132,202,1},
		{133,203,1},
		{134,204,2},
		{135,206,1},
		{136,207,1},
		{137,208,1},
		{138,209,1},
		{139,210,1},
		{140,211,3},
		{141,214,1},
		{142,215,2},
		{143,217,1},
		{144,218,1},
		{145,219,1},
		{146,220,1},
		{147,221,1},
		{148,222,1},
		{149,223,1},
		{150,224,2},
		{151,226,1},
		{152,227,1},
		{153,228,1},
		{154,229,1},
		{155,230,1},
		{156,231,1},
		{157,232,1},
		{158,233,1},
		{159,234,2},
		{160,236,26},
		{161,262,50},
		{162,312,23},
		{163,335,10},
		{164,345,22},
		{165,367,14},
		{166,381,13},
		{167,394,14},
		{168,408,13},
		{169,421,14},
		{170,435,13},
		{171,448,13},
		{172,461,13},
		{173,474,2},
		{174,476,14},
		{175,490,15},
		{176,505,6},
		{177,511,3},
		{178,514,3},
		{179,517,37},
		{180,554,37},
		{181,591,4},
		{182,595,36},
		{183,631,37},
		{184,668,3},
		{185,671,14},
		{186,685,14},
		{187,699,13},
		{188,712,13},
		{189,725,13},
		{190,738,3},
		{191,741,3},
		{192,744,1},
		{193,745,3},
		{194,748,1},
		{195,749,61},
		{196,809,62},
		{197,871,4},

};

//Segunda tabla compacta
int tabla2[880][3] = {
		{0,1,1},
		{1,8,2},
		{2,22,3},
		{3,29,4},
		{4,45,5},
		{5,92,7},
		{6,97,8},
		{7,115,11},
		{8,119,12},
		{9,127,15},
		{10,135,17},
		{11,139,18},
		{12,143,19},
		{13,151,21},
		{14,162,26},
		{5,162,27},
		{16,162,28},
		{17,162,29},
		{18,162,30},
		{19,162,31},
		{20,162,32},
		{21,162,33},
		{22,162,34},
		{23,162,35},
		{24,185,36},
		{25,186,37},
		{26,187,38},
		{27,188,39},
		{28,189,40},
		{29,167,41},
		{30,165,42},
		{31,171,43},
		{32,169,44},
		{33,173,45},
		{34,174,46},
		{35,175,47},
		{36,176,48},
		{37,177,49},
		{38,178,50},
		{39,179,51},
		{40,182,52},
		{41,197,53},
		{42,190,54},
		{43,191,55},
		{44,192,56},
		{45,160,58},
		{46,194,60},
		{47,2,14},
		{48,3,11},
		{49,4,4},
		{50,5,0},
		{51,6,13},
		{52,7,14},
		{53,-1,57},
		{54,9,0},
		{55,18,3},
		{56,12,17},
		{57,10,18},
		{58,11,14},
		{59,-2,57},
		{60,13,0},
		{61,14,2},
		{62,15,19},
		{63,16,4},
		{64,17,17},
		{65,-3,57},
		{66,19,4},
		{67,20,13},
		{68,21,0},
		{69,-4,57},
		{70,23,4},
		{71,24,5},
		{72,25,4},
		{73,26,2},
		{74,27,19},
		{75,28,14},
		{76,-5,57},
		{77,-5,59},
		{78,40,11},
		{79,30,13},
		{80,31,19},
		{81,32,4},
		{82,35,14},
		{83,33,17},
		{84,34,14},
		{85,-6,57},
		{86,36,13},
		{87,37,2},
		{88,38,4},
		{89,39,18},
		{90,-7,57},
		{91,-7,59},
		{92,41,4},
		{93,42,6},
		{94,43,8},
		{95,44,17},
		{96,-8,47},
		{97,-8,57},
		{98,46,8},
		{99,47,13},
		{100,86,4},
		{101,57,8},
		{102,78,12},
		{103,68,15},
		{104,76,18},
		{105,48,21},
		{106,49,0},
		{107,50,17},
		{108,51,8},
		{109,52,0},
		{110,53,1},
		{111,54,11},
		{112,55,4},
		{113,56,18},
		{114,-9,57},
		{115,-9,59},
		{116,58,13},
		{117,59,18},
		{118,60,19},
		{119,61,17},
		{120,62,20},
		{121,63,2},
		{122,64,2},
		{123,65,8},
		{124,66,14},
		{125,67,13},
		{126,-10,57},
		{127,-10,59},
		{128,69,17},
		{129,70,14},
		{130,71,6},
		{131,72,17},
		{132,73,0},
		{133,74,12},
		{134,75,0},
		{135,-11,57},
		{136,-11,59},
		{137,77,8},
		{138,-12,57},
		{139,-12,59},
		{140,79,8},
		{141,80,4},
		{142,81,13},
		{143,82,19},
		{144,83,17},
		{145,84,0},
		{146,85,18},
		{147,-13,57},
		{148,-13,59},
		{149,87,11},
		{150,88,4},
		{151,89,6},
		{152,90,8},
		{153,91,17},
		{154,-14,57},
		{155,-14,59},
		{156,93,0},
		{157,94,2},
		{158,95,4},
		{159,96,17},
		{160,-15,57},
		{161,-15,59},
		{162,98,12},
		{163,105,13},
		{164,99,15},
		{165,100,17},
		{166,101,8},
		{167,102,12},
		{168,103,8},
		{169,104,17},
		{170,-16,47},
		{171,-16,57},
		{172,106,18},
		{173,107,19},
		{174,108,17},
		{175,109,20},
		{176,110,2},
		{177,111,2},
		{178,112,8},
		{179,113,14},
		{180,114,13},
		{181,-17,57},
		{182,-17,59},
		{183,116,4},
		{184,117,4},
		{185,118,17},
		{186,-18,47},
		{187,-18,57},
		{188,120,8},
		{189,121,4},
		{190,122,13},
		{191,123,19},
		{192,124,17},
		{193,125,0},
		{194,126,18},
		{195,-19,47},
		{196,-19,57},
		{197,128,17},
		{198,129,14},
		{199,130,6},
		{200,131,17},
		{201,132,0},
		{202,133,12},
		{203,134,0},
		{204,-20,57},
		{205,-20,59},
		{206,136,4},
		{207,137,0},
		{208,138,11},
		{209,-21,57},
		{210,140,8},
		{211,141,13},
		{212,-22,47},
		{213,-22,57},
		{214,142,14},
		{215,-23,57},
		{216,-23,59},
		{217,144,4},
		{218,145,17},
		{219,146,12},
		{220,147,8},
		{221,148,13},
		{222,149,0},
		{223,150,17},
		{224,-24,57},
		{225,-24,59},
		{226,152,0},
		{227,153,17},
		{228,154,8},
		{229,155,0},
		{230,156,1},
		{231,157,11},
		{232,158,4},
		{233,159,18},
		{234,-25,57},
		{235,-25,59},
		{236,161,0},
		{237,161,1},
		{238,161,2},
		{239,161,3},
		{240,161,4},
		{241,161,5},
		{242,161,6},
		{243,161,7},
		{244,161,8},
		{245,161,9},
		{246,161,10},
		{247,161,11},
		{248,161,12},
		{249,161,13},
		{250,161,14},
		{251,161,15},
		{252,161,16},
		{253,161,17},
		{254,161,18},
		{255,161,19},
		{256,161,20},
		{257,161,21},
		{258,161,22},
		{259,161,23},
		{260,161,24},
		{261,161,25},
		{262,161,0},
		{263,161,1},
		{264,161,2},
		{265,161,3},
		{266,161,4},
		{267,161,5},
		{268,161,6},
		{269,161,7},
		{270,161,8},
		{271,161,9},
		{272,161,10},
		{273,161,11},
		{274,161,12},
		{275,161,13},
		{276,161,14},
		{277,161,15},
		{278,161,16},
		{279,161,17},
		{280,161,18},
		{281,161,19},
		{282,161,20},
		{283,161,21},
		{284,161,22},
		{285,161,23},
		{286,161,24},
		{287,161,25},
		{288,161,26},
		{289,161,27},
		{290,161,28},
		{291,161,29},
		{292,161,30},
		{293,161,31},
		{294,161,32},
		{295,161,33},
		{296,161,34},
		{297,161,35},
		{298,-26,36},
		{299,-26,37},
		{300,-26,38},
		{301,-26,39},
		{302,-26,40},
		{303,-26,41},
		{304,-26,42},
		{305,-26,44},
		{306,-26,45},
		{307,-26,46},
		{308,-26,47},
		{309,-26,48},
		{310,-26,57},
		{311,-26,59},
		{312,162,26},
		{313,162,27},
		{314,162,28},
		{315,162,29},
		{316,162,30},
		{317,162,31},
		{318,162,32},
		{319,162,33},
		{320,162,34},
		{321,162,35},
		{322,-28,36},
		{323,-28,37},
		{324,-28,38},
		{325,-28,39},
		{326,-28,40},
		{327,-28,41},
		{328,-28,42},
		{329,-28,44},
		{330,-28,45},
		{331,-28,46},
		{332,-28,48},
		{333,-28,57},
		{334,163,61},
		{335,164,26},
		{336,164,27},
		{337,164,28},
		{338,164,29},
		{339,164,30},
		{340,164,31},
		{341,164,32},
		{342,164,33},
		{343,164,34},
		{344,164,35},
		{345,164,26},
		{346,164,27},
		{347,164,28},
		{348,164,29},
		{349,164,30},
		{350,164,31},
		{351,164,32},
		{352,164,33},
		{353,164,34},
		{354,164,35},
		{355,-27,36},
		{356,-27,37},
		{357,-27,38},
		{358,-27,39},
		{359,-27,40},
		{360,-27,41},
		{361,-27,42},
		{362,-27,44},
		{363,-27,45},
		{364,-27,46},
		{365,-27,48},
		{366,-27,57},
		{367,-29,26},
		{368,-29,27},
		{369,-29,28},
		{370,-29,29},
		{371,-29,30},
		{372,-29,31},
		{373,-29,32},
		{374,-29,33},
		{375,-29,34},
		{376,-29,35},
		{377,166,44},
		{378,-29,47},
		{379,-29,57},
		{380,-29,58},
		{381,-30,26},
		{382,-30,27},
		{383,-30,28},
		{384,-30,29},
		{385,-30,30},
		{386,-30,31},
		{387,-30,32},
		{388,-30,33},
		{389,-30,34},
		{390,-30,35},
		{391,-30,47},
		{392,-30,57},
		{393,-30,58},
		{394,-31,26},
		{395,-31,27},
		{396,-31,28},
		{397,-31,29},
		{398,-31,30},
		{399,-31,31},
		{400,-31,32},
		{401,-31,33},
		{402,-31,34},
		{403,-31,35},
		{404,168,44},
		{405,-31,47},
		{406,-31,57},
		{407,-31,58},
		{408,-32,26},
		{409,-32,27},
		{410,-32,28},
		{411,-32,29},
		{412,-32,30},
		{413,-32,31},
		{414,-32,32},
		{415,-32,33},
		{416,-32,34},
		{417,-32,35},
		{418,-32,47},
		{419,-32,57},
		{420,-32,58},
		{421,-33,26},
		{422,-33,27},
		{423,-33,28},
		{424,-33,29},
		{425,-33,30},
		{426,-33,31},
		{427,-33,32},
		{428,-33,33},
		{429,-33,34},
		{430,-33,35},
		{431,170,44},
		{432,-33,47},
		{433,-33,57},
		{434,-33,58},
		{435,-34,26},
		{436,-34,27},
		{437,-34,28},
		{438,-34,29},
		{439,-34,30},
		{440,-34,31},
		{441,-34,32},
		{442,-34,33},
		{443,-34,34},
		{444,-34,35},
		{445,-34,47},
		{446,-34,57},
		{447,-34,58},
		{448,-35,26},
		{449,-35,27},
		{450,-35,28},
		{451,-35,29},
		{452,-35,30},
		{453,-35,31},
		{454,-35,32},
		{455,-35,33},
		{456,-35,34},
		{457,-35,35},
		{458,172,44},
		{459,-35,47},
		{460,-35,57},
		{461,-36,26},
		{462,-36,27},
		{463,-36,28},
		{464,-36,29},
		{465,-36,30},
		{466,-36,31},
		{467,-36,32},
		{468,-36,33},
		{469,-36,34},
		{470,-36,35},
		{471,-36,47},
		{472,-36,57},
		{473,-36,58},
		{474,-37,57},
		{475,-37,59},
		{476,-38,26},
		{477,-38,27},
		{478,-38,28},
		{479,-38,29},
		{480,-38,30},
		{481,-38,31},
		{482,-38,32},
		{483,-38,33},
		{484,-38,34},
		{485,-38,35},
		{486,-38,51},
		{487,-38,52},
		{488,-38,57},
		{489,-38,58},
		{490,-39,26},
		{491,-39,27},
		{492,-39,28},
		{493,-39,29},
		{494,-39,30},
		{495,-39,31},
		{496,-39,32},
		{497,-39,33},
		{498,-39,34},
		{499,-39,35},
		{500,-39,47},
		{501,-39,51},
		{502,-39,52},
		{503,-39,57},
		{504,-39,58},
		{505,-40,41},
		{506,-40,42},
		{507,-40,45},
		{508,-40,48},
		{509,-40,57},
		{510,-40,59},
		{511,-41,45},
		{512,-41,46},
		{513,-41,57},
		{514,-42,45},
		{515,-42,46},
		{516,-42,57},
		{517,180,0},
		{518,180,1},
		{519,180,2},
		{520,180,3},
		{521,180,4},
		{522,180,5},
		{523,180,6},
		{524,180,7},
		{525,180,8},
		{526,180,9},
		{527,180,10},
		{528,180,11},
		{529,180,12},
		{530,180,13},
		{531,180,14},
		{532,180,15},
		{533,180,16},
		{534,180,17},
		{535,180,18},
		{36,180,19},
		{537,180,20},
		{538,180,21},
		{539,180,22},
		{540,180,23},
		{541,180,24},
		{42,180,25},
		{543,180,26},
		{544,180,27},
		{545,180,28},
		{546,180,29},
		{547,180,30},
		{548,180,31},
		{549,180,32},
		{550,180,33},
		{551,180,34},
		{552,180,35},
		{553,-46,51},
		{554,180,0},
		{555,180,1},
		{556,180,2},
		{557,180,3},
		{558,180,4},
		{559,180,5},
		{560,180,6},
		{561,180,7},
		{562,180,8},
		{563,180,9},
		{564,180,10},
		{65,180,11},
		{566,180,12},
		{567,180,13},
		{568,180,14},
		{569,180,15},
		{570,180,16},
		{571,180,17},
		{572,180,18},
		{573,180,19},
		{574,180,20},
		{575,180,21},
		{576,180,22},
		{577,180,23},
		{578,180,24},
		{579,180,25},
		{580,180,26},
		{581,180,27},
		{582,180,28},
		{583,180,29},
		{584,180,30},
		{585,180,31},
		{586,180,32},
		{587,180,33},
		{588,180,34},
		{589,180,35},
		{590,181,51},
		{591,-43,45},
		{592,-43,46},
		{593,-43,48},
		{594,-43,57},
		{595,183,0},
		{596,183,1},
		{597,183,2},
		{598,183,3},
		{599,183,4},
		{600,183,5},
		{601,183,6},
		{602,183,7},
		{603,183,8},
		{604,183,9},
		{605,183,10},
		{606,183,11},
		{607,183,12},
		{608,183,13},
		{609,183,14},
		{610,183,15},
		{611,183,16},
		{612,183,17},
		{613,183,18},
		{614,183,19},
		{615,183,20},
		{616,183,21},
		{617,183,22},
		{618,183,23},
		{619,183,24},
		{620,183,25},
		{621,183,26},
		{622,183,27},
		{623,183,28},
		{624,183,29},
		{625,183,30},
		{626,183,31},
		{627,183,32},
		{628,183,33},
		{629,183,34},
		{630,183,35},
		{631,183,0},
		{632,183,1},
		{633,183,2},
		{634,183,3},
		{635,183,4},
		{636,183,5},
		{637,183,6},
		{638,183,7},
		{639,183,8},
		{640,183,9},
		{641,183,10},
		{642,183,11},
		{643,183,12},
		{644,183,13},
		{645,183,14},
		{646,183,15},
		{647,183,16},
		{648,183,17},
		{649,183,18},
		{650,183,19},
		{651,183,20},
		{652,183,21},
		{653,183,22},
		{654,183,23},
		{655,183,24},
		{656,183,25},
		{657,183,26},
		{658,183,27},
		{659,183,28},
		{660,183,29},
		{661,183,30},
		{662,183,31},
		{663,183,32},
		{664,183,33},
		{665,183,34},
		{666,183,35},
		{667,184,52},
		{668,-44,45},
		{669,-44,48},
		{670,-44,59},
		{671,-45,26},
		{672,-45,27},
		{673,-45,28},
		{674,-45,29},
		{675,-45,30},
		{676,-45,31},
		{677,-45,32},
		{678,-45,33},
		{679,-45,34},
		{680,-45,35},
		{681,-45,44},
		{682,-45,47},
		{683,-45,57},
		{684,-45,58},
		{685,-46,26},
		{686,-46,27},
		{687,-46,28},
		{688,-46,29},
		{689,-46,30},
		{690-46,31},
		{691,-46,32},
		{692,-46,33},
		{693,-46,34},
		{694,-46,35},
		{695,-46,44},
		{696,-46,47},
		{697,-46,57},
		{698,-46,58},
		{699,-47,26},
		{700,-47,27},
		{701,-47,28},
		{702,-47,29},
		{703,-47,30},
		{704,-47,31},
		{705,-47,32},
		{706,-47,33},
		{707,-47,34},
		{708,-47,35},
		{709,-47,47},
		{710,-47,57},
		{711,-47,58},
		{712,-48,26},
		{713,-48,27},
		{714,-48,28},
		{715,-48,29},
		{716,-48,30},
		{717,-48,31},
		{718,-48,32},
		{719,-48,33},
		{720,-48,34},
		{721,-48,35},
		{722,-48,47},
		{723,-48,57},
		{724,-48,58},
		{725,-49,26},
		{726,-49,27},
		{727,-49,28},
		{728,-49,29},
		{729,-49,30},
		{730,-49,31},
		{731,-49,32},
		{732,-49,33},
		{733,-49,34},
		{734,-49,35},
		{735,-49,47},
		{736,-49,57},
		{737,-49,58},
		{738,-50,47},
		{739,-50,57},
		{740,-50,58},
		{741,-51,47},
		{742,-51,57},
		{743,-51,58},
		{744,193,55},
		{745,-52,47},
		{746,-52,57},
		{747,-52,58},
		{748,195,60},
		{749,196,0},
		{750,196,1},
		{751,196,2},
		{752,196,3},
		{753,196,4},
		{754,196,5},
		{755,196,6},
		{756,196,7},
		{757,196,8},
		{758,196,9},
		{759,196,10},
		{760,196,11},
		{761,196,12},
		{762,196,13},
		{763,196,14},
		{764,196,15},
		{765,196,16},
		{766,196,17},
		{767,196,18},
		{768,196,19},
		{769,196,20},
		{770,196,21},
		{771,196,22},
		{772,196,23},
		{773,196,24},
		{774,196,25},
		{775,196,26},
		{776,196,27},
		{777,196,28},
		{778,196,29},
		{779,196,30},
		{780,196,31},
		{781,196,32},
		{782,196,33},
		{783,196,34},
		{784,196,35},
		{785,196,36},
		{786,196,37},
		{787,196,38},
		{788,196,39},
		{789,196,40},
		{790,196,41},
		{791,196,42},
		{792,196,43},
		{793,196,44},
		{794,196,45},
		{795,196,46},
		{796,196,47},
		{797,196,48},
		{798,196,49},
		{799,196,50},
		{800,196,51},
		{801,196,52},
		{802,196,53},
		{803,196,54},
		{804,196,55},
		{805,196,56},
		{806,196,57},
		{807,196,58},
		{808,196,60},
		{809,196,61},
		{810,196,0},
		{811,196,1},
		{812,196,2},
		{813,196,3},
		{814,196,4},
		{815,196,5},
		{816,196,6},
		{817,196,7},
		{818,196,8},
		{819,196,9},
		{820,196,10},
		{821,196,11},
		{822,196,12},
		{823,196,13},
		{824,196,14},
		{825,196,15},
		{826,196,16},
		{827,196,17},
		{828,196,18},
		{829,196,19},
		{830,196,20},
		{831,196,21},
		{832,196,22},
		{833,196,23},
		{834,196,24},
		{835,196,25},
		{836,196,26},
		{837,196,27},
		{838,196,28},
		{839,196,29},
		{840,196,30},
		{841,196,31},
		{842,196,32},
		{843,196,33},
		{844,196,34},
		{845,196,35},
		{846,196,36},
		{847,196,37},
		{848,196,38},
		{849,196,39},
		{850,196,40},
		{851,196,41},
		{852,196,42},
		{853,196,43},
		{854,196,44},
		{855,196,45},
		{856,196,46},
		{857,196,47},
		{858,196,48},
		{859,196,49},
		{860,196,50},
		{861,196,51},
		{862,196,52},
		{863,196,53},
		{864,196,54},
		{865,196,55},
		{866,196,56},
		{867,196,57},
		{868,196,58},
		{869,-53,59},
		{870,196,60},
		{871,196,61},
		{872,-54,51},
		{873,-54,52},
		{874,-54,57},
		{875,-54,58},

};
/*
Aqui va los metodos
 */
int comprobacion=0;
int cont=0;
int alfabeto(char c) {//Metodo para obtener la posicion de cada caracter dentro de nuestro alfabeto


	//int d = listarecorrido.size();
	//cout<<"Lista Recorrido>  "<<d<<endl;
	//cout<<"Lo que recibe xpos>  "<<po<<endl;
/*	if(po!=-1){
		cont--;
		po=-1;
		x=-1;
		comprobacion++;

	}*/
	//cout<<"Lista Recorrido>  "<<d<<endl;

	//for(int j=cont ; j<= d ; j++){
		//cout<<"Valor de J>  "<<j<<endl;
		//cont++;
		//cout<<"Valor de cont>  "<<cont<<endl;

		for (int i = 0; i <= 62; i++) {
			//cout<<listarecorrido[j]<<endl;

			if (c == alfa[i]) {

				return i;

				break;
			}
		}



   // }

    return 0;

}

void tablasCompactas(int pos, int l,char c) {//Realiza el recorrido en las Tablas Compactadas

    //alfabeto(pos);
    int t2c1 = 0;
    int aux = 0;

    if (recorrido >= 0) {

        int estado = tabla1[recorrido][1];
        int estadoFinal = tabla1[recorrido][2] + estado;

        while (aux <= 880) {

            if (estado == tabla2[aux][0]) {
                t2c1 = estado;
                break;
            }
            aux++;


        }

        bool a = false;
        int aux2 = 0;
        int error = 0;
        for (int j = t2c1; j < estadoFinal; j++) {

            if (pos == tabla2[j][2]) {
                aux2 = tabla2[j][1];
                a = true;
                break;
            } else {
                a = false;
                error = tabla2[j][2];

            }


        }

        if (a == true) {
            recorrido = aux2;

        }

        if (recorrido < 0) {
        	cout <<"Compilacion exitosa"<< recorrido << endl;
            recorrido = 0;
            x=pos;

        }

        if (a == false) {
        	if(error==60){
        		recorrido=0;
        	}else{
        		if((pos==57)||(pos==59)){
        			if (recorrido > 0) {
        			    cout << "linea" << l << " caracter: " <<c <<" Sentencia mal escrita " << endl;
        			}
        			recorrido=0;
        		}else{
        			cout << "linea" << l << " error" << error << " caracter: " << c<< endl;
        			//recorrido=0;
        		}


        	}
        	//recorrido=0;
        	//if((recorrido>0)&&((pos==57)||(pos==59))&&(error!=60)){
        		//cout << "linea" << l <<" Sentencia mal escrita " << endl;
        	//}

        }

    } else {
        cout << "el token es negativo " << endl;
    }

}
/*if(error>0){
        			cout << "linea" << l <<" caracter: " << ca<<" Sentencia mal escrita " << endl;
     }
*/

void metodoArchivo() {//Lee caracter por caracter del Archivo .txt
    //int linea = 0;
    ifstream fichero; //variable fichero para leer los datos
    fichero.open(("lenguaje.txt"));
    fichero.get(caracter);

    if (fichero.fail()) {// si fichero no falla coge un letra dle fichero
        cout << "Error al abrir el archivo lenguaje.txt" << endl;

    } else {

        while (!fichero.eof()) {//mientras fichero no llegue al final
        	listarecorrido.push_back(caracter);
/*        	listarecorrido.push_back(caracter);
        	int pos= alfabeto(caracter,xpos);
        	//cout<<"la posicion>  "<<pos<<endl;

        	if (pos == 59) {
                linea++;

            }

			tablasCompactas(pos, linea,dato);
			xpos=x;
			//cout<<"xxxxxx: "<<x<<endl;
            //cout<<"PRueba: "<<comprobacion<<endl;

            //cout<<pos<<endl;*/
            fichero.get(caracter);
            //alfabeto(caracter);






        }

    }
    fichero.close();

}








int main() {



    //recorridoTablasCompactas(metodoArchivo());
    //recorridoTablas();

    metodoArchivo();
    int f=listarecorrido.size();
    int nuevapos=0;
    int linea=0;
    for(int j=0;j<=f;j++){
    	if(xpos!=-1){
    			j--;
    			xpos=-1;
    			x=-1;
    			comprobacion++;
    	}

    	nuevapos=alfabeto(listarecorrido[j]);
    	if (nuevapos == 59) {
    	       linea++;
    	}
    	tablasCompactas(nuevapos,linea,listarecorrido[j]);
    	xpos=x;

    }

    return 0;
}






