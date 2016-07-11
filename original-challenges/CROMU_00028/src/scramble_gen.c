/*

Author: Bryce Kerley <bk@cromulence.co>

Copyright (c) 2014-2015 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

// Generated at 2015-01-25 15:11:01 -0500
#include "scramble_gen.h"

scramble_item phase_0(scramble_item i, scramble_item j) {
  j.f = log2(i.f * j.f * 1.8725730085700691);
  j.f = tan(i.f * j.f * 2.9105350093912783);
  j.f = cos(i.f * j.f * 0.5371365912333178);
  j.f = tan(i.f * j.f * 2.1313461122050468);
  i.i = i.i ^ (j.i << 1) ^ 0x278197da;
  i.i = i.i ^ (j.i >> 8) ^ 0x1a0181e9;
  i.i = i.i ^ (j.i << 12);
  i.i = i.i ^ (j.i >> 6);
  j.f = log2(i.f * j.f * 2.066331874014252);
  j.f = tan(i.f * j.f * 1.9695372951778336);
  j.f = cos(i.f * j.f * 0.18822584701410222);
  j.f = log2(i.f * j.f * 2.8415621226494956);
  i.i = i.i ^ (j.i << 2);
  i.i = i.i ^ (j.i << 13);
  i.i = i.i ^ (j.i >> 5) ^ 0x384848cd;
  i.i = i.i ^ (j.i >> 7);
  j.f = tan(i.f * j.f * 3.101665985668325);
  j.f = log2(i.f * j.f * 2.4520129336554053);
  j.f = tan(i.f * j.f * 2.265559877426349);
  j.f = tan(i.f * j.f * 3.0635451654412753);
  i.i = i.i ^ (j.i >> 8) ^ 0x35fd9e68;
  i.i = i.i ^ (j.i << 7) ^ 0x276f42fb;
  i.i = i.i ^ (j.i >> 7) ^ 0x32f0ddde;
  i.i = i.i ^ (j.i >> 6);
  j.f = cos(i.f * j.f * 2.2742663034678294);
  j.f = tan(i.f * j.f * 0.5243114624985246);
  j.f = cos(i.f * j.f * 0.14531023322245268);
  j.f = log2(i.f * j.f * 0.6525093569155739);
  i.i = i.i ^ (j.i << 5);
  i.i = i.i ^ (j.i << 4);
  i.i = i.i ^ (j.i >> 12) ^ 0xf65e277;
  i.i = i.i ^ (j.i >> 9) ^ 0x2e7cdca3;
  return i;
}

scramble_item phase_1(scramble_item i, scramble_item j) {
  j.f = tan(i.f * j.f * 0.8951928480997888);
  j.f = sin(i.f * j.f * 1.4067434105099248);
  j.f = cos(i.f * j.f * 2.26763385535229);
  j.f = sin(i.f * j.f * 0.6836884652647081);
  i.i = i.i ^ (j.i >> 6) ^ 0x1a2d585b;
  i.i = i.i ^ (j.i >> 2) ^ 0xe24f7b7;
  i.i = i.i ^ (j.i << 15);
  i.i = i.i ^ (j.i >> 11);
  j.f = log2(i.f * j.f * 2.9921967343222327);
  j.f = tan(i.f * j.f * 0.36244198441762676);
  j.f = log2(i.f * j.f * 1.8181921033193849);
  j.f = cos(i.f * j.f * 0.8312694743487108);
  i.i = i.i ^ (j.i >> 6);
  i.i = i.i ^ (j.i << 12);
  i.i = i.i ^ (j.i >> 9);
  i.i = i.i ^ (j.i >> 2);
  j.f = cos(i.f * j.f * 3.077262507519771);
  j.f = tan(i.f * j.f * 2.21236946467746);
  j.f = sin(i.f * j.f * 0.14376129586163638);
  j.f = log2(i.f * j.f * 0.7061368634812194);
  i.i = i.i ^ (j.i << 14) ^ 0x13891e63;
  i.i = i.i ^ (j.i << 11);
  i.i = i.i ^ (j.i >> 1);
  i.i = i.i ^ (j.i >> 10) ^ 0xbb3b303;
  j.f = sin(i.f * j.f * 1.805516719652539);
  j.f = sin(i.f * j.f * 1.096858338982223);
  j.f = cos(i.f * j.f * 2.1404691770911786);
  j.f = log2(i.f * j.f * 2.8502571130421472);
  i.i = i.i ^ (j.i >> 14);
  i.i = i.i ^ (j.i << 3);
  i.i = i.i ^ (j.i << 9);
  i.i = i.i ^ (j.i >> 1);
  return i;
}

scramble_item phase_2(scramble_item i, scramble_item j) {
  j.f = sin(i.f * j.f * 2.648975931219137);
  j.f = cos(i.f * j.f * 2.1009826379524017);
  j.f = cos(i.f * j.f * 2.663949502499673);
  j.f = sin(i.f * j.f * 1.8695817966063852);
  i.i = i.i ^ (j.i << 8);
  i.i = i.i ^ (j.i << 7);
  i.i = i.i ^ (j.i << 10);
  i.i = i.i ^ (j.i >> 14);
  j.f = cos(i.f * j.f * 1.5517394417671253);
  j.f = tan(i.f * j.f * 2.1488659525817777);
  j.f = sin(i.f * j.f * 0.7115086055511646);
  j.f = tan(i.f * j.f * 1.955036170030666);
  i.i = i.i ^ (j.i >> 8);
  i.i = i.i ^ (j.i << 5);
  i.i = i.i ^ (j.i << 9);
  i.i = i.i ^ (j.i >> 6);
  j.f = cos(i.f * j.f * 2.7384484177393915);
  j.f = cos(i.f * j.f * 0.9044550627917695);
  j.f = cos(i.f * j.f * 0.29168743347916326);
  j.f = sin(i.f * j.f * 3.1609600860847182);
  i.i = i.i ^ (j.i >> 13);
  i.i = i.i ^ (j.i >> 10) ^ 0x2eda46b4;
  i.i = i.i ^ (j.i << 11) ^ 0x692e8da;
  i.i = i.i ^ (j.i >> 5) ^ 0x22551df8;
  j.f = tan(i.f * j.f * 1.5211979662024404);
  j.f = log2(i.f * j.f * 1.6279389090188616);
  j.f = tan(i.f * j.f * 0.7692843012594827);
  j.f = log2(i.f * j.f * 1.734284555432186);
  i.i = i.i ^ (j.i << 11);
  i.i = i.i ^ (j.i >> 1);
  i.i = i.i ^ (j.i << 5) ^ 0x37daec81;
  i.i = i.i ^ (j.i << 8) ^ 0x210f83bb;
  return i;
}

scramble_item phase_3(scramble_item i, scramble_item j) {
  j.f = sin(i.f * j.f * 3.031871027095739);
  j.f = sin(i.f * j.f * 3.0931806625902523);
  j.f = cos(i.f * j.f * 2.3748923372681134);
  j.f = sin(i.f * j.f * 2.4520549307432855);
  i.i = i.i ^ (j.i >> 5) ^ 0x2a3d856c;
  i.i = i.i ^ (j.i << 15) ^ 0x1e10a214;
  i.i = i.i ^ (j.i << 11);
  i.i = i.i ^ (j.i << 15) ^ 0x26948e92;
  j.f = cos(i.f * j.f * 0.4663470715310989);
  j.f = cos(i.f * j.f * 2.8425674031134167);
  j.f = tan(i.f * j.f * 2.3307605024561893);
  j.f = log2(i.f * j.f * 1.5662878182800448);
  i.i = i.i ^ (j.i << 14);
  i.i = i.i ^ (j.i >> 4);
  i.i = i.i ^ (j.i >> 7) ^ 0x3b14a6c3;
  i.i = i.i ^ (j.i << 10);
  j.f = cos(i.f * j.f * 2.019827635143402);
  j.f = sin(i.f * j.f * 0.2514015316128835);
  j.f = log2(i.f * j.f * 2.5515184132107365);
  j.f = log2(i.f * j.f * 2.2986604030684994);
  i.i = i.i ^ (j.i << 13);
  i.i = i.i ^ (j.i >> 5) ^ 0x16efb5b4;
  i.i = i.i ^ (j.i << 7) ^ 0x2fca1d9e;
  i.i = i.i ^ (j.i << 10) ^ 0x15ba1ac2;
  j.f = cos(i.f * j.f * 1.681958200244821);
  j.f = sin(i.f * j.f * 2.002220571330305);
  j.f = tan(i.f * j.f * 0.29644532411798474);
  j.f = log2(i.f * j.f * 1.3741562278258521);
  i.i = i.i ^ (j.i >> 3) ^ 0x2f9d6950;
  i.i = i.i ^ (j.i >> 11);
  i.i = i.i ^ (j.i << 13) ^ 0x4a5aba8;
  i.i = i.i ^ (j.i << 3);
  return i;
}

scramble_item phase_4(scramble_item i, scramble_item j) {
  j.f = tan(i.f * j.f * 3.1317598665029824);
  j.f = sin(i.f * j.f * 0.7218053275121088);
  j.f = tan(i.f * j.f * 1.379561907159936);
  j.f = tan(i.f * j.f * 2.1140006573459127);
  i.i = i.i ^ (j.i >> 9);
  i.i = i.i ^ (j.i << 7) ^ 0x1c4a2401;
  i.i = i.i ^ (j.i >> 7) ^ 0x2712e2b5;
  i.i = i.i ^ (j.i >> 12);
  j.f = tan(i.f * j.f * 1.1322992511533552);
  j.f = tan(i.f * j.f * 1.001076013285175);
  j.f = log2(i.f * j.f * 1.1911257815425058);
  j.f = log2(i.f * j.f * 1.418913515375019);
  i.i = i.i ^ (j.i << 2);
  i.i = i.i ^ (j.i << 2) ^ 0x2ba33ef1;
  i.i = i.i ^ (j.i << 10) ^ 0x3cef4cf9;
  i.i = i.i ^ (j.i << 7);
  j.f = cos(i.f * j.f * 1.3793922789726878);
  j.f = log2(i.f * j.f * 2.974219040054912);
  j.f = tan(i.f * j.f * 0.12255822998940166);
  j.f = tan(i.f * j.f * 2.025885584262783);
  i.i = i.i ^ (j.i >> 14);
  i.i = i.i ^ (j.i << 2);
  i.i = i.i ^ (j.i << 3);
  i.i = i.i ^ (j.i << 9);
  j.f = cos(i.f * j.f * 0.36512139999258564);
  j.f = sin(i.f * j.f * 0.34363178404342487);
  j.f = sin(i.f * j.f * 0.8317669306996482);
  j.f = cos(i.f * j.f * 0.4579059129810992);
  i.i = i.i ^ (j.i << 7);
  i.i = i.i ^ (j.i >> 12) ^ 0xcbc997e;
  i.i = i.i ^ (j.i << 2) ^ 0x8123bcf;
  i.i = i.i ^ (j.i << 5) ^ 0x2d2ec851;
  return i;
}

scramble_item phase_5(scramble_item i, scramble_item j) {
  j.f = sin(i.f * j.f * 2.2618385737043707);
  j.f = cos(i.f * j.f * 0.3361406796559725);
  j.f = log2(i.f * j.f * 0.460105286159878);
  j.f = log2(i.f * j.f * 1.4261418727245736);
  i.i = i.i ^ (j.i >> 4) ^ 0x856bd5f;
  i.i = i.i ^ (j.i >> 12);
  i.i = i.i ^ (j.i << 10) ^ 0x2cc2c3de;
  i.i = i.i ^ (j.i << 9);
  j.f = tan(i.f * j.f * 1.0565316651956134);
  j.f = tan(i.f * j.f * 2.7382934205819045);
  j.f = tan(i.f * j.f * 1.7032432946201679);
  j.f = tan(i.f * j.f * 2.8872884946104516);
  i.i = i.i ^ (j.i << 2);
  i.i = i.i ^ (j.i >> 8) ^ 0x51d581b;
  i.i = i.i ^ (j.i >> 14);
  i.i = i.i ^ (j.i >> 2);
  j.f = sin(i.f * j.f * 3.226410552690949);
  j.f = log2(i.f * j.f * 0.9572991783113401);
  j.f = sin(i.f * j.f * 1.4382645233406335);
  j.f = cos(i.f * j.f * 2.25634271551903);
  i.i = i.i ^ (j.i << 15);
  i.i = i.i ^ (j.i >> 3);
  i.i = i.i ^ (j.i >> 12) ^ 0x57ee8b1;
  i.i = i.i ^ (j.i >> 12) ^ 0x265a587d;
  j.f = sin(i.f * j.f * 2.779213821531882);
  j.f = log2(i.f * j.f * 1.5366179720927262);
  j.f = sin(i.f * j.f * 2.7219866971740383);
  j.f = cos(i.f * j.f * 0.4570918121325992);
  i.i = i.i ^ (j.i << 14);
  i.i = i.i ^ (j.i >> 10);
  i.i = i.i ^ (j.i << 2);
  i.i = i.i ^ (j.i << 9) ^ 0x3e408913;
  return i;
}

scramble_item phase_6(scramble_item i, scramble_item j) {
  j.f = sin(i.f * j.f * 1.5071431053764);
  j.f = log2(i.f * j.f * 0.871900227590951);
  j.f = sin(i.f * j.f * 1.0307915698091092);
  j.f = sin(i.f * j.f * 0.29722369906790636);
  i.i = i.i ^ (j.i >> 13);
  i.i = i.i ^ (j.i << 3) ^ 0x218ad825;
  i.i = i.i ^ (j.i << 9);
  i.i = i.i ^ (j.i << 14) ^ 0xfc4e148;
  j.f = log2(i.f * j.f * 0.9867836186253758);
  j.f = log2(i.f * j.f * 1.1093453375868205);
  j.f = log2(i.f * j.f * 2.6520901363844644);
  j.f = sin(i.f * j.f * 0.2535750840452218);
  i.i = i.i ^ (j.i << 7);
  i.i = i.i ^ (j.i << 6) ^ 0x19bc7d14;
  i.i = i.i ^ (j.i << 4) ^ 0x1fba2ba3;
  i.i = i.i ^ (j.i << 10);
  j.f = sin(i.f * j.f * 2.537426508047054);
  j.f = sin(i.f * j.f * 0.34132486155163155);
  j.f = log2(i.f * j.f * 0.1143404439399488);
  j.f = log2(i.f * j.f * 1.9033504698417862);
  i.i = i.i ^ (j.i >> 8);
  i.i = i.i ^ (j.i >> 8) ^ 0x2f7f3c15;
  i.i = i.i ^ (j.i >> 5) ^ 0x12a2771c;
  i.i = i.i ^ (j.i << 11);
  j.f = sin(i.f * j.f * 0.7817392620545068);
  j.f = log2(i.f * j.f * 1.1114826738576067);
  j.f = sin(i.f * j.f * 1.1050307318997528);
  j.f = sin(i.f * j.f * 1.2326463871829376);
  i.i = i.i ^ (j.i << 4) ^ 0x2259265b;
  i.i = i.i ^ (j.i << 10) ^ 0x21288f50;
  i.i = i.i ^ (j.i << 10);
  i.i = i.i ^ (j.i >> 8);
  return i;
}

scramble_item phase_7(scramble_item i, scramble_item j) {
  j.f = tan(i.f * j.f * 0.34586086055073345);
  j.f = tan(i.f * j.f * 0.17447386509416535);
  j.f = cos(i.f * j.f * 0.8781802005265427);
  j.f = log2(i.f * j.f * 0.12715105810423036);
  i.i = i.i ^ (j.i << 8) ^ 0x2fc8f840;
  i.i = i.i ^ (j.i << 11) ^ 0x2a04c399;
  i.i = i.i ^ (j.i << 12);
  i.i = i.i ^ (j.i << 12) ^ 0x3ea8c7ba;
  j.f = sin(i.f * j.f * 0.2852791636530583);
  j.f = cos(i.f * j.f * 2.050003827445473);
  j.f = sin(i.f * j.f * 2.4571243702995518);
  j.f = log2(i.f * j.f * 1.5003659993867253);
  i.i = i.i ^ (j.i << 9) ^ 0x2ab9ce21;
  i.i = i.i ^ (j.i >> 5);
  i.i = i.i ^ (j.i >> 5);
  i.i = i.i ^ (j.i << 4) ^ 0x3d0ce0a0;
  j.f = log2(i.f * j.f * 1.5479611829059121);
  j.f = cos(i.f * j.f * 0.9856877724378321);
  j.f = cos(i.f * j.f * 1.2720302660390255);
  j.f = cos(i.f * j.f * 2.5764586227048567);
  i.i = i.i ^ (j.i >> 4) ^ 0x1a8adc84;
  i.i = i.i ^ (j.i << 10);
  i.i = i.i ^ (j.i >> 7);
  i.i = i.i ^ (j.i << 5);
  j.f = tan(i.f * j.f * 3.15715834422692);
  j.f = log2(i.f * j.f * 1.5025494854602364);
  j.f = cos(i.f * j.f * 0.22291847981018825);
  j.f = log2(i.f * j.f * 2.0053172340349668);
  i.i = i.i ^ (j.i << 1);
  i.i = i.i ^ (j.i << 12);
  i.i = i.i ^ (j.i << 8);
  i.i = i.i ^ (j.i << 5);
  return i;
}
