#include <iostream>
#include <fstream>
#include <stdexcept>
#include <format>
#include <vector>
#include "funcs.h"

using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		// STRESS TEST
		if (argc == 1)
		{
			int testsCnt = 8;
			for (int i = 1; i <= testsCnt; i++) {
				ifstream fi(format("input{}{}.txt", '\\', i));
				if (!fi.is_open())
					throw runtime_error("cannot open input file");
				ofstream fo(format("output{}{}.txt", '\\', i));
				if (!fo.is_open())
					throw runtime_error("cannot open output file");

				evaluateAllVariants(fi, fo);
			}
		}
		else
		{

			long long variantSize = 0;
			vector<string> data;

			if (argc == 2)
			{
				string filename = argv[1];
				ifstream f(filename);
				if (!f.is_open())
				{
					throw runtime_error("cannot open file: " + filename);
				}
				cout << "opened" << endl;
				cout << "Enter variant size: ";
				variantSize = readVariantSize(cin);
				data = loadQuestions(f);
			}
			else
			{
				cout << "Enter variant size: ";
				variantSize = readVariantSize(cin);
				cout << "Enter your questions (Ctrl+Z then Enter to stop):" << endl;
				data = loadQuestions(cin);
			}

			if (data.empty())
			{
				throw runtime_error("question bank is empty");
			}
			if (variantSize < 1 || static_cast<size_t>(variantSize) > data.size())
			{
				throw runtime_error(
					"invalid variant size = " + to_string(variantSize) +
					": must be between 1 and the question bank size (" +
					to_string(data.size()) + ")");
			}

			ofstream outFile("output.txt", ios::out | ios::trunc);
			if (!outFile.is_open())
			{
				throw runtime_error("cannot open file for writing: output.txt");
			}

			DS s(data, variantSize);
			cout << "total variants possible = " << s.varCount()
				<< ", variant size = " << s.varSize() << endl;

			processAllVariantsForOneTaskBlock(s,
				[&outFile](string&& str) -> void {
					outFile << string(25, '-') << '\n' << str << endl;
				},
				[&outFile](DS& ds, long long& calculated, long double& testTime, long double& timePerVar) -> void {
					outFile << string(50, '-') << '\n' << string(50, '-') << '\n';
					outFile << format("DATA SIZE : count of tasks = {}, variant size = {}, total variant count = {} (calculated = {})\n",
						ds.taskCount(), ds.varSize(), ds.varCount(), calculated);
					outFile << format("TIME STAMPS : total time = {0:e} seconds, time per test = {1:.3f} microseconds\n", testTime, timePerVar);
					outFile << string(50, '-') << '\n' << string(50, '-') << '\n';
					outFile << endl;
				}
			);

			cout << "Done. Results written to output.txt" << endl;
		}
	}
	catch (const exception& e)
	{
		cout << "Error: " << e.what() << endl;
	}
	return 0;
}