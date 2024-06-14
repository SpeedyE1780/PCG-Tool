#ifndef PCG_ENGINE_UTILITY_CALLBACK_FUNCTOR_HPP
#define PCG_ENGINE_UTILITY_CALLBACK_FUNCTOR_HPP

#include <memory>

namespace pcg::engine::utility
{
    template<typename ...Args>
    class CallbackFunctor
    {
    public:
        template<typename Functor>
        CallbackFunctor(Functor functor) : functorConcept(std::make_unique<FunctorModel<Functor>>(functor))
        {
        }

        void operator()(const Args&... arg) const
        {
            (*functorConcept)(arg...);
        }

        class FunctorConcept
        {
        public:
            virtual ~FunctorConcept() = default;
            virtual void operator()(const Args&... args) const = 0;
        };

        template<typename FunctorCallback>
        class FunctorModel : public FunctorConcept
        {
        public:
            FunctorModel(FunctorCallback callback) : callback(callback)
            {
            }

            virtual void operator()(const Args&... args) const override
            {
                callback(args...);
            }

        private:
            FunctorCallback callback;
        };

    private:
        std::unique_ptr<FunctorConcept> functorConcept;
    };
}

#endif // PCG_ENGINE_UTILITY_CALLBACK_FUNCTOR_HPP
