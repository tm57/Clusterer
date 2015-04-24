/**
 * @file GraphCoordinateTransformer.hpp
 * @brief implementation of a transformer to obtain coordinates for a graph's nodes
 * using the edge's weights
 */
#ifndef CLUSTERER_FRONTEND_GRAPH_COORD_TRANS_HPP
#define CLUSTERER_FRONTEND_GRAPH_COORD_TRANS_HPP

 // standard headers
#include <stdint.h>
#include <map>
#include <vector>

// internal headers
#include "ClusterEncoding.hpp"
#include "IntegerVectorEncoding.hpp"
#include "AbstractGraph.hpp"
#include "Graph.hpp"

//using namespace clb;

/**
* @namespace clusterer
* @brief The namespace clusterer is the main namespace of the clusterer project.
*/
namespace clusterer
{

/**
* @namespace backend
* @brief The namespace frontend is the namespace for all backend components of the
* project.
*/
namespace frontend
{

class GraphCoordinateTransformer{

    public:
    	/**
    	* @brief constructor which applies the MDS algorithm
    	* @param takes a graph reference to which the algorithm is applied
    	*/
	    GraphCoordinateTransformer(const backend::AbstractGraph& g);

	    /**
	    * @brief getter to obtain the constructed map
	    * @return map of the type <vertex id, pair of coordinates>
	    */
	    std::map<backend::VertexId,std::pair<double,double>> getCoordinateMap();

	    /**
	    * @brief empty destructor
	    */
	    ~GraphCoordinateTransformer();

    private:
        std::map<backend::VertexId,std::pair<double,double>> map_coord;

};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clf = clusterer::frontend;

#endif