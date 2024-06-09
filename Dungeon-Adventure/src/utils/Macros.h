#ifdef _DEBUG
	#define DEBUG_LOG(x) std::cout << x << std::endl
	#define ASSERT_LOG(x) std::cout << x << std::endl; __debugbreak()
	#define ASSERT_CONDITIONAL(c, m) if(c) {std::cout << m << std::endl; __debugbreak(); }

#else
	#define DEBUG_LOG(x)
	#define ASSERT_LOG(x) 
	#define ASSERT_CONDITIONAL(c, m) 
#endif