#ifndef PCG_ENGINE_UTILITY_CALLBACK_FUNCTOR_HPP
#define PCG_ENGINE_UTILITY_CALLBACK_FUNCTOR_HPP

#include <memory>

namespace pcg::engine::utility
{
    template<typename T>
    class CallbackFunctor;

    template<typename R, typename ...Args>
    class CallbackFunctor<R(Args...)>
    {
    public:
        template<typename Functor>
        CallbackFunctor(Functor functor) : functorConcept(std::make_unique<FunctorModel<Functor>>(functor))
        {
        }

        R operator()(const Args&... arg) const
        {
            return (*functorConcept)(arg...);
        }

        explicit operator bool() const
        {
            return functorConcept != nullptr;
        }

        class FunctorConcept
        {
        public:
            virtual ~FunctorConcept() = default;
            virtual R operator()(const Args&... args) const = 0;
        };

        template<typename FunctorCallback>
        class FunctorModel : public FunctorConcept
        {
        public:
            FunctorModel(FunctorCallback callback) : callback(callback)
            {
            }

            virtual R operator()(const Args&... args) const override
            {
                return callback(args...);
            }

        private:
            FunctorCallback callback;
        };

    private:
        std::unique_ptr<FunctorConcept> functorConcept;
    };
}

#endif // PCG_ENGINE_UTILITY_CALLBACK_FUNCTOR_HPP
