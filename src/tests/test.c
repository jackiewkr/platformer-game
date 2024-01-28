/**
 * \file test.c
 * \brief Tests components using UNITY_TEST.
 *
 * Unit tests for components. Compile with TEST_WINDOW preprocessor flag set
 * to test the Window library, etc.
 */

//supply your own UNITY_TEST library
#include "unity/unity.h"

// includes for specific components
#ifdef TEST_WINDOW
#include "../window/window.h"
#endif

void setUp( void ){}

void tearDown( void ){}

/**
 * \def TEST_WINDOW
 * \brief Whether to test Window library
 *
 * If TEST_WINDOW is defined, the tests for the Window library will be
 * run.
 */

#ifdef TEST_WINDOW
/**
 * \fn void test_windowOpen( void )
 * \brief Tests if the window opens with no errors.
 */
void test_windowOpen( void )
{
        TEST_ASSERT_NOT_NULL( window_init() );
}

/**
 * \fn void test_windowClose()
 * \brief Tests if the window_free() function can handle NULL pointers.
 */
void test_windowClose( void )
{
        struct Window* w = window_init();

        TEST_ASSERT_EQUAL_INT( 1, window_free( w ) );
        TEST_ASSERT_EQUAL_INT( 0, window_free( NULL ) );
}
#endif

/**
 * \fn int main( void )
 * \brief Runs tests for components.
 * Runs the specified tests. To add a component to test, compile file with
 * a given TEST_<component_name>
 */
int main( void )
{
        UNITY_BEGIN();
#ifdef TEST_WINDOW
        RUN_TEST( test_windowOpen );
        RUN_TEST( test_windowClose );
#endif
        return UNITY_END();
}
