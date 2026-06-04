from itertools import combinations
from typing import Optional
from itertools import *
from vertex_cover.types import VertexSets, EdgeList
from utils.dimacs import *


# TODO: add typing for graph
def VC(G,k,S) -> Optional[set[int]]:
    for u,v in G:
        if not (u in S) or not (v in S):
            break
    else:
        return S
    if k == 0: return None
    S1 = VC(G, k-1, S|{u})
    S2 = VC(G, k-1, S|{v})
    
    return S1 if S1 else S2