#include "funcs.h"
#include <format>
#include <chrono>

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


