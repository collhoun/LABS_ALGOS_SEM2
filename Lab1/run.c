#include "trees.h"
#include "test.h"

int main()
{
    int is_good = 0;
    is_good = check_tests();
    if (is_good)
        interactive_mode();
    else
        printf("Something gone wrong\n");
    printf("isgood = %d", is_good);
    return 0;
}