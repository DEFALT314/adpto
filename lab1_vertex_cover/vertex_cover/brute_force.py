from itertools import combinations
from typing import Optional
from itertools import *
from vertex_cover.types import VertexSets, EdgeList
from utils.dimacs import *


# TODO: add typing for graph
def brute_force(graph, k: int) -> Optional[set[int]]:
    """
    :param graph: graph represented as GRAPH REPRESENTATION?
    :param k: this many vertices have to cover the graphs
    :return: set of vertices that create the cover if the solution exists,
    otherwise Nonereprezentowanego
    """
    # TODO: implement
    E = edgeList(graph)
    for C in combinations(range(len(graph)), k):
        C= set(C)
        if isVC(E,C): return C
        
    return None
