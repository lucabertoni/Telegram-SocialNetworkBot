#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <algorithm> // std::find

using namespace std;

std::vector<std::string> explode(std::string const & s, char delim);
bool isInStringVector(std::vector<string> aVector, string sElement);