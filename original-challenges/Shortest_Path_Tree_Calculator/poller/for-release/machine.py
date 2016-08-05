#!/usr/bin/env python

from generator.actions import Actions
from struct import *
from sys import *
from random import *

class SPT:
    def __init__(self):
        self.nodes = {}
        self.node_list = list()
        self.edges = dict()
        self.weights = dict()
        self.visited = list()

    def new_node(self, name, value):
        self.nodes[name] = value
        self.node_list.insert(0, name)
        self.edges[name] = list()

    def new_edge(self, from_node, to_node, weight):
        try:
            if self.weights[(from_node, to_node)] > weight:
                self.weights[(from_node, to_node)] = weight
        except KeyError:
            self.weights[(from_node, to_node)] = weight
            self.edges[from_node].insert(0, to_node)
            self.edges[to_node].insert(0, from_node)

        try:
            if self.weights[(to_node, from_node)] > weight:
                self.weights[(to_node, from_node)] = weight
        except KeyError:
            self.weights[(to_node, from_node)] = weight

    def FindMinNode(self):
        min_dist = maxint
        min_node = -1
        #for n in self.nodes:
        for n in self.node_list:
            if n not in self.visited:
                if self.nodes[n] < min_dist:
                    min_dist = self.nodes[n]
                    min_node = n

        return min_node

    def SPT(self, starting_node, ending_node):
        parent_node = dict()

        prev_node = starting_node
        self.nodes[starting_node] = 0
        for i in range(len(self.nodes)):
            min_node = self.FindMinNode()
            if min_node is -1:
                return

            self.visited.append(min_node)

            if min_node is ending_node:
                break

            for n in self.edges[min_node]:
                if self.nodes[n] > self.nodes[min_node] + self.weights[(min_node, n)]:
                    self.nodes[n] = self.nodes[min_node] + self.weights[(min_node, n)]
                    parent_node[n] = min_node
                    
            prev_node = min_node

        shortest_path = list()
        n = min_node
        while n is not starting_node:
            shortest_path.insert(0, str(n))
            n = parent_node[n]
        shortest_path.insert(0, str(n))

        return(shortest_path)

class MyClass(Actions):
    CMD_SEND_NODES = 1
    CMD_SEND_EDGES = 2
    CMD_RUN_SPT = 3
    RESP_ERROR_DUPLICATE_NODE = 1
    RESP_ERROR_TOO_MANY_NODES = 2
    RESP_ERROR_TOO_MANY_EDGES = 3
    RESP_ERROR_INVALID_NODE = 4
    RESP_ERROR_INVALID_CMD = 5
    RESP_NODE_SET = 6
    RESP_ERROR_SPT_FAIL = 7
    index = 0
    NumNodes = 0
    NumEdges = 0

    def RndByte(self):
        self.index = (self.index+1) % 4096
        return(ord(self.magic_page[self.index]))

    def SendNodes(self, Num=0):
	if Num is 0:
            self.NumNodes = 0
            while self.NumNodes < 5:
                self.NumNodes = self.RndByte()
        else:
	    self.NumNodes = Num

        Nodes =  pack("B", self.CMD_SEND_NODES)
        Nodes += pack("<L", self.NumNodes) # num elements
        Nodes += pack("<L", 0) # N/A
        Nodes += pack("<L", 0) # N/A
        for i in range(self.NumNodes):
            Nodes += pack("<L", i) # elements
            self.spt.new_node(i,maxint)

        self.comment("Num Nodes: {}".format(self.NumNodes))
        self.write(Nodes)

    def SendEdges(self, Num=0):
        if Num is 0:
            self.NumEdges = self.RndByte()
        else:
            self.NumEdges = Num

        Edges =  pack("B", self.CMD_SEND_EDGES)
        Edges += pack("<L", self.NumEdges)
        Edges += pack("<L", 0)
        Edges += pack("<L", 0)
        for i in range(self.NumEdges):
            NodeA = self.RndByte() % self.NumNodes
            NodeZ = self.RndByte() % self.NumNodes
            while NodeZ is NodeA:
                NodeZ = self.RndByte() % self.NumNodes
            Weight = self.RndByte()
            #
            Edges += pack("<L", NodeA)
            Edges += pack("<L", NodeZ)
            Edges += pack("<L", Weight)
            self.spt.new_edge(NodeA,NodeZ,Weight+ord(self.magic_page[self.NumNodes]))
            self.comment("Edge: {} to {} weight {}".format(NodeA,NodeZ,Weight))

        self.write(Edges)

    def RunSpt(self):
        StartingNode = self.RndByte() % self.NumNodes
        EndingNode   = self.RndByte() % self.NumNodes
        Cmd =  pack("B", self.CMD_RUN_SPT)
        Cmd += pack("<L", 0)
        Cmd += pack("<L", StartingNode)
        Cmd += pack("<L", EndingNode)

        self.comment("SPT from {} to {}".format(StartingNode, EndingNode))
        self.write(Cmd)

        SptResult = self.spt.SPT(StartingNode,EndingNode)
        if SptResult is None:
            Resp  = pack("B", self.RESP_ERROR_SPT_FAIL)
            Resp += pack("B", 0)
            self.comment("Disconnected graph")
            self.read(length=len(Resp), expect=Resp)
            return;

        Resp  = pack("B", self.RESP_NODE_SET)
        Resp += pack("B", len(SptResult))
        for x in SptResult:
            Resp += pack("<L", int(x)) 

        self.comment(" ".join(SptResult))
        self.read(length=len(Resp), expect=Resp)

    def SendBadNodes(self):
        r = randint(0,1)
        if r is 0:
	    # Too many nodes
            self.comment("Too many nodes")
	    self.SendNodes(256)
            Resp  = pack("B", self.RESP_ERROR_TOO_MANY_NODES)
            Resp += pack("B", 0)
            self.read(length=len(Resp), expect=Resp)

        elif r is 1:
	    # Duplicate node
            self.comment("Duplicate node")
	    self.SendNodes(1)
	    self.SendNodes(1)
            Resp  = pack("B", self.RESP_ERROR_DUPLICATE_NODE)
            Resp += pack("B", 0)
            self.read(length=len(Resp), expect=Resp)

    def SendBadEdges(self):
        r = randint(0,2)
        if r is 0:
	    # Too many edges
            self.comment("Too many edges")
	    self.SendNodes()
	    self.SendEdges(2001)
            Resp  = pack("B", self.RESP_ERROR_TOO_MANY_EDGES)
            Resp += pack("B", 0)
            self.read(length=len(Resp), expect=Resp)
        elif r is 1:
	    # Invalid starting node in edge
            self.comment("Invalid starting node")
	    self.SendNodes(2)
            Edges =  pack("B", self.CMD_SEND_EDGES)
            Edges += pack("<L", 1)
            Edges += pack("<L", 0)
            Edges += pack("<L", 0)
            Edges += pack("<L", 3) # Node 3 which doesn't exist
            Edges += pack("<L", 0) # Node 0
            Edges += pack("<L", 1) # Don't care about weight
            self.write(Edges)
            Resp  = pack("B", self.RESP_ERROR_INVALID_NODE)
            Resp += pack("B", 0)
            self.read(length=len(Resp), expect=Resp)
        elif r is 2:
	    # Invalid ending node in edge
            self.comment("Invalid ending node")
	    self.SendNodes(2)
            Edges =  pack("B", self.CMD_SEND_EDGES)
            Edges += pack("<L", 1)
            Edges += pack("<L", 0)
            Edges += pack("<L", 0)
            Edges += pack("<L", 0) # Node 0
            Edges += pack("<L", 3) # Node 3 which doesn't exist
            Edges += pack("<L", 1) # Don't care about weight
            self.write(Edges)
            Resp  = pack("B", self.RESP_ERROR_INVALID_NODE)
            Resp += pack("B", 0)
            self.read(length=len(Resp), expect=Resp)

    def start(self):
        self.delay(50)
        self.spt = SPT()

    def end(self):
	pass
