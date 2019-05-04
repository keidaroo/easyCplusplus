#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum lineType {
  normal,
  caseSwitch,
  functionStart,
  publicPrivate,
  defineInclude
};

class LineInfo {
 private:
  int indentNum() {
    int spaceCnt = 0, tabCnt = 0;
    for (auto& c : line) {
      if (c == '\t')
        tabCnt++;
      if (c == ' ')
        spaceCnt++;
    }

    return tabCnt + spaceCnt / tabSpaceWidth;
  }

  vector<string> split(const string& s, char delim) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
      if (!item.empty()) {
        auto c = item.find('\t');
        while (c != string::npos) {
          item.erase(c, 1);
          c = item.find('\t');
        }
        c = item.find(' ');
        while (c != string::npos) {
          item.erase(c, 1);
          c = item.find(' ');
        }

        elems.push_back(item);
      }
    }
    return elems;
  }

  // コメント出会った場合は // を付け加え、
  // そうでない場合は ; を文末に加える。
  // vectorのなかみも書き換えちゃう
  string checkComment(vector<string>& splittedLine) {
    if (splittedLine[0][0] == '#') {
      splittedLine[0].erase(splittedLine[0].begin());
      splittedLine.insert(splittedLine.begin(), "//");
    } else {
      splittedLine.push_back(";");
    }

    return mixIn(splittedLine);
  }

 public:
  const int tabSpaceWidth = 2;
  string line;
  int nowIndentNum;
  lineType type;

  string closeBrackets(int beforeIndentNum, map<int, lineType>& indentInfo) {
    string ret = "";
    for (int i = nowIndentNum; i < beforeIndentNum; i++) {
      if (indentInfo[i] == functionStart) {
        ret += "};";
      }
    }
    return ret;
  }

  string mixIn(vector<string> v) {
    string ret = "";
    for (auto& s : v) {
      ret += " " + s;
    }
    return ret;
  }

  string input(string s, int beforeIndentNum, map<int, lineType>& indentInfo) {
    line = s;
    nowIndentNum = indentNum();
    vector<string> splittedLine = split(line, ' ');
    string ret = "";

    if (splittedLine.empty()) {
      nowIndentNum = beforeIndentNum;
      return "";
    }

    ret = closeBrackets(beforeIndentNum, indentInfo);

    if (splittedLine[0] == "public:" || splittedLine[0] == "private:") {
      type = publicPrivate;
      ret += line;
      indentInfo[nowIndentNum] = publicPrivate;
    } else if (splittedLine.back() == "then") {
      type = caseSwitch;
      splittedLine.pop_back();
      ret += mixIn(splittedLine) + ":";
      indentInfo[nowIndentNum] = caseSwitch;
    } else if (line.back() == ':') {
      type = functionStart;
      ret += mixIn(splittedLine);
      ret[ret.size() - 1] = '{';
      indentInfo[nowIndentNum] = functionStart;
    } else if (splittedLine[0] == "define" || splittedLine[0] == "include") {
      type = defineInclude;
      ret += "#" + line;
      indentInfo[nowIndentNum] = defineInclude;
    } else {
      type = normal;
      indentInfo[nowIndentNum] = normal;
      ret = checkComment(splittedLine);
    }
    return ret;
  }
};
