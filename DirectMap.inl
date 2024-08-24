#include "DirectMap.h"

template <typename Resource, typename ID>
DirectMap<Resource, ID>::DirectMap() {}

template <typename Resource, typename ID>
Resource& DirectMap<Resource, ID>::get(ID id) {
    return _resources[(size_t)id];
}

template <typename Resource, typename ID>
Resource& DirectMap<Resource, ID>::operator[](ID id) {
    return _resources[(size_t)id];
}