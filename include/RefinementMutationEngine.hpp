/**
  * @file MutationEngine.hpp
  * @brief mutation interface implementation
  */
#ifndef _BACKEND_GENETIC_RMUTATIONENGINE_HPP
#define _BACKEND_GENETIC_RMUTATIONENGINE_HPP

//Standard libraries
#include <stdint.h>

//Own libraries
#include "ClusterEncoding.hpp"

namespace backend
{
namespace genetic
{

class RefinementMutation: public MutationEngine
{
public:
    /**
     * @brief mutate a clustering solution
     * @param cluster the clustering solution to mutate
     * @param probability the probability with which the mutation will occur
     * @return the new clustering solution if a mutation occurred, or the old
     * one otherwise
     */
    virtual ClusterEncoding::Encoding mutate(const ClusterEncoding::Encoding& cluster,
                                            double probability);

    virtual ~RefinementMutationEngine();
};

}  // namespace genetic
}  // namespace backend

#endif  // _BACKEND_GENETIC_RMUTATIONENGINE_HPP

