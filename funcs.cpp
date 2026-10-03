#include "funcs.h"
#include <format>
#include <chrono>
#include <limits>

using namespace std;


string reader(istream& s)
{
	auto isBlankLine = [](const string& str) -> bool {
		for (char c : str) {
			if (c != ' ' && c != '\t' && c != '\r') {
				return false;
			}
		}
		return true;
		};

	string ans, t;

	while (getline(s, t) && (ans.empty() || !isBlankLine(t)))
	{
		if (!ans.empty() || !isBlankLine(t))
		{
			if (!t.empty() && t.back() == '\r')
			{
				t.pop_back();
			}
			ans += ((!ans.empty()) ? "\n" : "") + t;
		}
	}

	return ans;
}


vector<string> loadQuestions(istream& overHere,
	optional<reference_wrapper<ostream>> CoUutM,
	string messageStart,
	string messageInside)
{
	if (CoUutM)
	{
		CoUutM.value().get() << messageStart;
	}

	vector<string> ans;

	while (overHere.good())
	{
		if (CoUutM)
		{
			CoUutM.value().get() << messageInside;
		}

		string paragraph = reader(overHere);

		if (!paragraph.empty())
		{
			ans.push_back(move(paragraph));
		}
	}

	return ans;
}

long long processAllVariantsForOneTaskBlock(DS& s,
	std::function<void(std::string&& s)> varPrintFormat,
	std::function<void(DS& s, long long& calculated, long double& testTime, long double& timePerVar)> endPrintFormat) {
	long long iter = 0;
	auto time1 = chrono::steady_clock::now();
	try {
		long double i = 1;

		if (varPrintFormat)
			while (++iter) varPrintFormat(s());
		else
			while (++iter) s();
	}
	catch (const domain_error&) { --iter; }
	auto time2 = chrono::steady_clock::now();
	auto tdiff = time2 - time1;

	long double timePerVarMcs = (iter > 0)
		? (chrono::duration<long double, micro>(tdiff)).count() / iter
		: 0.0L;
	long double tdiffSeconds = chrono::duration<long double>(tdiff).count();

	if (endPrintFormat)
		endPrintFormat(s, iter, tdiffSeconds, timePerVarMcs);

	return iter;
}

void evaluateAllVariants(std::istream& from, std::ostream& to, string betweenVarsMessage) {
	vector<string> tasks = loadQuestions(from);

	for (size_t vars = 1; vars <= tasks.size(); vars++) {
		DS s(tasks, vars);
		processAllVariantsForOneTaskBlock(s,
			[&to](string&& s)->void {
				to << string(25, '-') << '\n' << s << endl;
			},
			[&to](DS& s, long long& calculated, long double& testTime, long double& timePerVar)->void {
				to << string(50, '-') << '\n' << string(50, '-') << '\n';
				to << format("DATA SIZE : count of tasks = {}, variant size = {}, total variant count = {} (calculated = {})\n",
					s.taskCount(), s.varSize(), s.varCount(), calculated);
				to << format("TIME STAMPS : total time = {0:e} seconds, time per test = {1:.3f} microseconds\n", testTime, timePerVar);
				to << string(50, '-') << '\n' << string(50, '-') << '\n';
				to << endl;
			});
		if (vars < tasks.size())
		{
			to << betweenVarsMessage;
		}
	}
}

long long readVariantSize(istream& s,
	optional<reference_wrapper<ostream>> CoUutM,
	string startMessage,
	string repeatMessage)
{
	long long ans = 0;

	if (CoUutM)
	{
		CoUutM.value().get() << startMessage;
	}

	while (!(s >> ans))
	{
		if (!CoUutM || repeatMessage.empty())
		{
			throw runtime_error("readVarianSize: failed to read a number from the input stream");
		}
		s.clear();
		s.ignore(numeric_limits<streamsize>::max(), '\n');
		CoUutM.value().get() << repeatMessage;
	}

	return ans;
}

ostream& print(ostream& os, string& s) {
	return os <<
		format("\n{0}NEW VARIANT{0}\n{1}\n{0}END VARIANT{0}\n",
			string(25, '-'), s);
}


