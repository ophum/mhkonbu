#ifndef DEF_DEFINES_H
#define DEF_DEFINES_H

typedef enum ENUM_ElmType ElmType;
enum ENUM_ElmType 
{
  E_H1, E_H2, E_H3, E_H4, E_H5, E_H6,
  E_HR,
  E_P,
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

#endif /* DEF_DEFINES_H */
