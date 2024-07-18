namespace pcg::engine::combination_generation
{
    class ISequenceNode
    {
    public:
        virtual ~ISequenceNode() = default;

        virtual void setNext(ISequenceNode* node) = 0;
        virtual int getNextCount() const = 0;
        virtual ISequenceNode* getNodeAt(int index) const = 0;
    };

    void generateSequence(ISequenceNode* node);
}
