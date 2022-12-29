/*
 * Copyright (C) 2015 Jared Boone, ShareBrained Technology, Inc.
 *
 * This file is part of PortaPack.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __SINE_TABLE_H__
#define __SINE_TABLE_H__

// TODO: Including only for pi. Need separate math.hpp...
#include "complex.hpp"

#include <array>
#include <cmath>

/*
import numpy
length = 256
w = numpy.arange(length, dtype=numpy.float64) * (2 * numpy.pi / length)
v = numpy.sin(w)
print(v)
*/
constexpr uint16_t sine_table_f32_period = 256;	
// periode is 256 . means sine_table_f32[0]= sine_table_f32[0+256], sine_table_f32[1]=sine_table_f32[1+256] (those two added manualy)
// Then table has 257 values , [0,..255] + [256] and [257], those two are  used when we interpolate[255] with [255+1], and [256] with [256+1]
// [256] index is needed in the function sin_f32() when we are inputing very small radian values , example , sin_f32((-1e-14) in radians) 

static constexpr std::array<float, sine_table_f32_period + 2> sine_table_f32{
	 0.00000000e+00,   2.45412285e-02,   4.90676743e-02,
	 7.35645636e-02,   9.80171403e-02,   1.22410675e-01,
	 1.46730474e-01,   1.70961889e-01,   1.95090322e-01,
	 2.19101240e-01,   2.42980180e-01,   2.66712757e-01,
	 2.90284677e-01,   3.13681740e-01,   3.36889853e-01,
	 3.59895037e-01,   3.82683432e-01,   4.05241314e-01,
	 4.27555093e-01,   4.49611330e-01,   4.71396737e-01,
	 4.92898192e-01,   5.14102744e-01,   5.34997620e-01,
	 5.55570233e-01,   5.75808191e-01,   5.95699304e-01,
	 6.15231591e-01,   6.34393284e-01,   6.53172843e-01,
	 6.71558955e-01,   6.89540545e-01,   7.07106781e-01,
	 7.24247083e-01,   7.40951125e-01,   7.57208847e-01,
	 7.73010453e-01,   7.88346428e-01,   8.03207531e-01,
	 8.17584813e-01,   8.31469612e-01,   8.44853565e-01,
	 8.57728610e-01,   8.70086991e-01,   8.81921264e-01,
	 8.93224301e-01,   9.03989293e-01,   9.14209756e-01,
	 9.23879533e-01,   9.32992799e-01,   9.41544065e-01,
	 9.49528181e-01,   9.56940336e-01,   9.63776066e-01,
	 9.70031253e-01,   9.75702130e-01,   9.80785280e-01,
	 9.85277642e-01,   9.89176510e-01,   9.92479535e-01,
	 9.95184727e-01,   9.97290457e-01,   9.98795456e-01,
	 9.99698819e-01,   1.00000000e+00,   9.99698819e-01,
	 9.98795456e-01,   9.97290457e-01,   9.95184727e-01,
	 9.92479535e-01,   9.89176510e-01,   9.85277642e-01,
	 9.80785280e-01,   9.75702130e-01,   9.70031253e-01,
	 9.63776066e-01,   9.56940336e-01,   9.49528181e-01,
	 9.41544065e-01,   9.32992799e-01,   9.23879533e-01,
	 9.14209756e-01,   9.03989293e-01,   8.93224301e-01,
	 8.81921264e-01,   8.70086991e-01,   8.57728610e-01,
	 8.44853565e-01,   8.31469612e-01,   8.17584813e-01,
	 8.03207531e-01,   7.88346428e-01,   7.73010453e-01,
	 7.57208847e-01,   7.40951125e-01,   7.24247083e-01,
	 7.07106781e-01,   6.89540545e-01,   6.71558955e-01,
	 6.53172843e-01,   6.34393284e-01,   6.15231591e-01,
	 5.95699304e-01,   5.75808191e-01,   5.55570233e-01,
	 5.34997620e-01,   5.14102744e-01,   4.92898192e-01,
	 4.71396737e-01,   4.49611330e-01,   4.27555093e-01,
	 4.05241314e-01,   3.82683432e-01,   3.59895037e-01,
	 3.36889853e-01,   3.13681740e-01,   2.90284677e-01,
	 2.66712757e-01,   2.42980180e-01,   2.19101240e-01,
	 1.95090322e-01,   1.70961889e-01,   1.46730474e-01,
	 1.22410675e-01,   9.80171403e-02,   7.35645636e-02,
	 4.90676743e-02,   2.45412285e-02,   1.22464680e-16,
	-2.45412285e-02,  -4.90676743e-02,  -7.35645636e-02,
	-9.80171403e-02,  -1.22410675e-01,  -1.46730474e-01,
	-1.70961889e-01,  -1.95090322e-01,  -2.19101240e-01,
	-2.42980180e-01,  -2.66712757e-01,  -2.90284677e-01,
	-3.13681740e-01,  -3.36889853e-01,  -3.59895037e-01,
	-3.82683432e-01,  -4.05241314e-01,  -4.27555093e-01,
	-4.49611330e-01,  -4.71396737e-01,  -4.92898192e-01,
	-5.14102744e-01,  -5.34997620e-01,  -5.55570233e-01,
	-5.75808191e-01,  -5.95699304e-01,  -6.15231591e-01,
	-6.34393284e-01,  -6.53172843e-01,  -6.71558955e-01,
	-6.89540545e-01,  -7.07106781e-01,  -7.24247083e-01,
	-7.40951125e-01,  -7.57208847e-01,  -7.73010453e-01,
	-7.88346428e-01,  -8.03207531e-01,  -8.17584813e-01,
	-8.31469612e-01,  -8.44853565e-01,  -8.57728610e-01,
	-8.70086991e-01,  -8.81921264e-01,  -8.93224301e-01,
	-9.03989293e-01,  -9.14209756e-01,  -9.23879533e-01,
	-9.32992799e-01,  -9.41544065e-01,  -9.49528181e-01,
	-9.56940336e-01,  -9.63776066e-01,  -9.70031253e-01,
	-9.75702130e-01,  -9.80785280e-01,  -9.85277642e-01,
	-9.89176510e-01,  -9.92479535e-01,  -9.95184727e-01,
	-9.97290457e-01,  -9.98795456e-01,  -9.99698819e-01,
	-1.00000000e+00,  -9.99698819e-01,  -9.98795456e-01,
	-9.97290457e-01,  -9.95184727e-01,  -9.92479535e-01,
	-9.89176510e-01,  -9.85277642e-01,  -9.80785280e-01,
	-9.75702130e-01,  -9.70031253e-01,  -9.63776066e-01,
	-9.56940336e-01,  -9.49528181e-01,  -9.41544065e-01,
	-9.32992799e-01,  -9.23879533e-01,  -9.14209756e-01,
	-9.03989293e-01,  -8.93224301e-01,  -8.81921264e-01,
	-8.70086991e-01,  -8.57728610e-01,  -8.44853565e-01,
	-8.31469612e-01,  -8.17584813e-01,  -8.03207531e-01,
	-7.88346428e-01,  -7.73010453e-01,  -7.57208847e-01,
	-7.40951125e-01,  -7.24247083e-01,  -7.07106781e-01,
	-6.89540545e-01,  -6.71558955e-01,  -6.53172843e-01,
	-6.34393284e-01,  -6.15231591e-01,  -5.95699304e-01,
	-5.75808191e-01,  -5.55570233e-01,  -5.34997620e-01,
	-5.14102744e-01,  -4.92898192e-01,  -4.71396737e-01,
	-4.49611330e-01,  -4.27555093e-01,  -4.05241314e-01,
	-3.82683432e-01,  -3.59895037e-01,  -3.36889853e-01,
	-3.13681740e-01,  -2.90284677e-01,  -2.66712757e-01,
	-2.42980180e-01,  -2.19101240e-01,  -1.95090322e-01,
	-1.70961889e-01,  -1.46730474e-01,  -1.22410675e-01,
	-9.80171403e-02,  -7.35645636e-02,  -4.90676743e-02,
	-2.45412285e-02,   0.00000000e+00,   2.45412285e-02
};

inline float sin_f32(const float w) {
	const float x = w / (2 * pi); // normalization
	const float x_frac = x - std::floor(x); // [0, 1]

	const float n = x_frac * sine_table_f32_period;
	const uint16_t n_int = static_cast<uint16_t>(n);
	const float n_frac = n - n_int;

	const float p0 = sine_table_f32[n_int];
	const float p1 = sine_table_f32[n_int + 1];
	const float diff = p1 - p0;
	const float result = p0 + n_frac * diff; // linear interpolation

	return result;
}

#endif/*__SINE_TABLE_H__*/
