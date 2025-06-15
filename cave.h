//set up cave (dodecahedral node list
//data 1 less than original
//since arrays in c start at 0 (not 1 like 
//BASIC) room #s start at 0 too
//to match array number

int cave[20][3] = {
	{1,4,7}, //room 0 three connecting rooms
	{0,2,9}, //room 1
	{1,3,11}, //room 2
	{2,4,13}, //room 3
	{0,3,5}, //room 4
	{4,6,14}, //room 5
	{5,7,16}, //room 6
	{0,6,8}, //room 7
	{7,9,17}, //room 8
	{1,8,10}, //room 9
	{9,11,18}, //room 10
	{2,10,12}, //room 11
	{11,13,19}, //room 12
	{3,12,14}, //room 13
	{5,13,15}, //room 14
	{14,16,19}, //room 15
	{6,15,17}, //room 16
	{8,16,18}, //room 17
	{10,17,19}, //room 18
	{12,15,18} //room 19
};
