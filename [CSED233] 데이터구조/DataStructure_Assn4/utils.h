#include <iostream>

using namespace std;

class Instruction {
public:
  void setCommand(string cmd);
  void setValue(int val);
  void setValueStr(string val);

  string getCommand();
  int getValue();
  string getValueStr();

private:
  string command;
  string value_str;
  int value;
};

class InstructionSequence {
public:
  InstructionSequence();
  ~InstructionSequence();

  int getLength();
  Instruction &getInstruction(int index);

  void parseInstructions(const char *arg);
  void printInstructions();

private:
  Instruction *instructions;
  int length;
};

const char *const TASK_1_DEFAULT_ARGUMENT = "[('A','B'), ('B','C'), ('D','C')]";
const char *const TASK_2_DEFAULT_ARGUMENT =
    "[('A','B'), ('B','C'), ('D','C'), ('A',NULL)]";

const char *const TASK_3_DEFAULT_ARGUMENT =
    "[('A','B'), ('A','C'), ('B','F'), ('F','E'), ('C','E'), ('C','D')";
const char *const TASK_4_DEFAULT_ARGUMENT =
    "[('A','B'), ('A','C'), ('C','D'), ('E','C'), ('D','B'), ('D','E')]";

const char *const TASK_5_DEFAULT_ARGUMENT =
    "[('A-B',10),('A-C',3),('B-D',5),('C-B',2),('C-E',15),('A-D',20),('D-E',11)"
    ",('A',11)]";

const char *const TASK_6_DEFAULT_ARGUMENT =
    "[('D-B', 1), ('D-C', 2), ('E-D', 5), ('B-A', 3), ('C-A', 1), ('C-B', 4), "
    "('B-D', -1), ('MST', NULL)]";
