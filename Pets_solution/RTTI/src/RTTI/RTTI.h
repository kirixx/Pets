#pragma once
#include <atomic>
#include <string>

#define ASSERT(x) if (!(x)) __debugbreak();
namespace RTTI
{
    namespace
    {
        std::atomic<int32_t> gLastClassIndex;
    }

    //class for easier identification like X::id()
    //with comparison support and should be unique for each dynamic type
    class CClassId
    {
    public:
        CClassId(const std::string& className) noexcept
            : mName(className)
            , mIndex(++gLastClassIndex)
        {}

        inline const std::string getName() const noexcept { return mName; }
        inline int32_t getIndex() const noexcept { return mIndex; }

        bool operator==(const CClassId& ref) const noexcept
        {
            return mIndex == ref.getIndex();
        }

    private:
        std::string mName;
        int32_t mIndex;
    };

    class CDynamicType
    {
    public:
        CDynamicType() noexcept {};
        virtual ~CDynamicType() noexcept {};

        static const CClassId& id() noexcept
        {
            static const CClassId id("CCDynamicType");
            return id;
        }

        virtual const CClassId& who() const noexcept { return id(); }

        template<class T>
        bool is() const noexcept
        {
            return isBaseId(T::id()) || T::id() == who();
        }

        virtual bool isBaseId(const CClassId& baseId) const noexcept
        {
            return baseId == id();
        }

        template<typename T>
        const T& get()
        {
            ASSERT(is<T>());
            return static_cast<const T&>(*this);
        }

        template<typename T>
        T& get()
        {
            ASSERT(is<T>());
            return static_cast<T&>(*this);
        }
    };

    // Check if X derived from Y
    template <class X>
    struct IsDerived
    {
        template <class Y>
        static bool from() noexcept
        {
            return X::id() == Y::id() || IsDerived<class X::base>::template from<Y>();
        }
    };

    //Stop recursion if we faced the parent class
    template <>                              
    struct IsDerived<CDynamicType>                
    {                                        
        template<class Y>                    
        static bool from() noexcept          
        {                                    
            return CDynamicType::id() == Y::id();
        }                                    
    };
}

//generate overloaded function to minimize code duplication
#define DERIVED_FROM(baseClass)                                                 \
    typedef baseClass base;                                                     \
    virtual bool isBaseId(const RTTI::CClassId& baseId) const noexcept override \
    {                                                                           \
        return baseId == id() || base::isBaseId(baseId);                        \
    }                                                                           \
    virtual const RTTI::CClassId& who() const noexcept override                 \
    {                                                                           \
        return id();                                                            \
    }                                                                           \
    static const RTTI::CClassId& id() noexcept