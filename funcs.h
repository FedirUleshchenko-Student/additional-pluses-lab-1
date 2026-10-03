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

void evaluateAllVariants(std::istream& from, std::ostream& to, std::string betweenVarsMessage = "");

std::ostream& print(std::ostream& os, std::string& s);

long long readVariantSize(std::istream& s,
	std::optional<std::reference_wrapper<std::ostream>> CoUutM = std::nullopt,
	std::string startMessage = "",
	std::string repeatMessage = "");
