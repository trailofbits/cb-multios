/*
 * Copyright (c) 2016 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#pragma once

#include "vector.h"

unsigned int g_prng(void);

struct Edge
{
    double weight;
    double delta;
};

class Neuron
{
  public:
    Neuron() {};
    Neuron(unsigned int n, unsigned int outLen);
    void setValue(double v) { m_value = v; }
    double getValue() { return m_value; }
    void feedForward(vector<Neuron> &prev);
    void computeOutGrad(double target);
    void computeHiddenGrad(vector<Neuron> &next);
    void updateWeights(vector<Neuron> &prev);

    double sigmoid(double x);
    double dsigmoid(double x);

  private:
    static double k_eta;
    static double k_alpha;
    double m_value;
    double m_gradient;
    unsigned int m_n;
    vector<Edge> m_weights;
};
