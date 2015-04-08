#include <iostream>
#include <string>
#include <utility>
#include <cassert>

#include "ExtHashSet.h"
#include "ExtHashFunc.h"

typedef ExtHashSet<std::string, hash_string_obj> ExtHashSetType;

int main()
{
	ExtHashSetType set1;
	std::pair<ExtHashSetType::iterator, bool> insertRes;

	return 1;
}

