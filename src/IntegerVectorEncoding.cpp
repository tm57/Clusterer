/**
  * @file IntegerVectorEncoding.hpp
  * @brief encoder interface implementation
  */

// standard headers
#include <unordered_map>
// external headers

// internal headers
#include "../include/IntegerVectorEncoding.hpp"

namespace clusterer
{
namespace backend
{

IntegerVectorEncoding::IntegerVectorEncoding(Graph& g) : graph(g), ClusterEncoding(g)
{
    // Set encoding to be as big as the vertex array
    encoding.resize(g.getNoVertices());
}

int IntegerVectorEncoding::addToCluster(VertexId vertexId, ClusterId clusterId)
{
    if (encoding.size() < vertexId)
    {
        return -1;
    }
    encoding[vertexId] = clusterId;
    return 0;
}

ClusterId IntegerVectorEncoding::getClusterOfVertex(VertexId vertexId) const
{
    return encoding[vertexId];
}

std::vector<VertexId> IntegerVectorEncoding::getVerticesInCluster(ClusterId clusterId) const
{
    std::vector<VertexId> result;
    //iterating through the encoding vector
    for (int i = 0; i < encoding.size(); i++)
    {
        //check if VertexId is in the cluster
        if (encoding[i] == clusterId)
        {
            result.push_back(i);
        }
    }
    return result;
}

std::unordered_map<ClusterId, uint64_t> IntegerVectorEncoding::getClusterVerticesCountMap() const
{
    std::unordered_map<ClusterId, uint64_t> map;
    for (auto& e : this->encoding)
    {
        ++map[e];
    }
    return map;
}

uint64_t IntegerVectorEncoding::getVerticesCountInCluster(ClusterId clusterId) const
{
    std::unordered_map<ClusterId, uint64_t> map;
    for (auto& e : this->encoding)
    {
        ++map[e];
    }
    return map[clusterId];
}

uint32_t IntegerVectorEncoding::getClusterCount() const
{
    std::unordered_map<ClusterId, uint64_t> map;
    for (auto& e : this->encoding)
    {
        ++map[e];
    }
    return map.size();
}

ClusterEncoding::Encoding IntegerVectorEncoding::getEncoding()
{
    return encoding;
}

int IntegerVectorEncoding::normalize()
{
    std::map<ClusterId, VertexId> minVertex;
    VertexId i;

    // Find the minimum vertex id in each cluster
    for (i = 0; i < encoding.size(); i++)
    {
        if (minVertex.find(encoding[i]) == minVertex.end())
        {
            // Newly found cluster
            minVertex[encoding[i]] = i;
        }
        else if (i < minVertex[encoding[i]])
        {
            // vertexId smaller than the current smallest
            minVertex[encoding[i]] = i;
        }
    }

    // Rename all clusters
    for (i = 0; i < encoding.size(); i++)
    {
        encoding[i] = minVertex[encoding[i]];
    }

    return 0;
}

IntegerVectorEncoding::~IntegerVectorEncoding()
{
}

}
}
