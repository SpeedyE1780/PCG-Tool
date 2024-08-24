#include <pcg/engine/combination-generation/SequenceGenerator.hpp>

#include <pcg/engine/math/random.hpp>

#include <pcg/engine/tests/PCGTest.hpp>

#include <gtest/gtest.h>

using PCGTest = pcg::engine::tests::PCGTest;

namespace pcg::engine::combination_generation::tests
{
    namespace
    {
        class SequenceNode : public pcg::engine::combination_generation::ISequenceNode
        {
        public:
            SequenceNode(std::string&& message, std::vector<SequenceNode*>&& nextNodes) :
                ISequenceNode(),
                message(message),
                nextNodes(nextNodes)
            {
            }

            SequenceNode(std::string&& message) : SequenceNode(std::move(message), std::vector<SequenceNode*>{})
            {
            }

            virtual void setNext(ISequenceNode* next) { nextNode = next; }
            virtual ISequenceNode* getNext() const { return nextNode; }
            virtual ISequenceNode* getNextAt(int index) const { return nextNodes[index]; }
            virtual int getNextCount() const override { return nextNodes.size(); }

            virtual void generateSequence() const override
            {
                std::cout << message;

                if (nextNode)
                {
                    std::cout << "->";
                    nextNode->generateSequence();
                }
            }

            void addNextNodes(const std::vector<SequenceNode*>& next)
            {
                nextNodes.insert(end(nextNodes), begin(next), end(next));
            }

        private:
            std::string message = "";
            std::vector<SequenceNode*> nextNodes{};
            ISequenceNode* nextNode = nullptr;
        };

        class Sequence : public PCGTest
        {
        protected:
            virtual void SetUp() override
            {
                PCGTest::SetUp();

                red.addNextNodes(nextNodes);
                green.addNextNodes(nextNodes);
                blue.addNextNodes(nextNodes);
                yellow.addNextNodes(nextNodes);
            }

            SequenceNode red{ "Red" };
            SequenceNode green{ "Green" };
            SequenceNode blue{ "Blue" };
            SequenceNode yellow{ "Yellow" };

            std::vector<SequenceNode*> nextNodes{ &red, &green, &blue, &yellow };
        };
    }

    TEST_F(Sequence, QuestGeneration)
    {
        SequenceNode goldIngots("5 Gold Ingots");
        SequenceNode logs("10 Logs");
        SequenceNode give("Give", { &goldIngots, &logs });

        SequenceNode axe("Axe");
        SequenceNode dagger("Dagger");
        SequenceNode sword("Sword");
        SequenceNode craft("Craft", { &axe, &dagger, &sword });

        SequenceNode smith("Smith", { &give, &craft });

        SequenceNode amulet("Amulet of Resistance");
        SequenceNode stolenGold("Stolen Gold");
        SequenceNode retrieve("Retrieve", { &amulet, &stolenGold });

        SequenceNode merchant("Merchant", { &retrieve });

        SequenceNode town("Town");
        SequenceNode defend("Defend", { &town });

        SequenceNode wolf("Wolf");
        SequenceNode orc("Orc");
        SequenceNode goblin("Goblin");
        SequenceNode kill("Kill", { &wolf, &orc, &goblin });

        SequenceNode guildMaster("Guild Master", { &kill, &defend });

        SequenceNode speak("Speak", { &guildMaster, &merchant, &smith });

        generateSequence(speak);

        EXPECT_EQ(speak.getNext(), &smith);
        EXPECT_EQ(smith.getNext(), &craft);
        EXPECT_EQ(craft.getNext(), &dagger);
    }

    TEST_F(Sequence, CyclicSequence)
    {
        std::vector<ISequenceNode*> sequence{};
        std::function<void(ISequenceNode*)> callback = [&sequence](ISequenceNode* node) {sequence.emplace_back(node); };
        generateSequence(red, 10, callback);
        const auto expected = std::vector<ISequenceNode*>{ &red, &blue, &yellow, &blue, &green, &yellow, &green, &green, &green, &blue };

        EXPECT_TRUE(std::ranges::equal(sequence, expected));
    }

    TEST_F(Sequence, EarlyExitFromSequence)
    {
        generateSequence(red);

        EXPECT_EQ(red.getNext(), &blue);
        EXPECT_EQ(blue.getNext(), &yellow);
        EXPECT_EQ(yellow.getNext(), nullptr);
    }
}
