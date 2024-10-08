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
        /// @param nodeIndex Index of next node in sequence
        virtual void setNext(int nodeIndex) = 0;
        /// @brief Get next node in sequence
        /// @return Next node in sequence
        virtual ISequenceNode* getNext() const = 0;
        /// @brief Get next nodes count
        /// @return Next nodes count
        virtual int getNextCount() const = 0;
        /// @brief Generate sequence
        virtual void generateSequence() const = 0;
    };

    /// @brief Generate a sequence starting from node
    /// @param node First node in sequence
    void generateSequence(ISequenceNode& node);
}

#endif // PCG_ENGINE_COMBINATION_GENERATION_SEQUENCE_GENERATOR_HPP
