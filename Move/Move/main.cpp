#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>

#if defined(_WIN32)
#define int64 __int64
#define uint64 __int64
#elif defined(unix)
#define int64 long long int
#define uint64 unsigned long long int
#endif

using namespace std;

#define NUM_REGISTERS 256

int64* registers = new int64[NUM_REGISTERS];
int parse(char* source);
int eval(int from, int to, int pc);
int wasd_to_int(char* wasd);
void print_mem();
int64 get_register(int address);

int debug = 0;

int main(int argc, const char* argv[]) {
	if (argc == 1) {
		printf("usage: move.exe <source> [d]\n");
		return 0;
	}

	//printf("==== Main (%s) ====\n", argv[1]);

	if (argc == 3) debug = 1;

	ifstream file (argv[1], ios::in|ios::binary|ios::ate);
	if (file.is_open()) {
		//cout << "Opened file" << endl;
		int size = (int) file.tellg();
		if (size % 4 != 0) {
			printf("Invalid source.\n");
			//system("PAUSE");
			return 0;
		}
		char* source = new char[size+1];
		file.seekg(0, ios::beg);
		file.read(source, size);
		file.close();
		source[size] = '\0';
		//cout << "Read source" << endl << endl;

		memset(registers, 0, sizeof(int64) * NUM_REGISTERS);

		parse(source);
		//cout << endl << "Executed" << endl;
		free(source);
	} else {
		cout << "Error of some sort." << endl;
	}

	//system("PAUSE");
	return 0;
}

int parse(char* source) {
	char from[] = "\0\0\0\0\0";
	char to[] = "\0\0\0\0\0";

	for (unsigned int i = 0; i < strlen(source); i += 4) {
		if (i % 8 == 0) {
			strncpy(from, &(source[i]), 4);
		} else if (i % 8 == 4) {
			strncpy(to, &(source[i]), 4);
			if (debug)
				printf("%s -> %s: ", from, to);
			i = eval(wasd_to_int(from), wasd_to_int(to), i);
			if (debug) {
				printf("\n");
				print_mem();
				system("PAUSE");
			}
		}
	}
	return 0;
}

int eval(int from, int to, int pc) {
	registers[255] = pc;

	registers[to] = get_register(from);

	if (registers[32] != 0) {
		registers[32] = 0;
		pc += (registers[33] - 1) * 8;
		registers[255] = pc;
	}
	if (registers[35] != 0) {
		if (registers[35] == 1) {
			printf("%c", registers[34]);
		} else {
			printf("%I64d", registers[34]);
		}
		registers[35] = 0;
	}
	return pc;
}

int wasd_to_int(char* wasd) {
	int out = 0;

	for (int i = 0; i < 4; i++) {
		out *= 4;
		switch (wasd[i]) {
		case 'd':
			out++;
		case 's':
			out++;
		case 'a':
			out++;
		case 'w':
		default:
			break;
		}
	}
	return out;
}

char* int_to_wasd(int address) {
	switch (address) {
	case   0: return "wwww";
	case   1: return "wwwa";
	case   2: return "wwws";
	case   3: return "wwwd";
	case   4: return "wwaw";
	case   5: return "wwaa";
	case   6: return "wwas";
	case   7: return "wwad";
	case   8: return "wwsw";
	case   9: return "wwsa";
	case  10: return "wwss";
	case  11: return "wwsd";
	case  12: return "wwdw";
	case  13: return "wwda";
	case  14: return "wwds";
	case  15: return "wwdd";
	case  16: return "waww";
	case  17: return "wawa";
	case  18: return "waws";
	case  19: return "wawd";
	case  20: return "waaw";
	case  21: return "waaa";
	case  22: return "waas";
	case  23: return "waad";
	case  24: return "wasw";
	case  25: return "wasa";
	case  26: return "wass";
	case  27: return "wasd";
	case  28: return "wadw";
	case  29: return "wada";
	case  30: return "wads";
	case  31: return "wadd";
	case  32: return "wsww";
	case  33: return "wswa";
	case  34: return "wsws";
	case  35: return "wswd";
	case  36: return "wsaw";
	case  37: return "wsaa";
	case  38: return "wsas";
	case  39: return "wsad";
	case  40: return "wssw";
	case  41: return "wssa";
	case  42: return "wsss";
	case  43: return "wssd";
	case  44: return "wsdw";
	case  45: return "wsda";
	case  46: return "wsds";
	case  47: return "wsdd";
	case  48: return "wdww";
	case  49: return "wdwa";
	case  50: return "wdws";
	case  51: return "wdwd";
	case  52: return "wdaw";
	case  53: return "wdaa";
	case  54: return "wdas";
	case  55: return "wdad";
	case  56: return "wdsw";
	case  57: return "wdsa";
	case  58: return "wdss";
	case  59: return "wdsd";
	case  60: return "wddw";
	case  61: return "wdda";
	case  62: return "wdds";
	case  63: return "wddd";
	case  64: return "awww";
	case  65: return "awwa";
	case  66: return "awws";
	case  67: return "awwd";
	case  68: return "awaw";
	case  69: return "awaa";
	case  70: return "awas";
	case  71: return "awad";
	case  72: return "awsw";
	case  73: return "awsa";
	case  74: return "awss";
	case  75: return "awsd";
	case  76: return "awdw";
	case  77: return "awda";
	case  78: return "awds";
	case  79: return "awdd";
	case  80: return "aaww";
	case  81: return "aawa";
	case  82: return "aaws";
	case  83: return "aawd";
	case  84: return "aaaw";
	case  85: return "aaaa";
	case  86: return "aaas";
	case  87: return "aaad";
	case  88: return "aasw";
	case  89: return "aasa";
	case  90: return "aass";
	case  91: return "aasd";
	case  92: return "aadw";
	case  93: return "aada";
	case  94: return "aads";
	case  95: return "aadd";
	case  96: return "asww";
	case  97: return "aswa";
	case  98: return "asws";
	case  99: return "aswd";
	case 100: return "asaw";
	case 101: return "asaa";
	case 102: return "asas";
	case 103: return "asad";
	case 104: return "assw";
	case 105: return "assa";
	case 106: return "asss";
	case 107: return "assd";
	case 108: return "asdw";
	case 109: return "asda";
	case 110: return "asds";
	case 111: return "asdd";
	case 112: return "adww";
	case 113: return "adwa";
	case 114: return "adws";
	case 115: return "adwd";
	case 116: return "adaw";
	case 117: return "adaa";
	case 118: return "adas";
	case 119: return "adad";
	case 120: return "adsw";
	case 121: return "adsa";
	case 122: return "adss";
	case 123: return "adsd";
	case 124: return "addw";
	case 125: return "adda";
	case 126: return "adds";
	case 127: return "addd";
	case 128: return "swww";
	case 129: return "swwa";
	case 130: return "swws";
	case 131: return "swwd";
	case 132: return "swaw";
	case 133: return "swaa";
	case 134: return "swas";
	case 135: return "swad";
	case 136: return "swsw";
	case 137: return "swsa";
	case 138: return "swss";
	case 139: return "swsd";
	case 140: return "swdw";
	case 141: return "swda";
	case 142: return "swds";
	case 143: return "swdd";
	case 144: return "saww";
	case 145: return "sawa";
	case 146: return "saws";
	case 147: return "sawd";
	case 148: return "saaw";
	case 149: return "saaa";
	case 150: return "saas";
	case 151: return "saad";
	case 152: return "sasw";
	case 153: return "sasa";
	case 154: return "sass";
	case 155: return "sasd";
	case 156: return "sadw";
	case 157: return "sada";
	case 158: return "sads";
	case 159: return "sadd";
	case 160: return "ssww";
	case 161: return "sswa";
	case 162: return "ssws";
	case 163: return "sswd";
	case 164: return "ssaw";
	case 165: return "ssaa";
	case 166: return "ssas";
	case 167: return "ssad";
	case 168: return "sssw";
	case 169: return "sssa";
	case 170: return "ssss";
	case 171: return "sssd";
	case 172: return "ssdw";
	case 173: return "ssda";
	case 174: return "ssds";
	case 175: return "ssdd";
	case 176: return "sdww";
	case 177: return "sdwa";
	case 178: return "sdws";
	case 179: return "sdwd";
	case 180: return "sdaw";
	case 181: return "sdaa";
	case 182: return "sdas";
	case 183: return "sdad";
	case 184: return "sdsw";
	case 185: return "sdsa";
	case 186: return "sdss";
	case 187: return "sdsd";
	case 188: return "sddw";
	case 189: return "sdda";
	case 190: return "sdds";
	case 191: return "sddd";
	case 192: return "dwww";
	case 193: return "dwwa";
	case 194: return "dwws";
	case 195: return "dwwd";
	case 196: return "dwaw";
	case 197: return "dwaa";
	case 198: return "dwas";
	case 199: return "dwad";
	case 200: return "dwsw";
	case 201: return "dwsa";
	case 202: return "dwss";
	case 203: return "dwsd";
	case 204: return "dwdw";
	case 205: return "dwda";
	case 206: return "dwds";
	case 207: return "dwdd";
	case 208: return "daww";
	case 209: return "dawa";
	case 210: return "daws";
	case 211: return "dawd";
	case 212: return "daaw";
	case 213: return "daaa";
	case 214: return "daas";
	case 215: return "daad";
	case 216: return "dasw";
	case 217: return "dasa";
	case 218: return "dass";
	case 219: return "dasd";
	case 220: return "dadw";
	case 221: return "dada";
	case 222: return "dads";
	case 223: return "dadd";
	case 224: return "dsww";
	case 225: return "dswa";
	case 226: return "dsws";
	case 227: return "dswd";
	case 228: return "dsaw";
	case 229: return "dsaa";
	case 230: return "dsas";
	case 231: return "dsad";
	case 232: return "dssw";
	case 233: return "dssa";
	case 234: return "dsss";
	case 235: return "dssd";
	case 236: return "dsdw";
	case 237: return "dsda";
	case 238: return "dsds";
	case 239: return "dsdd";
	case 240: return "ddww";
	case 241: return "ddwa";
	case 242: return "ddws";
	case 243: return "ddwd";
	case 244: return "ddaw";
	case 245: return "ddaa";
	case 246: return "ddas";
	case 247: return "ddad";
	case 248: return "ddsw";
	case 249: return "ddsa";
	case 250: return "ddss";
	case 251: return "ddsd";
	case 252: return "dddw";
	case 253: return "ddda";
	case 254: return "ddds";
	case 255: return "dddd";
	}
}

void print_mem() {
	printf("=====\n");
	for (int i = 0; i < 256; i++) {
		if (i > 37 && i < 96)
			continue;
		if (i <= 37 || (i >= 96 && get_register(i) != 0))
			printf("%s: %I64d\n", int_to_wasd(i), get_register(i));
	}
	printf("=====\n");
}

int64 get_register(int address) {
	switch (address) {
	case   0:	// wwww
		return 0;
	case   1:	// wwwa
		return 1;
	case   3:	// wwwd
		return ~registers[2];
	case   6:	// wwas
		return registers[4] & registers[5];
	case   9:	// wwsa
		return registers[7] | registers[8];
	case  12:	// wwdw
		return registers[10] << registers[11];
	case  15:	// wwdd
		return registers[13] >> registers[14];
	case  16:	// waww
		return ~((registers[13] >> registers[14]) << registers[14]) & registers[13];
	case  19:	// wawd
		return registers[17] + registers[18];
	case  22:	// waas
		return registers[20] - registers[21];
	case  25:	// wasa
		return registers[23] * registers[24];
	case  28:	// wadw
		if (registers[27] == 0)
			return 0;
		else
			return registers[26] / registers[27];
	case  31:	// wadd
		if (registers[30] == 0)
			return 0;
		else
			return registers[29] % registers[30];
	case  37:	// wsaa
		return -registers[36];
	case  40:	// wssw
		return registers[38] == registers[39];
	case  41:	// wssa
		return registers[38] > registers[39];
	case 255:	// dddd
		return registers[address] / 8;
	default:
		return registers[address];
	}
}