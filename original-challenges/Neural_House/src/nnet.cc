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
#include "nnet.h"

NeuralNet::NeuralNet(vector<unsigned int> &t)
{
  unsigned int i, j;
  for (i = 0; i < t.size(); ++i)
  {
    m_layers.push_back(Layer());
    for (j = 0; j <= t[i]; ++j)
      m_layers.back().push_back(Neuron(j, i == t.size() - 1 ? 0 : t[i+1]));
    m_layers.back().back().setValue(BIAS_VAL);
  }
}

void NeuralNet::feedForward(vector<double> &in)
{
  unsigned int i, j;
  Layer &inputLayer = m_layers.front();
  for (i = 0; i < in.size(); ++i)
    inputLayer[i].setValue(in[i]);
  for (i = 1; i < m_layers.size(); ++i)
  {
    Layer &prev = m_layers[i - 1];
    for (j = 0; j < m_layers[i].size() - 1; ++j)
      m_layers[i][j].feedForward(prev);
  }
}

void NeuralNet::backProp(vector<double> &target)
{
  unsigned int i, j;
  Layer &outputLayer = m_layers.back();
  for (i = 0; i < outputLayer.size() - 1; ++i)
    outputLayer[i].computeOutGrad(target[i]);
  for (i = m_layers.size() - 2; i > 0; --i)
  {
    Layer &hiddenLayer = m_layers[i];
    Layer &next = m_layers[i+1];
    for (j = 0; j < hiddenLayer.size(); ++j)
      hiddenLayer[j].computeHiddenGrad(next);
  }
  for (i = m_layers.size() - 1; i > 0; --i)
  {
    Layer &l = m_layers[i];
    Layer &prev = m_layers[i-1];
    for (j = 0; j < l.size() - 1; ++j)
      l[j].updateWeights(prev);
  }
}

void NeuralNet::getOutput(vector<double> &out)
{
  unsigned int i;
  out.clear();
  Layer &outputLayer = m_layers.back();
  for (i = 0; i < outputLayer.size() - 1; ++i)
    out.push_back(outputLayer[i].getValue());
}
