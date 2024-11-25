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
	OrtographicError(Language lan);
	
private:
	nuspell::Dictionary dict;
	
};