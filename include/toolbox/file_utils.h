#pragma once
#include <string>
#include <vector>

std::string ReadFileIntoString( const char *filename );
bool file_exists( const char* filepath );
bool dir_exists( const char* dirpath );
std::string GetHomeFolder();
std::vector<std::string> GetFilesInDirectory(const std::string& dir);
std::string GetFileExtension(const std::string& FileName);
std::string GetFilename(const std::string& WholeFile);
// Create directory if it doesn't already exist.  Return bool indicating
// existence of directory.
bool MaybeCreateDirectory(const std::string& dir);

// this function will split the input strings based on the separator
std::vector<std::string> split(const std::string& s, char seperator);

