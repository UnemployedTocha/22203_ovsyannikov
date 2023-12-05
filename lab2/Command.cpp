#include "Command.h"

Command::Command() = default;

void Command::Execute(std::stack<int>& numbers_, Tokens& tokens, std::string& output, Reader& reader){}
void Command::Check(Tokens& tokens, Reader& reader){}

Command::~Command() = default;
