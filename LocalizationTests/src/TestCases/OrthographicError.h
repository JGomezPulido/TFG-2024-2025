#pragma once
#include "nuspell/dictionary.hxx"
#include "TestCase.h"

class OrtographicError : public TestCase {
public:
	enum class Language {
		EN,
		ES
	};
public:
	OrtographicError(nuspell::Dictionary& lan) : dict(lan) {}

	void test(const std::string& testString) override;
	
private:
	nuspell::Dictionary& dict;
	



};