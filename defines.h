#ifndef DEF_DEFINES_H
#define DEF_DEFINES_H

typedef enum ENUM_ElmType ElmType;
enum ENUM_ElmType 
{
  E_HEADER,
  E_HR,
  E_TABLE,
  E_STRIKE,
  E_BOLD,
  E_ITALIC,
  E_CODE,
  E_BR,
  E_LIST,
  E_BLOCKQUOTE,
  E_LINK,
};

typedef struct DATA_ELM Elm;
struct DATA_ELM
{
  ElmType type;
  char *content;
};

typedef struct DATA_List List;
struct DATA_List
{
  void *data;
  List *prev, *next;
};

#endif /* DEF_DEFINES_H */
