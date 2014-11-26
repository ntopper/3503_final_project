#include "headers/md5awsum.h"
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

#define LOOKUP 0 
#define ADD 1
#define REMOVE 2
#define UPDATE 3
#define HELP 4
#define CHECKSUM 5
#define DOWNLOAD 6
#define SOURCES 7
#define QUIET 8

class inputParser{
	public:
		int mainFlag = 0;
		vector<int> subFlag;
		vector<string> params;
		md5awsum prog;

		inputParser(int argc, char* argv[], md5awsum p) {
			prog = p;
			if(argc < 2) mainFlag = HELP;
			else if(argc == 2) mainFlag = CHECKSUM;
			for(int i = 1; i < argc; i++) {
				parseInput(argv[i]);
			}
		}

		void parseInput(char *input){

			//MAINFLAGS
			//lookup flag, return LOOKUP if 3 arguments given
			if(!strcmp(input, "--lookup") || !strcmp(input, "-l")) {
				if(mainFlag != 0) mainFlag = HELP;			
				mainFlag = LOOKUP;
			} 
			
			//add flag, return ADD if 3 arguments given
			else if(!strcmp(input, "--add") || !strcmp(input, "-a")) {
				if(mainFlag != 0) mainFlag = HELP;				
				mainFlag = ADD;
			} 
			
			//remove flag, return REMOVE if 3 arguments given
			else if(!strcmp(input, "--remove") || !strcmp(input, "-r")) {
				if(mainFlag != 0) mainFlag = HELP;	
				mainFlag = REMOVE;
			} 
			
			//update flag, return UPDATE if less than 4 arguments given
			else if(!strcmp(input, "--update") || !strcmp(input, "-u")) {
				if(mainFlag != 0) mainFlag = HELP;	
				mainFlag = UPDATE;
			}

			//download flag, return DOWNLOAD if 3 arguments are given
			else if(!strcmp(input, "--download") || !strcmp(input, "-d")) {
				if(mainFlag != 0) mainFlag = HELP;	
				mainFlag = DOWNLOAD;
			}

			//sources flag, returns SOURCES
			else if(!strcmp(input, "--sources") || !strcmp(input, "-s")) {
				if(mainFlag != 0) mainFlag = HELP;	
				mainFlag = SOURCES;
			}
			
			//SUBFLAGS
			//quiet flag, adds to subFlag
			else if(!strcmp(input, "--quiet") || !strcmp(input, "-q")) {
				subFlag.push_back(QUIET);
			}

			//PARAMETERS
			else params.push_back(input);
		}

		void analyze() {
			string argument_string;

			head();

			switch(mainFlag) {
				case LOOKUP: //reverse lookup from given hash string
					if(!params.size()) usage();
					else {
						argument_string = params.front();
						prog.lookup(argument_string, false);
					}
					break;
					
				case ADD: //add a repository given a url
					if(!params.size()) usage();
					else {
						argument_string = params.front();
						prog.add(argument_string);
					}
					break;
					
				case REMOVE: //remove a repository given a url
					if(!params.size()) usage();
					else {
						argument_string = params.front();
						prog.remove(argument_string);
					}
					break;
					
				case UPDATE: //update one (given a url) or all of the stored repositories
					//if no url argument is given, update all
					if (!params.size()) { prog.update(); }
					
					//otherwize update the given URL
					else {
						argument_string = params.front();
						prog.update(argument_string);
					}
					break;
				
				case DOWNLOAD:
					if(!params.size()) usage();
					else {
						argument_string = params.front();
						prog.download(argument_string);
					}
					break;

				case CHECKSUM://hash file at a given filepath and lookup the resulting cecksum
					argument_string = params.front();
					prog.lookup(argument_string, true);
					break;

				case SOURCES: //search for all entires labeld as "repository"
					argument_string = "repository";
					prog.lookup(argument_string, false);
					break;
					
				case HELP:
					usage();
					break;
			}
		}

		static void head() {
			cout << " __  __ ____  ____    _            ____                  " << endl;
			cout << "|  \\/  |  _ \\| ___|  / \\__      __/ ___| _   _ _ __ ___  " << endl;
			cout << "| |\\/| | | | |___ \\ / _ \\ \\ /\\ / /\\___ \\| | | | '_ ` _ \\ " << endl;
			cout << "| |  | | |_| |___) / ___ \\ V  V /  ___) | |_| | | | | | |" << endl;
			cout << "|_|  |_|____/|____/_/   \\_\\_/\\_/  |____/ \\__,_|_| |_| |_|" << endl;
			cout << endl;
		}

		static void usage() {
			cout << "Usage: MD5AwSum [options]" << endl;
			cout << "\nOptions: " << endl;
			cout << "\t-h, --help\t\tshow this information" << endl;
			cout << "\t-q, --quiet\t\tsupress output (default verbose)" << endl;
			//modify the following to be correct and more helpful
			cout << "\t-l, --lookup\t\tlookup the given hash" << endl;
			cout << "\t-a, --add\t\tadd the given url to the local table" << endl;
			cout << "\t-r, --remove\t\tremove the given url from the local table" << endl;
			cout << "\t-s, --sources\t\tshow repositories that are locally stored" << endl;
			cout << "\t-d, --download\t\tdownload the given url and lookup" << endl;
			cout << "\t-u, --update\t\tupdate the local table, updates\n\t\t\t\tall urls if it is not specified" << endl;
		}


};



  

