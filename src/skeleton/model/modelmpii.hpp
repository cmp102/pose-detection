#pragma once
#include <skeleton/model/imodel.hpp>

struct ModelMPII : IModel
{
	enum Joint : unsigned int {
		HEAD, 
		NECK, 
		R_SHO,
		R_ELB,
		R_WR, 
		L_SHO,
		L_ELB,
		L_WR,
		R_HIP,
		R_KNEE,
		R_ANK, 
		L_HIP,
		L_KNEE,
		L_ANK,
		CHEST,
		JOINTCOUNT};

	inline static pair_vec pairs = {
		{HEAD, NECK},
		{R_SHO, L_SHO},
		{NECK, R_SHO},
		{NECK, L_SHO},
		{R_SHO, R_ELB},
		{L_SHO, L_ELB},
		{R_ELB, R_WR},
		{L_ELB, L_WR},
		{R_SHO, R_HIP},
		{L_SHO, L_HIP},
		{R_HIP, L_HIP},
		{R_HIP, R_KNEE},
		{L_HIP, L_KNEE},
		{R_KNEE, R_ANK},
		{L_KNEE, L_ANK},
		{CHEST, L_HIP},
		{CHEST, R_HIP},
		{CHEST, R_SHO},
		{CHEST, L_SHO},
	};
	~ModelMPII() override {};
	const pair_vec& getPairs() const override {return pairs;};
	unsigned int getMaxJoints() const override {return JOINTCOUNT;};
};
