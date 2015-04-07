/**
* @file MQAnalyzer.hpp
* @brief MQAnalyzer implementation.
*/

// standard headers
#include <stdint.h>
#include <unordered_map>
// external headers

// internal headers
#include "../include/MQAnalyzer.hpp"

namespace clusterer
{
namespace backend
{

double MQAnalyzer::analyze(const ClusterEncoding& clusteringSolution, const AbstractGraph& graph)
{
    double mqValue = 0.0;
    uint32_t clusterCount = clusteringSolution.getClusterCount();
    if (clusterCount == 1)
    {
        double totalEdgeWeightSum = 0.0;
        for (auto& e : graph.getEdges())
        {
            totalEdgeWeightSum += e.weight;
        }
        mqValue = totalEdgeWeightSum / (graph.getVerticesCount() * graph.getVerticesCount());
    }
    else
    {
        double clusterAValueSum = 0.0;
        double clusterBValueSum = 0.0;
        auto clusterVerticesMap = clusteringSolution.getClusterVerticesCountMap();
        uint32_t clusterCount = clusterVerticesMap.size();
        // @todo check if we can assume cluster ids from 0 to n or if they can be non continous
        std::vector<double> clusterAValue;
        std::vector<std::vector<double>> clusterBValue(clusterCount, std::vector<double>(clusterCount, 0.0));

        // go through all edges and compute either inter or intra edge weight sums
        for (auto& e : graph.getEdges())
        {
            ClusterId startNodeCluster = clusteringSolution.getClusterOfVertex(e.startNode);
            ClusterId endNodeCluster = clusteringSolution.getClusterOfVertex(e.endNode);
            if (startNodeCluster == endNodeCluster)
            {
                clusterAValue[startNodeCluster] += e.weight;
            }
            else
            {
                clusterBValue[startNodeCluster][endNodeCluster] += e.weight;
            }
        }

        // compute the A part of the given equation
        for (size_t i = 0; i < clusterAValue.size(); ++i)
        {
            clusterAValueSum += clusterAValue[i] / (clusterVerticesMap[i] * clusterVerticesMap[i]);
        }
        clusterAValueSum /= clusterCount;

        // compute the B part of the given equation
        for (size_t i = 0; i < clusterBValue.size(); ++i)
        {
            for (size_t j = 0; j < clusterBValue[i].size(); ++j)
            {
                clusterBValueSum += clusterBValue[i][j] / (2 * clusterVerticesMap[i] * clusterVerticesMap[j]);
            }
        }
        clusterBValueSum /= (clusterCount*(clusterCount - 1) / 2);

        // compute final mq value
        mqValue = clusterAValueSum - clusterBValueSum;
    }
    return mqValue;
}

MQAnalyzer::~MQAnalyzer()
{

}

}
}