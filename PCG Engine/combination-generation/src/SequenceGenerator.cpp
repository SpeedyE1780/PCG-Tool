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
            math::Random::resetSeed();

            while (node->getNextCount() > 0)
            {
                ISequenceNode* nextNode = node->getNodeAt(math::Random::number(node->getNextCount()));
                node->setNext(nextNode);
                node = nextNode;
            }
        }
    }

    void generateSequence(ISequenceNode& node)
    {
        generateSequence(&node);
    }
}
