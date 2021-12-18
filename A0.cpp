#include <iostream>
using namespace std;
int main()
{
  char s[8000];
  int word, count = 0;
  //system("chcp 1251");
  //system("cls");
  cout << "Enter the string: " << endl;
  cin.get(s, 8000);
  int i = 0;
  while (s[i] == ' ' && s[i] != '\0')
    i++;
  word = 0;
  while (s[i] != '\0') {
    if ((s[i] != ' ' || s[i] == '\t' || s[i] == '\n') && word == 0)
    {
      word = 1;
      count++;
    }
    else if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' )
      word = 0;
    i++;
  }
  cout << "Number of words in the string " << count;
  cin.get(); cin.get();
  return 0;
}
