#include <pcg/engine/combination-generation/SequenceGenerator.hpp>

#include <pcg/engine/math/random.hpp>

#include <unordered_set>

namespace pcg::engine::combination_generation
{
    namespace
    {
        /// @brief Generate a sequence starting from node
        /// @param node First node added to sequence
        void generateSequence(ISequenceNode* node)
        {
            std::unordered_set<ISequenceNode*> processedNodes{};

            while (node->getNextCount() > 0 && processedNodes.find(node) == end(processedNodes))
            {
                processedNodes.emplace(node);
                ISequenceNode* next = node->getNextAt(math::Random::number(node->getNextCount()));

                if (processedNodes.find(next) != end(processedNodes))
                {
                    return;
                }

                node->setNext(next);
                node = next;
            }
        }

        /// @brief Generate a sequence starting from node with a max number of nodes
        /// @param node First node in sequence
        /// @param count Max number of node in sequence
        /// @param callback Callback indicating which was the next node added
        void generateSequence(ISequenceNode* node, int count, const std::function<void(ISequenceNode*)>& callback)
        {
            callback(node);
            count -= 1;

            while (count > 0 && node->getNextCount() > 0)
            {
                node = node->getNextAt(math::Random::number(node->getNextCount()));
                callback(node);
                count -= 1;
            }
        }
    }

    void generateSequence(ISequenceNode& node)
    {
        generateSequence(&node);
    }

    void generateSequence(ISequenceNode& node, int count, const std::function<void(ISequenceNode*)>& callback)
    {
        return generateSequence(&node, count, callback);
    }
}
