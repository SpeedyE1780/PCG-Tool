#ifndef PCG_ENGINE_UTILITY_CALLBACK_FUNCTOR_HPP
#define PCG_ENGINE_UTILITY_CALLBACK_FUNCTOR_HPP

#include <memory>

namespace pcg::engine::utility
{
    /// @brief Templated callback functor
    /// @tparam T Template type used with functor
    template<typename T>
    class CallbackFunctor;

    /// @brief Specialization of CallbackFunctor<T> allowing the use of CallbackFunctor<R(Args...)
    /// @tparam R Return type of operator()
    /// @tparam ...Args Arguments passed in to operator()
    template<typename R, typename ...Args>
    class CallbackFunctor<R(Args...)>
    {
    public:
        /// @brief Templated construsctor allowing for type erasure
        /// @tparam Functor Functor model
        /// @param functor Functor model stored in class
        template<typename Functor>
        CallbackFunctor(Functor functor) : functorConcept(std::make_unique<FunctorModel<Functor>>(functor))
        {
        }

        /// @brief Call functor model function
        /// @param ...arg List of arguments passed to functor
        /// @return R
        R operator()(const Args&... arg) const
        {
            return (*functorConcept)(arg...);
        }

        /// @brief Convert CallbackFunctor to bool
        explicit operator bool() const
        {
            return functorConcept != nullptr;
        }

        /// @brief Base class of FunctorModel used for type erasure
        class FunctorConcept
        {
        public:
            virtual ~FunctorConcept() = default;
            /// @brief Call functor model operator()
            /// @param ...args List of arguments passed to functor
            /// @return R
            virtual R operator()(const Args&... args) const = 0;
        };

        /// @brief FunctorModel inheriting from FunctorConcept used for type erasure
        /// @tparam FunctorCallback callback function given to functor
        template<typename FunctorCallback>
        class FunctorModel : public FunctorConcept
        {
        public:
            /// @brief Set callback function
            /// @param callback Callback function
            FunctorModel(FunctorCallback callback) : callback(callback)
            {
            }

            /// @brief Call callback with given arguments
            /// @param ...args List of arguments passed to callback
            /// @return R
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
