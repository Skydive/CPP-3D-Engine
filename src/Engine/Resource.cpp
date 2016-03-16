#include "Resource.h"

Resource::~Resource()
{
    Destroy();
}
bool Resource::Load(){ return false; }
void Resource::Destroy() {}
