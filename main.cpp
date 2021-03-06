#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include "lineInfo.h"

using namespace std;

const string inputFileName = "test.kei";
const string outputFileName = "output.cpp";
int main() {
  // 現在の行番号、一行前のインデント
  int lineNumCnt = 0, beforeIndentNum = 0;
  // インデントごとの枠のくくり
  map<int, lineType> indentInfo;

  ifstream ifs(inputFileName);
  string lineStr;
  ofstream ofs(outputFileName);

  // 読み込み失敗
  if (ifs.fail()) {
    cerr << "The file " + inputFileName + " doesn't exist" << endl;
    return -1;
  }

  // 解析
  while (getline(ifs, lineStr)) {
    LineInfo nowLine;
    // 一行分渡して、帰ってきたものをwriteする
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
