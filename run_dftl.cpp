/* Copyright 2009, 2010 Brendan Tauras */

/* run_test.cpp is part of FlashSim. */

/* FlashSim is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version. */

/* FlashSim is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details. */

/* You should have received a copy of the GNU General Public License
 * along with FlashSim.  If not, see <http://www.gnu.org/licenses/>. */

/****************************************************************************/

#include "ssd.h"
#include <fstream>
#include <iostream>

using namespace ssd;

int main(int argc, char *argv[]) {
	load_config();
	print_config (NULL);
	printf("\n");

	Ssd *ssd = new Ssd;

	unsigned int asu;
	unsigned long lba, size;
	char opcode = NULL;
	enum event_type op;
	double timestamp;
	ulong num = 0;
	double result = 0.0;

	//FILE *trace = NULL;
	//char *filename = argv[1];
	char *filename = "Financial2.spc";

	std::ifstream fin;
	fin.open(filename, std::ios::in);

	//if ((trace = fopen(filename, "r")) == NULL) {
	if (!fin.good()) {
		printf("File doesn't exist");
		fin.close();
		return 0;
	}

	char line[100];
	fin >> line;

	//while (fgets(line, 100, trace) != NULL) {
	while (line != NULL) {
		sscanf(line, "%u,%lu,%lu,%c,%lf", &asu, &lba, &size, &opcode,
				&timestamp);
		lba = lba % 20000000;
		if (opcode == 'w' || opcode == 'W') {
			op = WRITE;
		} else if (opcode == 'r' || opcode == 'R') {
			op = READ;
		}
		num++;

		result += ssd->event_arrive(op, lba, 1, timestamp);
	}

	//fclose(trace);
	fin.close();
	ssd->print_ftl_statistics();
	printf("Average Delay: %lf\n", result / num);

	printf("numFTLRead: %u\n", ssd->get_controller().stats.numFTLRead);
	printf("numFTLWrite: %u\n", ssd->get_controller().stats.numFTLWrite);
	printf("numFTLErase: %u\n", ssd->get_controller().stats.numFTLErase);
	printf("numCacheHits: %u\n", ssd->get_controller().stats.numCacheHits);
	printf("numCacheFaults: %u\n", ssd->get_controller().stats.numCacheFaults);

	//delete controller;
	delete ssd;

	return 0;
}
