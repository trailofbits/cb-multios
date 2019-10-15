#!/usr/bin/env python

from generator.actions import Actions
import struct
import random

g_state = 0

def g_prng():
  global g_state
  g_state = g_state * 1103515247 + 13579
  return (g_state / 65536) % 32768

def init_g_state(secret):
  global g_state
  g_state = secret * 1103515247 + 13579

class Edge(object):
  def __init__(self, w, d):
    self.weight = w
    self.delta = d

class Neuron(object):
  def __init__(self, n, outlen):
    self.eta = 0.20
    self.alpha = 0.50
    self.value = 0.0
    self.gradient = 0.0
    self.n = n
    self.weights = list()
    for i in xrange(outlen):
      w = (g_prng() & 0xFFFF) * 1.0 / 0xFFFF
      e = Edge(w, 0)
      self.weights.append(e)

  def feed_forward(self, prev):
    val = 0.0
    for i in xrange(len(prev)):\
        val += prev[i].value * prev[i].weights[self.n].weight
    self.value = self.sigmoid(val)

  def compute_out_grad(self, target):
    self.gradient = (target - self.value) * self.dsigmoid(self.value)

  def compute_hidden_grad(self, nxt):
    val = 0.0
    for i in xrange(len(nxt) - 1):
      val += nxt[i].gradient * self.weights[i].weight
    self.gradient = val * self.dsigmoid(self.value)

  def update_weights(self, prev):
    for i in xrange(len(prev)):
      old = prev[i].weights[self.n].delta
      tmp = self.eta * prev[i].value * self.gradient + self.alpha * old
      prev[i].weights[self.n].delta = tmp
      prev[i].weights[self.n].weight += tmp

  def sigmoid(self, x):
    return x / (1 + abs(x))

  def dsigmoid(self, x):
    return 1 / ((abs(x) + 1) * (abs(x) + 1))

class NNet(object):
  def __init__(self, t):
    self.layers = list()
    for i in xrange(len(t)):
      nl = list()
      self.layers.append(nl)
      for j in xrange(t[i] + 1):
        nl.append(Neuron(j, 0 if i == len(t) - 1 else t[i+1]))
      nl[-1].value = 1.0

  def feed_forward(self, inp):
    layer = self.layers[0]
    for i in xrange(len(inp)):
      layer[i].value = inp[i]
    for i in xrange(1, len(self.layers)):
      prev = self.layers[i - 1]
      for j in xrange(len(self.layers[i]) - 1):
        self.layers[i][j].feed_forward(prev)

  def back_prop(self, target):
    out_layer = self.layers[-1]
    for i in xrange(len(out_layer) - 1):
      out_layer[i].compute_out_grad(target[i])
    for i in xrange(len(self.layers) - 2, 0, -1):
      hidden_layer = self.layers[i]
      nxt = self.layers[i+1]
      for j in xrange(len(hidden_layer)):
        hidden_layer[j].compute_hidden_grad(nxt)
    for i in xrange(len(self.layers) - 1, 0, -1):
      l = self.layers[i]
      prev = self.layers[i-1]
      for j in xrange(len(l) - 1):
        l[j].update_weights(prev)

  def get_output(self):
    out = list()
    out_layer = self.layers[-1]
    for i in xrange(len(out_layer)):
      out.append(out_layer[i].value)
    return out

class NeuralHouse(Actions):

  def start_training(self):
    num_samples = random.randint(500, 1000)
    if self.pov_mode:
      num_samples = 1000
    self.write(struct.pack('<I', num_samples))
    s = ''
    if self.pov_mode:
      self.num_beds = random.randint(1, 20)
      self.num_baths = random.randint(1, 25)
      self.sq_ft = random.randint(300, 20000)
      self.num_crimes = random.randint(0, 500)
      price = 1337
      for i in xrange(num_samples):
        s += struct.pack('<HHHH', self.num_beds, self.num_baths, self.sq_ft, self.num_crimes)
        s += struct.pack('<H', price)
        inp = list()
        inp.append(self.num_beds / 20.0)
        inp.append(self.num_baths / 25.0)
        inp.append(self.sq_ft / 20000.0)
        inp.append(self.num_crimes / 500.0)
        self.nnet.feed_forward(inp)
        target = [price / 50000.0]
        self.nnet.back_prop(target)
    else:
      for i in xrange(num_samples):
        num_beds = random.randint(1, 20)
        num_baths = random.randint(1, 25)
        sq_ft = random.randint(300, 20000)
        num_crimes = random.randint(0, 500)
        price = num_beds * random.randint(10, 20)
        price += num_baths * random.randint(5, 10)
        price += sq_ft / 10
        price -= num_crimes
        if price < 0:
          price = 100
        s += struct.pack('<HHHH', num_beds, num_baths, sq_ft, num_crimes)
        s += struct.pack('<H', price)
        inp = list()
        inp.append(num_beds / 20.0)
        inp.append(num_baths / 25.0)
        inp.append(sq_ft / 20000.0)
        inp.append(num_crimes / 500.0)
        self.nnet.feed_forward(inp)
        target = [price / 50000.0]
        self.nnet.back_prop(target)
    self.write(s)

  def start(self):
    self.delay(50)
    init_g_state(struct.unpack('<I', self.magic_page[:4])[0])
    t = list()
    t.append(4)
    t.append(2)
    t.append(1)
    self.nnet = NNet(t)
    s = '\x00\x00\x00\x01'
    self.read(length=len(s), expect=s)
    if random.randint(1, 100) <= 5:
      self.pov_mode = True
    else:
      self.pov_mode = False
    self.start_training()

  def ready(self):
    s = '\x00\x00\x00\x02'
    self.read(length=len(s), expect=s)

  def query(self):
    self.write('\x00\x00\x00\x03')

    # Handle query
    if self.pov_mode and random.randint(1, 100) <= 15:
      num_beds = self.num_beds
      num_baths = self.num_baths
      sq_ft = self.sq_ft
      num_crimes = self.num_crimes
    else:
      num_beds = random.randint(1, 20)
      num_baths = random.randint(1, 25)
      sq_ft = random.randint(300, 20000)
      num_crimes = random.randint(0, 500)
    inp = list()
    inp.append(num_beds / 20.0)
    inp.append(num_baths / 25.0)
    inp.append(sq_ft / 20000.0)
    inp.append(num_crimes / 500.0)
    self.nnet.feed_forward(inp)
    out = self.nnet.get_output()
    if out[0] < 0:
      out[0] = (100.0 / 50000.0)
    self.comment('out[0]: %s' % out[0])
    price = int(out[0] * 50000.0 + 0.5)
    self.comment('price: %s' % price)

    self.write(struct.pack('<HHHH', num_beds, num_baths, sq_ft, num_crimes))

    s = '\x00\x00\x00\x00'
    self.read(length=len(s), expect=s)
    s = struct.pack('<I', price)
    self.read(length=len(s), expect=s)

    if price == 1337:
      s = '\xAA\xBB\xCC\xDD'
      self.read(length=len(s), expect=s)
      self.write(struct.pack('<II', 4, random.randint(0, 0xFFFFFFFF)))

  def quit(self):
    self.write('\x00\x00\x00\x04')
