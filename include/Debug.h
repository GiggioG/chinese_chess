#pragma once;
#include <iostream>
#define D(x) std::cerr << #x << " = " << (x) << " | " << __LINE__ << std::endl;
#define Dex(x) std::cerr << #x << " = " << (x) << " | " << __LINE__ << " " << __FILE__ << std::endl;