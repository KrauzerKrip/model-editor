#include "npc_graph.h"

#include <queue>
#include "lc_client/exceptions/npc_exceptions.h"


NpcGraph::NpcGraph(std::vector<npc::GraphVertex> vertices, std::vector<npc::GraphNode> nodes) : m_vertices(vertices), m_nodes(nodes) {
	_ASSERT_EXPR(m_vertices.size() < UINT_MAX, "NpcGraph: too much vertices.");
	_ASSERT_EXPR(m_nodes.size() < UINT_MAX, "NpcGraph: too much nodes.");

	if (m_nodes.size() != m_nodes.size()) {
		throw NpcGraphException("NpcGraph: the size of vertices vector isn`t equal to the size of nodes vector.");
	}
}

GraphPath NpcGraph::getShortestPath(unsigned int source, unsigned int destination) {
	std::vector<unsigned int> vertices;
	std::vector<float> distances(m_vertices.size());
	std::vector<unsigned int> previous(m_vertices.size());

	for (unsigned int i = 0; i < m_vertices.size(); i++) {
		distances[i] = INFINITY;
		vertices.push_back(i);
	}

	distances[source] = 0;
	float alt = distances[source];

	unsigned int vertices_size = (unsigned int)vertices.size();

	while (vertices_size > 0) {
		unsigned int minDistVertex = INFINITY; 
		float minDist = INFINITY;			  
		for (unsigned int i = 0; i < distances.size(); i++) {
			bool isVerticeInVertices = false;

			if (vertices[i] != UINT_MAX) {
				isVerticeInVertices = true;
			}

			if ((distances[i] < minDist) && isVerticeInVertices) {
				minDistVertex = i;
				minDist = distances[i];
			}
		}

		vertices[minDistVertex] = UINT_MAX;
		vertices_size--;

		if (minDistVertex == destination) {
			break;
		}

		for (unsigned int adjVertex : m_vertices[minDistVertex].adjacentVertices) {
			if (adjVertex == 3) {
				int i = 0;
			}

			if (vertices[adjVertex] != UINT_MAX) {
				alt = distances[minDistVertex] + getDistance(minDistVertex, adjVertex);

				if (alt < distances[adjVertex]) {
					distances[adjVertex] = alt;
					previous[adjVertex] = minDistVertex;
				}
			}
		}
	}

	std::vector<unsigned int> pathVertices;
	float distance = distances[destination];

	if (distance != INFINITY) {
		unsigned int current = destination;
		while (current != source) {
			pathVertices.push_back(current);
			current = previous[current];
		}
		pathVertices.push_back(source);
		std::reverse(pathVertices.begin(), pathVertices.end());
	}

	return GraphPath(pathVertices, distance);
}


unsigned int NpcGraph::getClosestVertice(glm::vec3 position) const {
	GraphNode minNode;
	unsigned int minNodeVertice = 0;

	for (unsigned int i = 0; i < m_nodes.size(); i++) {
		float distanceNode = glm::distance(m_nodes.at(i).position, position);
		float distanceMinNode = glm::distance(minNode.position, position);

		if (distanceNode < distanceMinNode) {
			minNode = m_nodes.at(i);
			minNodeVertice = i;
		}
	}

	return minNodeVertice;
}

const GraphNode& NpcGraph::getNode(unsigned int vertice) const { return m_nodes.at(vertice); }

float NpcGraph::getDistance(unsigned int source, unsigned int destination) { 
	GraphNode node1 = getNode(source);
	GraphNode node2 = getNode(destination);

	return glm::distance(node1.position, node2.position);
}

const std::vector<GraphNode>& NpcGraph::getNodes() { return m_nodes; }
const std::vector<GraphVertex>& NpcGraph::getVertices() { return m_vertices; }

//void NpcGraph::addEdge(unsigned int source, unsigned int destination) {
//	m_vertices.at(source).adjacentVertices.push_back(destination);
//	m_vertices.at(destination).adjacentVertices.push_back(source);
//}
//
//void NpcGraph::addNode(unsigned int vertice, npc::Node node) { 
//	m_nodes[vertice] = node;
//}

