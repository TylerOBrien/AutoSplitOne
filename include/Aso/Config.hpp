#ifndef _ASO_CONFIG_HPP_
#define _ASO_CONFIG_HPP_

#include <Aso/Aso.hpp>

namespace aso {
namespace Config {

union Entry {
    char c;
    int i;
    float f;
    bool b;
};

int uid();

int insert(char value);
int insert(int value);
int insert(float value);
int insert(bool value);

char getc(int uid);
int geti(int uid);
float getf(int uid);
bool getb(int uid);

void set(int uid, char value);
void set(int uid, int value);
void set(int uid, float value);
void set(int uid, bool value);

}
}

#endif
