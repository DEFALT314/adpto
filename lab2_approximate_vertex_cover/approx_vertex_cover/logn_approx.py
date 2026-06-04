from approx_vertex_cover.types import EdgeList


def logn_approx(graph: EdgeList) -> set[int]:
    """
    Approximation algorithm for the Vertex Cover problem, which takes the vertex
    with the highest degree and adds it to the solution.

    Approximation factor: log(n)

    :param graph: graph represented as a list of edges
    :return: set of vertices that approximate the cover
    """
    cover = set()
    degree = {}

    for edge in graph:
        degree[edge[0]] = degree.get(edge[0], 0) + 1
        degree[edge[1]] = degree.get(edge[1], 0) + 1

    while graph:
        max_degree_vertex = max(degree, key=degree.get)
        cover.add(max_degree_vertex)
        for edge in graph:
            if max_degree_vertex in edge:
                degree[edge[0]] = degree.get(edge[0], 0) - 1
                degree[edge[1]] = degree.get(edge[1], 0) - 1
        graph = [edge for edge in graph if max_degree_vertex not in edge]

        degree.pop(max_degree_vertex)

    return cover