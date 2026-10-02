#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

std::vector<int> readFileToVector(const std::string& filename);

void printVectorPreview(const std::vector<int>& v, const std::string& name, int n = 10);

#endif // UTILS_H