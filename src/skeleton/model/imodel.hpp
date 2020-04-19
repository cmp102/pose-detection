#pragma once
#include <utility>
#include <vector>

using pair_vec = std::vector<std::pair<unsigned int, unsigned int>>;

struct IModel{
	virtual ~IModel() {};
	virtual const pair_vec& getPairs() const = 0;
	virtual unsigned int getMaxJoints() const = 0;
	
};
