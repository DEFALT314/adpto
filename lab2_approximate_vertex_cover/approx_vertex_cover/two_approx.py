from approx_vertex_cover.types import EdgeList


def two_approx(graph: EdgeList) -> set[int]:
    """
    Approximation algorithm for the Vertex Cover problem, which takes any edge
    and adds its ends to the solution.

    Approximation factor: 2

    :param graph: graph represented as a list of edges
    :return: set of vertices that approximate the cover
    """
    cover = set()

    for edge in graph:
        if edge[0] not in cover and edge[1] not in cover:
            cover.add(edge[0])
            cover.add(edge[1])

    return cover
