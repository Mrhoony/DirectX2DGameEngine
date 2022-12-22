#include "stdafx.h"
#include "Math.h"

std::random_device Math::rd;
std::mt19937 Math::mt(rd());