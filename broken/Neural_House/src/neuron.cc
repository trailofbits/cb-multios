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
#include "neuron.h"
#include <cstdio.h>

double Neuron::k_eta = 0.20;
double Neuron::k_alpha = 0.50;

Neuron::Neuron(unsigned int n, unsigned int outLen)
{
  unsigned int i;
  m_n = n;
  for (i = 0; i < outLen; ++i)
  {
    m_weights.push_back(Edge());
    double w = int(g_prng() & 0xFFFF) * 1.0 / double(0xFFFF);
    m_weights.back().weight = w;
  }
}

double Neuron::sigmoid(double x)
{
  double abs_x = (x < 0) ? -x : x;
  return (x / (1 + abs_x));
}

double Neuron::dsigmoid(double x)
{
  double abs_x = (x < 0) ? -x : x;
  return (1 / ((abs_x + 1) * (abs_x + 1)));
}

void Neuron::feedForward(vector<Neuron> &prev)
{
  unsigned int i;
  double val = 0.0;
  for (i = 0; i < prev.size(); ++i)
    val += prev[i].getValue() * prev[i].m_weights[m_n].weight;
  m_value = sigmoid(val);
}

void Neuron::computeOutGrad(double target)
{
  m_gradient = (target - m_value) * dsigmoid(m_value);
}

void Neuron::computeHiddenGrad(vector<Neuron> &next)
{
  unsigned int i;
  double val = 0.0;
  for (i = 0; i < next.size() - 1; ++i)
    val += next[i].m_gradient * m_weights[i].weight;
  m_gradient = val * dsigmoid(m_value);
}

void Neuron::updateWeights(vector<Neuron> &prev)
{
  double old, tmp;
  unsigned int i;
  for (i = 0; i < prev.size(); ++i)
  {
    old = prev[i].m_weights[m_n].delta;
    tmp = k_eta * prev[i].getValue() * m_gradient + k_alpha * old;
    prev[i].m_weights[m_n].delta = tmp;
    prev[i].m_weights[m_n].weight += tmp;
  }
}
