#ifndef PCG_ENGINE_COMBINATION_GENERATION_SEQUENCE_GENERATOR_HPP
#define PCG_ENGINE_COMBINATION_GENERATION_SEQUENCE_GENERATOR_HPP

namespace pcg::engine::combination_generation
{
    /// @brief Interface for sequence nodes
    class ISequenceNode
    {
    public:
        virtual ~ISequenceNode() = default;

        /// @brief Set next node in sequence
        /// @param node Next node in sequence
        virtual void setNext(ISequenceNode* node) = 0;
        /// @brief Get next nodes count
        /// @return Next ndoes count
        virtual int getNextCount() const = 0;
        /// @brief Get node at index in list of next nodes
        /// @param index Index of node in list of next nodes
        /// @return Node at index
        virtual ISequenceNode* getNodeAt(int index) const = 0;
        /// @brief Generate sequence
        virtual void generateSequence() const = 0;
    };

    /// @brief Generate a sequence starting from node
    /// @param node First node in sequence
    void generateSequence(ISequenceNode& node);
}

#endif // PCG_ENGINE_COMBINATION_GENERATION_SEQUENCE_GENERATOR_HPP
