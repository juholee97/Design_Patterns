#include <iostream>
#include <memory>
class AnyFunction
{
private:
    struct Base
    {
        virtual ~Base() {}
        virtual void MyFunc( int a ) = 0;
    };

    template <typename Func>
    struct Impl : public Base
    {
        Impl( Func f ) : m_f( f ) {}

        void MyFunc( int a ) override
        {
            m_f( a );
        }

        Func m_f;
    };

    std::unique_ptr<Base> m_FuncPtr;

public:
    template <typename Func>
    AnyFunction( Func f ) : m_FuncPtr( std::make_unique<Impl<Func>>( f ) ) {}

    void operator()( int a )
    {
        m_FuncPtr->MyFunc( a );
    }
};

void funcCall( int a )
{
    std::cout << "funcCall : " << a << std::endl;
}

int main()
{
    auto lamdaCall = [] ( int a ) { std::cout << "lamdaCall : " << a << std::endl; };

    // AnyFunction 는 lamda, function 객체 둘 다 인자로 ok.
    AnyFunction wrapLamda( lamdaCall );
    AnyFunction wrapFunc( funcCall );

    wrapLamda( 2 );
    wrapFunc( 1 );

    return 0;
}