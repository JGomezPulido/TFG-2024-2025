#pragma once
#ifndef ASSERT_H
#define ASSERT_H
#include <iostream>
#define assertEquals(a,b,error) \
	if(a == b)\
		std::cout << "TEST PASSED\n";\
	else\
		std::cout << "TEST FAILED: " << error << "\n";
#endif