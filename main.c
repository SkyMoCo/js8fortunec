/* main.c */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <json-c/json.h>
#include <js8fortune.h>
#include "log.h"

#define PORT 8080 

/* Function defs */


int main(int argc, char const* argv[]) {
  struct json_object *jobj, *jobj2;
  int status, valread, client_fd;
  struct sockaddr_in serv_addr;
  char send_buffer[1024] = { 0 };
  char buffer[1024] = { 0 };

  log_trace("Opening connection to js8call");
  if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    log_error("\n Socket creation error \n");
    return -1;
  }
  
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  
  // Convert IPv4 and IPv6 addresses from text to binary
  // form
  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
    printf("\nInvalid address/ Address not supported \n");
    return -1;
  }
  
  if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
    printf("\nConnection Failed \n");
    return -1;
  }
  
  strcpy(send_buffer,"{\"type\": \"STATION.GET_GRID\", \"value\": \"\", \"params\": {\"_ID\": \"1694291538588\"}}");
  printf("Sending \"%s\"\n", send_buffer);
  send(client_fd, send_buffer, strlen(send_buffer), 0);
  valread = read(client_fd, buffer, 1024);
  printf("%s\n", buffer);
  jobj = json_tokener_parse(buffer);
  jobj2 = f(jobj,"value");
  printf("jobj from str:\n---\n%s\n---\n", json_object_to_json_string_ext(jobj2, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));
  printf("jobj from str:\n---\n%s\n---\n", remove_quotes(json_object_to_json_string_ext(jobj2, JSON_C_TO_STRING_PLAIN)));
  // closing the connected socket
  close(client_fd);

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

char* remove_quotes(char* s1) {
    if (s1[0] == '"' && s1[strlen(s1) - 1] == '"') {
        s1[strlen(s1) - 1] = '\0';
        return s1 + 1;
    }
    return s1;
}
