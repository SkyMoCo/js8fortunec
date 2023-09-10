/*
 * A simple example of json string parsing with json-c.
 *
 * clang -Wall -g -I/usr/include/json-c/ -o json_parser json_parser.c -ljson-c
 */
#include <json.h>
#include <stdio.h>



json_object* f(json_object* rootObj, const char* key);

int main() {
  struct json_object *jobj, *jobj2;

  char *str1 = "{ \"msg-type\": [ \"0xdeadbeef\", \"irc log\" ], \
\"msg-from\": { \"class\": \"soldier\", \"name\": \"Wixilav\" }, \
\"msg-to\": { \"class\": \"supreme-commander\", \"name\": \"[Redacted]\" }, \
\"msg-log\": [ \
\"soldier: Boss there is a slight problem with the piece offering to humans\", \
\"supreme-commander: Explain yourself soldier!\", \
\"soldier: Well they don't seem to move anymore...\", \
\"supreme-commander: Oh snap, I came here to see them twerk!\" \
] \
}";

  char *str2 = "{\"params\":{\"_ID\":1694291538588},\"type\":\"STATION.GRID\",\"value\":\"DN15AN\"}";

  printf("str:\n---\n%s\n---\n\n", str2);

  jobj = json_tokener_parse(str1);
  jobj = json_tokener_parse(str2);
  printf("Print Everything\n");
  printf("jobj from str:\n---\n%s\n---\n", json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY)); 

  printf("Print msg-from key values\n");
  jobj2 = f(jobj,"value");

  printf("jobj from str:\n---\n%s\n---\n", json_object_to_json_string_ext(jobj2, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY)); 



  return 0;
}

json_object* f(json_object* rootObj, const char* key)
{
  json_object* returnObj;

  if (json_object_object_get_ex(rootObj, key, &returnObj))  {
    return returnObj;
  }
  return NULL;
}
