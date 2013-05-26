/*
    C-Dogs SDL
    A port of the legendary (and fun) action/arcade cdogs.
    Copyright (C) 1995 Ronny Wester
    Copyright (C) 2003 Jeremy Chin 
    Copyright (C) 2003-2007 Lucas Martin-King 

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

-------------------------------------------------------------------------------

 pics.c - sprite functions
 
 Author: $Author$
 Rev:    $Revision$
 URL:    $HeadURL$
 ID:     $Id$
 
*/

#include "pics.h"


color_t gPalette[256], origPalette[256];
void *gPics[PIC_MAX];
void *gCompiledPics[PIC_MAX];
void *gRLEPics[PIC_MAX];


const int cBodyPic[BODY_COUNT][DIRECTION_COUNT][STATE_COUNT] = {
	{
	 {25, 25, 25, 21, 22, 23, 24, 25, 25},
	 {25, 25, 25, 21, 22, 23, 24, 25, 25},
	 {20, 20, 20, 19, 18, 17, 16, 20, 20},
	 {4, 4, 4, 7, 8, 9, 10, 4, 4},
	 {4, 4, 4, 7, 8, 9, 10, 4, 4},
	 {4, 4, 4, 7, 8, 9, 10, 4, 4},
	 {15, 15, 15, 11, 12, 13, 14, 15, 15},
	 {15, 15, 15, 11, 12, 13, 14, 15, 15}
	 },
	{
	 {73, 73, 73, 74, 75, 76, 77, 73, 73},
	 {73, 73, 73, 74, 75, 76, 77, 73, 73},
	 {68, 68, 68, 72, 71, 70, 69, 68, 68},
	 {63, 63, 63, 64, 65, 66, 67, 63, 63},
	 {63, 63, 63, 64, 65, 66, 67, 63, 63},
	 {63, 63, 63, 64, 65, 66, 67, 63, 63},
	 {15, 15, 15, 11, 12, 13, 14, 15, 15},
	 {15, 15, 15, 11, 12, 13, 14, 15, 15}
	 }
};

const int cHeadPic[FACE_COUNT][DIRECTION_COUNT][STATE_COUNT] = {
	{
	 {26, 26, 26, 26, 26, 26, 26, 26, 26},
	 {27, 27, 27, 27, 27, 27, 27, 27, 27},
	 {28, 28, 28, 28, 28, 28, 28, 137, 137},
	 {29, 29, 29, 29, 29, 29, 29, 138, 138},
	 {30, 30, 30, 30, 30, 30, 30, 139, 139},
	 {31, 31, 31, 31, 31, 31, 31, 140, 140},
	 {32, 32, 32, 32, 32, 32, 32, 141, 141},
	 {33, 33, 33, 33, 33, 33, 33, 33, 33}
	 },
	{
	 {129, 129, 129, 129, 129, 129, 129, 129, 129},
	 {130, 130, 130, 130, 130, 130, 130, 130, 130},
	 {131, 131, 131, 131, 131, 131, 131, 146, 146},
	 {132, 132, 132, 132, 132, 132, 132, 147, 147},
	 {133, 133, 133, 133, 133, 133, 133, 148, 148},
	 {134, 134, 134, 134, 134, 134, 134, 149, 149},
	 {135, 135, 135, 135, 135, 135, 135, 150, 150},
	 {136, 136, 136, 136, 136, 136, 136, 136, 136}
	 },
	{
	 {121, 121, 121, 121, 121, 121, 121, 121, 121},
	 {122, 122, 122, 122, 122, 122, 122, 122, 122},
	 {123, 123, 123, 123, 123, 123, 123, 123, 123},
	 {124, 124, 124, 124, 124, 124, 124, 124, 124},
	 {125, 125, 125, 125, 125, 125, 125, 125, 125},
	 {126, 126, 126, 126, 126, 126, 126, 126, 126},
	 {127, 127, 127, 127, 127, 127, 127, 127, 127},
	 {128, 128, 128, 128, 128, 128, 128, 128, 128}
	 },
	{
	 {228, 228, 228, 228, 228, 228, 228, 228, 228},
	 {227, 227, 227, 227, 227, 227, 227, 227, 227},
	 {226, 226, 226, 226, 226, 226, 226, 265, 265},
	 {225, 225, 225, 225, 225, 225, 225, 264, 264},
	 {224, 224, 224, 224, 224, 224, 224, 263, 263},
	 {223, 223, 223, 223, 223, 223, 223, 262, 262},
	 {222, 222, 222, 222, 222, 222, 222, 261, 261},
	 {229, 229, 229, 229, 229, 229, 229, 229, 229}
	 },
	{
	 {236, 236, 236, 236, 236, 236, 236, 236, 236},
	 {235, 235, 235, 235, 235, 235, 235, 235, 235},
	 {234, 234, 234, 234, 234, 234, 234, 242, 242},
	 {233, 233, 233, 233, 233, 233, 233, 241, 241},
	 {232, 232, 232, 232, 232, 232, 232, 240, 240},
	 {231, 231, 231, 231, 231, 231, 231, 239, 239},
	 {230, 230, 230, 230, 230, 230, 230, 238, 238},
	 {237, 237, 237, 237, 237, 237, 237, 237, 237}
	 },
	{
	 {249, 249, 249, 249, 249, 249, 249, 249, 249},
	 {248, 248, 248, 248, 248, 248, 248, 248, 248},
	 {247, 247, 247, 247, 247, 247, 247, 247, 247},
	 {246, 246, 246, 246, 246, 246, 246, 246, 246},
	 {245, 245, 245, 245, 245, 245, 245, 245, 245},
	 {244, 244, 244, 244, 244, 244, 244, 244, 244},
	 {243, 243, 243, 243, 243, 243, 243, 243, 243},
	 {250, 250, 250, 250, 250, 250, 250, 250, 250}
	 },
	{
	 {272, 272, 272, 272, 272, 272, 272, 272, 272},
	 {271, 271, 271, 271, 271, 271, 271, 271, 271},
	 {270, 270, 270, 270, 270, 270, 270, 278, 278},
	 {269, 269, 269, 269, 269, 269, 269, 277, 277},
	 {268, 268, 268, 268, 268, 268, 268, 276, 276},
	 {267, 267, 267, 267, 267, 267, 267, 275, 275},
	 {266, 266, 266, 266, 266, 266, 266, 274, 274},
	 {273, 273, 273, 273, 273, 273, 273, 273, 273}
	 },
	{
	 {308, 308, 308, 308, 308, 308, 308, 308, 308},
	 {307, 307, 307, 307, 307, 307, 307, 307, 307},
	 {306, 306, 306, 306, 306, 306, 306, 306, 306},
	 {305, 305, 305, 305, 305, 305, 305, 305, 305},
	 {304, 304, 304, 304, 304, 304, 304, 304, 304},
	 {303, 303, 303, 303, 303, 303, 303, 303, 303},
	 {302, 302, 302, 302, 302, 302, 302, 302, 302},
	 {309, 309, 309, 309, 309, 309, 309, 309, 309}
	 },
	{
	 {372, 372, 372, 372, 372, 372, 372, 372, 372},
	 {371, 371, 371, 371, 371, 371, 371, 371, 371},
	 {370, 370, 370, 370, 370, 370, 370, 370, 370},
	 {369, 369, 369, 369, 369, 369, 369, 369, 369},
	 {368, 368, 368, 368, 368, 368, 368, 368, 368},
	 {367, 367, 367, 367, 367, 367, 367, 367, 367},
	 {366, 366, 366, 366, 366, 366, 366, 366, 366},
	 {373, 373, 373, 373, 373, 373, 373, 373, 373}
	 },
	{
	 {396, 396, 396, 396, 396, 396, 396, 396, 396},
	 {395, 395, 395, 395, 395, 395, 395, 395, 395},
	 {394, 394, 394, 394, 394, 394, 394, 394, 394},
	 {393, 393, 393, 393, 393, 393, 393, 393, 393},
	 {392, 392, 392, 392, 392, 392, 392, 392, 392},
	 {391, 391, 391, 391, 391, 391, 391, 391, 391},
	 {390, 390, 390, 390, 390, 390, 390, 390, 390},
	 {397, 397, 397, 397, 397, 397, 397, 397, 397}
	 },
	{
	 {P2 + 6, P2 + 6, P2 + 6, P2 + 6, P2 + 6, P2 + 6, P2 + 6, P2 + 6,
	  P2 + 6},
	 {P2 + 5, P2 + 5, P2 + 5, P2 + 5, P2 + 5, P2 + 5, P2 + 5, P2 + 5,
	  P2 + 5},
	 {P2 + 4, P2 + 4, P2 + 4, P2 + 4, P2 + 4, P2 + 4, P2 + 4, P2 + 4,
	  P2 + 4},
	 {P2 + 3, P2 + 3, P2 + 3, P2 + 3, P2 + 3, P2 + 3, P2 + 3, P2 + 3,
	  P2 + 3},
	 {P2 + 2, P2 + 2, P2 + 2, P2 + 2, P2 + 2, P2 + 2, P2 + 2, P2 + 2,
	  P2 + 2},
	 {P2 + 1, P2 + 1, P2 + 1, P2 + 1, P2 + 1, P2 + 1, P2 + 1, P2 + 1,
	  P2 + 1},
	 {P2 + 0, P2 + 0, P2 + 0, P2 + 0, P2 + 0, P2 + 0, P2 + 0, P2 + 0,
	  P2 + 0},
	 {P2 + 7, P2 + 7, P2 + 7, P2 + 7, P2 + 7, P2 + 7, P2 + 7, P2 + 7,
	  P2 + 7}
	 },
	{
	 {P2 + 14, P2 + 14, P2 + 14, P2 + 14, P2 + 14, P2 + 14, P2 + 14,
	  P2 + 14, P2 + 14},
	 {P2 + 13, P2 + 13, P2 + 13, P2 + 13, P2 + 13, P2 + 13, P2 + 13,
	  P2 + 13, P2 + 13},
	 {P2 + 12, P2 + 12, P2 + 12, P2 + 12, P2 + 12, P2 + 12, P2 + 12,
	  P2 + 12, P2 + 12},
	 {P2 + 11, P2 + 11, P2 + 11, P2 + 11, P2 + 11, P2 + 11, P2 + 11,
	  P2 + 11, P2 + 11},
	 {P2 + 10, P2 + 10, P2 + 10, P2 + 10, P2 + 10, P2 + 10, P2 + 10,
	  P2 + 10, P2 + 10},
	 {P2 + 9, P2 + 9, P2 + 9, P2 + 9, P2 + 9, P2 + 9, P2 + 9, P2 + 9,
	  P2 + 9},
	 {P2 + 8, P2 + 8, P2 + 8, P2 + 8, P2 + 8, P2 + 8, P2 + 8, P2 + 8,
	  P2 + 8},
	 {P2 + 15, P2 + 15, P2 + 15, P2 + 15, P2 + 15, P2 + 15, P2 + 15,
	  P2 + 15, P2 + 15}
	 },
	{
	 {P2 + 22, P2 + 22, P2 + 22, P2 + 22, P2 + 22, P2 + 22, P2 + 22,
	  P2 + 22, P2 + 22},
	 {P2 + 21, P2 + 21, P2 + 21, P2 + 21, P2 + 21, P2 + 21, P2 + 21,
	  P2 + 21, P2 + 21},
	 {P2 + 20, P2 + 20, P2 + 20, P2 + 20, P2 + 20, P2 + 20, P2 + 20,
	  P2 + 20, P2 + 20},
	 {P2 + 19, P2 + 19, P2 + 19, P2 + 19, P2 + 19, P2 + 19, P2 + 19,
	  P2 + 19, P2 + 19},
	 {P2 + 18, P2 + 18, P2 + 18, P2 + 18, P2 + 18, P2 + 18, P2 + 18,
	  P2 + 18, P2 + 18},
	 {P2 + 17, P2 + 17, P2 + 17, P2 + 17, P2 + 17, P2 + 17, P2 + 17,
	  P2 + 17, P2 + 17},
	 {P2 + 16, P2 + 16, P2 + 16, P2 + 16, P2 + 16, P2 + 16, P2 + 16,
	  P2 + 16, P2 + 16},
	 {P2 + 23, P2 + 23, P2 + 23, P2 + 23, P2 + 23, P2 + 23, P2 + 23,
	  P2 + 23, P2 + 23}
	 },
	{
	 {P2 + 30, P2 + 30, P2 + 30, P2 + 30, P2 + 30, P2 + 30, P2 + 30,
	  P2 + 30, P2 + 30},
	 {P2 + 29, P2 + 29, P2 + 29, P2 + 29, P2 + 29, P2 + 29, P2 + 29,
	  P2 + 29, P2 + 29},
	 {P2 + 28, P2 + 28, P2 + 28, P2 + 28, P2 + 28, P2 + 28, P2 + 28,
	  P2 + 28, P2 + 28},
	 {P2 + 27, P2 + 27, P2 + 27, P2 + 27, P2 + 27, P2 + 27, P2 + 27,
	  P2 + 27, P2 + 27},
	 {P2 + 26, P2 + 26, P2 + 26, P2 + 26, P2 + 26, P2 + 26, P2 + 26,
	  P2 + 26, P2 + 26},
	 {P2 + 25, P2 + 25, P2 + 25, P2 + 25, P2 + 25, P2 + 25, P2 + 25,
	  P2 + 25, P2 + 25},
	 {P2 + 24, P2 + 24, P2 + 24, P2 + 24, P2 + 24, P2 + 24, P2 + 24,
	  P2 + 24, P2 + 24},
	 {P2 + 31, P2 + 31, P2 + 31, P2 + 31, P2 + 31, P2 + 31, P2 + 31,
	  P2 + 31, P2 + 31}
	 },
	{
	 {P2 + 38, P2 + 38, P2 + 38, P2 + 38, P2 + 38, P2 + 38, P2 + 38,
	  P2 + 38, P2 + 38},
	 {P2 + 37, P2 + 37, P2 + 37, P2 + 37, P2 + 37, P2 + 37, P2 + 37,
	  P2 + 37, P2 + 37},
	 {P2 + 36, P2 + 36, P2 + 36, P2 + 36, P2 + 36, P2 + 36, P2 + 36,
	  P2 + 44, P2 + 44},
	 {P2 + 35, P2 + 35, P2 + 35, P2 + 35, P2 + 35, P2 + 35, P2 + 35,
	  P2 + 43, P2 + 43},
	 {P2 + 34, P2 + 34, P2 + 34, P2 + 34, P2 + 34, P2 + 34, P2 + 34,
	  P2 + 42, P2 + 42},
	 {P2 + 33, P2 + 33, P2 + 33, P2 + 33, P2 + 33, P2 + 33, P2 + 33,
	  P2 + 41, P2 + 41},
	 {P2 + 32, P2 + 32, P2 + 32, P2 + 32, P2 + 32, P2 + 32, P2 + 32,
	  P2 + 40, P2 + 40},
	 {P2 + 39, P2 + 39, P2 + 39, P2 + 39, P2 + 39, P2 + 39, P2 + 39,
	  P2 + 39, P2 + 39}
	 },
	{
	 {P2 + 129, P2 + 129, P2 + 129, P2 + 129, P2 + 129, P2 + 129,
	  P2 + 129, P2 + 129, P2 + 129},
	 {P2 + 128, P2 + 128, P2 + 128, P2 + 128, P2 + 128, P2 + 128,
	  P2 + 128, P2 + 128, P2 + 128},
	 {P2 + 127, P2 + 127, P2 + 127, P2 + 127, P2 + 127, P2 + 127,
	  P2 + 127, P2 + 127, P2 + 127},
	 {P2 + 126, P2 + 126, P2 + 126, P2 + 126, P2 + 126, P2 + 126,
	  P2 + 126, P2 + 126, P2 + 126},
	 {P2 + 125, P2 + 125, P2 + 125, P2 + 125, P2 + 125, P2 + 125,
	  P2 + 125, P2 + 125, P2 + 125},
	 {P2 + 124, P2 + 124, P2 + 124, P2 + 124, P2 + 124, P2 + 124,
	  P2 + 124, P2 + 124, P2 + 124},
	 {P2 + 123, P2 + 123, P2 + 123, P2 + 123, P2 + 123, P2 + 123,
	  P2 + 123, P2 + 123, P2 + 123},
	 {P2 + 130, P2 + 130, P2 + 130, P2 + 130, P2 + 130, P2 + 130,
	  P2 + 130, P2 + 130, P2 + 130}
	 },
	{
	 {P2 + 175, P2 + 175, P2 + 175, P2 + 175, P2 + 175, P2 + 175,
	  P2 + 175, P2 + 175, P2 + 175},
	 {P2 + 174, P2 + 174, P2 + 174, P2 + 174, P2 + 174, P2 + 174,
	  P2 + 174, P2 + 174, P2 + 174},
	 {P2 + 173, P2 + 173, P2 + 173, P2 + 173, P2 + 173, P2 + 173,
	  P2 + 173, P2 + 181, P2 + 181},
	 {P2 + 172, P2 + 172, P2 + 172, P2 + 172, P2 + 172, P2 + 172,
	  P2 + 172, P2 + 180, P2 + 180},
	 {P2 + 171, P2 + 171, P2 + 171, P2 + 171, P2 + 171, P2 + 171,
	  P2 + 171, P2 + 179, P2 + 179},
	 {P2 + 170, P2 + 170, P2 + 170, P2 + 170, P2 + 170, P2 + 170,
	  P2 + 170, P2 + 178, P2 + 178},
	 {P2 + 169, P2 + 169, P2 + 169, P2 + 169, P2 + 169, P2 + 169,
	  P2 + 169, P2 + 177, P2 + 177},
	 {P2 + 176, P2 + 176, P2 + 176, P2 + 176, P2 + 176, P2 + 176,
	  P2 + 176, P2 + 176, P2 + 176}
	 }
};

const TOffsetPic cGunPics[GUNPIC_COUNT][DIRECTION_COUNT][GUNSTATE_COUNT] = {
	{
	 {{-2, -10, 86}, {-3, -8, 78}, {-3, -7, 78}},
	 {{-2, -10, 87}, {-2, -9, 79}, {-3, -8, 79}},
	 {{0, -12, 88}, {0, -5, 80}, {-1, -5, 80}},
	 {{-2, -9, 90}, {0, -2, 81}, {-1, -3, 81}},
	 {{-2, -9, 90}, {-1, -2, 82}, {-1, -3, 82}},
	 {{-6, -10, 91}, {-7, -4, 83}, {-6, -5, 83}},
	 {{-8, -11, 92}, {-12, -6, 84}, {-11, -6, 84}},
	 {{-6, -14, 93}, {-8, -12, 85}, {-7, -11, 85}}
	 },
	{
	 {{-1, -7, 142}, {-1, -7, 142}, {-1, -7, 142}},
	 {{-1, -7, 142}, {-1, -7, 142}, {-1, -7, 142}},
	 {{-2, -8, 143}, {-2, -8, 143}, {-2, -8, 143}},
	 {{-3, -5, 144}, {-3, -5, 144}, {-3, -5, 144}},
	 {{-3, -5, 144}, {-3, -5, 144}, {-3, -5, 144}},
	 {{-3, -5, 144}, {-3, -5, 144}, {-3, -5, 144}},
	 {{-8, -10, 145}, {-8, -10, 145}, {-8, -10, 145}},
	 {{-8, -10, 145}, {-8, -10, 145}, {-8, -10, 145}}
	 }
};

const OffsetTable cMuzzleOffset[GUNPIC_COUNT] = {
	{
	 {2, 0},
	 {7, 2},
	 {13, 2},
	 {7, 6},
	 {2, 6},
	 {2, 6},
	 {0, 2},
	 {2, 2}
	 }
};


const OffsetTable cBodyOffset[BODY_COUNT] = {
	{
	 {-8, -11},
	 {-8, -11},
	 {-6, -11},
	 {-8, -11},
	 {-8, -11},
	 {-8, -11},
	 {-5, -11},
	 {-5, -11}
	 },
	{
	 {-8, -11},
	 {-8, -11},
	 {-6, -11},
	 {-8, -11},
	 {-8, -11},
	 {-8, -11},
	 {-5, -11},
	 {-5, -11}
	 }
};

const OffsetTable cNeckOffset[BODY_COUNT] = {
	{
	 {0, -11},
	 {0, -11},
	 {0, -11},
	 {0, -11},
	 {0, -11},
	 {0, -11},
	 {1, -11},
	 {1, -11}
	 },
	{
	 {0, -11},
	 {0, -11},
	 {0, -11},
	 {0, -11},
	 {0, -11},
	 {0, -11},
	 {1, -11},
	 {1, -11}
	 }
};

const OffsetTable cGunHandOffset[BODY_COUNT] = {
	{
	 {6, -6},
	 {6, -6},
	 {2, -4},
	 {-7, -6},
	 {-7, -6},
	 {-7, -6},
	 {-3, -7},
	 {-3, -7}
	 },
	{
	 {6, -6},
	 {6, -6},
	 {2, -4},
	 {-7, -6},
	 {-7, -6},
	 {-7, -6},
	 {-3, -7},
	 {-3, -7}
	 }
};

const OffsetTable cHeadOffset[FACE_COUNT] = {
	{
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7}
	 },
	{
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7}
	 },
	{
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7}
	 },
	{
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7}
	 },
	{
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7}
	 },
	{
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7}
	 },
	{
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7}
	 },
	{
	 {-5, -9},
	 {-5, -9},
	 {-5, -9},
	 {-5, -9},
	 {-5, -9},
	 {-5, -9},
	 {-5, -9},
	 {-5, -9}
	 },
	{
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7}
	 },
	{
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7}
	 },
	{
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7}
	 },
	{
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7}
	 },
	{
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7}
	 },
	{
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7}
	 },
	{
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7},
	 {-5, -7}
	 },
	{
	 {-5, -5},
	 {-5, -5},
	 {-5, -5},
	 {-5, -5},
	 {-5, -5},
	 {-5, -5},
	 {-5, -5},
	 {-5, -5}
	 },
	{
	 {-3, -7},
	 {-4, -7},
	 {-7, -7},
	 {-4, -8},
	 {-3, -8},
	 {-4, -8},
	 {-5, -7},
	 {-4, -7}
	 }
};

const TOffsetPic cGrenadePics[4] = {
	{-3, -3, 34},
	{-3, -3, 35},
	{-3, -3, 36},
	{-3, -3, 37}
};

const TOffsetPic cFlamePics[4] = {
	{-5, -8, 38},
	{-7, -8, 39},
	{-5, -8, 40},
	{-6, -8, 41}
};

const TOffsetPic cFireBallPics[FIREBALL_MAX] = {
	{-9, -9, 47},
	{-9, -9, 48},
	{-9, -9, 49},
	{-9, -9, 50},
	{-9, -9, 51},
	{-12, -10, 52},
	{-12, -10, 53},
	{-11, -10, 54},
	{-12, -10, 55},
	{-12, -10, 56},
	{-12, -10, 57},
	{-12, -10, 58},
	{-12, -10, 59},
	{-11, -9, 60},
	{-10, -8, 61},
	{-10, -8, 62}
};

const TOffsetPic cBeamPics[DIRECTION_COUNT] = {
	{-1, -3, 43},
	{-2, -2, 46},
	{-3, -1, 44},
	{-2, -2, 45},
	{-1, -3, 43},
	{-2, -2, 46},
	{-3, -1, 44},
	{-2, -2, 45}
};

const TOffsetPic cBrightBeamPics[DIRECTION_COUNT] = {
	{-1, -3, 362},
	{-2, -2, 365},
	{-3, -1, 363},
	{-2, -2, 364},
	{-1, -3, 362},
	{-2, -2, 365},
	{-3, -1, 363},
	{-2, -2, 364}
};

const int cWallPics[WALL_STYLE_COUNT][WALL_TYPES] = {
	{6, 108, 107, 95, 102, 97, 96, 104,	// "Steel"
	 103, 101, 100, 98, 105, 99, 106, 94},

	{157, 160, 159, 155, 157, 154, 156, 160,	// Stone/bricks
	 159, 154, 156, 153, 158, 155, 158, 153},

	{181, 188, 187, 174, 182, 176, 175, 184,	// Red ornamental
	 183, 180, 179, 177, 185, 178, 186, 173},

	{210, 217, 216, 203, 211, 205, 204, 213,	// Grey/wood ornamental
	 212, 209, 208, 206, 214, 207, 215, 202},

	{326, 333, 332, 319, 327, 321, 320, 329,	// Rough stone
	 328, 325, 324, 322, 330, 323, 331, 318},

	{P2 + 60, P2 + 67, P2 + 66, P2 + 53, P2 + 61, P2 + 55, P2 + 54,
	 P2 + 63,
	 P2 + 62, P2 + 59, P2 + 58, P2 + 56, P2 + 64, P2 + 57, P2 + 65,
	 P2 + 52},	// Plasteel

	{P2 + 76, P2 + 83, P2 + 82, P2 + 69, P2 + 77, P2 + 71, P2 + 70,
	 P2 + 79,
	 P2 + 78, P2 + 75, P2 + 74, P2 + 72, P2 + 80, P2 + 73, P2 + 81,
	 P2 + 68}	// Granite
};

const int cFloorPics[FLOOR_STYLE_COUNT][FLOOR_TYPES] = {
	{2, 1, 165, 166},	// Green grid

	{152, 151, 167, 168},	// Purple plates

	{170, 169, 171, 172},	// Dirt

	{199, 198, 200, 201},	// Plain blue

	{253, 254, 255, 256},	// Brown stripes

	{257, 258, 259, 260},	// Gray squares

	{311, 310, 312, 313},	// Pebbles

	{315, 314, 316, 317},	// Wood

	{384, 383, 383, 383},	// White

	{P2 + 46, P2 + 45, P2 + 45, P2 + 45}	// Grid
};

const int cRoomPics[ROOMFLOOR_COUNT][ROOMFLOOR_TYPES] = {
	{P2 + 85, P2 + 84},
	{P2 + 87, P2 + 86},
	{P2 + 89, P2 + 88},
	{P2 + 91, P2 + 90},
	{P2 + 93, P2 + 92},
	{P2 + 95, P2 + 94},
	{P2 + 97, P2 + 96},
	{P2 + 99, P2 + 98},
	{P2 + 101, P2 + 100},
	{P2 + 103, P2 + 102},
	{P2 + 105, P2 + 104}
};

const struct Offset cWallOffset = { 0, -12 };


const TOffsetPic cGeneralPics[OFSPIC_COUNT] = {
	{-1, -1, PIC_UZIBULLET},
	{0, 3, 110},		// Note: offset relative to _wall_ upper left!!
	{-4, -4, 111},
	{-8, -16, 189},
	{-8, -16, 190},
	{-8, -15, 191},
	{-8, -7, 193},
	{-8, -6, 192},
	{-8, -16, 194},
	{-8, -15, 195},
	{-8, -5, 196},
	{-8, -7, 197},
	{-6, -6, 218},
	{-3, -6, 219},
	{-3, -6, 220},
	{-3, -6, 221},
	{3, 1, 251},		// Note: offset relative to _wall_ upper left!!
	{3, 1, 252},		// Note: offset relative to _wall_ upper left!!
	{3, 1, 279},		// Red door: v + h + key-card
	{0, 3, 280},
	{-4, -2, 281},
	{3, 1, 282},		// Blue door: v + h + key-card
	{0, 3, 283},
	{-4, -2, 284},
	{3, 1, 285},		// Green door: v + h + key-card
	{0, 3, 286},
	{-4, -2, 287},
	{3, 1, 288},		// Yellow door: v + h + key-card
	{0, 3, 289},
	{-4, -2, 290},
	{-8, -18, 291},
	{-6, -4, 292},
	{-8, -17, 293},
	{-7, -6, 294},
	{-7, -15, 295},
	{-6, -5, 296},
	{-7, -17, 297},
	{-5, -4, 298},
	{-8, -12, 299},
	{-9, -6, 300},
	{-4, -4, 301},
	{-2, -2, 340},
	{0, 3, 341},
	{3, 1, 343},
	{3, 1, 344},
	{3, 1, 345},		// Red door #2: v + h + key-card
	{0, 3, 346},
	{-5, -3, 356},
	{3, 1, 347},		// Blue door #2: v + h + key-card
	{0, 3, 348},
	{-5, -3, 355},
	{3, 1, 349},		// Green door #2: v + h + key-card
	{0, 3, 350},
	{-5, -3, 354},
	{3, 1, 351},		// Yellow door #2: v + h + key-card
	{0, 3, 352},
	{-5, -3, 353},
	{-8, -16, 337},
	{-8, -16, 338},
	{-8, -7, 193},		// Wrecked barrel: same as #6 above!
	{-8, -15, 336},
	{-8, -15, 335},
	{-8, -15, 334},
	{-8, -6, 339},
	{-8, -11, 357},
	{-8, -17, 358},
	{-8, -17, 359},
	{-8, -23, 360},
	{-8, -17, 361},
	{0, 0, 366},
	{0, 11, 367},
	{0, 22, 368},
	{13, 0, 369},
	{13, 11, 370},
	{13, 22, 371},
	{26, 0, 372},
	{26, 11, 373},
	{26, 22, 374},
	{-3, -17, 377},
	{-13, -24, 386},	// Tree
	{-3, -3, 388},
	{-5, -8, 389},
	{-8, -15, P2 + 47},	// Bookshelf
	{-8, -10, P2 + 48},	// Wooden box
	{-9, -24, P2 + 49},	// Rocket
	{-8, -11, P2 + 50},	// Table + cloth
	{-8, -11, P2 + 51},	// Steel table
	{-11, -6, P2 + 106},	// Blueprint
	{-7, -4, P2 + 107},	// CD
	{-7, -12, P2 + 108},	// Bag
	{-7, -13, P2 + 109},	// Hologram
	{-5, -9, P2 + 110},	// Bottle
	{-5, -6, P2 + 111},	// Radio
	{-8, -5, P2 + 112},	// Circuit board
	{-6, -5, P2 + 113},	// Paper
	{-9, -6, P2 + 114},	// Burn marks
	{-13, -24, P2 + 115},	// Autumn tree
	{-8, -7, P2 + 116},	//  ...remains
	{-13, -24, P2 + 117},	// Green tree
	{-10, -8, P2 + 118},	//  ...remains
	{-8, -12, P2 + 119},	// Alien egg
	{-9, -5, P2 + 120},	//  ...remains
	{-8, -5, P2 + 121},	// Naked tree remains
	{-5, -12, 163},		// Blood-stain (on wall)
	{3, 1, P2 + 134},	// Red door #3: v + h + key
	{0, 3, P2 + 135},
	{-5, -2, P2 + 136},
	{3, 1, P2 + 137},	// Blue door #3: v + h + key
	{0, 3, P2 + 138},
	{-5, -2, P2 + 139},
	{3, 1, P2 + 140},	// Green door #3: v + h + key
	{0, 3, P2 + 141},
	{-5, -2, P2 + 142},
	{3, 1, P2 + 143},	// Yellow door #3: v + h + key
	{0, 3, P2 + 144},
	{-5, -2, P2 + 145},
	{3, 1, P2 + 146},	// Door #3: v + h
	{0, 3, P2 + 147},
	{3, 1, P2 + 149},	// Red door #4: v + h + key
	{0, 3, P2 + 150},
	{-5, -2, P2 + 151},
	{3, 1, P2 + 152},	// Blue door #4: v + h + key
	{0, 3, P2 + 153},
	{-5, -2, P2 + 154},
	{3, 1, P2 + 155},	// Green door #4: v + h + key
	{0, 3, P2 + 156},
	{-5, -2, P2 + 157},
	{3, 1, P2 + 158},	// Yellow door #4: v + h + key
	{0, 3, P2 + 159},
	{-5, -2, P2 + 160},
	{3, 1, P2 + 161},	// Door #4: v + h
	{0, 3, P2 + 162},
	{-4, -10, P2 + 131},	// Skull (on wall)
	{-6, -4, P2 + 132},	// Yeuch!
	{-4, -11, P2 + 133},	// Bullet marks
	{-5, -3, 3},		// Blood-stain
	{-4, -2, P2 + 164},	// Skull
	{-5, -9, P2 + 165},	// Scratch on wall
	{-3, -15, P2 + 166},	// Alien yellowish stuff
	{-4, -11, P2 + 167},	// Alien green stuff
	{-4, -3, P2 + 168}	// Ditto on the ground
};

const TOffsetPic cDeathPics[DEATH_MAX] = {
	{-8, -18, 112},
	{-8, -18, 113},
	{-8, -18, 114},
	{-8, -18, 115},
	{-8, -18, 116},
	{-8, -18, 117},
	{-8, -18, 118},
	{-8, -18, 119},
	{-8, -18, 120}
};

const TOffsetPic cBloodPics[BLOOD_MAX] = {
	{-5, -3, 3},
	{-5, -3, 161},
	{-5, -3, 162}
};
