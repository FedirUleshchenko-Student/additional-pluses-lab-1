#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <optional>
#include <functional>
#include "DS.h"


std::string reader(std::istream& s);

std::vector<std::string> loadQuestions(std::istream& overHere,
	std::optional<std::reference_wrapper<std::ostream>> CoUutM = std::nullopt,
	std::string messageStart = "",
	std::string messageInside = "");

long long processAllVariantsForOneTaskBlock(DS& s,
	std::function<void(std::string&& s)> varPrintFormat = nullptr,
	std::function<void(DS& s, long long& calculated, long double& testTime, long double& timePerVar)> endPrintFormat = nullptr);


