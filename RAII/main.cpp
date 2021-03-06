#include <cstdlib>
#include <cstdio>
#include <memory>

using namespace std;

int main ()
{
  auto file_open = [](const char* filename, const char* mode) -> FILE* {
    return std::fopen(filename, mode);
  };

  auto file_deleter=[](FILE* file) {
      std::puts("Close file\n");
      std::fclose(file);
  };

  // Using a unique pointer and custom deleter (lamda)
  std::unique_ptr<FILE, decltype(file_deleter)> fp{file_open("test.txt", "r"), file_deleter};
  if(!fp) {
      std::perror("File opening failed");
      return EXIT_FAILURE;
  }

  int c{};
  while ((c = std::fgetc(fp.get())) != EOF) {
     std::putchar(c);
  }

  if (std::ferror(fp.get())) {
      std::puts("I/O error when reading");
      return EXIT_FAILURE;
  } else if (std::feof(fp.get())) {
      std::puts("End of file reached successfully");
  }
  return EXIT_SUCCESS;
}
