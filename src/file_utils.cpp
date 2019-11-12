#include <stdio.h>
#include <stdlib.h>
#include "file_utils.h"
#include <sys/statvfs.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <dirent.h>
#include <experimental/filesystem> //#include <filesystem>
#include <errno.h>
#include <string.h>
#include <sys/resource.h>
#include <dirent.h>
#include <fcntl.h>

std::string ReadFileIntoString( const char *filename )
{
  FILE* f;
  f = fopen(filename, "r");
  if (f == nullptr) {
    fprintf(stderr, "Could not open file %s for reading\n", filename);
    return std::string();
  }
  fseek(f, 0, SEEK_END);
  auto size = ftello64(f);
  std::string buf;
  buf.resize(size+1);
  buf[size] = 0;
  fseek(f, 0, SEEK_SET);
  auto bytes_read = fread(&buf[0], 1, size, f);
  if (bytes_read != size) {
    fprintf(stderr, "Failed to read required bytes from file %s\n", filename);
    buf.resize(0);
  }
  fclose(f);
  return buf;
}

bool file_exists( const char* filepath )
{
  struct stat status;
  if( stat( filepath, &status ) == 0 && S_ISREG( status.st_mode ) ) {
    return true;
  }
  return false;
}

bool dir_exists( const char* dirpath )
{
  struct stat status;
  if( stat( dirpath, &status ) == 0 && S_ISDIR( status.st_mode ) ) {
    return true;
  }
  return false;
}

std::string GetHomeFolder()
{
  const char *home_dir = nullptr;
  home_dir = getenv("HOME");
  if (home_dir == nullptr) {
    home_dir = getpwuid(getuid())->pw_dir;
  }
  return std::string(home_dir);
}

std::vector<std::string> GetFilesInDirectory(const std::string& dir)
{
  std::vector<std::string> vec;

  DIR *dirp = opendir(dir.c_str());
  if (dirp == nullptr) return vec;

  struct dirent *dp = readdir(dirp);

  while(dp != nullptr) {
    vec.push_back(std::string(dp->d_name));
    dp = readdir(dirp);
  }
  closedir(dirp);

  return vec;
}

std::string GetFileExtension(const std::string& FileName)
{
    if(FileName.find_last_of(".") != std::string::npos)
        return FileName.substr(FileName.find_last_of(".")+1);
    return "";
}

std::string GetFilename(const std::string& WholeFile)
{
    if(WholeFile.find_last_of("/") != std::string::npos)
        return WholeFile.substr(WholeFile.find_last_of("/")+1);
    return WholeFile;
}

bool MaybeCreateDirectory(const std::string& dir) {
  if( !std::experimental::filesystem::exists( dir.c_str() ) ) {
    if( !std::experimental::filesystem::create_directories( dir.c_str() ) ) {
      return false;
    }
  }
  return true;
}

std::vector<std::string> split(const std::string& s, char seperator)
{
   std::vector<std::string> output;
   std::string::size_type prev_pos = 0, pos = 0;

    while((pos = s.find(seperator, pos)) != std::string::npos) {
      std::string substring( s.substr(prev_pos, pos-prev_pos) );
      output.push_back(substring);
      prev_pos = ++pos;
    }

    output.push_back(s.substr(prev_pos, pos-prev_pos)); // Last word
    return output;
}

static char *fcntl_flags(int flags)
{
    static char output[128];
    *output = 0;

    if (flags & O_RDONLY)
        strcat(output, "O_RDONLY ");
    if (flags & O_WRONLY)
        strcat(output, "O_WRONLY ");
    if (flags & O_RDWR)
        strcat(output, "O_RDWR ");
    if (flags & O_CREAT)
        strcat(output, "O_CREAT ");
    if (flags & O_EXCL)
        strcat(output, "O_EXCL ");
    if (flags & O_NOCTTY)
        strcat(output, "O_NOCTTY ");
    if (flags & O_TRUNC)
        strcat(output, "O_TRUNC ");
    if (flags & O_APPEND)
        strcat(output, "O_APPEND ");
    if (flags & O_NONBLOCK)
        strcat(output, "O_NONBLOCK ");
    if (flags & O_SYNC)
        strcat(output, "O_SYNC ");
    if (flags & O_ASYNC)
        strcat(output, "O_ASYNC ");

    return output;
}

static char *fd_info(int fd)
{
    if (fd < 0 || fd >= FD_SETSIZE)
        return nullptr;
    // if (fcntl(fd, F_GETFL) == -1 && errno == EBADF)
    int rv = fcntl(fd, F_GETFL);
    return (rv == -1) ? strerror(errno) : fcntl_flags(rv);
}

/* check first 1024 (usual size of FD_SESIZE) file handles */
void test_fds()
{
     int i;
     int fd_dup;
     char errst[64];
     for (i = 0; i < 20; i++) {
          *errst = 0;
          fd_dup = dup(i);
          if (fd_dup == -1) {
                strcpy(errst, strerror(errno));
                // EBADF  oldfd isnâ€™t an open file descriptor, or newfd is out of the allowed range for file descriptors.
                // EBUSY  (Linux only) This may be returned by dup2() during a race condition with open(2) and dup().
                // EINTR  The dup2() call was interrupted by a signal; see signal(7).
                // EMFILE The process already has the maximum number of file descriptors open and tried to open a new one.
          } else {
                close(fd_dup);
                strcpy(errst, "dup() ok");
          }
          printf("%4i: %5i %24s %s\n", i, fcntl(i, F_GETOWN), fd_info(i), errst);
     }
}
