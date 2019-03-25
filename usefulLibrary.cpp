#include <string>
#include <vector>

using namespace std;

vector<std::string> split(std::string str, char del) {
  int first = 0;
  int last = str.find_first_of(del);

  std::vector<std::string> result;

  while (first < str.size()) {
    std::string subStr(str, first, last - first);
    size_t c;
    while ((c = subStr.find_first_of("\t")) != string::npos) {
      subStr.erase(c, 1);
    }
    result.push_back(subStr);

    first = last + 1;
    last = str.find_first_of(del, first);

    if (last == std::string::npos) {
      last = str.size();
    }
  }

  return result;
}