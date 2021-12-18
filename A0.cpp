#include <iostream>
#include <cstring>

using namespace std;
int main(int argc, char* argv[])
{
  
  int n = strlen(argv[1]);
  int word, count = 0;
  int i = 0;
  while (argv[1][i] == ' ' && argv[1][i] != '\0')
    i++;
  word = 0;
  while (argv[1][i] != '\0') {
    if ((argv[1][i] != ' ' || argv[1][i] == '\t' || argv[1][i] == '\n') && word == 0)
    {
      word = 1;
      count++;
    }
    else if (argv[1][i] == ' ' || argv[1][i] == '\t' || argv[1][i] == '\n' )
      word = 0;
    i++;
  }
  cout << "Number of words in the string " << count << endl;

  return 0;
}

