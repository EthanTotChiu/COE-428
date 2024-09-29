#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

extern char pop();
extern void push(char);
extern int isEmpty();

int main(int argc, char * argv[])
{
  int ch;
  while ((ch = getchar()) != EOF) {
    if (!(isalpha(ch) || ch == '>' || ch == '<' || ch == '/'))
      continue; // Skip characters that are not part of tags

    if (ch == '<') { // Beginning of a tag
      int isEndTag = 0;
      char tag[100];
      int i = 0;

      // Check if it's an end-tag
      if ((ch = getchar()) == '/') {
        isEndTag = 1;
      } else {
        tag[i++] = ch; // Read the first character of the tag's identity
      }

      // Read the tag's identity
      while ((ch = getchar()) != '>' && ch != EOF && i < 49) {
        if (isalpha(ch)) { // Check if it's an alphabetical character
          tag[i++] = ch;
        }
      }
      tag[i] = '\0';

      if (!isEndTag) { // Start-tag
        push(tag[0]);
      } else { // End-tag
        char poppedTag = pop();
        if (poppedTag != tag[0]) {
          printf("Invalid XML expression\n");
          exit(1);
        }
      }
    }
  }
  if (isEmpty()) {
    printf("Valid  expression\n");
  } else {
    printf("Tags not closed\n");
  }
  return 0;
}