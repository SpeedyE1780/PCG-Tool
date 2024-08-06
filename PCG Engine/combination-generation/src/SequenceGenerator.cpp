#include <pcg/engine/combination-generation/SequenceGenerator.hpp>

#include <pcg/engine/math/random.hpp>

namespace pcg::engine::combination_generation
{
    namespace
    {
        /// @brief Generate a sequence starting from node
        /// @param node Last node added to sequence
        void generateSequence(ISequenceNode* node)
        {
            while (node->getNextCount() > 0)
            {
                node->setNext(math::Random::number(node->getNextCount()));
                node = node->getNext();
            }
        }
    }

    void generateSequence(ISequenceNode& node)
    {
        generateSequence(&node);
    }
}
