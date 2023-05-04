#include "menu.h"
#include "Sequential/sequential.h"
#include "DynamicHash/extendibleHash.h"
int main()
{
    init();
    Sequential<Record<char[40]>, string> seq("data", "daux");
    ExtendibleHash<int> extendibleHash("dataHash", "index");
    menu_principal(seq, extendibleHash);
    return 0;
}