#include <pcg/engine/combination-generation/SequenceGenerator.hpp>

#include <pcg/engine/math/random.hpp>

namespace pcg::engine::combination_generation
{
    namespace
    {
        /// @brief Generate a sequence starting from node
        /// @param node First node added to sequence
        void generateSequence(ISequenceNode* node)
        {
            while (node->getNextCount() > 0)
            {
                node->setNext(math::Random::number(node->getNextCount()));
                node = node->getNext();
            }
        }

        /// @brief Generate a sequence starting from node with a max number of nodes
        /// @param node First node in sequence
        /// @param count Max number of node in sequence
        std::vector<ISequenceNode*> generateSequence(ISequenceNode* node, int count)
        {
            std::vector<ISequenceNode*> sequence{};
            sequence.reserve(count);
            sequence.push_back(node);

            while (count > 0 && node->getNextCount() > 0)
            {
                node = node->getNextAt(math::Random::number(node->getNextCount()));
                sequence.push_back(node);
                count--;
            }

            return sequence;
        }
    }

    void generateSequence(ISequenceNode& node)
    {
        generateSequence(&node);
    }

    std::vector<ISequenceNode*> generateSequence(ISequenceNode& node, int count)
    {
        return generateSequence(&node, count);
    }
}
