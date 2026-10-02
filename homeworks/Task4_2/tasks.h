#ifndef TASKS_H
#define TASKS_H

#include <vector>
#include <string>

std::vector<int> readFileToVector(const std::string& filename);

void solveTask4_1(const std::vector<int>& vecA, const std::vector<int>& vecB);

void solveTask4_2(const std::vector<int>& vecLarge, const std::vector<int>& vecSmall);

void printVectorPreview(const std::vector<int>& v, const std::string& name, int n);

#endif 