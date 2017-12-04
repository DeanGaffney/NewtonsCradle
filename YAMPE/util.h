/**
	@file 		util.h
	@author		kmurphy
	@practical 	
	@brief		Collection of miscellaneous code to simplify development.

	Collection of miscellaneous utility macros and definitions.
	
 	The run time assertions and static (complie time) assertions
	
	\section static Static Assertions

	Runtime and complie time (static) assertions.

 	http://www.pixelbeat.org/programming/gcc/static_assert.html

	*/

/**
  * Macro to handle unused parameter warning across multiple 
  * compilers
  * found at http://sourcefrog.net/weblog/software/languages/C/unused.html
  */
#ifdef UNUSED 
#elif defined(__GNUC__) 
# define UNUSED(x) UNUSED_ ## x __attribute__((unused)) 
#elif defined(__LCLINT__) 
# define UNUSED(x) /*@unused@*/ x 
#else 
# define UNUSED(x) x 
#endif


#include <cassert>

// run time assertions

/**
 * Run time assertion.
 *
 * This is just a wrapper around the stantard run time assertion in cassert
 */
#define ASSERT(cond,mess) assert ((cond)&&mess);

// compile time assertions - UPDATE not used 2013

// Compile time assertions are soon to be part of the standard 
// (gcc>=4.3 and Visual studio 2010) but in the interim using this (non-ideal) 
// implementation will do. 
// source http://www.pixelbeat.org/programming/gcc/static_assert.html

/** */
#define ASSERT_CONCAT_(a, b) a##b

/** */
#define ASSERT_CONCAT(a, b) ASSERT_CONCAT_(a, b)
/* These can't be used after statements in c89. */
#ifdef __COUNTER__
/* microsoft */
/** */
#define STATIC_ASSERT(cond,mess) \
enum { ASSERT_CONCAT(static_assert_, __COUNTER__) = 1/(!!(cond)) }
#else
/* This can't be used twice on the same line so ensure if using in headers
 * that the headers are not included twice (by wrapping in #ifndef...#endif)
 * Note it doesn't cause an issue when used on same line of separate modules
 * compiled with gcc -combine -fwhole-program.  */
/** */
#define STATIC_ASSERT(cond,mess) \
enum { ASSERT_CONCAT(assert_line_, __LINE__) = 1/(!!(cond)) }
#endif

namespace YAMPE {

typedef std::string String;
 
// TODO - must convert over to FastFormat (http://www.fastformat.org/)
template <class T>
inline String toString (const T& t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}
    
// source http://stackoverflow.com/questions/191757/c-concatenate-string-and-int
#define MAKE_STRING(tokens) \
    static_cast<std::ostringstream&>( \
    std::ostringstream().flush() << tokens \
).str()

    
const float EPS = 1.0e-05;
  
// http://anthony.liekens.net/index.php/Computers/CppForeach
#define foreach( i, c )\
 typedef __typeof__( c ) c##_CONTAINERTYPE;\
  for( c##_CONTAINERTYPE::iterator i = c.begin(); i != c.end(); ++i )

// specialisation because VC is crap
#define foreachParticle( i, c )\
 for(ParticleRegistry::iterator i = c.begin(); i != c.end(); ++i)
#define foreachEntry( i, c )\
 for(Registry::iterator i = c.begin(); i != c.end(); ++i)

/*
define foreach(var, container) \
  for(typeof((container).begin()) var = (container).begin(); \
      var != (container).end(); \
      ++var)
*/
}	// namespace YAMPE
