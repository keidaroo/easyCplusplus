#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include "lineInfo.h"

using namespace std;

const string inputFileName = "test.kei";
const string outputFileName = "output.cpp";
int main() {
  int lineNumCnt = 0, beforeIndentNum = 0;
  map<int, lineType> indentInfo;

  ifstream ifs(inputFileName);
  string lineStr;
  ofstream ofs(outputFileName);

  if (ifs.fail()) {
    cerr << "The file " + inputFileName + " doesn't exist" << endl;
    return -1;
  }

  while (getline(ifs, lineStr)) {
    LineInfo nowLine;
    string output = nowLine.input(lineStr, beforeIndentNum, indentInfo);

    lineNumCnt++;
    beforeIndentNum = nowLine.nowIndentNum;

    ofs << output << endl;
  }

  LineInfo lastLine;
  lastLine.nowIndentNum = 0;
  ofs << lastLine.closeBrackets(beforeIndentNum, indentInfo) << endl;

  ofs.close();
  return 0;
}
