#include "eratosthenes.h"

void Eratosthenes(BitArray_t pole) {
    BA_set_bit(pole, 0, 1);
    BA_set_bit(pole, 1, 1);

    for(int i=2; i<=sqrt(BA_size(pole)); ++i) {
        if(BA_get_bit(pole, i)==0) {
            for(int j=i,n=2; (n*j)<BA_size(pole); ++n) {
                BA_set_bit(pole, n*j, 1);
            }
        }
    }
}
